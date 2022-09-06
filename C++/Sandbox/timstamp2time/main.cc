#include <iostream>
#include <string.h>
#include <cstdint>
#include <iostream>
#include <thread>
#include <chrono>

#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

std::chrono::system_clock::time_point GetTimeFromTimestamp(const std::string& timestamp) {
  std::tm time_point{};
  std::istringstream ss(timestamp);
  ss >> std::get_time(&time_point, "%Y-%m-%dT%H:%M:%S");
  if (ss.fail())
    std::cout << "couldn't parse input\n";

  std::time_t t = std::mktime(&time_point);

  std::cout << "time_point 2 time_t: " << std::ctime(&t) << "\n";

  std::tm *utc_time = std::gmtime(&t);

  auto tt = std::mktime(utc_time);
  std::cout << "utc time 2 time_t: " << std::ctime(&tt) << "\n";

  return std::chrono::system_clock::from_time_t(std::mktime(utc_time));
}

std::int64_t GetTimestampDifferenceToNow(const std::string& timestamp) {
  auto now = std::chrono::system_clock::now();

  auto tt = std::chrono::system_clock::to_time_t(now);
  std::cout << "now: " << std::ctime(&tt) << "\n";

  auto timestamp_time = GetTimeFromTimestamp(timestamp);
  tt = std::chrono::system_clock::to_time_t(timestamp_time);
  std::cout << "timestamp: " << std::ctime(&tt) << "\n";


  std::cout << "count(): " << std::chrono::duration_cast<std::chrono::seconds>(now - timestamp_time).count() << "\n";
  return std::chrono::duration_cast<std::chrono::seconds>(now - timestamp_time).count();
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  // MeasureTime();
  // Print_ms_SinceEpoch();
  // Timestamps();

  std::cout << "sizeof(time_t): " << sizeof(time_t) << "\n";
  std::cout << "sizeof(std::time_t): " << sizeof(std::time_t) << "\n";

  auto timestamp = argc > 1 ? argv[1] : "4022-08-25T13:56:00.638Z";
  std::cout << "seconds: " << GetTimestampDifferenceToNow(timestamp) << "\n";

  return 0;
}