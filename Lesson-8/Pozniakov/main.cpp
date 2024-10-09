 #include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "appcore.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    AppCore appCore;

    const QUrl url(QStringLiteral("qrc:/Qt/main.qml"));
    engine.rootContext()->setContextProperty("appCore",&appCore);
    engine.load(url);

    return app.exec();
}
