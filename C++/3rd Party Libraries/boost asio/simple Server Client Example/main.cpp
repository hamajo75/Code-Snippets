#include <iostream>
#include <boost/asio.hpp>

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{	

	if(argc != 3)
	{
		std::cout << "Wrong number of parameters\n" << "Example: 127.0.0.1 1234\n";
	}

	auto const address = boost::asio::ip::make_address(argv[1]);
	auto const port = std::atoi(argv[2]);

	boost::asio::io_service io_service;
	
	boost::system::error_code error;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(address, port));
	boost::asio::ip::tcp::socket socket(io_service);
	acceptor.accept(socket);	// wait for message from client

	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, "\n", error);
	if (error)
	{
		std::cout << error.message() << std::endl;
		return -1;
	}
	std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
	std::cout << data << std::endl;

	boost::asio::write(socket, boost::asio::buffer(data), error);
	if (error)
	{
		std::cout << error.message() << std::endl;
		return -1;
	}

	return 0;
	
}




