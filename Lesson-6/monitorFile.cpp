#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include <string>

std::mutex mtx;
std::condition_variable cv;
bool fileChanged = false;


void watchFile(std::filesystem::path filePath)
{
    try
    {
        auto lastWriteTime = std::filesystem::last_write_time(filePath);

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            auto currentWriteTime = std::filesystem::last_write_time(filePath);

            if(lastWriteTime != currentWriteTime)
            {
                lastWriteTime = currentWriteTime;

                std::unique_lock<std::mutex> lock(mtx);

                fileChanged = true;
                cv.notify_all();
            }
        }
    }
    catch(std::exception& ex)
    {
        std::cout << "Exception! " << ex.what();
    }
}

void printFile(std::filesystem::path filePath)
{
    try
    {
        std::unique_lock<std::mutex> lock(mtx);

        while(true)
        {
            cv.wait(lock, [] { return fileChanged; }); // wait for file to be changed
            fileChanged = false;

            std::ifstream file(filePath);

            if(file.is_open())
            {
                std::cout << "File was changed! New file: \n";

                std::string line;

                while(std::getline(file, line))
                {
                    std::cout << line << std::endl;
                }
                std::cout << "====================\n";
                file.close();
            }
            else
            {
                std::cerr << "Couldn't open the file!\n";
            }

        }
    }
    catch(std::exception& ex)
    {
        std::cout << "Exception! " << ex.what();
    }
}

int main()
{
    std::filesystem::path filePath = "../aboba.txt";

    //create 2 threads
    std::thread watcher(watchFile, filePath);
    std::thread printer(printFile, filePath);

    watcher.join();
    printer.join();


    return 0;
}

