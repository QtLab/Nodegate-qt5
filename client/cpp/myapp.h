#ifndef MYAPP_H
#define MYAPP_H

#include <QObject>
#include <QVariant>
#include <QQmlContext>

#include "services/usersservice.h"

class MyApp : public QObject
{
    Q_OBJECT

public:
    explicit MyApp(QQmlContext * ctx, QObject * parent = nullptr);

private :
    UsersService       m_us;
    QQmlContext *      m_ctx;
};

#endif // MYAPP_H
