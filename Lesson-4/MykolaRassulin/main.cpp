#include<iostream>
#include<boost/asio.hpp> //подключение библеотеки
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include<string>
#include<sstream>

using boost::asio::ip::tcp; //как бы пространство имен

//метод который посылает запрос 
std::string fetchWeather(const std::string& api_key, const std::string & city)
{
    try
    {
        //Set up
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::socket socket(io_context);

        //Reso;ve and connection
        auto endpoint = resolver.resolve("api.openweathermap.org", "80");
        boost::asio::connect(socket, endpoint);

        //Request
        boost::asio::write(socket, boost::asio::buffer(
            "GET /data/2.5/weather?q=" + city + "&appid=" + api_key + "&units=metric HTTP/1.1\r\n"
            "Host: api.openweathermap.org\r\n"
            "Connection: close\r\n\r\n"
            ));

        //Response
        std::string response;

        boost::system::error_code error;

        do
        {
            char buf[1024];
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if(!error || error == boost::asio::error::eof)
            {
                response.append(buf, len);
            }

        } while (!error);

        return response;
        
    }
    catch(std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
        return "";
    }
    
}

/*парсер получаемых данных*/
void parseAndPring(const std::string& json)
{
    try
    {
        auto json_start = json.find("{");
        if(json_start == std::string::npos)
        {
            std::cout << "Invalid Json response. Stopping. \n";
            return;
        }

        std::stringstream ss(json.substr(json_start));
        boost::property_tree::ptree pt;

        boost::property_tree::read_json(ss, pt);

        //получение название города
        std::string city = pt.get<std::string>("name");

        //Weather Array (масив помгоды)
        const boost::property_tree::ptree& weather_array = pt.get_child("weather");
        //проверка не пустойли он
        if(!weather_array.empty())
        {
            //получение первого элимента масива
            const boost::property_tree::ptree& first_element = weather_array.begin()->second;

            std::string main_weather = first_element.get<std::string>("main");

            //получение температуры
            double max_temp = pt.get<double>("main.temp_max"); //максимальная
            double temp = pt.get<double>("main.temp"); //средняя
            double min_temp = pt.get<double>("main.temp_min"); //минимальная температура

            //получение скорости ветра
            double wind_speed =pt.get<double>("wind.speed");

            //получение влажности воздуха
            double humid = pt.get<double>("main.humidity");

            //вывод

            std::cout << "City: " << city << "\nMain Weather: " << main_weather << "\n";
            std::cout << "Maximum temperature: " << max_temp << "\nAverage temperature: " << temp << "\nMinimum temperature: " << min_temp << "\n";
            std::cout << "Wind speed: " << wind_speed << " met/sec.\n";
            std::cout << "Air humidity: " << humid << " %\n";
        }
        else
        {
            std::cout << "Error! Empty Array!\n";
        }
    }
    catch(std::exception& ex)
    {
        std::cout << "Error!" << ex.what() << std::endl;
    }
    
}

int main()
{
    std::string api_key = "7ad3badbea5f46987365bc0d0716c57c"; // API ключь от сайта погоды
    std::string city = "Kyiv"; // название города по умолчанию
    bool ansver_1 = true;
    char ansver_2;

    //названия города
    std::cout << "Hello, to get a forecast,";
    while (ansver_1)
    {
        std::cout << "enter the city name: ";
        std::cin >> city;

        //запрос
        parseAndPring(fetchWeather(api_key, city));

        std::cout << "Do you want to know the weather in another city? (y/n): ";
        std::cin >> ansver_2;
        
        if(ansver_2 == 'n')
        {
            ansver_1 = false;
        }
    }
    
    return 0;
}