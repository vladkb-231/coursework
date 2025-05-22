#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    m_simulation = new BasicSimulation(this);

    connect(m_simulation, &BasicSimulation::eventOccurred, this, &MainWindow::onSimulationEvent);
    connect(m_simulation, &BasicSimulation::scoreUpdated, this, &MainWindow::onScoreUpdated);
    connect(m_simulation, &BasicSimulation::matchFinished, this, &MainWindow::onMatchFinished);

    ui->tournamentTableWidget->setColumnCount(4);
    ui->tournamentTableWidget->setHorizontalHeaderLabels({"Команда", "Очки", "Победы", "Поражения"});
    ui->tournamentTableWidget->horizontalHeader()->setStretchLastSection(true);

    updatePlayersList();
    updateTeamsList();

    ui->startTournamentButton->setEnabled(false);
    ui->currentMatchLabel->setText("Матч: -");
    ui->scoreLabel->setText("0 : 0");
}

MainWindow::~MainWindow() {
    delete ui;
    qDeleteAll(m_currentPlayers);
    qDeleteAll(m_teams);
    delete m_tournament;
}

void MainWindow::on_addPlayerButton_clicked() {
    QString name = ui->playerNameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя игрока");
        return;
    }

    int speed = ui->speedSpinBox->value();
    int attack = ui->attackSpinBox->value();
    int stamina = ui->staminaSpinBox->value();

    Player* player = new Player(name, speed, attack, stamina, nullptr, this);
    m_currentPlayers.append(player);
    updatePlayersList();

    ui->playerNameEdit->clear();
}

void MainWindow::updatePlayersList() {
    ui->playersListWidget->clear();
    for (Player* p : m_currentPlayers) {
        ui->playersListWidget->addItem(p->name());
    }
}

void MainWindow::on_createTeamButton_clicked() {
    QString teamName = ui->teamNameEdit->text().trimmed();
    if (teamName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя команды");
        return;
    }
    if (m_currentPlayers.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Добавьте хотя бы одного игрока");
        return;
    }

    Team* team = new Team(teamName, this);
    for (Player* p : m_currentPlayers) {
        team->addPlayer(p);
    }
    m_teams.append(team);

    m_currentPlayers.clear();
    updatePlayersList();
    updateTeamsList();

    ui->teamNameEdit->clear();

    ui->startTournamentButton->setEnabled(false);
}

void MainWindow::updateTeamsList() {
    ui->teamsListWidget->clear();
    for (Team* t : m_teams) {
        ui->teamsListWidget->addItem(t->name());
    }
}

void MainWindow::on_createTournamentButton_clicked() {
    if (m_teams.size() < 2) {
        QMessageBox::warning(this, "Ошибка", "Добавьте минимум 2 команды");
        return;
    }

    if (m_tournament) {
        delete m_tournament;
        m_tournament = nullptr;
    }

    m_tournament = new Tournament("Турнир", this);
    for (Team* t : m_teams) {
        m_tournament->addTeam(t);
    }
    m_tournament->generateSchedule();

    m_currentMatchIndex = 0;

    updateScheduleList();
    updateTournamentTable();

    ui->startTournamentButton->setEnabled(true);
}

void MainWindow::on_startTournamentButton_clicked() {
    if (!m_tournament || m_tournament->schedule().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Создайте турнир с расписанием");
        return;
    }

    ui->startTournamentButton->setEnabled(false);
    ui->matchLogTextEdit->clear();
    ui->currentMatchLabel->setText("Матч: -");
    ui->scoreLabel->setText("0 : 0");

    startNextMatch();
}

void MainWindow::startNextMatch() {
    if (!m_tournament || m_currentMatchIndex >= m_tournament->schedule().size()) {
        QMessageBox::information(this, "Турнир", "Турнир завершён!");
        ui->currentMatchLabel->setText("Матч: -");
        ui->scoreLabel->setText("0 : 0");
        return;
    }

    Match* match = m_tournament->schedule().at(m_currentMatchIndex);
    ui->currentMatchLabel->setText(QString("Матч: %1 vs %2").arg(match->team1()->name()).arg(match->team2()->name()));

    ui->scoreLabel->setText("0 : 0");
    ui->matchLogTextEdit->append(QString("\n--- Начинается матч %1 vs %2 ---").arg(match->team1()->name()).arg(match->team2()->name()));

    m_simulation->simulateStepByStep(match, GameRules());
}

void MainWindow::onSimulationEvent(const QString& eventDescription) {
    ui->matchLogTextEdit->append(eventDescription);
}

void MainWindow::onScoreUpdated(int team1Score, int team2Score) {
    ui->scoreLabel->setText(QString("%1 : %2").arg(team1Score).arg(team2Score));
}

void MainWindow::onMatchFinished(Match* match) {
    m_tournament->updateTournament(match);
    updateTournamentTable();
    updateScheduleList();

    m_currentMatchIndex++;
    startNextMatch();
}

void MainWindow::updateScheduleList() {
    ui->scheduleListWidget->clear();
    if (!m_tournament) return;

    auto schedule = m_tournament->schedule();
    for (int i = 0; i < schedule.size(); ++i) {
        Match* m = schedule.at(i);
        QString status = (i < m_currentMatchIndex) ? "[Завершён]" : "[Ожидает]";
        ui->scheduleListWidget->addItem(QString("%1 vs %2 %3")
                                            .arg(m->team1()->name())
                                            .arg(m->team2()->name())
                                            .arg(status));
    }
}

void MainWindow::updateTournamentTable() {
    ui->tournamentTableWidget->clearContents();
    if (!m_tournament) return;

    auto table = m_tournament->table();
    auto points = table->points();
    auto wins = table->wins();
    auto losses = table->losses();

    QList<Team*> teams = points.keys();
    std::sort(teams.begin(), teams.end(), [&points](Team* a, Team* b) {
        return points[a] > points[b];
    });

    ui->tournamentTableWidget->setRowCount(teams.size());

    for (int row = 0; row < teams.size(); ++row) {
        Team* team = teams[row];
        ui->tournamentTableWidget->setItem(row, 0, new QTableWidgetItem(team->name()));
        ui->tournamentTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(points.value(team, 0))));
        ui->tournamentTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(wins.value(team, 0))));
        ui->tournamentTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(losses.value(team, 0))));
    }
}

