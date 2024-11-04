#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <expected>

struct User
{
    std::string name;
    int age;
    std::optional<std::string> phone;
};

std::vector<User> users = 
{
    {"Alice", 30, "12-43-53-446"},
    {"Bob", 20, std::nullopt}
};

std::optional<User> findUser(const std::string& name)
{
    for(const auto& user : users)
    {
        if(user.name == name)
        {
            return user;
        }
    }

    return std::nullopt;
}

std::expected<std::string, std::string> getPhoneNumber(const std::optional<User>& user) noexcept
{   
    if(!user) 
    {
        return std::unexpected("User not found");
    }
    if(!user->phone.has_value())
    {
        return std::unexpected("User has not a phone");
    }

    return user->phone.value();
}

int main()
{
    auto result = getPhoneNumber(findUser("Bob"));
    if(result)
    {
        std::cout << "Bob's phone number: " << *result << "\n";
    }
    else{
        std::cout << "Error: " << result.error() << "\n";
    }

    result = getPhoneNumber(findUser("U"));
    if(result)
    {
        std::cout << "U's phone number: " << *result << "\n";
    }
    else{
        std::cout << "Error: " << result.error() << "\n";
    }

    result = getPhoneNumber(findUser("Alice"));
    if(result)
    {
        std::cout << "Alice's phone number: " << *result << "\n";
    }
    else{
        std::cout << "Error: " << result.error() << "\n";
    }

    return 0;
}

/* TUPLE AND PAIR
int main()
{

    std::tuple<int, double, std::string> t = {1, 2.0, "a"};

    std::cout << "First " << std::get<1>(t) << "\n";

    std::pair<int, std::string> p = {1, "Hello"};

    std::cout << "First element: " << p.first << "Second: " << p.second << "\n";
}
*/




/* ANY
void printAny(const std::any& param)
{
    if(param.type() == typeid(int))
    {
        std::cout << "Integer: " << std::any_cast<int>(param) << "\n";
    }
    else if(param.type() == typeid(std::string))
    {
        std::cout << "String: " << std::any_cast<std::string>(param) << "\n";
    }
    else{
        std::cout << "Unknown type :(\n";
    }
}

int main()
{
    std::any a = 10;
    printAny(a);

    a = std::string("Hello");
    printAny(a);

    a = 2.0;
    printAny(a);

    return 0;
}


*/



/* EXPECTED
std::expected<int, std::string> divide(int a, int b)
{
    if(b == 0) 
        return std::unexpected("Error: Division by zero");

    return a / b;
}

int main()
{
    auto result = divide(10, 0);
    
    if(result)
    {
        std::cout << *result << "\n";
    }
    else
    {
        std::cout << result.error() << "\n";
    }
}
*/











/* VARIANT
void process(const std::variant<int, std::string>& value)
{
    if(std::holds_alternative<int>(value))
    {
        std::cout << "Integer: " << std::get<int>(value) << "\n";
    }
    else if (std::holds_alternative<std::string>(value))
    {
        std::cout << "String: " << std::get<std::string>(value) << "\n";
    }
}

int main()
{
    std::variant<int, std::string> data = "Hello";
    process(data);

    data = 42;
    process(data);
}

*/









/* OPTIONAL
const std::vector<std::string> vec = {"a", "b", "c"};
// Returns id if found. Else returns -1
std::optional<size_t> findElement(std::string el) noexcept
{
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i] == el) return i;
    }

    return std::nullopt;
}

int main()
{
    auto result = findElement("e");

    if(result) std::cout << "Found " << *result << "\n";
    else std::cout << "Not found\n";
    size_t index;
    if(result.has_value()) index = result.value();

    size_t index1 = result.value_or(-1);

    return 0;
}

*/


