#pragma once

#include <string>

#include "channel.h"
#include "message.h"


// An Object that does something (it's just an example)
class Object {
  private:
    std::string name;
    int value;
    ReceivingChannel<Message>& inbox;
    SendingChannel<Message>& other;

    void print_hello();
    void print_message(std::string);
    void send_value();
    void print_value(int);
    void execute(ObjectMethod);
    void send_message(Message*);
    void _print_repeated(std::string, unsigned int);

  public:
    Object(
        std::string name, 
        int value,
        ReceivingChannel<Message>& inbox, 
        SendingChannel<Message>& other
    ): name{name}, value{value}, inbox{inbox}, other{other}
    {}

    // the execution loop of the object, 
    // which has to be run in a separate thread
    void operator()();

    static ObjectMethod print_repeated(std::string text, unsigned int count);
};
