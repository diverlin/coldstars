#include "Message.hpp"

Message::Message(TELEGRAM type_id, const ID& sender_id, const ID& receiver_id, const std::string& extra, double delay)
    :
      type_id(type_id)
    , sender_id(sender_id)
    , receiver_id(receiver_id)
    , extra(extra)
    , delay(delay)
{}

//Message::Message(const Message& message)
//{
//    delay       = message.delay;
//    sender_id   = message.sender_id;
//    receiver_id = message.receiver_id;
//    type_id     = message.type_id;
//    extra       = message.extra;
//}


bool Message::operator<(const Message& rhs) const
{
    return (dispatch_time < rhs.dispatch_time);
}
