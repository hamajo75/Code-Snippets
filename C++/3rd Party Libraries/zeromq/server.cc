#include <zmq.hpp>

#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std::chrono_literals;
int main () {
    //  Prepare our context and socket
    int nr_threads;
    zmq::context_t context (nr_threads = 2);
    zmq::socket_t socket (context, zmq::socket_type::rep);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (request, zmq::recv_flags::none);
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
        std::this_thread::sleep_for(1000ms);

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply, zmq::send_flags::none);
    }
    return 0;
}