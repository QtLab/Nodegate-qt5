#include <QDebug>
#include <QMap>
#include <qjson/parser.h>

#include "myapp.h"


MyApp::MyApp(QQmlContext * ctx, QObject *parent) : m_ctx(ctx), QObject(parent)
{
    m_us.list();

    m_ctx->setContextProperty("us", &m_us);
}
