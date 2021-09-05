#include <iostream>
#include <string.h>
#include <map>

struct MyStruct {
  int i_;

  MyStruct() = default;              // remove this line -> compile error
  MyStruct(int i) : i_{i}{}
};

void InsertUserDefinedType() {
  MyStruct str{1};
  std::map<std::string, MyStruct> gas_detectors_;
  gas_detectors_["ARJJ-0002"] = str;  // to do this you need the default ctor above !!
}
//-------------------------------------------------------------------------------
std::string ReturnValue() {
  static std::map<std::string, std::string> msg_queue_map = {
  {"cameraControl.activateCameraLight", "camera_daemon_default"}};

  return msg_queue_map["hello"];
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
    std::map<int, int> memo;
    memo.insert({0, 1});
    memo.insert({1, 2});
    // easy creation of new entries
    memo[2] = 3;
    memo[3] = 4;

    memo.erase(3);                 // use key
    memo.erase(++memo.begin());    // use iterator

    std::cout << memo[0] << "\n";

    // C++ 17 way of looping through a map
    for(auto [first, second]: memo)
        std::cout << "first: " << first << " second: " << second << "\n";

    // no duplicate keys
    std::map<int, std::string> my_map;

    my_map[1] = "Bart";
    my_map[2] = "Lisa";
    my_map.insert(std::pair <int, std::string> (3, "Marge"));
    my_map.insert(std::pair <int, std::string> (4, "Homer"));

    std::cout << "non existing element: " << my_map[5] << "\n";

    std::map<int, std::string>::iterator it;

    // iterator - way of looping through a map
    for(it = my_map.begin(); it != my_map.end(); ++it)
    {
        std::cout << "Key: " << it->first << "\n";
        std::cout << "Value: " << it->second << "\n";
    }

    // initialize map
    std::map<std::string,int> myMap{{"Scott",1976}, {"Dijkstra",1972}};

    InsertUserDefinedType();

    return 0;
}




