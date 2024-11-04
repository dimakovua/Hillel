//pmr (Polymorphic Memory Resource) 

// memory_resource
// #include <iostream>
// #include <memory_resource>
// #include <vector>
// #include <string>
// #include <chrono>


// std::string generateMessage(int id)
// {
//     return "Log occured on process " + std::to_string(id) + " on Module XYZ";
// }

// class LogManagerRegular
// {
//     public:
//     LogManagerRegular() 
//     {
//     }
    
//     void addLog(const std::string& message)
//     {
//         logs.emplace_back(message);
//     }

//     void processLogs() const
//     {
//         for(const auto& log : logs)
//         {
//             std::cout << log << "\n";
//         }
//     }

//     private:
//         std::vector<std::string> logs;
// };


// class LogManager
// {
//     public:
//     LogManager(std::pmr::memory_resource* memResource) 
//         : logs(memResource)
//         {
//         }
    
//     void addLog(const std::string& message)
//     {
//         logs.emplace_back(message);
//     }

//     void processLogs() const
//     {
//         for(const auto& log : logs)
//         {
//             std::cout << log << "\n";
//         }
//     }

//     private:
//         std::pmr::vector<std::pmr::string> logs;
// };


// void testWithPmr()
// {
//     std::byte buffer[1048576];
//     std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

//     LogManager logManager(&pool);

//     auto start = std::chrono::high_resolution_clock::now();

//     for(int i = 0; i < 10000; ++i)
//     {
//         logManager.addLog(generateMessage(i));
//     }

//     auto end = std::chrono::high_resolution_clock::now();

//     std::cout << "PMR Duration : " 
//               << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
//               << " ms\n";
// }


// void testWithReg()
// {
//     LogManagerRegular logManager;

//     auto start = std::chrono::high_resolution_clock::now();

//     for(int i = 0; i < 10000; ++i)
//     {
//         logManager.addLog(generateMessage(i));
//     }

//     auto end = std::chrono::high_resolution_clock::now();

//     std::cout << "Regular Duration : " 
//               << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
//               << " ms\n";
// }



// int main()
// {
//     testWithPmr();
//     testWithReg();
// }


#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory_resource> 

#include <random>


std::string generateRandomString(size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t max_index = sizeof(charset) - 1;
    std::string random_string(size, 0);
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, max_index - 1);

    for (size_t i = 0; i < size; ++i) {
        random_string[i] = charset[dist(rng)];
    }

    return random_string;
}


/**
 * @brief Tests the performance of using a polymorphic memory resource (PMR) with a monotonic buffer resource.
 * 
 * This function creates a buffer of 1 MB and uses it to initialize a monotonic buffer resource.
 * It then creates a PMR vector of PMR strings using this buffer resource.
 * The function measures the time taken to insert 100,000 log messages into the vector.
 * 
 * The duration of the operation is printed to the standard output in milliseconds.
 */
void testWithPmr() {
    std::byte buffer[1048576];  
    std::pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));
    std::pmr::vector<std::pmr::string> logs(&pool);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        logs.emplace_back("Log message number " + std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "PMR duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void testWithoutPmr() {
    std::vector<std::string> logs;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        logs.emplace_back("Log message number " + std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Standard duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    testWithoutPmr();
    testWithPmr();
    return 0;
}

/*
- <Event xmlns="http://schemas.microsoft.com/win/2004/08/events/event">
- <System>
  <Provider Name="Application Error" Guid="{a0e9b465-b939-57d7-b27d-95d8e925ff57}" /> 
  <EventID>1000</EventID> 
  <Version>0</Version> 
  <Level>2</Level> 
  <Task>100</Task> 
  <Opcode>0</Opcode> 
  <Keywords>0x8000000000000000</Keywords> 
  <TimeCreated SystemTime="2024-10-31T18:56:48.7286094Z" /> 
  <EventRecordID>436640</EventRecordID> 
  <Correlation /> 
  <Execution ProcessID="34448" ThreadID="19656" /> 
  <Channel>Application</Channel> 
  <Computer>LVIV-L80768.IMPRIVATA.com</Computer> 
  <Security UserID="S-1-5-21-1753436933-4115783883-2094863134-1001" /> 
  </System>
- <EventData>
  <Data Name="AppName">optional.exe</Data> 
  <Data Name="AppVersion">0.0.0.0</Data> 
  <Data Name="AppTimeStamp">6723d2ed</Data> 
  <Data Name="ModuleName">optional.exe</Data> 
  <Data Name="ModuleVersion">0.0.0.0</Data> 
  <Data Name="ModuleTimeStamp">6723d2ed</Data> 
  <Data Name="ExceptionCode">c00000fd</Data> 
  <Data Name="FaultingOffset">000000000000d187</Data> 
  <Data Name="ProcessId">0x9380</Data> 
  <Data Name="ProcessCreationTime">0x1db2bc6a335d2c0</Data> 
  <Data Name="AppPath">C:\Hillel\Lesson-16\optional.exe</Data> 
  <Data Name="ModulePath">C:\Hillel\Lesson-16\optional.exe</Data> 
  <Data Name="IntegratorReportId">9b626c68-6dc1-473a-83c2-3fbb4040940b</Data> 
  <Data Name="PackageFullName" /> 
  <Data Name="PackageRelativeAppId" /> 
  </EventData>
  </Event>


*/








/* PMR
#include <memory_resource>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::byte buffer[1024]; // кілобайт пам'яті

    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

    std::pmr::vector<std::pmr::string> words{&pool};



    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");
    words.emplace_back("hello");

    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";


}

*/