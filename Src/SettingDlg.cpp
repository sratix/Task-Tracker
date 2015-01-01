#include "SettingDlg.h"
#include "ui_SettingDlg.h"

SettingDlg::SettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDlg)
{
    ui->setupUi(this);
    QDesktopWidget d;
    move(d.screenGeometry().center().x() - width() / 2, d.screenGeometry().center().y() - height() / 2);
    loadSettings();

#ifdef Q_OS_LINUX
    ui->gb_About->setStyleSheet("QGroupBox{background-color: transparent;border: 2px solid gray;border-radius: 6px;padding: 2px;selection-background-color: darkgray; \
                                 margin-top: 1ex;}");
#else
    ui->gb_About->setStyleSheet("QGroupBox{background-color: transparent;border: 2px solid gray;border-radius: 6px;padding: 2px;selection-background-color: darkgray; \
                                 margin-top: 4ex;}");
#endif
    ui->gb_Settings->setStyleSheet(ui->gb_About->styleSheet());
    ui->gb_Shortcuts->setStyleSheet(ui->gb_About->styleSheet());
}

SettingDlg::~SettingDlg()
{
    saveSettings();
    delete ui;
}

void SettingDlg::loadSettings()
{
    QSettings settings("Task-Tracker", "tasktracker");
    ui->cbStartup->setChecked(settings.value("setting/alwaysontop").toBool());
}

void SettingDlg::saveSettings()
{
    QSettings settings("Task-Tracker", "tasktracker");
    settings.clear();
    settings.setValue("setting/alwaysontop", ui->cbStartup->isChecked());
    settings.sync();
#ifdef Q_OS_WIN
    QSettings WIN_REG("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if(ui->cbStartup->isChecked())
    {
        WIN_REG.setValue("TaskTracker", QCoreApplication::applicationFilePath().replace('/','\\'));
    }
    else
    {
        WIN_REG.remove("TaskTracker");
    }
    WIN_REG.sync();
#else
    if(ui->cbStartup->isChecked())
    {
        QFile file(":/data/task-tracker.desktop");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        }
        QByteArray lines = file.readAll();
        file.close();
        lines.replace(QString("##"), qApp->applicationFilePath().toLatin1());
        file.setFileName(LinuxAppStartupPath+LinuxAppStartupFileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << file.fileName();
        }
        file.write(lines);
        file.close();
    }
    else
    {
        QDir dir(LinuxAppStartupPath);
        dir.remove(LinuxAppStartupFileName);
    }
#endif
}

void SettingDlg::on_pbClearDB_clicked()
{
    DBManager::Instance()->clearDB();
    QMessageBox::information(this, "راه اندازی مجدد", "برنامه نیاز به راه اندازی مجدد دارد");
    exit(EXIT_SUCCESS);
}
