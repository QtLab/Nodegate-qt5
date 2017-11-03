#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "myapp.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext * ctx = engine.rootContext();
    MyApp myApp(ctx);

    engine.load(QUrl(QStringLiteral("qml/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
