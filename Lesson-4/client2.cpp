// client.cpp
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
        std::cout << "Connected to server!" << std::endl;

        std::thread read_thread([&socket]() {
            while (true) {
                try {
                    char data[1024] = {0};
                    boost::system::error_code error;
                    size_t length = socket.read_some(boost::asio::buffer(data), error);

                    if (error == boost::asio::error::eof) {
                        std::cout << "Server closed the connection." << std::endl;
                        break; // Закриття з'єднання
                    } else if (error) {
                        std::cerr << "Error reading from server: " << error.message() << std::endl;
                        break;
                    }

                    std::string message(data, length);
                    std::cout << "Received from other client: " << message << std::endl;
                } catch (std::exception& e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                    break;
                }
            }
        });

        while (true) {
            //std::cout << "Enter message (type 'exit' to quit): ";
            std::string message;
            std::getline(std::cin, message);

            boost::asio::write(socket, boost::asio::buffer(message));
            // if (message == "exit") {
            //     break;
            // }
        }

        read_thread.join();

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
