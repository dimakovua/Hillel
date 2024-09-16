// main.cpp
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>
#include <sstream>

using boost::asio::ip::tcp;

// Функція для відправки запиту до OpenWeather API і отримання відповіді
std::string fetchWeather(const std::string& api_key, const std::string& city) {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::socket socket(io_context);

        // Резолвимо адресу і підключаємося до сервера
        boost::asio::connect(socket, resolver.resolve("api.openweathermap.org", "80"));

        // Формуємо і відправляємо запит однією командою
        boost::asio::write(socket, boost::asio::buffer(
            "GET /data/2.5/weather?q=" + city + "&appid=" + api_key + "&units=metric HTTP/1.1\r\n"
            "Host: api.openweathermap.org\r\n"
            "Connection: close\r\n\r\n"
        ));

        // Отримання відповіді
        std::string response;
        boost::system::error_code error;
        do {
            char buf[1024];
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (!error || error == boost::asio::error::eof) {
                response.append(buf, len);
            }
        } while (!error);

        return response;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}

// Функція для парсингу JSON і виводу необхідної інформації
void parseWeatherJson(const std::string& json) {
    try {
        // Знаходимо початок JSON в відповіді
        auto json_start = json.find('{');
        if (json_start == std::string::npos) {
            std::cerr << "Invalid JSON response" << std::endl;
            return;
        }

        std::stringstream ss(json.substr(json_start));  // Створюємо stream з JSON частини відповіді
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);  // Читаємо JSON в дерево властивостей

        // Дістаємо назву міста
        std::string city = pt.get<std::string>("name");

        // Отримуємо масив weather
        const boost::property_tree::ptree& weather_array = pt.get_child("weather");

        // Перевіряємо, що масив не пустий
        if (!weather_array.empty()) {
            // Отримуємо перший елемент масиву
            const boost::property_tree::ptree& first_weather = weather_array.begin()->second;
            std::string weather_main = first_weather.get<std::string>("main");

            // Дістаємо температуру
            double temperature = pt.get<double>("main.temp");

            // Виводимо необхідну інформацію
            std::cout << "City: " << city << std::endl;
            std::cout << "Weather: " << weather_main << std::endl;
            std::cout << "Temperature: " << temperature << "°C" << std::endl;
        } else {
            std::cerr << "Weather array is empty." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}


int main() {
    std::string api_key = "8915429fcf6a68275f7c20caab444827"; // Замініть "YOUR_API_KEY" на дійсний ключ
    std::string city = "Kyiv";            // Заміни на своє місто

    std::string response = fetchWeather(api_key, city);
    parseWeatherJson(response);
    return 0;
}
