#include <iostream>
#include <string>

#include <cxxopts/include/cxxopts.hpp>

// //-------------------------------------------------------------------------------
// int main(int argc, char** argv) {
//     cxxopts::Options options("mmc", "Mock Message Client for sending and receiving messages.");

//     options.add_options()
//         ("send_receive", "first parameter", cxxopts::value<std::string>())
//         ("address", R"(e.g. //52.157.151.140:5671/wps_default)", cxxopts::value<std::string>())
//         ("bool", "", cxxopts::value<bool>())
//         // default value: value, when the option is not given on the cli
//         // value has to be a string !
//         ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
//         // implicit value: given on the cli without argument
//         // value has to be a string !
//         ("p,send-periodically", "Keep sending the message with optional interval in s (default is 0)",
//           cxxopts::value<double>()->implicit_value("0"))
//         ("h,help", "Print usage");

//     // this defines which params are positional (without "-" or "--")
//     options.parse_positional({"send_receive", "address"});

//     auto result = options.parse(argc, argv);

//     if (result.count("send_receive"))
//       std::cout << "send receive " << result["send_receive"].as<std::string>() << "\n";

//     if (result.count("help")) {                   // how often did it appear
//       options.custom_help("replace the [OPTION..] part with something like this: [-a][-d]");
//       options.positional_help("first second");
//       std::cout << options.help() << std::endl;
//       exit(0);
//     }
//     bool debug = result["debug"].as<bool>();
//     if (debug)
//       std::cout << "Debugging is enabled\n";
//     else
//       std::cout << "Debugging is disabled\n";

//     if (result.count("address")) {
//       auto address = result["address"].as<std::string>();
//       std::cout << "Address is: " << address << "\n";
//     }

//     return 0;
// }

//-------------------------------------------------------------------------------
int main(int argc, char** argv) {
  cxxopts::Options options("tester", " - test basic options");

  options.add_options()
    ("value", "an option with a value", cxxopts::value<std::string>())
    ("a,av", "a short option with a value", cxxopts::value<std::string>())
    ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
    ;

  auto result = options.parse(argc, argv);

  if (result.count("a")) {
    auto value = result["a"].as<std::string>();
    std::cout << value;
  }
  if (result.count("d")) {
    auto value = result["d"].as<std::bool>();
    std::cout << value;
  }
  return 0;
}