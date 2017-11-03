#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "httpresponse.h"


namespace Network
{
    typedef QMap<QString, QString> params;

    class HTTPRequest : public QObject
    {
        Q_OBJECT

    public:
        HTTPRequest(QString url);

        QString                 getUrl() const;

        void                    get(params uriParams = {}, params queryParams = {});
        void                    remove(params uriParams = {}, params queryParams = {});
        void                    post(params uriParams = {}, QByteArray data = {});
        void                    update(params uriParams = {}, QByteArray data = {});

    public slots:
        void                    httpReadyRead();

    signals:
        void                    finished(Network::HTTPResponse);

    private:
        QString                 serializeQueryParams(params queryParams);
        QString                 transformUrlParams(params uriParams);

    private:
        QNetworkAccessManager   m_qnam;
        QString                 m_url;
    };
}

#endif // HTTPREQUEST_H
