#include <iostream>
#include <boost/asio.hpp>

//-------------------------------------------------------------------------------
// callback function, called asynchronously 
void print(const boost::system::error_code&)
{
	std::cout << "Asynchronous operation finished \n";
	std::cout << "Timer expired\n";
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	boost::asio::io_context io_context;
	boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(5));
	
	// non blocking wait, immediately return
	timer.async_wait(&print);
	std::cout << "Waiting for timer\n";

	// callback handlers will only be called from threads running io_context.run()
 	io_context.run();  // runs while there is work to do

	return 0;	
}




