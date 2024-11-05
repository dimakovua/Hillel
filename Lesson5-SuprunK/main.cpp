#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "counter.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Counter>("CustomComponents", 1, 0, "Counter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("/home/kate/Lesson5-SuprunK/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
