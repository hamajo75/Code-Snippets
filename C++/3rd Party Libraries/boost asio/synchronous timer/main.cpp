#include <iostream>
#include <boost/asio.hpp>

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	boost::asio::io_context io_context;
	boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(5));

	std::cout << "Waiting for timer\n";
	// blocking wait
	timer.wait();
	
	std::cout << "Timer expired\n";

	return 0;	
}




