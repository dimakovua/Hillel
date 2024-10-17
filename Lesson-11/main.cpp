#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Фонове застосування фільтра");
    window.resize(1920, 1080);
    window.show();

    return app.exec();
}
