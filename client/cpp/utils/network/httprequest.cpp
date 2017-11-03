#include "httprequest.h"

namespace Network
{
    //
    // CONSTRUCTOR
    //---------------------------------------------------------------------
    HTTPRequest::HTTPRequest(QString url) : m_url(url), QObject(nullptr)
    {}


    //
    // GET URL
    //---------------------------------------------------------------------
    QString HTTPRequest::getUrl() const
    {
        return m_url;
    }


    //
    // REQUEST GET
    //---------------------------------------------------------------------
    void HTTPRequest::get(params uriParams, params queryParams)
    {
        QString url = transformUrlParams(uriParams) + serializeQueryParams(queryParams);

        QNetworkReply * reply = m_qnam.get(QNetworkRequest(url));

        connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    }


    //
    // REQUEST DELETE
    //---------------------------------------------------------------------
    void HTTPRequest::remove(params uriParams, params queryParams)
    {
        QString url = transformUrlParams(uriParams) + serializeQueryParams(queryParams);

        QNetworkReply * reply = m_qnam.deleteResource(QNetworkRequest(url));

        connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    }


    //
    // REQUEST POST
    //---------------------------------------------------------------------
    void HTTPRequest::post(params uriParams, QByteArray data)
    {
        QString url = transformUrlParams(uriParams);

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QNetworkReply * reply = m_qnam.post(request, data);

        connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    }


    //
    // REQUEST PUT
    //---------------------------------------------------------------------
    void HTTPRequest::update(params uriParams, QByteArray data)
    {
        QString url = transformUrlParams(uriParams);

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QNetworkReply * reply = m_qnam.put(request, data);

        connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    }


    //
    // SLOT CALL A FINISHED SIGNAL
    //---------------------------------------------------------------------
    void HTTPRequest::httpReadyRead()
    {
        QNetworkReply * reply = qobject_cast<QNetworkReply *>(QObject::sender());

        emit finished(HTTPResponse(reply));
        delete reply;
    }


    //
    // UTILS METHOD FOR SERIALIZE QUERYPARAMS IN URL
    //---------------------------------------------------------------------
    QString HTTPRequest::serializeQueryParams(params queryParams)
    {
        QString res;

        if (queryParams.size() > 0)
        {
            res += "?";

            QMapIterator<QString, QString> it(queryParams);

            while (it.hasNext())
            {
                it.next();
                res += it.key() + "=" + it.value() + "&";
            }

            res.chop(1);
        }

        return res;
    }


    //
    // TRANSFORM URL PARAMS BY VALUES
    //---------------------------------------------------------------------
    QString HTTPRequest::transformUrlParams(params uriParams)
    {
        QString url = m_url;
        QMapIterator<QString, QString> it(uriParams);

        while (it.hasNext())
        {
            it.next();

            int start = url.indexOf(":" + it.key());

            if (start >= 0)
            {
                url.replace(start, it.key().size() + 1, it.value());
            }
        }

        return url;
    }
}
