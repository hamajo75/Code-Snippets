#include <iostream>
#include <string.h>

#include <nlohmann/json.hpp>

//-----------------------------------------------------------------------------
int main()
{
    // create a JSON array
    nlohmann::json j1 = {"one", "two", 3, 4.5, false};

    // create a copy
    nlohmann::json j2(j1);

    // serialize the JSON array
    std::cout << j1 << " = " << j2 << '\n';
    std::cout << std::boolalpha << (j1 == j2) << '\n';

    std::string json_str = R"(
{
  "messageHeader": {
    "messageType": "gasValues",
    "messageVersion": "1.0",
    "messageId": "e2ead843-0158-408b-8cd5-2497534be297",
    "createdAt": "2021-12-17T09:30:47.0"
  }}
    )";

    nlohmann::json j3 = nlohmann::json::parse(json_str);

    auto messageType = j3["messageHeader"]["messageType"];

    // auto hdr = j3.at("messageHeader").get();
    std::cout << messageType << "\n";
}
