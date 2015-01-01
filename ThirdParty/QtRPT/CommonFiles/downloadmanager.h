#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <updatedlg.h>

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);
    QNetworkReply::NetworkError error;
    void download(bool ver);
    bool isDownloaded();
    void setTarget(const QString &t);
    QString fileName;

private:
    QNetworkAccessManager *manager;
    QString m_target;
    bool m_isdownloaded;
    bool m_version;
    QStringList fileList;

signals:
    void done();
    void downloadingProgress(qint64 recieved, qint64 total);

public slots:
    void downloadFinished(QNetworkReply* data);
    void downloadProgress(qint64 recieved, qint64 total);
};

#endif // DOWNLOADMANAGER_H
