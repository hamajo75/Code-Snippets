#include <iostream>
#include <string.h>

#include <nlohmann/json.hpp>

std::string json_msg = R"(
{
  "messageHeader": {
    "messageType": "gd.periodical.gasValues",
    "messageVersion": "1.0",
    "messageId": "c832655d-8f87-4c6f-b60b-e51250dbdfe3",
    "createdAt": "2021-08-30T08:55:56.420Z"
  },
  "messageBody": {
    "gasValues": [
    {
      "physicalDeviceId": "00:11:22:33:FF:01",
      "measurementTimestamp": "2021-12-17T09:30:47.000Z",
      "sensorChannels": [
        {
          "channelNumber": 0,
          "gasType": "ch4",
          "gasUnit": "%UEG",
          "gasValue": "0"
        },
        {
          "channelNumber": 2,
          "gasType": "O2",
          "gasUnit": "Vol%",
          "gasValue": "20.9"
        },
        {
          "channelNumber": 3,
          "gasType": "CO",
          "gasUnit": "ppm",
          "gasValue": "0"
        },
        {
          "channelNumber": 4,
          "gasType": "H2S",
          "gasUnit": "ppm",
          "gasValue": "0"
        }
      ]
    },
    {
      "physicalDeviceId": "00:11:22:33:FF:02",
      "measurementTimestamp": "2021-12-17T09:31:47.000Z",
      "sensorChannels": [
        {
          "channelNumber": 0,
          "gasType": "ch4",
          "gasUnit": "%UEG",
          "gasValue": "0"
        },
        {
          "channelNumber": 2,
          "gasType": "O2",
          "gasUnit": "Vol%",
          "gasValue": "20.9"
        },
        {
          "channelNumber": 3,
          "gasType": "CO",
          "gasUnit": "ppm",
          "gasValue": "0"
        },
        {
          "gasType": "H2S",
          "gasUnit": "ppm",
          "gasValue": "0"
        }
      ]
    }
    ]
  }
}
  )";

void ConvertMessage(const std::string& msg) {
  nlohmann::json j_in = nlohmann::json::parse(msg);
  nlohmann::json j_out;

  j_out["messageHeader"] = "Header";

  auto gasValues = j_in["messageBody"]["gasValues"];
  for (auto gasValue : gasValues) {
    nlohmann::json j;
    j["gasDetectorId"] = "e0a074f1-f321-4910-a5a5-5a721ba7f44a";
    j["measurementTimestamp"] = "2021-12-17T09:30:47.000";

    for (auto sensorChannel : gasValue["sensorChannels"])
      j["sensorChannels"].push_back(sensorChannel);

    j_out["messageBody"]["gasValues"].push_back(j);
  }

  // check if a field exists
  if (j_in.find("periodic_workplace_state_send_interval") != j_in.end())
    j_out["periodic_workplace_state_send_interval"] = 100;

  std::cout << j_out;
}

void BasicStuff() {
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

void ObjectCreation() {
  // write it almost like json text file:
  // nlohmann::json j_object = {
  //   {"pi", 3.141},
  //   {"happy", true},
  //   {"name", "Niels"},
  //   {"nothing", nullptr},
  //   {"answer", {
  //     {"everything", 42}
  //   }},
  //   {"list", {1, 0, 2}},
  //   {"object", {
  //     {"currency", "USD"},
  //     {"value", 42.99}
  //   }}
  // };
  nlohmann::json j_object = {
    {"url", "172.31.1.83:5671"},
    {"ConnectionOptions", {
      {"reconnect", true},
      {"Credentials", {
        {"user", "intercom-123"},
        {"password", "intercom-123"}
      }}
      },
      {"SSL", {
        {"ssl_path", "../../intercom_daemon/ssl-certs/"},
        {"ssl_client_certificate", "intercom-123.cert.pem"},
        {"ssl_client_private_key", "intercom-123.key.pem"},
        {"ssl_broker_certificate", "ccs_dev_ca.pem"}
      }}
    }
  };

  std::cout << j_object << "\n";

  nlohmann::json j_object2;
  j_object2["url"] = "172.31.1.83:5671";
  j_object2["ConnectionOptions"] = {{"reconnect", true}, {"Credentials", {{"user", "123"}, {"password, 123"}}}};
  if (j_object2.find("url") != j_object2.end())
    std::cout << "url found: " << j_object2["url"] << "\n";


  // create from string
  std::string json_str = R"(
      {
        "url": "172.31.1.83:5671",
        "ConnectionOptions": {
          "reconnect": true,
          "Credentials": {
            "user": "intercom-123",
            "password": "intercom-123"
          },
          "SSL": {
            "ssl_path": "../../intercom_daemon/ssl-certs/",
            "ssl_client_certificate": "intercom-123.cert.pem",
            "ssl_client_private_key": "intercom-123.key.pem",
            "ssl_broker_certificate": "ccs_dev_ca.pem"
          }
        }
      }
  )";
  nlohmann::json j_object3 = nlohmann::json::parse(json_str);
}

//-----------------------------------------------------------------------------
int main()
{
  BasicStuff();
  ObjectCreation();
  // ConvertMessage(json_msg);
}
