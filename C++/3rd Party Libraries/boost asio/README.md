# Boost Asio

## Documentation

- [Tutorial](https://www.boost.org/doc/libs/master/doc/html/boost_asio/tutorial.html)

Videos

- [Asynchronous IO with Boost.Asio - cppcon 2016](https://www.youtube.com/watch?v=rwOv_tw2eA4)

## Basic Concepts

- You always need an io-context.

```C++
boost::asio::io_context io_context{};
// start event loop
io_context.run();
```