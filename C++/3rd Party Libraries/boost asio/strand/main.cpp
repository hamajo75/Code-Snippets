#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <deque>
#include <iostream>
#include <string>

class Connection {
public:
  Connection(boost::asio::io_service &io_service)
      : _io_service(io_service), _strand(_io_service), _socket(_io_service),
        _outbox() {}

  void write(const std::string &message) {
    _strand.post(boost::bind(&Connection::writeImpl, this, message));
  }

 private:
  void writeImpl(const std::string &message) {
    _outbox.push_back(message);
    if (_outbox.size() > 1) {
      // outstanding async_write
      return;
    }

    this->write();
  }

  void write() {
    const std::string &message = _outbox[0];
    boost::asio::async_write(
        _socket, boost::asio::buffer(message.c_str(), message.size()),
        _strand.wrap(boost::bind(
            &Connection::writeHandler, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)));
  }

  void writeHandler(const boost::system::error_code &error,
                    const size_t bytesTransferred) {
    _outbox.pop_front();

    if (error) {
      std::cerr << "could not write: "
                << boost::system::system_error(error).what() << std::endl;
      return;
    }

    if (!_outbox.empty()) {
      // more messages to send
      this->write();
    }
  }

 private:
  typedef std::deque<std::string> Outbox;

 private:
  boost::asio::io_service &_io_service;
  boost::asio::io_service::strand _strand;
  boost::asio::ip::tcp::socket _socket;
  Outbox _outbox;
};

int main() {
  boost::asio::io_service io_service;
  Connection foo(io_service);
}