#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QMap>

#include "httprequest.h"
#include "httpresponse.h"


namespace Network
{
    class Service : public QObject
    {
        Q_OBJECT

    public:
        Service(QString name, QString webServiceHost, QString webServiceAPI, QObject * parent = nullptr);
        ~Service();

        HTTPRequest *                   getRessource();
        HTTPRequest *                   getRessource(const QString & uri);

        QString                         getWebServiceHost() const;
        QString                         getWebServiceAPI() const;

        QString                         getName() const;
        QString                         getFullpath() const;

    private:
        QString                         m_webServiceHost;
        QString                         m_webServiceAPI;

        QString                         m_name;
        QString                         m_fullpath;

        QMap<QString, HTTPRequest *>    m_ressources;
    };
}

#endif
