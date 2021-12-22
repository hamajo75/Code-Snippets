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
## Multithreading

- Completion handlers are always called in the corresponding `io_context` thread (where the event loop is running).
- Don't call `async_write` (or other socket operations) on the same socket in different threads. Use a `strand` in order
  to avoid this (i think this is some kind of work queue).

### Strand
- [Asio Docu](https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/overview/core/strands.html)

`io_context::strand` allows for strictly sequential calls of event handlers in a multithreaded context without having to use extra locking mechanisms. Objects like sockets have implicit strands that can
be used via `ws_.get_executor()`.

When using asynchronous functions like `async_read()` or `async_write()`, all calls should go through the
same strand.

```cpp
boost::asio::bind_executor()
```