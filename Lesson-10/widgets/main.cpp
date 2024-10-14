#include <QApplication>
#include "weatherapp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WeatherApp window;
    window.setWindowTitle("Пошук погоди");
    window.resize(300, 200);
    window.show();

    return app.exec();
}
