#include "Telegramm.hpp"

#include <ceti/StringUtils.hpp>

#include <assert.h>

namespace core {
namespace comm {

Telegramm::Telegramm(telegramm::Type type, const std::string& data, double delay)
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
} // namespace core
