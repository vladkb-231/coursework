#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include "model/team.h"
#include "model/match.h"
#include "simulation/basicsimulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка диапазонов характеристик
    ui->speedSpin->setRange(0, 100);
    ui->attackSpin->setRange(0, 100);
    ui->staminaSpin->setRange(0, 100);

    // Подключение сигналов
    connect(ui->addPlayerBtn, &QPushButton::clicked, this, &MainWindow::onAddPlayerClicked);
    connect(ui->createTeamBtn, &QPushButton::clicked, this, &MainWindow::onCreateTeamClicked);
    connect(ui->simulateBtn, &QPushButton::clicked, this, &MainWindow::onSimulateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_teams);
}

void MainWindow::onAddPlayerClicked()
{
    QString name = ui->playerNameEdit->text().trimmed();
    if(name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter player name!");
        return;
    }

    Player* player = new Player(
        name,
        ui->speedSpin->value(),
        ui->attackSpin->value(),
        ui->staminaSpin->value(),
        this
        );

    m_currentTeamBuilder.addPlayer(player);
    ui->playersList->addItem(name);
    ui->playerNameEdit->clear();
}

void MainWindow::onCreateTeamClicked()
{
    QString teamName = ui->teamNameEdit->text().trimmed();
    if(teamName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter team name!");
        return;
    }

    if(m_currentTeamBuilder.getPlayers().isEmpty()) {
        QMessageBox::warning(this, "Error", "Add at least one player!");
        return;
    }

    Team* newTeam = m_currentTeamBuilder.setName(teamName).build(this);
    m_teams.append(newTeam);
    updateTeamsList();

    // Сбросить билдер
    m_currentTeamBuilder = TeamBuilder();
    ui->teamNameEdit->clear();
    ui->playersList->clear();
}

void MainWindow::updateTeamsList()
{
    ui->teamsList->clear();
    ui->team1Combo->clear();
    ui->team2Combo->clear();

    for(Team* team : m_teams) {
        QString itemText = QString("%1 (Attack: %2, Defense: %3)")
        .arg(team->name())
            .arg(team->attackLevel())
            .arg(team->defenseLevel());

        ui->teamsList->addItem(itemText);
        ui->team1Combo->addItem(team->name());
        ui->team2Combo->addItem(team->name());
    }
}

void MainWindow::onSimulateClicked()
{
    if(m_teams.size() < 2) {
        QMessageBox::warning(this, "Error", "Create at least two teams!");
        return;
    }

    int idx1 = ui->team1Combo->currentIndex();
    int idx2 = ui->team2Combo->currentIndex();

    if(idx1 == idx2 || idx1 < 0 || idx2 < 0) {
        QMessageBox::warning(this, "Error", "Select different teams!");
        return;
    }

    Match* match = new Match(m_teams[idx1], m_teams[idx2], this);

    // Подключение сигналов
    connect(match, &Match::eventAdded, this, &MainWindow::handleNewEvent);
    connect(match, &Match::scoreChanged, this, &MainWindow::handleScoreChanged);

    // Запуск в отдельном потоке
    QtConcurrent::run([this, match](){
        BasicSimulation simulator;
        simulator.simulate(match, GameRules(3, 6, 25));
        QMetaObject::invokeMethod(this, [this, match](){
            QMessageBox::information(this, "Result",
                                     QString("%1 %2 - %3 %4")
                                         .arg(match->team1()->name())
                                         .arg(match->score()[match->team1()])
                                         .arg(match->score()[match->team2()])
                                         .arg(match->team2()->name()));
            match->deleteLater();
        });
    });
}

void MainWindow::handleNewEvent(const MatchEvent& event)
{
    QStringList eventTypes = {"Attack", "Block", "Serve", "Defense"};
    QString result = event.isSuccessful() ? "✓" : "✗";
    QString time = QDateTime::fromMSecsSinceEpoch(event.timestamp()).toString("mm:ss");

    ui->eventsLog->addItem(
        QString("[%1] %2: %3 %4 (%5)")
            .arg(time)
            .arg(event.team()->name())
            .arg(eventTypes[event.type()])
            .arg(result)
            .arg(event.player()->name())
        );
    ui->eventsLog->scrollToBottom();
}

void MainWindow::handleScoreChanged(int team1Score, int team2Score)
{
    ui->lblScore->setText(
        QString("Score: %1 - %2")
            .arg(team1Score)
            .arg(team2Score)
        );
}

