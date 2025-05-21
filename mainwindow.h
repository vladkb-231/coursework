#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFutureWatcher>
#include "model/match.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddPlayerClicked();
    void onCreateTeamClicked();
    void onSimulateClicked();
    void handleNewEvent(const MatchEvent& event);
    void handleScoreChanged(int team1Score, int team2Score);

private:
    Ui::MainWindow *ui;
    QList<Team*> m_teams;
    TeamBuilder m_currentTeamBuilder;
    QFutureWatcher<void> m_simulationWatcher;

    void updateTeamsList();
    void clearPlayerInputs();
};

#endif // MAINWINDOW_H

