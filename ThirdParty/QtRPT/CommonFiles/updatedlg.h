#ifndef UPDATEDLG_H
#define UPDATEDLG_H

#include <QDialog>
#include <QFileDialog>
#include "downloadmanager.h"

namespace Ui {
    class UpdateDlg;
}

class UpdateDlg : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateDlg(QString url, QWidget *parent = 0);
    ~UpdateDlg();
    void showThis(QStringList list);

private:    
    Ui::UpdateDlg *ui;
    QString m_url;

private slots:
    void doDownload();
    void downloadProgress(qint64 recieved, qint64 total);
};

#endif // UPDATEDLG_H
