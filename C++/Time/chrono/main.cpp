#include <iostream>
#include <thread>
#include <chrono>

#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

using namespace std::chrono_literals;   // i think you must do it like this

std::chrono::system_clock::time_point GetTimeFromTimestamp(const std::string& timestamp) {
  std::tm time_point{};
  std::istringstream ss(timestamp);
  ss >> std::get_time(&time_point, "%Y-%m-%dT%H:%M:%S");
  std::time_t t = std::mktime(&time_point);
  std::tm *utc_time = std::gmtime(&t);
  return std::chrono::system_clock::from_time_t(std::mktime(utc_time));
}
//-----------------------------------------------------------------------------
// only seconds
std::string GetTimestamp() {
  time_t now;
  time(&now);
  char buf[sizeof "2011-10-08T07:07:09"];
  strftime(buf, sizeof buf, "%FT%T", gmtime(&now));
  std::string timestamp_str{buf};
  return timestamp_str;
}
//-----------------------------------------------------------------------------
// using boost library
// #include <boost/date_time/posix_time/posix_time.hpp>
// std::string GetISO_8601_Timestamp_boost() {
//     auto t = boost::posix_time::microsec_clock::universal_time();
//     return boost::posix_time::to_iso_extended_string(t) + "Z";
// }
//-----------------------------------------------------------------------------
std::string currentISO8601TimeUTC() {
  auto now = std::chrono::system_clock::now();
  auto itt = std::chrono::system_clock::to_time_t(now);
  auto t = now.time_since_epoch();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t).count() -
            std::chrono::duration_cast<std::chrono::seconds>(t).count() * 1000;

  std::ostringstream ss;
  ss << std::put_time(std::gmtime(&itt), "%FT%T") << "." << ms;
  return ss.str();
}
//-----------------------------------------------------------------------------
void sleep_chrono_literals(std::chrono::duration<float> duration) {
  std::this_thread::sleep_for(duration);
}
//-----------------------------------------------------------------------------
void MeasureTime() {
  auto start = std::chrono::high_resolution_clock::now();

  sleep_chrono_literals(100ms);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));                  // this seems easier for me
// std::chrono::nanoseconds
// std::chrono::microseconds
// std::chrono::milliseconds
// std::chrono::seconds
// std::chrono::minutes

// std::chrono::hours

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Waited " << elapsed.count() << " ms\n";
}
//-----------------------------------------------------------------------------
void Print_ms_SinceEpoch() {
  std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count() << "\n";
}
void Timestamps() {
  // std::cout << GetTimestamp() << "\n";
  // std::cout << GetISO_8601_Timestamp() << "\n";
  // std::cout << GetISO_8601_Timestamp_boost() << "\n";
  // for (int i = 0; i < 2000; ++i){
  //   std::this_thread::sleep_for(std::chrono::milliseconds(1));
  //   std::cout << currentISO8601TimeUTC() << "\n";
  // }
}

void PrintTimeDifference(const std::string& timestamp) {
  auto now = std::chrono::system_clock::now();
  auto timestamp_time = GetTimeFromTimestamp(timestamp);
  std::cout << "seconds: " << std::chrono::duration_cast<std::chrono::seconds>(now - timestamp_time).count() << "\n";
}
//-----------------------------------------------------------------------------
int main() {
  // MeasureTime();
  // Print_ms_SinceEpoch();
  // Timestamps();
  PrintTimeDifference("4022-08-25T13:56:00.638Z");

  return 0;
}