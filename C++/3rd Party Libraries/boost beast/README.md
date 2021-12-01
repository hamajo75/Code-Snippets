# Boost Beast

## Documentation

- [Written Docu](https://www.boost.org/doc/libs/master/libs/beast/doc/html/index.html)
- [Quick Reference](https://www.boost.org/doc/libs/master/libs/beast/doc/html/beast/quickref.html)

Videos:
- [Get rich quick!](https://www.youtube.com/watch?v=7FQwAjELMek&t=2037s)

## Basic Concepts

### Buffers

ConstBufferSequence
MutableBufferSequence
DynamicBuffer - resizable

### Networking

- Connections are named `streams`. They are usually full duplex.
- Bytes arrive in the same order as they are sent.
- Beast is exclusively based on TCP/IP.

### Asynchronous I/O

- completion handler: `beast::bind_front_handler(&Session::on_write, shared_from_this())`
- I/O objects such as sockets and streams are not thread-safe.