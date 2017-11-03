#include "httpresponse.h"

namespace Network
{
    //
    // CONSTRUCTOR
    //---------------------------------------------------------------------
    HTTPResponse::HTTPResponse(QNetworkReply * reply)
    {
        m_status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        m_operation = reply->operation();
        m_data = reply->readAll();
    }


    //
    // GET STATUS
    //---------------------------------------------------------------------
    int HTTPResponse::status()
    {
        return m_status;
    }


    //
    // GET OPERATION
    //---------------------------------------------------------------------
    Method HTTPResponse::operation()
    {
        return m_operation;
    }


    //
    // GET DATA
    //---------------------------------------------------------------------
    QByteArray HTTPResponse::data()
    {
        return m_data;
    }
}
