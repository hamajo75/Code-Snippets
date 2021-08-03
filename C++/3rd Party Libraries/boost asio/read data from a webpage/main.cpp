#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include <chrono>

using namespace boost;
//-------------------------------------------------------------------------------
int main()
{	

	system::error_code ec;
	asio::io_context context;	// platform specific interface 

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("84.112.110.15", ec), 80);
	//asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

	// create a socket, context delivers the implementation
	asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, ec);

	if (!ec)
		std::cout << "Connected\n";
	else
	 	std::cout << "Failed to connect to: " + 
						endpoint.address().to_string() + 
						"\n" << ec.message() << "\n";
	
	
	if (socket.is_open())
	{
		std::string sRequest = 
			"GET /public_html/index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);	

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(200ms);

	 	size_t bytes = socket.available();
		std::cout << "Bytes available: " << bytes << "\n";

		if (bytes > 0)
		{
			std::vector<char> vBuffer(bytes);
			socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
			for(auto c : vBuffer)
				std::cout << c;
		}
	}

	return 0;
	
}




