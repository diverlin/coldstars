#include "Telegramm.hpp"

#include <ceti/StringUtils.hpp>

#include <assert.h>

namespace comm {

Telegramm::Telegramm(Type type, const std::string& data, double delay)
    :
      m_type(type)
    , m_data(data)
    , m_delay(delay)
{}

bool Telegramm::operator<(const Telegramm& rhs) const
{
    return (m_dispatchTime < rhs.dispatchTime());
}

} // namespace comm
