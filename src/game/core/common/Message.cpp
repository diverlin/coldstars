#include "Message.hpp"

Message::Message(double delay, int sender_id, int receiver_id, int type_id, void* extra)
{
    this->delay       = delay;
    this->sender_id   = sender_id;
    this->receiver_id = receiver_id;
    this->type_id     = type_id;
    this->extra       = extra;
}

Message::Message(const Message& message)
{
    this->delay       = message.delay;
    this->sender_id   = message.sender_id;
    this->receiver_id = message.receiver_id;
    this->type_id     = message.type_id;
    this->extra       = message.extra;
}


bool Message::operator<(const Message& rhs) const
{
    return (this->dispatch_time < rhs.dispatch_time);
}
