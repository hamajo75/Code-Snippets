#include <iostream>
#include <thread>
#include <vector>

#include "channel.h"
#include "message.h"
#include "object.h"

using namespace std;


int main() {
    Channel<Message> to_b;
    Channel<Message> to_a;

    Object a("A", 42, to_a, to_b);
    Object b("B", 64, to_b, to_a);

    thread thread_a{a};
    thread thread_b{b};

    Message print_repeated{MsgType::Execute, Object::print_repeated("==", 8)};
    Message get_value{MsgType::GetValue};

    vector<Message> messages{
        Message{MsgType::PrintHello},
        Message{MsgType::PrintMessage, "Hello, World!"},
        Message{MsgType::GetValue},
        Message{MsgType::Value, 3},
        Message{MsgType::Execute, Object::print_repeated(".", 10)},
        Message{MsgType::SendToOther, &print_repeated},
        Message{MsgType::SendToOther, &get_value}
    };

    to_a.send(messages);
    to_b.send(messages);
    
    thread_a.join();
    thread_b.join();
}
