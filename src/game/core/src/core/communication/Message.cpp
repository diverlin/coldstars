#include "Message.hpp"

#include <ceti/StringUtils.hpp>

#include <assert.h>

namespace comm {

Message::Message(Type type, const std::string& data, double delay)
    :
      m_type(type)
    , m_data(data)
    , m_delay(delay)
{}

bool Message::operator<(const Message& rhs) const
{
    return (m_dispatchTime < rhs.dispatchTime());
}

} // namespace comm
