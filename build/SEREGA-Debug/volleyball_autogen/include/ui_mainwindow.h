/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayoutMain;
    QTabWidget *tabWidget;
    QWidget *tabTeam;
    QVBoxLayout *verticalLayoutTeam;
    QHBoxLayout *horizontalLayoutPlayerInput;
    QLineEdit *playerNameEdit;
    QSpinBox *speedSpinBox;
    QSpinBox *attackSpinBox;
    QSpinBox *staminaSpinBox;
    QPushButton *addPlayerButton;
    QListWidget *playersListWidget;
    QHBoxLayout *horizontalLayoutTeamNameCreate;
    QLineEdit *teamNameEdit;
    QPushButton *createTeamButton;
    QListWidget *teamsListWidget;
    QWidget *tabTournament;
    QVBoxLayout *verticalLayoutTournament;
    QPushButton *createTournamentButton;
    QListWidget *scheduleListWidget;
    QHBoxLayout *horizontalLayoutTournamentControls;
    QPushButton *startTournamentButton;
    QLabel *currentMatchLabel;
    QLabel *scoreLabel;
    QTextEdit *matchLogTextEdit;
    QTableWidget *tournamentTableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutMain = new QVBoxLayout(centralwidget);
        verticalLayoutMain->setObjectName("verticalLayoutMain");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabTeam = new QWidget();
        tabTeam->setObjectName("tabTeam");
        verticalLayoutTeam = new QVBoxLayout(tabTeam);
        verticalLayoutTeam->setObjectName("verticalLayoutTeam");
        horizontalLayoutPlayerInput = new QHBoxLayout();
        horizontalLayoutPlayerInput->setObjectName("horizontalLayoutPlayerInput");
        playerNameEdit = new QLineEdit(tabTeam);
        playerNameEdit->setObjectName("playerNameEdit");

        horizontalLayoutPlayerInput->addWidget(playerNameEdit);

        speedSpinBox = new QSpinBox(tabTeam);
        speedSpinBox->setObjectName("speedSpinBox");
        speedSpinBox->setMinimum(1);
        speedSpinBox->setMaximum(100);
        speedSpinBox->setValue(50);

        horizontalLayoutPlayerInput->addWidget(speedSpinBox);

        attackSpinBox = new QSpinBox(tabTeam);
        attackSpinBox->setObjectName("attackSpinBox");
        attackSpinBox->setMinimum(1);
        attackSpinBox->setMaximum(100);
        attackSpinBox->setValue(50);

        horizontalLayoutPlayerInput->addWidget(attackSpinBox);

        staminaSpinBox = new QSpinBox(tabTeam);
        staminaSpinBox->setObjectName("staminaSpinBox");
        staminaSpinBox->setMinimum(1);
        staminaSpinBox->setMaximum(100);
        staminaSpinBox->setValue(50);

        horizontalLayoutPlayerInput->addWidget(staminaSpinBox);

        addPlayerButton = new QPushButton(tabTeam);
        addPlayerButton->setObjectName("addPlayerButton");

        horizontalLayoutPlayerInput->addWidget(addPlayerButton);


        verticalLayoutTeam->addLayout(horizontalLayoutPlayerInput);

        playersListWidget = new QListWidget(tabTeam);
        playersListWidget->setObjectName("playersListWidget");

        verticalLayoutTeam->addWidget(playersListWidget);

        horizontalLayoutTeamNameCreate = new QHBoxLayout();
        horizontalLayoutTeamNameCreate->setObjectName("horizontalLayoutTeamNameCreate");
        teamNameEdit = new QLineEdit(tabTeam);
        teamNameEdit->setObjectName("teamNameEdit");

        horizontalLayoutTeamNameCreate->addWidget(teamNameEdit);

        createTeamButton = new QPushButton(tabTeam);
        createTeamButton->setObjectName("createTeamButton");

        horizontalLayoutTeamNameCreate->addWidget(createTeamButton);


        verticalLayoutTeam->addLayout(horizontalLayoutTeamNameCreate);

        teamsListWidget = new QListWidget(tabTeam);
        teamsListWidget->setObjectName("teamsListWidget");

        verticalLayoutTeam->addWidget(teamsListWidget);

        tabWidget->addTab(tabTeam, QString());
        tabTournament = new QWidget();
        tabTournament->setObjectName("tabTournament");
        verticalLayoutTournament = new QVBoxLayout(tabTournament);
        verticalLayoutTournament->setObjectName("verticalLayoutTournament");
        createTournamentButton = new QPushButton(tabTournament);
        createTournamentButton->setObjectName("createTournamentButton");

        verticalLayoutTournament->addWidget(createTournamentButton);

        scheduleListWidget = new QListWidget(tabTournament);
        scheduleListWidget->setObjectName("scheduleListWidget");

        verticalLayoutTournament->addWidget(scheduleListWidget);

        horizontalLayoutTournamentControls = new QHBoxLayout();
        horizontalLayoutTournamentControls->setObjectName("horizontalLayoutTournamentControls");
        startTournamentButton = new QPushButton(tabTournament);
        startTournamentButton->setObjectName("startTournamentButton");

        horizontalLayoutTournamentControls->addWidget(startTournamentButton);

        currentMatchLabel = new QLabel(tabTournament);
        currentMatchLabel->setObjectName("currentMatchLabel");

        horizontalLayoutTournamentControls->addWidget(currentMatchLabel);

        scoreLabel = new QLabel(tabTournament);
        scoreLabel->setObjectName("scoreLabel");

        horizontalLayoutTournamentControls->addWidget(scoreLabel);


        verticalLayoutTournament->addLayout(horizontalLayoutTournamentControls);

        matchLogTextEdit = new QTextEdit(tabTournament);
        matchLogTextEdit->setObjectName("matchLogTextEdit");
        matchLogTextEdit->setReadOnly(true);

        verticalLayoutTournament->addWidget(matchLogTextEdit);

        tournamentTableWidget = new QTableWidget(tabTournament);
        if (tournamentTableWidget->columnCount() < 4)
            tournamentTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tournamentTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tournamentTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tournamentTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tournamentTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tournamentTableWidget->setObjectName("tournamentTableWidget");
        tournamentTableWidget->setColumnCount(4);
        tournamentTableWidget->setRowCount(0);

        verticalLayoutTournament->addWidget(tournamentTableWidget);

        tabWidget->addTab(tabTournament, QString());

        verticalLayoutMain->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\320\270\320\274\321\203\320\273\321\217\321\206\320\270\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", nullptr));
        playerNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\270\320\263\321\200\320\276\320\272\320\260", nullptr));
        speedSpinBox->setPrefix(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214: ", nullptr));
        attackSpinBox->setPrefix(QCoreApplication::translate("MainWindow", "\320\220\321\202\320\260\320\272\320\260: ", nullptr));
        staminaSpinBox->setPrefix(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\275\320\276\321\201\320\273\320\270\320\262\320\276\321\201\321\202\321\214: ", nullptr));
        addPlayerButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\263\321\200\320\276\320\272\320\260", nullptr));
        teamNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\272\320\276\320\274\320\260\320\275\320\264\321\213", nullptr));
        createTeamButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\272\320\276\320\274\320\260\320\275\320\264\321\203", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTeam), QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\272\320\276\320\274\320\260\320\275\320\264\321\213", nullptr));
        createTournamentButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\321\203\321\200\320\275\320\270\321\200", nullptr));
        startTournamentButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \321\202\321\203\321\200\320\275\320\270\321\200", nullptr));
        currentMatchLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\207: -", nullptr));
        scoreLabel->setText(QCoreApplication::translate("MainWindow", "0 : 0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tournamentTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\260\320\275\320\264\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tournamentTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\272\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tournamentTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\261\320\265\320\264\321\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tournamentTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTournament), QCoreApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
