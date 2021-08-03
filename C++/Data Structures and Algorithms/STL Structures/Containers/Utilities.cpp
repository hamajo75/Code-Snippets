#include <iostream>     // cout

#include <chrono>        // high_resolution_clock::now(), chrono::duration_cast
#include <thread>        // sleep_for

//#include <boost/chrono.hpp>

using namespace std;
//using namespace boost;

//------------------------------------------------------------------------------
chrono::milliseconds measureTime()
{
//    auto t1_ns = chrono::system_clock::now();
//    
//    //this_thread::sleep_for(1us);
//    
//    std::cout << "printing out 1000 stars...\n";
//    for (int i=0; i<1000; ++i) std::cout << "*";
//        std::cout << std::endl;
//    
//    auto t2_ns = chrono::high_resolution_clock::now();
//    return chrono::duration_cast<chrono::milliseconds>(t2_ns - t1_ns);          // this is not working on windows, use Boost Chrono
    
//    auto t1 = boost::chrono::system_clock::now();
//    
//    std::cout << "printing out 1000 stars...\n";
//    for (int i=0; i<1000; ++i) std::cout << "*";
//        std::cout << std::endl;
//    
//    auto t2 = boost::chrono::system_clock::now() - t1;
//    return boost::chrono::duration_cast<boost::chrono::milliseconds>(t2);
}
//------------------------------------------------------------------------------
bool test_Utilities()
{
    //std::cout << "time passed: " << measureTime().count() << "ns" << "\n";
    return true;
}
