#pragma once

#include <unordered_map>
#include "boost/asio.hpp"

class OpenWeatherMapClient
{
private:
    boost::asio::io_context         _io_context;
    boost::asio::ip::tcp::resolver  _resolver;
    boost::asio::ip::tcp::socket    _socket;
    std::string _key;

    void connect();
    void readAPIKey();
    std::string httpGetCurrentWeatherData(std::string& city);

public:
    OpenWeatherMapClient();
    ~OpenWeatherMapClient();

    std::unordered_map<std::string,std::string> getCurrenWeatherData(std::string city);

};



