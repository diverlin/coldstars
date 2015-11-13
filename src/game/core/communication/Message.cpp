#include "Message.hpp"
#include <ceti/myStr.hpp>
#include <assert.h>

Message::Message(TELEGRAM type_id, const std::string& data, double delay)
    :
      type_id(type_id)
    , data(data)
    , delay(delay)
{}

bool Message::operator<(const Message& rhs) const
{
    return (dispatch_time < rhs.dispatch_time);
}

