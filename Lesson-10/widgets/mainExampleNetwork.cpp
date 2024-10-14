#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

int main1(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QNetworkAccessManager manager; // відповідає за всі запроси та доступ в інтернет
    QNetworkRequest request(QUrl("https://jsonplaceholder.typicode.com/todos/1")); // куди кидається запит

    QObject::connect(&manager, &QNetworkAccessManager::finished, [](QNetworkReply* reply){ // що робимо після запиту
        if(reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Response: " << reply->readAll();
        }
        else qDebug() << "Error: " << reply->errorString();

        reply->deleteLater(); // робимо delete reply коли reply вже не юзається
    });

    manager.get(request); // кидається запит

    return app.exec(); // головний цикл
}


/*.
 * {
  "userId": 1,
  "id": 1,
  "title": "delectus aut autem",
  "completed": false
}
*/
