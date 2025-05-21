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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *teamTab;
    QVBoxLayout *verticalLayout;
    QLineEdit *teamNameEdit;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *playerNameEdit;
    QLabel *label_2;
    QSpinBox *speedSpin;
    QLabel *label_3;
    QSpinBox *attackSpin;
    QLabel *label_4;
    QSpinBox *staminaSpin;
    QPushButton *addPlayerBtn;
    QListWidget *playersList;
    QPushButton *createTeamBtn;
    QListWidget *teamsList;
    QWidget *simulationTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *team1Combo;
    QLabel *label_6;
    QComboBox *team2Combo;
    QLabel *lblScore;
    QPushButton *simulateBtn;
    QListWidget *eventsLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        teamTab = new QWidget();
        teamTab->setObjectName("teamTab");
        verticalLayout = new QVBoxLayout(teamTab);
        verticalLayout->setObjectName("verticalLayout");
        teamNameEdit = new QLineEdit(teamTab);
        teamNameEdit->setObjectName("teamNameEdit");

        verticalLayout->addWidget(teamNameEdit);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(teamTab);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        playerNameEdit = new QLineEdit(teamTab);
        playerNameEdit->setObjectName("playerNameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, playerNameEdit);

        label_2 = new QLabel(teamTab);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        speedSpin = new QSpinBox(teamTab);
        speedSpin->setObjectName("speedSpin");
        speedSpin->setMaximum(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, speedSpin);

        label_3 = new QLabel(teamTab);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        attackSpin = new QSpinBox(teamTab);
        attackSpin->setObjectName("attackSpin");
        attackSpin->setMaximum(100);

        formLayout->setWidget(2, QFormLayout::FieldRole, attackSpin);

        label_4 = new QLabel(teamTab);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        staminaSpin = new QSpinBox(teamTab);
        staminaSpin->setObjectName("staminaSpin");
        staminaSpin->setMaximum(100);

        formLayout->setWidget(3, QFormLayout::FieldRole, staminaSpin);


        verticalLayout->addLayout(formLayout);

        addPlayerBtn = new QPushButton(teamTab);
        addPlayerBtn->setObjectName("addPlayerBtn");

        verticalLayout->addWidget(addPlayerBtn);

        playersList = new QListWidget(teamTab);
        playersList->setObjectName("playersList");

        verticalLayout->addWidget(playersList);

        createTeamBtn = new QPushButton(teamTab);
        createTeamBtn->setObjectName("createTeamBtn");

        verticalLayout->addWidget(createTeamBtn);

        teamsList = new QListWidget(teamTab);
        teamsList->setObjectName("teamsList");

        verticalLayout->addWidget(teamsList);

        tabWidget->addTab(teamTab, QString());
        simulationTab = new QWidget();
        simulationTab->setObjectName("simulationTab");
        verticalLayout_2 = new QVBoxLayout(simulationTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(simulationTab);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        team1Combo = new QComboBox(simulationTab);
        team1Combo->setObjectName("team1Combo");

        horizontalLayout_2->addWidget(team1Combo);

        label_6 = new QLabel(simulationTab);
        label_6->setObjectName("label_6");

        horizontalLayout_2->addWidget(label_6);

        team2Combo = new QComboBox(simulationTab);
        team2Combo->setObjectName("team2Combo");

        horizontalLayout_2->addWidget(team2Combo);


        verticalLayout_2->addLayout(horizontalLayout_2);

        lblScore = new QLabel(simulationTab);
        lblScore->setObjectName("lblScore");
        lblScore->setAlignment(Qt::AlignCenter);
        lblScore->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50;"));

        verticalLayout_2->addWidget(lblScore);

        simulateBtn = new QPushButton(simulationTab);
        simulateBtn->setObjectName("simulateBtn");
        simulateBtn->setStyleSheet(QString::fromUtf8("padding: 10px; font-weight: bold;"));

        verticalLayout_2->addWidget(simulateBtn);

        eventsLog = new QListWidget(simulationTab);
        eventsLog->setObjectName("eventsLog");
        eventsLog->setStyleSheet(QString::fromUtf8("font-family: monospace; font-size: 12px;"));

        verticalLayout_2->addWidget(eventsLog);

        tabWidget->addTab(simulationTab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Volleyball Simulator", nullptr));
        teamNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Team name", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Player Name:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Speed:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Attack:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Stamina:", nullptr));
        addPlayerBtn->setText(QCoreApplication::translate("MainWindow", "Add Player", nullptr));
        createTeamBtn->setText(QCoreApplication::translate("MainWindow", "Create Team", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(teamTab), QCoreApplication::translate("MainWindow", "Teams", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Team 1:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Team 2:", nullptr));
        lblScore->setText(QCoreApplication::translate("MainWindow", "Score: 0 - 0", nullptr));
        simulateBtn->setText(QCoreApplication::translate("MainWindow", "Simulate Match", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(simulationTab), QCoreApplication::translate("MainWindow", "Simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
