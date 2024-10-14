#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherApp : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherApp(QWidget *parent = nullptr);

private slots:
    void fetchWeather(); // get weather
    void handleNetworkData(QNetworkReply* reply);

private:
    QLineEdit *cityInput;
    QPushButton *getWeatherButton;
    QLabel *resultLabel;
    QNetworkAccessManager *networkManager;

    QString apiKey = "8915429fcf6a68275f7c20caab444827";

};
