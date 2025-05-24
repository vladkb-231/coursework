#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_tournament(nullptr)
    , m_simulation(new BasicSimulation(this))
    , m_currentMatchIndex(0)
    , m_tournamentFinished(false)
{
    ui->setupUi(this);

    ui->tournamentTableWidget->setColumnCount(4);
    ui->tournamentTableWidget->setHorizontalHeaderLabels({"Команда", "Очки", "Победы", "Поражения"});
    ui->tournamentTableWidget->horizontalHeader()->setStretchLastSection(true);

    connect(m_simulation, &BasicSimulation::eventOccurred, this, &MainWindow::onSimulationEvent);
    connect(m_simulation, &BasicSimulation::scoreUpdated, this, &MainWindow::onScoreUpdated);
    connect(m_simulation, &BasicSimulation::matchFinished, this, &MainWindow::onMatchFinished);
    connect(ui->playersListWidget, &QListWidget::doubleClicked, this, &MainWindow::onPlayerDoubleClicked);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_tournament;
}

void MainWindow::on_addPlayerButton_clicked()
{
    QString name = ui->playerNameEdit->text().trimmed();
    if(name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя игрока");
        return;
    }

    Player* player = new Player(
        name,
        ui->speedSpinBox->value(),
        ui->attackSpinBox->value(),
        ui->staminaSpinBox->value(),
        nullptr,
        this
        );

    m_currentPlayers.append(player);
    updatePlayersList();
    ui->playerNameEdit->clear();
}

void MainWindow::on_createTeamButton_clicked() {
    QString teamName = ui->teamNameEdit->text().trimmed();
    if(teamName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя команды");
        return;
    }

    // Проверка количества игроков
    if(m_currentPlayers.size() != 6) {
        QMessageBox::warning(
            this,
            "Ошибка",
            QString("В команде должно быть 6 игроков! Сейчас: %1").arg(m_currentPlayers.size())
            );
        return;
    }

    Team* team = new Team(teamName, this);
    for(Player* player : m_currentPlayers) {
        team->addPlayer(player);
        player->setTeam(team);
    }
    team->calculateStats();

    m_teams.append(team);
    m_currentPlayers.clear();

    updateTeamsList();
    updatePlayersList();
    ui->teamNameEdit->clear();
}

void MainWindow::on_createTournamentButton_clicked() {
    // Добавить проверку состава команд
    for(Team* team : m_teams) {

        bool validTeams = true;
        QString errorMsg;
        for(Team* team : m_teams) {
            if(team->players().size() != 6) {
                validTeams = false;
                errorMsg = QString("Команда '%1' имеет %2/6 игроков!")
                               .arg(team->name())
                               .arg(team->players().size());
                break;
            }
        }

        if(!validTeams) {
            QMessageBox::warning(this, "Ошибка", errorMsg);
            return;
        }

        if(team->players().size() != 6) {
            QMessageBox::warning(
                this,
                "Ошибка",
                QString("Команда '%1' имеет некорректный состав (%2/6 игроков)!")
                    .arg(team->name())
                    .arg(team->players().size())
                );
            return;
        }
    }

    if(m_teams.size() < 2) {
        QMessageBox::warning(this, "Ошибка", "Необходимо минимум 2 команды");
        return;
    }

    if(m_tournament) {
        delete m_tournament;
        m_tournament = nullptr;
    }

    m_tournament = new Tournament("Турнир", this);
    for(Team* team : m_teams) {
        m_tournament->addTeam(team);
    }
    m_tournament->generateSchedule();

    m_currentMatchIndex = 0;
    updateScheduleList();
    updateTournamentTable();
    ui->startTournamentButton->setEnabled(true);
}

void MainWindow::on_startTournamentButton_clicked()
{
    if(!m_tournament || m_tournament->schedule().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте турнир");
        return;
    }

    ui->startTournamentButton->setEnabled(false);
    ui->matchLogTextEdit->clear();
    startNextMatch();
}

void MainWindow::onSimulationEvent(const QString& eventDescription)
{
    ui->matchLogTextEdit->append(eventDescription);
}

void MainWindow::onScoreUpdated(int team1Score, int team2Score)
{
    ui->scoreLabel->setText(QString("%1 : %2").arg(team1Score).arg(team2Score));
}

QList<Team*> MainWindow::findTournamentLeaders()
{
    QMap<Team*, int> points = m_tournament->table()->points();
    int maxPoints = 0;
    QList<Team*> leaders;

    for (Team* team : points.keys()) {
        if (points[team] > maxPoints) {
            maxPoints = points[team];
            leaders.clear();
            leaders.append(team);
        }
        else if (points[team] == maxPoints) {
            leaders.append(team);
        }
    }
    return leaders;
}

void MainWindow::onMatchFinished(Match* match) {
    if (m_tournamentFinished) return;

    m_tournament->updateTournament(match);
    updateTournamentTable();
    updateScheduleList();

    // Отображение лучшего игрока
    Player* bestPlayer = match->getBestPlayer();
    if (bestPlayer) {
        QMessageBox::information(this,
                                 "Лучший игрок матча",
                                 QString("%1 (%2) - %3 событий")
                                     .arg(bestPlayer->name())
                                     .arg(bestPlayer->team()->name())
                                     .arg(match->getBestPlayerCount()));
    }

    m_currentMatchIndex++;

    if (m_currentMatchIndex >= m_tournament->schedule().size()) {
        QList<Team*> leaders = findTournamentLeaders();
        if (leaders.size() > 1) {
            Match* tiebreaker = new Match(leaders.first(), leaders.last(), m_tournament);
            m_tournament->schedule().append(tiebreaker);
            QMessageBox::information(this,
                                     "Дополнительный матч",
                                     QString("%1 vs %2 для определения победителя!")
                                         .arg(leaders.first()->name())
                                         .arg(leaders.last()->name()));
            m_tournamentFinished = false;
            startNextMatch();
            return;
        }
        else {
            m_tournamentFinished = true;
            QMessageBox::information(this,
                                     "Турнир завершен",
                                     "Победитель: " + leaders.first()->name());
            ui->currentMatchLabel->setText("Матч: -");
        }
    }
    else {
        QTimer::singleShot(1000, this, [this]() {
            startNextMatch();
        });
    }
}



void MainWindow::updateTeamsList()
{
    ui->teamsListWidget->clear();
    for(Team* team : m_teams) {
        ui->teamsListWidget->addItem(
            QString("%1 (Атака: %2, Защита: %3)")
                .arg(team->name())
                .arg(team->attackLevel())
                .arg(team->defenseLevel()));
    }
}

void MainWindow::updatePlayersList()
{
    ui->playersListWidget->clear();
    for(Player* player : m_currentPlayers) {
        QListWidgetItem* item = new QListWidgetItem(
            QString("%1 (А: %2, С: %3)").arg(player->name())
                .arg(player->attack())
                .arg(player->speed())
            );
        ui->playersListWidget->addItem(item);
    }

    // Добавляем счетчик с цветовой индикацией
    QListWidgetItem* counter = new QListWidgetItem(
        QString("Игроков: %1/6 | Двойной клик для удаления").arg(m_currentPlayers.size())
        );
    counter->setForeground(m_currentPlayers.size() == 6 ? Qt::darkGreen : Qt::red);
    ui->playersListWidget->addItem(counter);
}

void MainWindow::updateScheduleList() {
    ui->scheduleListWidget->clear();
    if(!m_tournament) return;

    auto schedule = m_tournament->schedule();
    for(int i = 0; i < schedule.size(); ++i) {
        Match* m = schedule.at(i);
        QString status = m->isFinished() ? "[Завершён]" : "[Ожидает]";
        ui->scheduleListWidget->addItem(
            QString("%1 vs %2 %3")
                .arg(m->team1()->name())
                .arg(m->team2()->name())
                .arg(status));
    }
}

void MainWindow::updateTournamentTable()
{
    ui->tournamentTableWidget->setRowCount(0);
    if (!m_tournament) return;

    TournamentTable* table = m_tournament->table();
    QList<Team*> teams = m_tournament->teams(); // Все команды турнира

    // Сортируем по убыванию очков с учетом отсутствующих значений
    std::sort(teams.begin(), teams.end(), [table](Team* a, Team* b) {
        return table->points().value(a, 0) > table->points().value(b, 0);
    });

    // Заполняем таблицу
    for (Team* team : teams) {
        int row = ui->tournamentTableWidget->rowCount();
        ui->tournamentTableWidget->insertRow(row);

        ui->tournamentTableWidget->setItem(row, 0, new QTableWidgetItem(team->name()));
        ui->tournamentTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(table->points().value(team, 0)))); // Исправлено
        ui->tournamentTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(table->wins().value(team, 0)))); // Исправлено
        ui->tournamentTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(table->losses().value(team, 0)))); // Исправлено
    }
}

void MainWindow::startNextMatch() {
    if (m_tournamentFinished) return;

    Match* nextMatch = m_tournament->schedule().at(m_currentMatchIndex);
    ui->currentMatchLabel->setText(QString("Матч: %1 vs %2").arg(nextMatch->team1()->name()).arg(nextMatch->team2()->name()));
    ui->scoreLabel->setText("0 : 0");
    m_simulation->simulate(nextMatch, GameRules(3, 6, 25));
}

void MainWindow::onPlayerDoubleClicked(const QModelIndex &index)
{
    // Удаляем только игроков, а не счетчик
    if (index.row() < m_currentPlayers.size()) {
        Player* player = m_currentPlayers.takeAt(index.row());
        delete player;
        updatePlayersList();

        // Обновляем доступность кнопки создания команды
        ui->createTeamButton->setEnabled(m_currentPlayers.size() == 6);
    }
}




