#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QNetworkReply>


namespace Network
{
    typedef QNetworkAccessManager::Operation Method;

    class HTTPResponse
    {
    public:
        HTTPResponse(QNetworkReply * reply);

        int                     status();
        Method                  operation();
        QByteArray              data();

    private:
        int                     m_status;
        Method                  m_operation;
        QByteArray              m_data;
    };
}

#endif // HTTPRESPONSE_H
