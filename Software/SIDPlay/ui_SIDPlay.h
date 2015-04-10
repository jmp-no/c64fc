/********************************************************************************
** Form generated from reading UI file 'SIDPlay.ui'
**
** Created: Wed Apr 8 12:19:06 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDPLAY_H
#define UI_SIDPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SIDPlay
{
public:
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionSingle_mode;
    QAction *actionPlalyst_mode;
    QAction *actionShuffle_mode;
    QAction *actionReset;
    QAction *actionRelaunch_player;
    QAction *action1_minute;
    QAction *action3_minutes;
    QAction *action5_minutes;
    QAction *actionIndefinitely;
    QAction *actionPlay;
    QAction *actionRewind;
    QAction *actionFast_forward;
    QAction *actionStop;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuJukebox_mode;
    QMenu *menuPlay_time;
    QMenu *menuC64;
    QMenu *menuControl;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SIDPlay)
    {
        if (SIDPlay->objectName().isEmpty())
            SIDPlay->setObjectName(QString::fromUtf8("SIDPlay"));
        SIDPlay->resize(588, 437);
        actionAbout = new QAction(SIDPlay);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExit = new QAction(SIDPlay);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSingle_mode = new QAction(SIDPlay);
        actionSingle_mode->setObjectName(QString::fromUtf8("actionSingle_mode"));
        actionSingle_mode->setCheckable(true);
        actionSingle_mode->setChecked(true);
        actionPlalyst_mode = new QAction(SIDPlay);
        actionPlalyst_mode->setObjectName(QString::fromUtf8("actionPlalyst_mode"));
        actionPlalyst_mode->setCheckable(true);
        actionShuffle_mode = new QAction(SIDPlay);
        actionShuffle_mode->setObjectName(QString::fromUtf8("actionShuffle_mode"));
        actionShuffle_mode->setCheckable(true);
        actionReset = new QAction(SIDPlay);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionRelaunch_player = new QAction(SIDPlay);
        actionRelaunch_player->setObjectName(QString::fromUtf8("actionRelaunch_player"));
        action1_minute = new QAction(SIDPlay);
        action1_minute->setObjectName(QString::fromUtf8("action1_minute"));
        action1_minute->setCheckable(true);
        action3_minutes = new QAction(SIDPlay);
        action3_minutes->setObjectName(QString::fromUtf8("action3_minutes"));
        action3_minutes->setCheckable(true);
        action5_minutes = new QAction(SIDPlay);
        action5_minutes->setObjectName(QString::fromUtf8("action5_minutes"));
        action5_minutes->setCheckable(true);
        actionIndefinitely = new QAction(SIDPlay);
        actionIndefinitely->setObjectName(QString::fromUtf8("actionIndefinitely"));
        actionIndefinitely->setCheckable(true);
        actionIndefinitely->setChecked(true);
        actionPlay = new QAction(SIDPlay);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionRewind = new QAction(SIDPlay);
        actionRewind->setObjectName(QString::fromUtf8("actionRewind"));
        actionFast_forward = new QAction(SIDPlay);
        actionFast_forward->setObjectName(QString::fromUtf8("actionFast_forward"));
        actionStop = new QAction(SIDPlay);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        centralwidget = new QWidget(SIDPlay);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        horizontalLayout_2->addLayout(verticalLayout);

        SIDPlay->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SIDPlay);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 588, 27));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuJukebox_mode = new QMenu(menubar);
        menuJukebox_mode->setObjectName(QString::fromUtf8("menuJukebox_mode"));
        menuPlay_time = new QMenu(menuJukebox_mode);
        menuPlay_time->setObjectName(QString::fromUtf8("menuPlay_time"));
        menuPlay_time->setEnabled(true);
        menuC64 = new QMenu(menubar);
        menuC64->setObjectName(QString::fromUtf8("menuC64"));
        menuControl = new QMenu(menubar);
        menuControl->setObjectName(QString::fromUtf8("menuControl"));
        SIDPlay->setMenuBar(menubar);
        statusbar = new QStatusBar(SIDPlay);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SIDPlay->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuControl->menuAction());
        menubar->addAction(menuJukebox_mode->menuAction());
        menubar->addAction(menuC64->menuAction());
        menuFile->addAction(actionAbout);
        menuFile->addAction(actionExit);
        menuJukebox_mode->addAction(actionSingle_mode);
        menuJukebox_mode->addAction(actionPlalyst_mode);
        menuJukebox_mode->addAction(actionShuffle_mode);
        menuJukebox_mode->addAction(menuPlay_time->menuAction());
        menuPlay_time->addAction(action1_minute);
        menuPlay_time->addAction(action3_minutes);
        menuPlay_time->addAction(action5_minutes);
        menuPlay_time->addAction(actionIndefinitely);
        menuC64->addAction(actionReset);
        menuC64->addAction(actionRelaunch_player);
        menuControl->addAction(actionPlay);
        menuControl->addAction(actionRewind);
        menuControl->addAction(actionFast_forward);
        menuControl->addAction(actionStop);

        retranslateUi(SIDPlay);
        QObject::connect(actionExit, SIGNAL(activated()), SIDPlay, SLOT(update()));
        QObject::connect(actionAbout, SIGNAL(activated()), SIDPlay, SLOT(update()));
        QObject::connect(treeView, SIGNAL(doubleClicked(QModelIndex)), SIDPlay, SLOT(update()));
        QObject::connect(actionRelaunch_player, SIGNAL(activated()), SIDPlay, SLOT(update()));

        QMetaObject::connectSlotsByName(SIDPlay);
    } // setupUi

    void retranslateUi(QMainWindow *SIDPlay)
    {
        SIDPlay->setWindowTitle(QApplication::translate("SIDPlay", "SIDPlay", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("SIDPlay", "About", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("SIDPlay", "Exit", 0, QApplication::UnicodeUTF8));
        actionSingle_mode->setText(QApplication::translate("SIDPlay", "Single mode", 0, QApplication::UnicodeUTF8));
        actionPlalyst_mode->setText(QApplication::translate("SIDPlay", "Playlist mode", 0, QApplication::UnicodeUTF8));
        actionShuffle_mode->setText(QApplication::translate("SIDPlay", "Shuffle mode", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("SIDPlay", "Reset", 0, QApplication::UnicodeUTF8));
        actionRelaunch_player->setText(QApplication::translate("SIDPlay", "Relaunch player", 0, QApplication::UnicodeUTF8));
        action1_minute->setText(QApplication::translate("SIDPlay", "1 minute", 0, QApplication::UnicodeUTF8));
        action3_minutes->setText(QApplication::translate("SIDPlay", "3 minutes", 0, QApplication::UnicodeUTF8));
        action5_minutes->setText(QApplication::translate("SIDPlay", "5 minutes", 0, QApplication::UnicodeUTF8));
        actionIndefinitely->setText(QApplication::translate("SIDPlay", "Indefinitely", 0, QApplication::UnicodeUTF8));
        actionPlay->setText(QApplication::translate("SIDPlay", "&Play", 0, QApplication::UnicodeUTF8));
        actionRewind->setText(QApplication::translate("SIDPlay", "&Rewind", 0, QApplication::UnicodeUTF8));
        actionFast_forward->setText(QApplication::translate("SIDPlay", "&Fast forward", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("SIDPlay", "&Stop", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("SIDPlay", "File", 0, QApplication::UnicodeUTF8));
        menuJukebox_mode->setTitle(QApplication::translate("SIDPlay", "Jukebox", 0, QApplication::UnicodeUTF8));
        menuPlay_time->setTitle(QApplication::translate("SIDPlay", "Play time", 0, QApplication::UnicodeUTF8));
        menuC64->setTitle(QApplication::translate("SIDPlay", "C64", 0, QApplication::UnicodeUTF8));
        menuControl->setTitle(QApplication::translate("SIDPlay", "Control", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SIDPlay: public Ui_SIDPlay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDPLAY_H
