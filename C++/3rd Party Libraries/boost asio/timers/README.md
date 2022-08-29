# Boost Asio Timers

## Links
- https://dens.website/tutorials/cpp-asio/timers

## Types of timers
based on `boost::posix_time`
- `boost::asio::deadline_timer`

based on `std::chrono`
- `boost::asio::high_resolution_timer`
- `boost::asio::steady_timer`
- `boost::asio::system_timer`

## Member Functions
Set the timers expiration time:
- `expires_after` - duration
- `expires_at`- point in time

Cancel a timer (threadsafe):
- `timer.cancel()` - completion handler will receive: `boost::asio::error::operation_aborted`

