#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "counter.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Counter counter;

    engine.rootContext()->setContextProperty("counter", &counter);

    engine.load(QUrl::fromLocalFile("C:\\Users\\DK\\Documents\\HillelIntro\\Main.qml"));

    return app.exec();
}

//engine.load(QUrl::fromLocalFile("C:\\Users\\DK\\Documents\\HillelIntro\\Main.qml"));
