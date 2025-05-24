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

void MainWindow::on_createTeamButton_clicked()
{
    QString teamName = ui->teamNameEdit->text().trimmed();
    if(teamName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя команды");
        return;
    }

    if(m_currentPlayers.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Добавьте игроков в команду");
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

void MainWindow::on_createTournamentButton_clicked()
{
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

void MainWindow::onMatchFinished(Match* match) {
    if (m_tournamentFinished) return;

    m_tournament->updateTournament(match);
    updateTournamentTable();
    updateScheduleList();

    m_currentMatchIndex++;
    if (m_currentMatchIndex >= m_tournament->schedule().size()) {
        m_tournamentFinished = true;
        QMessageBox::information(this, "Турнир завершен", "Все матчи сыграны!");
        ui->currentMatchLabel->setText("Матч: -");
        return;
    }

    QTimer::singleShot(1000, this, [this]() {
        startNextMatch();
    });
}

void MainWindow::updatePlayersList()
{
    ui->playersListWidget->clear();
    for(Player* player : m_currentPlayers) {
        ui->playersListWidget->addItem(player->name());
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

void MainWindow::updateScheduleList()
{
    ui->scheduleListWidget->clear();
    if(!m_tournament) return;

    auto schedule = m_tournament->schedule();
    for(int i = 0; i < schedule.size(); ++i) {
        Match* m = schedule.at(i);
        QString status = (i < m_currentMatchIndex) ? "[Завершён]" : "[Ожидает]";
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
    if(!m_tournament) return;

    auto table = m_tournament->table();
    auto points = table->points();
    auto wins = table->wins();
    auto losses = table->losses();

    QList<Team*> teams = points.keys();
    std::sort(teams.begin(), teams.end(), [&points](Team* a, Team* b) {
        return points[a] > points[b];
    });

    for(Team* team : teams) {
        int row = ui->tournamentTableWidget->rowCount();
        ui->tournamentTableWidget->insertRow(row);

        ui->tournamentTableWidget->setItem(row, 0,
                                           new QTableWidgetItem(team->name()));
        ui->tournamentTableWidget->setItem(row, 1,
                                           new QTableWidgetItem(QString::number(points[team])));
        ui->tournamentTableWidget->setItem(row, 2,
                                           new QTableWidgetItem(QString::number(wins[team])));
        ui->tournamentTableWidget->setItem(row, 3,
                                           new QTableWidgetItem(QString::number(losses[team])));
    }
}


void MainWindow::startNextMatch() {
    if (m_tournamentFinished) return;

    Match* nextMatch = m_tournament->schedule().at(m_currentMatchIndex);
    ui->currentMatchLabel->setText(QString("Матч: %1 vs %2").arg(nextMatch->team1()->name()).arg(nextMatch->team2()->name()));
    ui->scoreLabel->setText("0 : 0");
    m_simulation->simulate(nextMatch, GameRules(3, 25, 30));
}



