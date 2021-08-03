#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>


// The interface for the sending end of a Channel
template<typename T>
class SendingChannel {
  public:
    // send one or multiple Messages
    virtual void send(const std::vector<T>&) = 0;
    virtual void send(T) = 0;

    virtual ~SendingChannel() = default;
};


// The interface for the receiving end of a Channel
template<typename T>
class ReceivingChannel {
  public:
    // returns the Message, when the Message was received
    virtual T receive() = 0;

    virtual ~ReceivingChannel() = default;
};


// The implementation for a whole Channel
template<typename T>
class Channel: public SendingChannel<T>, public ReceivingChannel<T> {
  private:
    std::queue<T> msgs{};
    std::mutex channel_mtx{};
    std::condition_variable receiving_finishable{};

  public:
    bool is_empty() const { return msgs.empty(); }
    bool is_not_empty() const { return !is_empty(); }

    void send(const std::vector<T>& new_msgs) override {
        std::lock_guard channel_lck{channel_mtx};

        for (auto msg: new_msgs) {
            msgs.push(std::move(msg));
        }
        receiving_finishable.notify_all();
    }

    void send(T msg) override {
        std::lock_guard channel_lck{channel_mtx};

        msgs.push(std::move(msg));
        receiving_finishable.notify_one();
    }

    T receive() override {
        std::unique_lock channel_lck{channel_mtx};
        receiving_finishable.wait(
            channel_lck, 
            [this](){ return is_not_empty(); }
        );

        T msg{std::move(msgs.front())};
        msgs.pop();

        return msg;
    }
};
