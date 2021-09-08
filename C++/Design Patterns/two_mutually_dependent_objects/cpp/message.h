#pragma once

#include <functional>
#include <string>
#include <variant>


// Types of Messages the objects can send each other 
enum class MsgType {
    PrintHello,
    PrintMessage,
    GetValue,
    Value,
    Execute,
    SendToOther
};

struct Object;
struct Message;

// for passing methods as arguments
using ObjectMethod = std::function<void(Object*)>;

// for passing various arguments along with the message
using Argument = std::variant<int, std::string, Message*, ObjectMethod>;

// Message the objects can send each other
struct Message {
    MsgType type;

    // to be able to transfer data depending on the type of the Message,
    // one could also use polymorphism
    Argument argument;

    operator std::string() {
        std::string type, argument;

        switch (this->type) {
            case MsgType::PrintHello:
                type = "PrintHello";
                argument = "None";
                break;
            case MsgType::PrintMessage:
                type = "PrintMessage";
                argument = "'" + std::get<std::string>(this->argument) + "'";
                break;
            case MsgType::GetValue:
                type = "GetValue";
                argument = "None";
                break;
            case MsgType::Value:
                type = "Value";
                argument = std::to_string(std::get<int>(this->argument));
                break;
            case MsgType::Execute:
                type = "Execute";
                argument = "Method";
                break;
            case MsgType::SendToOther:
                type = "SendToOther";
                argument = (std::string)*std::get<Message*>(this->argument);
                break;
        }

        return "Message {type: " + type + "; argument: " + argument + " }";
    }
};
