#ifndef USERSSERVICE_H
#define USERSSERVICE_H

#include <QObject>

#include "qjson/parser.h"
#include "../utils/network/service.h"


class UsersService : public QObject
{
    Q_OBJECT

public:
    UsersService(QObject * parent = nullptr);

    Q_INVOKABLE void                    create(QString username, QString password);
    Q_INVOKABLE void                    read(int id);
    Q_INVOKABLE void                    list();

signals:
    void                                usersListReceived(QVariant users);
    void                                userReadReceived(QVariant user);

private slots:
    void                                users(Network::HTTPResponse);
    void                                user(Network::HTTPResponse);

private:
    Network::Service                    m_service;
    Network::HTTPRequest *              m_users;
    Network::HTTPRequest *              m_user;
};

#endif // USERSSERVICE_H
