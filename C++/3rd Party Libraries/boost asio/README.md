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
- [Buffers in boost](https://www.boost.org/doc/libs/1_77_0/doc/html/boost_asio/overview/core/buffers.html)

A buffer is a sequence of bytes represented by
- [boost::asio::const_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/const_buffer.html)
- [boost::asio::mutable_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/mutable_buffer.html)

```cpp
boost::asio::const_buffer cb("Hello, world!", 13);

char storage[13];
net::mutable_buffer mb(storage, sizeof(storage));
std::memcpy(mb.data(), cb.data(), mb.size());
```

### Vectored IO or Scatter/Gather IO

Gather data from, scatter data into multiple buffers.

A single function call either
- reads from multiple buffers and writes to a single stream, or
- reads from a single stream and writes to multiple buffers (vector of buffers)

Usually done for efficiency.
