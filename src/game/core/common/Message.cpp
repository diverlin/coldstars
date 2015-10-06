#include "Message.hpp"

Message::Message(TELEGRAM type_id, const IDTYPE& sender_id, const IDTYPE& receiver_id, void* extra)
    :
      type_id(type_id)
    , sender_id(sender_id)
    , receiver_id(receiver_id)
    , extra(extra)
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
