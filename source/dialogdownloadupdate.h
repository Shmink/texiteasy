

#ifndef DIALOGDOWNLOADUPDATE_H
#define DIALOGDOWNLOADUPDATE_H

#define CODE_INSTALL_AND_RESTART 5000

#ifdef OS_WINDOWS

#include "configmanager.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMutex>
#include <QSemaphore>
#include <QStandardPaths>


namespace Ui {
class DialogDownloadUpdate;
}

class DialogDownloadUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDownloadUpdate(QWidget *parent = 0);
    ~DialogDownloadUpdate();

    QString filename() { return path() + "/" + _filename; }
    QString path()
    {
        return ConfigManager::Instance.dataLocation();
    }

    QString version() { return _version; }

private:
    Ui::DialogDownloadUpdate *ui;
    QNetworkAccessManager manager;

signals:
    void done();
    void downloadProgress(int);
    void versionDownloaded(QString);
public slots:
    void onDownloaded();
    void installAndRestart();
    void onFinished(int);

    void onError(QNetworkReply::NetworkError);
    void onDataDownloaded();
    void onDownloadProgress(qint64 recieved, qint64 total);
    void onVersionDownloaded();
    void onUrlDownloaded();
private slots:
    void download();
private:

    QNetworkReply * versionReply;
    QNetworkReply * urlReply;
    QNetworkReply * dataReply;
    QUrl _url;
    QString _urlString;
    QString _version;
    bool _started;
    bool _isVersionDownloaded;
    bool _isUrlDownloaded;
    QString _filename;
    QMutex _mutex;
};
#else // OS_WINDOWS
class DialogDownloadUpdate {

};
#endif

#endif // DIALOGDOWNLOADUPDATE_H
