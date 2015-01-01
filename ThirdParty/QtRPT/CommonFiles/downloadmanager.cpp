#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::setTarget(const QString &t) {
    this->m_target = t;
    m_isdownloaded = false;
}

bool DownloadManager::isDownloaded() {
    return m_isdownloaded;
}

void DownloadManager::download(bool ver) {
    m_version = ver;
    m_isdownloaded = false;
    QUrl url = QUrl::fromEncoded(this->m_target.toLocal8Bit());
    QNetworkRequest request(url);
    QObject::connect(manager->get(request), SIGNAL(downloadProgress(qint64,qint64)),
                     this, SIGNAL(downloadingProgress(qint64,qint64)));
}

void DownloadManager::downloadFinished(QNetworkReply *data) {
    error = data->error();
    if (error != QNetworkReply::NoError) {
        //QMessageBox::warning(0,tr("Error"),tr("No file or Internet is not connected"),QMessageBox::Ok);
        emit done();
        return;
    }

    if (m_version) {
        const QByteArray sdata = data->readAll();
        QStringList fl;
        fl << sdata;
        fileList = fl.at(0).split("\n");        
        //qDebug()<<fl;
        //qDebug()<<fileList;

        if (QApplication::applicationVersion().replace(".","") < fileList[0].replace(".","").simplified()) {
            fileList.removeAt(0);
            UpdateDlg *updateDlg = new UpdateDlg(m_target.replace("version.txt",""),qobject_cast<QWidget *>(this->parent()));
            updateDlg->showThis(fileList);
        }
    } else {
        QFile localFile(fileName);
        if (!localFile.open(QIODevice::WriteOnly))
            return;
        const QByteArray sdata = data->readAll();
        localFile.write(sdata);
        localFile.close();
    }
    m_isdownloaded = true;
    emit done();
}

void DownloadManager::downloadProgress(qint64 recieved, qint64 total) {
    qDebug() << recieved << total;
}
