#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QDebug>
#include "DBManager.h"
#include "Const.h"

namespace Ui {
class SettingDlg;
}

class SettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDlg(QWidget *parent = 0);
    ~SettingDlg();
private:
    void loadSettings();
    void saveSettings();

private slots:
    void on_pbClearDB_clicked();

private:
    Ui::SettingDlg *ui;
};

#endif // SETTINGDLG_H
