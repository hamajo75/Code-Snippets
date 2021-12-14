# Boost Asio

## Documentation

- [Tutorial](https://www.boost.org/doc/libs/master/doc/html/boost_asio/tutorial.html)

Videos

- [Asynchronous IO with Boost.Asio - cppcon 2016](https://www.youtube.com/watch?v=rwOv_tw2eA4)

## Basic Concepts

- Uses **Proactor** pattern.
- You always need an io-context.

```cpp
boost::asio::io_context io_context{};
// start event loop
io_context.run();
```

- Use a **Strand** to synchronize multiple threads.

### Buffers

A buffer is a sequence of bytes represented by
- [boost::asio::const_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/const_buffer.html)
- [boost::asio::mutable_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/mutable_buffer.html)