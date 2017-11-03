#include "websocket.h"

namespace Network
{
    //
    // CONSTRUCTOR
    //---------------------------------------------------------------------
    Websocket::Websocket(QString url, QObject *parent) : QObject(parent), m_url(url)
    {
        connect(&m_webSocket, &QWebSocket::connected, this, &onConnected);
    }


    //
    // SLOT CALL WHEN CONNECT HANDSHAKE IS MADE
    //---------------------------------------------------------------------
    void Websocket::onConnected()
    {
        connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &onTextMessageReceived);
        emit connected();
    }


    //
    // SLOT CALL WHEN MESSAGE IS RECEIVED
    //---------------------------------------------------------------------
    void Websocket::onTextMessageReceived(QString message)
    {
        bool ok;
        QJson::Parser parser;
        QVariantMap json = parser.parse(message.toUtf8(), &ok).toMap();

        if (ok)
        {
            QString eventName = json["t"].toString();
            emit received(eventName, json["a"].toList());
        }
    }


    //
    // OPEN CONNEXION WITH SERVER
    //---------------------------------------------------------------------
    void Websocket::open()
    {
        m_webSocket.open(m_url);
    }


    //
    // SEND AN EVENT
    //---------------------------------------------------------------------
    void Websocket::sendText(QString eventName, QString data)
    {
        m_webSocket.sendTextMessage("{ \"t\": \"" + eventName + "\", \"a\": [ " + data + " ] }");
    }

    void Websocket::sendBinary(QByteArray eventName, QByteArray data)
    {
        m_webSocket.sendBinaryMessage("{ \"t\": \"" + eventName + "\", \"a\": [ " + data + " ] }");
    }
}
