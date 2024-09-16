cmake_minimum_required(VERSION 3.10)
project(BoostServerClient)

# Пошук пакету Boost
find_package(Boost 1.86 REQUIRED COMPONENTS system)

# Перевірка, чи Boost знайдено
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})  # Додавання шляхів до заголовків
    link_directories(${Boost_LIBRARY_DIRS})     # Додавання шляхів до бібліотек
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Створення виконавчих файлів серверу і клієнта
add_executable(server server.cpp)
add_executable(client client.cpp)

# Підключення бібліотек Boost до проєкту
target_link_libraries(server Boost::system)
target_link_libraries(client Boost::system)
