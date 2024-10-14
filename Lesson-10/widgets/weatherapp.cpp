#include "weatherapp.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>


WeatherApp::WeatherApp(QWidget* parent) : QWidget(parent)
{
    cityInput = new QLineEdit(this);
    cityInput->setPlaceholderText("Input city name:");

    getWeatherButton = new QPushButton("Get Weather", this);

    resultLabel = new QLabel("Result will be here", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(cityInput);
    layout->addWidget(getWeatherButton);
    layout->addWidget(resultLabel);

    setLayout(layout);

    networkManager = new QNetworkAccessManager(this);

    connect(getWeatherButton, &QPushButton::clicked, this, &WeatherApp::fetchWeather);// done

    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherApp::handleNetworkData);//todo
}

void WeatherApp::fetchWeather()
{
    QString cityName = cityInput->text().trimmed();

    if(cityName.isEmpty())
    {
        resultLabel->setText("Please input city name");
        return;
    }

    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
                      .arg(cityName, apiKey);

    networkManager->get(QNetworkRequest(QUrl(url)));
}

void WeatherApp::handleNetworkData(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        resultLabel->setText("error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    auto responseData = reply->readAll();
    reply->deleteLater();

    auto jsonDoc = QJsonDocument::fromJson(responseData);
    if(!jsonDoc.isObject())
    {
        resultLabel->setText("Invalid response from the server(");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    auto mainObj = jsonObj["main"].toObject();
    double temperature = mainObj["temp"].toDouble();
    double feelsLike = mainObj["feels_like"].toDouble();

    QJsonArray weatherArray = jsonObj["weather"].toArray();
    auto weatherObj = weatherArray[0].toObject();
    QString description = weatherObj["description"].toString();

    QString result = QString("Temperature: %1°C\nFeels like: %2\nWeather: %3")
                         .arg(temperature)
                         .arg(feelsLike)
                         .arg(description);

    resultLabel->setText(result);
}


/*
 * {
  "coord": {
    "lon": 30.5167,
    "lat": 50.4333
  },
  "weather": [
    {
      "id": 801,
      "main": "Clouds",
      "description": "few clouds",
      "icon": "02n"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 19.28,
    "feels_like": 19.61,
    "temp_min": 18.7,
    "temp_max": 19.29,
    "pressure": 1007,
    "humidity": 90,
    "sea_level": 1007,
    "grnd_level": 991
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.45,
    "deg": 222,
    "gust": 0.89
  },
  "clouds": {
    "all": 13
  },
  "dt": 1728660146,
  "sys": {
    "type": 2,
    "id": 2003742,
    "country": "UA",
    "sunrise": 1728620044,
    "sunset": 1728659690
  },
  "timezone": 10800,
  "id": 703448,
  "name": "Kyiv",
  "cod": 200
}
*/
