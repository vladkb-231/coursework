#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "C:\Users\drego\Documents\volleyball\model\player.h"
#include "C:\Users\drego\Documents\volleyball\model\team.h"
#include "C:\Users\drego\Documents\volleyball\model\tournament.h"
#include "C:\Users\drego\Documents\volleyball\simulation\basicsimulation.h"
#include "C:\Users\drego\Documents\volleyball\model\gamerules.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPlayerButton_clicked();
    void on_createTeamButton_clicked();

    void on_createTournamentButton_clicked();
    void on_startTournamentButton_clicked();

    void onSimulationEvent(const QString& eventDescription);
    void onScoreUpdated(int team1Score, int team2Score);
    void onMatchFinished(Match* match);

private:
    Ui::MainWindow* ui;

    QList<Player*> m_currentPlayers;
    QList<Team*> m_teams;
    Tournament* m_tournament = nullptr;
    BasicSimulation* m_simulation = nullptr;

    int m_currentMatchIndex = 0;

    void updatePlayersList();
    void updateTeamsList();
    void updateScheduleList();
    void updateTournamentTable();

    void startNextMatch();
};


#endif // MAINWINDOW_H
