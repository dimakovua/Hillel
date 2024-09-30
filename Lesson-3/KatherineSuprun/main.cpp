#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>
#include <sstream>

using boost::asio::ip::tcp;

std::string readApiKey(const std::string& config) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(config, pt);
    return pt.get<std::string>("API_KEY");
}

std::string fetchWeather(const std::string& api_key, const std::string& city)
{
    try
    {
        // Set up
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::socket socket(io_context);

        // Resolve and connection
        auto endpoint = resolver.resolve("api.openweathermap.org", "80");
        boost::asio::connect(socket, endpoint);

        // Request
        boost::asio::write(socket, boost::asio::buffer(
            "GET /data/2.5/weather?q=" + city + "&appid=" + api_key + "&units=metric HTTP/1.1\r\n"
            "Host: api.openweathermap.org\r\n"
            "Connection: close\r\n\r\n"
        ));

        // Response

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

void parseAndPrint(const std::string& json)
{
    try
    {
        auto json_start = json.find('{');
        if(json_start == std::string::npos)
        {
            std::cout << "Invalid JSON response. Stopping.\n";
            return;
        }

        std::stringstream ss(json.substr(json_start));
        boost::property_tree::ptree pt;

        boost::property_tree::read_json(ss, pt);

        // Getting city name
        std::string city = pt.get<std::string>("name");

        // Weather Array
        const boost::property_tree::ptree& weather_array = pt.get_child("weather");

        if(!weather_array.empty())
        {
            // Get first element
            const boost::property_tree::ptree& first_element = weather_array.begin()->second;

            std::string main_weather = first_element.get<std::string>("main");
            
            // Get temp

            double temp = pt.get<double>("main.temp");

            std::cout << "City: " << city << "\nMain Weather: " << main_weather << "\nTemp: " << temp << "\n";
        }
        else
        {
            std::cout << "Error! Empty Array!\n";
        }
    }
    catch(std::exception& ex)
    {   
        std::cout << "Error! " << ex.what() << std::endl;
    }
}

int main()
{
    std::string api_key = readApiKey("config.json"); 
    std::string city = "Kyiv";

    parseAndPrint(fetchWeather(api_key, city));

    return 0;
}
