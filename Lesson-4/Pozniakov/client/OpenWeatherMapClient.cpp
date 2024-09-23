#include <iostream>
#include <fstream>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "OpenWeatherMapClient.h"


OpenWeatherMapClient::OpenWeatherMapClient() :
        _resolver(_io_context),
        _socket(_io_context)
{
    connect();
}

OpenWeatherMapClient::~OpenWeatherMapClient()
{
    if(_socket.is_open())
    {
        _socket.close();
    }
}

void OpenWeatherMapClient::connect()
{
    try
    {
        auto endpoint = _resolver.resolve("api.openweathermap.org","80");
        boost::asio::connect(_socket,endpoint);
        std::cout << "Connected to OpenWeatherMap server." << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
}

//http GET request
std::string OpenWeatherMapClient::httpGetCurrentWeatherData(std::string& city)
{
    try
    {
        std::string response;

        readAPIKey();

        boost::asio::write(_socket,boost::asio::buffer(
                "GET /data/2.5/weather?q=" + city + "&appid=" + _key + "&units=metric HTTP/1.1\r\n"
                                                                        "Host: api.openweathermap.org\r\n"
                                                                        "Connection: close\r\n\r\n"
        ));

        boost::system::error_code error;
        do
        {
            char buf[1024];
            std::size_t len = _socket.read_some(boost::asio::buffer(buf),error);

            if(!error || error == boost::asio::error::eof)
            {
                response.append(buf,len);
            }
        } while(!error);
        return response;
    }
    catch(std::exception& ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
    }
    return {};
}


//public method
std::unordered_map<std::string,std::string> OpenWeatherMapClient::getCurrenWeatherData(std::string city)
{
    std::string json =  httpGetCurrentWeatherData(city);
    auto json_start = json.find('{');

    if(!json.empty() || json_start != std::string::npos)
    {
        try
        {
            std::unordered_map<std::string,std::string> resultData;
            std::string response_code;
            std::string city_name;
            std::string temp;
            std::string feels_like;
            std::string wind;
            std::string main_weather;

            std::stringstream ss(json.substr(json_start));
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(ss,pt);

            response_code   = pt.get<std::string>("cod");
            if(response_code != "200")
            {
                throw std::runtime_error("Error! response cod: " + response_code
                    + "\nResponse body: " + json
                );
            }

            const auto weather_array = pt.get_child("weather");
            if(!weather_array.empty())
            {
                const auto first_elem = weather_array.begin()->second;
                main_weather = first_elem.get<std::string>("main");
            }

            city_name       = pt.get<std::string>("name");
            temp            = pt.get<std::string>("main.temp");
            feels_like      = pt.get<std::string>("main.feels_like");
            wind            = pt.get<std::string>("wind.speed");

            resultData["response_code"] = response_code;
            resultData["city_name"]     = city_name;
            resultData["temp"]          = temp;
            resultData["feels_like"]    = feels_like;
            resultData["wind"]          = wind;

            return resultData;
        }
        catch(std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }
    else std::cout << "Invalid JSON response.\n";
    return {};
}

void OpenWeatherMapClient::readAPIKey()
{
    std::ifstream file("key.txt");
    if(file.is_open())
    {
        _key.clear();
        std::getline(file,_key);
        file.close();
    }
}
