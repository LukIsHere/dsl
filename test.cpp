#include "json.hpp"
#include <iostream>

using namespace dsl;

int main(){
    json j = json("{\"boolean\":true,\"number\":42,\"string\":\"Hello\",\"array\":[42]}");
    //json b = json("{\"hej\":2}");
    j["boolean"].getBoolean() = false;
    j["number"].getNumber()--;
    j["string"].getString() = "Hello World";
    j["array"][0].getNumber()++;
    //j["copy"] = b;
    std::cout << j << std::endl;
}