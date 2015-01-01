#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QList>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSettings>
#include <QWindowStateChangeEvent>
#include <QTimer>
#include <QDesktopWidget>
#include <QStringListModel>
#include <QLocale>
#include "qticonloader.h"
#include "TaskButton.h"
#include "JalaliDate.h"
#include "DBManager.h"
#include "Const.h"
#include "Report.h"
#include "ui_MainWindow.h"
#include "SettingDlg.h"
#include "qxt/qxtglobalshortcut.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void mainOperationButtonClicked();
    void taskStartedEditing();
    void taskCancelledEditing();
    void taskFinishedEditing();
    void taskDeleted();
    void taskMovedUp();
    void taskMovedDown();
    void taskClicked();
    void taskDone();
    void saveSettings();
    void systemTrayActivated(QSystemTrayIcon::ActivationReason activationReason);
    void updateSystemTrayToolTip();
    void doHideRestoreAction();
    void quit();
    void showHideSettingAction();

private slots:
    void on_pbReport_clicked();
private slots:
    void shortcutPressed(QxtGlobalShortcut *gs);

private:

    enum State
    {
        NORMAL,
        EDITING
    };

    struct TaskItem {
        Task *task;
        TaskButton *taskButton;
        QAction *trayAction;
        bool valid;
    };


    Ui::MainWindow *ui;
    SettingDlg * m_SettingDlg;
    QList<TaskItem*> taskItems;
    QTimer tickTimer;
    QTimer saveTimer;
    State state;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *systemTrayMenu;
    QAction *quitAction;
    QAction *hideRestoreAction;
    QAction *settingAction;
    QRect oldGeometry;
    bool reallyQuit;
    QLocale m_Locale;

    void addNewTask();
    TaskItem *createTaskItem(Task *task);
    void changeState(State newState);
    void loadSettings();
    void setupTrayIcon();
    void removeTaskItem(TaskItem* taskItem);
    TaskItem* getTaskItemFromButton(TaskButton* taskButton);
    void moveTaskItem(int fromIndex, int toIndex);
    void restore();
    bool event(QEvent *event);

    JalaliDate m_jDate;
    //QSystemHotkey *hotkeys;
};

#endif // MAINWINDOW_H
