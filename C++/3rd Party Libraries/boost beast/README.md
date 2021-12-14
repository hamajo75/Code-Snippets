# Boost Beast

## Documentation

- [Written Docu](https://www.boost.org/doc/libs/master/libs/beast/doc/html/index.html)
- [Quick Reference](https://www.boost.org/doc/libs/master/libs/beast/doc/html/beast/quickref.html)

Videos:
- [Get rich quick!](https://www.youtube.com/watch?v=7FQwAjELMek&t=2037s)

## Basic Concepts

### Buffers
See also [boost::asio](<../boost asio/README.md#Buffers>).

There are two concepts:
- `ConstBufferSequence`
- `MutableBufferSequence`

They allow transacting with multiple buffers in a single function call.

The following buffers are by definition `ConstBufferSequence` and `MutableBufferSequence`.
- [boost::asio::const_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/const_buffer.html)
- [boost::asio::mutable_buffer](https://www.boost.org/doc/libs/master/doc/html/boost_asio/reference/mutable_buffer.html)

The `DynamicBuffer` concept defines a resizable buffer sequence interface.
Examples are:
- `flat_buffer`

### Networking

- Connections are named `streams`. They are usually full duplex.
- Bytes arrive in the same order as they are sent.
- Beast is exclusively based on TCP/IP.

### Asynchronous I/O

- completion handler: `beast::bind_front_handler(&Session::on_write, shared_from_this())`
- I/O objects such as sockets and streams are not thread-safe.