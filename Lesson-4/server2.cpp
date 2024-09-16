// server.cpp
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

using boost::asio::ip::tcp;

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io_context, int port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        std::cout << "Server is running. Waiting for two connections..." << std::endl;
        startAccept();
    }

private:
    tcp::acceptor acceptor_;
    std::shared_ptr<tcp::socket> client1_;
    std::shared_ptr<tcp::socket> client2_;

    void startAccept() {
        client1_ = std::make_shared<tcp::socket>(acceptor_.get_executor());
        acceptor_.async_accept(*client1_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "First client connected!" << std::endl;
                acceptSecondClient();
            } else {
                std::cerr << "Error accepting first client: " << ec.message() << std::endl;
            }
        });
    }

    void acceptSecondClient() {
        client2_ = std::make_shared<tcp::socket>(acceptor_.get_executor());
        acceptor_.async_accept(*client2_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "Second client connected!" << std::endl;
                startChat();
            } else {
                std::cerr << "Error accepting second client: " << ec.message() << std::endl;
            }
        });
    }

    void startChat() {
        std::thread([this]() { readFromClient(client1_, client2_); }).detach();
        std::thread([this]() { readFromClient(client2_, client1_); }).detach();
    }

    void readFromClient(std::shared_ptr<tcp::socket> from, std::shared_ptr<tcp::socket> to) {
        while (true) {
            try {
                char data[1024] = {0};
                boost::system::error_code error;
                size_t length = from->read_some(boost::asio::buffer(data), error);

                if (error == boost::asio::error::eof) {
                    std::cout << "A client disconnected." << std::endl;
                    break; // Розрив з'єднання
                } else if (error) {
                    std::cerr << "Error reading from client: " << error.message() << std::endl;
                    break;
                }

                std::string message(data, length);
                std::cout << "Message from client: " << message << std::endl;

                // Надсилаємо повідомлення іншому клієнту
                boost::asio::write(*to, boost::asio::buffer(message), error);
                if (error) {
                    std::cerr << "Error sending to other client: " << error.message() << std::endl;
                    break;
                }
            } catch (std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                break;
            }
        }

        // Не закриваємо сокет автоматично, щоб сервер продовжував працювати з іншим клієнтом
        // Закриття виконується лише у випадку відключення клієнта (eof)
    }
};

int main() {
    try {
        boost::asio::io_context io_context;

        auto work_guard = boost::asio::make_work_guard(io_context);
        
        ChatServer server(io_context, 12345);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
