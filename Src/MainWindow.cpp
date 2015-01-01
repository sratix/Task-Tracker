#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , state(NORMAL)
    , reallyQuit(false)
{
    ui->setupUi(this);
    QRect rect = this->geometry();
    QDesktopWidget dw;
    setGeometry(dw.screenGeometry().width()-rect.width(), dw.screenGeometry().height()/2-(dw.screenGeometry().height()-100)/2, rect.width(), dw.screenGeometry().height()-100);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    QDir dir("DB");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    dir.setPath("Rep");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    DBManager::Instance()->loadDB(DBName);
    setupTrayIcon();
    loadSettings();

    connect(ui->mainOperationButton, SIGNAL(clicked()), this, SLOT(mainOperationButtonClicked()));
    connect(&saveTimer, SIGNAL(timeout()), this, SLOT(saveSettings()));
    connect(&tickTimer, SIGNAL(timeout()), this, SLOT(updateSystemTrayToolTip()));
    saveTimer.start(60000);
    tickTimer.start(1000);
    ui->gbComment->setVisible(false);
    int jMonth = (m_jDate.GetJTodayMonth()-1 == 0) ? 12:m_jDate.GetJTodayMonth()-1;
    ui->leFromDate->setText(QString("%1/%2/%3")
                            .arg(QString::number(m_jDate.GetJTodayYear()))
                            .arg(QString::number(jMonth), 2, QChar('0'))
                            .arg("21"));
    ui->leToDate->setText(m_jDate.Today());

    QxtGlobalShortcut *gs = new QxtGlobalShortcut(QKeySequence(tr("Ctrl+Shift+A")), this);
    connect(gs, SIGNAL(activated(QxtGlobalShortcut*)), this, SLOT(shortcutPressed(QxtGlobalShortcut*)));

#ifdef Q_OS_LINUX
    ui->gb_Report->setStyleSheet("QGroupBox{background-color: transparent;border: 2px solid gray;border-radius: 6px;padding: 2px;selection-background-color: darkgray; \
                                 margin-top: 1ex;}");
#else
    ui->gb_Report->setStyleSheet("QGroupBox{background-color: transparent;border: 2px solid gray;border-radius: 6px;padding: 2px;selection-background-color: darkgray; \
                                 margin-top: 4ex;}");
#endif

    m_Locale.setDefault(QLocale(QLocale::Persian, QLocale::Iran));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupTrayIcon()
{
    quitAction = new QAction("خروج", this);
    quitAction->setIcon(QIcon(":icons/exit.png"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
    hideRestoreAction = new QAction("نمایش", this);
    connect(hideRestoreAction, SIGNAL(triggered()), this, SLOT(doHideRestoreAction()));
    settingAction = new QAction("تنظیمات", this);
    settingAction->setIcon(QIcon(":icons/setting.png"));
    connect(settingAction, SIGNAL(triggered()), this, SLOT(showHideSettingAction()));
    systemTrayMenu = new QMenu(this);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(settingAction);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(hideRestoreAction);
    systemTrayMenu->addAction(quitAction);
    systemTrayMenu->setCursor(Qt::PointingHandCursor);
    systemTrayMenu->setStyleSheet("font-size:17px;background-color:gray;");
    systemTrayIcon = new QSystemTrayIcon(QIcon(":icons/tasktracker.png"), this);
    systemTrayIcon->setContextMenu(systemTrayMenu);
    updateSystemTrayToolTip();
    systemTrayIcon->show();
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(systemTrayActivated(QSystemTrayIcon::ActivationReason)));
}
void MainWindow::systemTrayActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    if(activationReason == QSystemTrayIcon::Trigger ||
            activationReason == QSystemTrayIcon::DoubleClick)
    {
        doHideRestoreAction();
    }
}
void MainWindow::mainOperationButtonClicked()
{
    if(state == NORMAL)
    {
        addNewTask();
    }
    else if (state == EDITING)
    {
        for(int i=0; i < taskItems.size(); i++)
        {
            taskItems[i]->taskButton->cancelEditing();
        }
    }
}
void MainWindow::addNewTask()
{
    Task* task = new Task();
    task->setName(QString::fromUtf8("کار جدید"));
    TaskItem *taskItem = createTaskItem(task);
    taskItem->valid = false;
    taskItem->taskButton->startRenaming();
    ui->gbComment->setVisible(true);
}
MainWindow::TaskItem* MainWindow::createTaskItem(Task *task)
{
    TaskButton *taskButton = new TaskButton(this);
    taskButton->setTask(task);
    connect(&tickTimer, SIGNAL(timeout()), taskButton, SLOT(tick()));
    connect(taskButton, SIGNAL(startedEditing()), this, SLOT(taskStartedEditing()));
    connect(taskButton, SIGNAL(cancelledEditing()), this, SLOT(taskCancelledEditing()));
    connect(taskButton, SIGNAL(finishedEditing()), this, SLOT(taskFinishedEditing()));
    connect(taskButton, SIGNAL(deleted()), this, SLOT(taskDeleted()));
    connect(taskButton, SIGNAL(movedUp()), this, SLOT(taskMovedUp()));
    connect(taskButton, SIGNAL(movedDown()), this, SLOT(taskMovedDown()));
    connect(taskButton, SIGNAL(buttonClicked()), this, SLOT(taskClicked()));
    connect(taskButton, SIGNAL(taskDone()), this, SLOT(taskDone()));
    ui->taskListLayout->insertWidget(0, taskButton);
    ui->taskListScrollArea->ensureWidgetVisible(taskButton);
    setTabOrder(ui->mainOperationButton, taskButton); // We insert to top rather than bottom, so we need to manually set tab order
    QAction *trayAction = new QAction(task->getName(), this);
    trayAction->setCheckable(true);
    connect(taskButton, SIGNAL(activated(bool)), trayAction, SLOT(setChecked(bool)));
    connect(trayAction, SIGNAL(toggled(bool)), taskButton, SLOT(setActive(bool)));
    systemTrayMenu->insertAction(systemTrayMenu->actions().first(), trayAction);
    TaskItem *taskItem = new TaskItem();
    taskItem->task = task;
    taskItem->taskButton = taskButton;
    taskItem->trayAction = trayAction;
    taskItems.insert(0, taskItem);
    return taskItem;
}
void MainWindow::taskStartedEditing()
{
    for(int i=0; i < taskItems.size(); i++)
    {
        TaskButton *taskButton = taskItems[i]->taskButton;
        if(taskButton != sender() && taskButton->isEditing())
        {
            taskButton->cancelEditing();
        }
    }
    QString comment;
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    DBManager::Instance()->readComment(taskItem->task->getID(), comment);
    ui->teComment->setText(comment);
    ui->gbComment->setVisible(true);
    changeState(EDITING);
}
void MainWindow::taskCancelledEditing()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    if(taskItem->valid == false)
    {
        removeTaskItem(taskItem);
    }
    changeState(NORMAL);
    ui->gbComment->setVisible(false);
    ui->teComment->clear();
}
void MainWindow::removeTaskItem(TaskItem* taskItem)
{
    taskItem->taskButton->deleteLater();
    taskItem->trayAction->deleteLater();
    taskItems.removeOne(taskItem);
}
MainWindow::TaskItem* MainWindow::getTaskItemFromButton(TaskButton* taskButton)
{
    for(int i=0; i < taskItems.size(); i++)
    {
        if(taskItems[i]->taskButton == taskButton)
        {
            return taskItems[i];
        }
    }
    return NULL;
}
void MainWindow::taskFinishedEditing()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    switch (taskItem->valid)
    {
    case false: // Added new Task
        taskItem->task->makeID();
        DBManager::Instance()->addTask(QVector<QVariant>()
                                       << taskItem->task->getID()
                                       << taskItem->task->getName()
                                       << CREATED
                                       << QTime::currentTime().toString()
                                       << QDate::currentDate().toString(Qt::ISODate).replace('-', '/')//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd")
                                       << QString("00:00:00")
                                       << QString("0000/00/00")
                                       << QString("00:00:00")
                                       << QString("0000/00/00")
                                       << taskItem->task->getTime()
                                       << ui->teComment->toPlainText()
                                       );
        taskItem->task->setTaskState(CREATED);
        break;
    case true:  // Edit the Task
        DBManager::Instance()->updateNameConsumeComment(taskItem->task->getID(),
                                                        taskItem->task->getTaskState(),
                                                        taskItem->task->getName(),
                                                        taskItem->task->getTime(),
                                                        ui->teComment->toPlainText());
        break;
    }
    taskItem->valid = true;
    QString newTaskName = taskItem->task->getName();
    taskItem->trayAction->setText(newTaskName);
    taskItem->taskButton->setFocus();
    changeState(NORMAL);
    ui->gbComment->setVisible(false);
    ui->teComment->clear();
}
void MainWindow::changeState(State newState)
{
    if(newState == EDITING)
    {
        ui->mainOperationButton->setText(QString::fromUtf8("لغو"));
    } else if(newState == NORMAL)
    {
        ui->mainOperationButton->setText(QString::fromUtf8("افزودن کار جدید"));
    }
    state = newState;
}
void MainWindow::taskDeleted()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    removeTaskItem(taskItem);
    DBManager::Instance()->deleteTask(taskItem->task->getID());
}
void MainWindow::taskMovedUp()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    int index = taskItems.indexOf(taskItem);
    if(index > 0)
    {
        moveTaskItem(index, index - 1);
    }
}
void MainWindow::taskMovedDown()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    int index = taskItems.indexOf(taskItem);
    if(index < taskItems.size() - 1)
    {
        moveTaskItem(index, index + 1);
    }
}
void MainWindow::taskClicked()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    if(taskItem->task->getTaskState() == CREATED) // TaskState = Started & Running
    {
        DBManager::Instance()->updateTask(taskItem->task->getID(),
                                          STARTED,
                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                          QTime::currentTime().toString());
        DBManager::Instance()->updateTask(taskItem->task->getID(),
                                          RUNNING,
                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                          QTime::currentTime().toString());
        taskItem->task->setTaskState(RUNNING);
    }
    else if(taskItem->task->getTaskState() == WAITED) // TaskState = Runnig
    {
        DBManager::Instance()->updateTask(taskItem->task->getID(),
                                          RUNNING,
                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                          QTime::currentTime().toString());
        taskItem->task->setTaskState(RUNNING);
    }
    else if(taskItem->task->getTaskState() == RUNNING) // TaskState = Waited
    {
        DBManager::Instance()->updateTask(taskItem->task->getID(),
                                          WAITED,
                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                          QTime::currentTime().toString());
        taskItem->task->setTaskState(WAITED);
    }
}
void MainWindow::taskDone()
{
    TaskButton *taskButton = static_cast<TaskButton*>(sender());
    TaskItem *taskItem = getTaskItemFromButton(taskButton);
    taskItem->task->setActive(false);
    taskItem->valid = false;
    DBManager::Instance()->updateTask(taskItem->task->getID(),
                                      DONE,
                                      QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                      QTime::currentTime().toString());
    removeTaskItem(taskItem);
}
void MainWindow::moveTaskItem(int fromIndex, int toIndex)
{
    TaskItem *taskItem = taskItems[fromIndex];
    ui->taskListLayout->removeWidget(taskItem->taskButton);
    ui->taskListLayout->insertWidget(toIndex, taskItem->taskButton);
    systemTrayMenu->removeAction(taskItem->trayAction);
    systemTrayMenu->insertAction(systemTrayMenu->actions()[toIndex], taskItem->trayAction);
    taskItems.move(fromIndex, toIndex);
}
void MainWindow::loadSettings()
{
    QVector<TaskData> tasks;
    DBManager::Instance()->readAllExistTask(tasks);
    foreach (TaskData task, tasks)
    {
        Task *tsk = new Task();
        tsk->setID(task.taskuID);
        tsk->setName(task.taskShortName);
        tsk->setTime(task.taskConsumeTime);
        tsk->setTaskState(TaskState(task.taskState));
        TaskItem *taskItem = createTaskItem(tsk);
        taskItem->valid = true;
    }
}
void MainWindow::saveSettings()
{
    int numTasks = taskItems.size();
    for(int i=0; i < numTasks; i++)
    {
        Task* task = taskItems[i]->task;
        if(task->getTaskState() == CREATED) continue; // TaskState = Just Created Not Started
        DBManager::Instance()->updateNameConsumeComment(task->getID(), WAITED, task->getName(), task->getTime(), "");
    }
}
void MainWindow::updateSystemTrayToolTip()
{
    ui->lblToday->setText("<center>"+QString::fromUtf8("امروز ")+m_jDate.TodayText()+
                          "</center>\n<center>"+QTime().currentTime().toString()+"</center>");
    QList<TaskItem*> activeTaskItems;
    foreach(TaskItem *taskItem, taskItems)
    {
        if(taskItem->task->isActive())
        {
            activeTaskItems.append(taskItem);
        }
    }
    QString tooltip;
    if(activeTaskItems.count() == 0)
    {
        tooltip = "No tasks active";
    }
    else
    {
        for(int i=0; i < activeTaskItems.size(); i++)
        {
            QString taskText = activeTaskItems[i]->task->toText();
            tooltip += taskText;
            if(i < activeTaskItems.size() - 1)
            {
                tooltip += '\n';
            }
        }
    }
    systemTrayIcon->setToolTip(tooltip);
}
void MainWindow::doHideRestoreAction()
{
    if (this->isVisible())
        this->hide();
    else
        this->restore();
}
bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        if(!reallyQuit)
        {
            QCloseEvent *closeEvent = static_cast<QCloseEvent*>(event);
            this->hide();
            closeEvent->ignore();
            return true;
        }
    }
    else if(event->type() == QEvent::Resize || event->type() == QEvent::Move)
    {
        if(this->geometry().width() > 0 && this->geometry().height() > 0)
        {
            oldGeometry = this->geometry();
        }
    }
    else if(event->type() == QEvent::Hide && !event->spontaneous())
    {
        hideRestoreAction->setText("نمایش");
    }
    else if(event->type() == QEvent::Show && !event->spontaneous())
    {
        hideRestoreAction->setText("عدم نمایش");
    }
    else if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->modifiers() & Qt::ControlModifier)
        {
            int key = keyEvent->key();
            switch(key)
            {
            case Qt::Key_1:
            case Qt::Key_2:
            case Qt::Key_3:
            case Qt::Key_4:
            case Qt::Key_5:
            case Qt::Key_6:
            case Qt::Key_7:
            case Qt::Key_8:
            case Qt::Key_9:
            {
                int num = key - Qt::Key_1;
                if(taskItems.size() > num)
                {
                    taskItems[num]->task->toggle();
                    if(taskItems[num]->task->getTaskState() == CREATED)
                    {
                        DBManager::Instance()->updateTask(taskItems[num]->task->getID(),
                                                          STARTED,
                                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                                          QTime::currentTime().toString());
                        DBManager::Instance()->updateTask(taskItems[num]->task->getID(),
                                                          RUNNING,
                                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                                          QTime::currentTime().toString());
                        taskItems[num]->task->setTaskState(RUNNING);
                    }
                    else if(taskItems[num]->task->getTaskState() == WAITED)
                    {
                        DBManager::Instance()->updateTask(taskItems[num]->task->getID(),
                                                          RUNNING,
                                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                                          QTime::currentTime().toString());
                        taskItems[num]->task->setTaskState(RUNNING);
                    }
                    else if(taskItems[num]->task->getTaskState() == RUNNING)
                    {
                        DBManager::Instance()->updateTask(taskItems[num]->task->getID(),
                                                          WAITED,
                                                          QDate::currentDate().toString(Qt::ISODate).replace('-', '/'),//m_Locale.toDate(QDate::currentDate().toString(Qt::DefaultLocaleShortDate), "yyyy/MM/dd").toString("yyyy/MM/dd"),
                                                          QTime::currentTime().toString());
                        taskItems[num]->task->setTaskState(WAITED);
                    }
                    return true;
                }
            }
            case Qt::Key_T:
            {
                if(state == NORMAL)
                {
                    this->addNewTask();
                }
                return true;
            }
            case Qt::Key_Q:
            {
                quitAction->trigger();
            }
            }
        }
        if (keyEvent->key() == Qt::Key_Escape && state == NORMAL)
        {
            this->hide();
        }
    }
    return QMainWindow::event(event);
}
void MainWindow::restore()
{
    this->show();
    this->activateWindow();
    this->setGeometry(oldGeometry);
}
void MainWindow::quit()
{
    reallyQuit = true;
    saveSettings();
    exit(EXIT_SUCCESS);
}
void MainWindow::showHideSettingAction()
{
    //FIXME: problem on show dialog om movement the main move
    m_SettingDlg = new SettingDlg(this);
#ifdef Q_OS_WIN
    m_SettingDlg->setModal(true);
#endif
    qApp->setQuitOnLastWindowClosed(false);
    m_SettingDlg->setAttribute( Qt::WA_DeleteOnClose );
    //connect(m_SettingDlg, SIGNAL(finished(int)), m_SettingDlg, SLOT(deleteLater()));
    m_SettingDlg->show();
}
void MainWindow::on_pbReport_clicked()
{
    Report rep;
    rep.makeReport(ui->leFromDate->text().trimmed(), ui->leToDate->text().trimmed());
}
void MainWindow::shortcutPressed(QxtGlobalShortcut *gs)
{
    if (gs->shortcut().toString().compare("Ctrl+Shift+A") == 0)
    {
        if (this->isVisible())
            this->hide();
        else
            this->restore();
    }
}
