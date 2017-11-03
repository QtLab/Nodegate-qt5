#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <qjson/parser.h>
#include <QVariant>
#include <QUrl>
#include <QMap>
#include <functional>


namespace Network
{
    class Websocket : public QObject
    {
        Q_OBJECT

    public:
        Websocket(QString url, QObject * parent = nullptr);

    private slots:
        void            onConnected();
        void            onTextMessageReceived(QString message);

    signals:
        void            connected();
        void            received(QString, QVariantList);

    public:
        void            open();

        void            sendText(QString eventName, QString data);
        void            sendBinary(QByteArray eventName, QByteArray data);

    private:
        QWebSocket      m_webSocket;
        QUrl            m_url;
    };
}

#endif // WEBSOCKET_H
