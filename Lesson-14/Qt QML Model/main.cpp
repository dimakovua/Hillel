#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mylistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MyListModel>("MyModule", 1, 0, "MyListModel");

    engine.load(QUrl::fromLocalFile("modelcpp/Main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
