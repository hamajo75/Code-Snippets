#include "object.h"

#include <functional>
#include <iostream>
#include <mutex>

#include "channel.h"
#include "message.h"

using namespace std;


// for synchronized output
mutex output_mtx;

template<typename... Args>
void println(const Args&... args) {
    lock_guard lg{output_mtx};
    (cout << ... << args) << endl;
}


void Object::operator()() {
    while (true) {
        auto message = inbox.receive();
        println(name, ": got ", (string)message);

        switch (message.type) {
            case MsgType::PrintHello:
                print_hello();
                break;
            case MsgType::PrintMessage:
                print_message(get<std::string>(message.argument));
                break;
            case MsgType::GetValue:
                send_value();
                break;
            case MsgType::Value:
                print_value(get<int>(message.argument));
                break;
            case MsgType::Execute:
                execute(get<ObjectMethod>(message.argument));
                break;
            case MsgType::SendToOther:
                send_message(get<Message*>(message.argument));
                break;
        }
    }
}

void Object::print_hello() {
    println(name, ": Hello");
}

void Object::print_message(string message) {
    println(name, ": ", message);
}

void Object::send_value() {
    other.send(Message{MsgType::Value, value});
}

void Object::print_value(int value) {
    println(name, ": got value ", value);
}

void Object::execute(ObjectMethod method) {
    method(this);
}

void Object::send_message(Message* message) {
    other.send(*message);
}

void Object::_print_repeated(string text, unsigned int count) {
    string repeated = "";
    for (unsigned int i=0; i < count; i++) {
        repeated += text;
    }

    println(name, ": ", repeated);
}

ObjectMethod Object::print_repeated(string text, unsigned int count) {
    using namespace placeholders;

    return bind(&Object::_print_repeated, _1, text, count);
}

