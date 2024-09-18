#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        // Створення TCP-акцептора, що слухає підключення на порту 12345
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
        std::cout << "Server is running. Waiting for connections..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket); // Очікування підключення клієнта BLOCKING
        std::cout << "Client connected!" << std::endl;

        // Прийом даних від клієнта
        char data[1024];
        size_t length = socket.read_some(boost::asio::buffer(data));
        std::cout << "Received: " << std::string(data, length) << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
