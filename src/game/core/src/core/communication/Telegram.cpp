#include "Telegram.hpp"

#include <ceti/StringUtils.hpp>

#include <assert.h>

namespace core {

Telegram::Telegram(telegram::Type type, const std::string& data, double delay)
    :
      m_type(type)
    , m_data(data)
    , m_delay(delay)
{}

bool Telegram::operator<(const Telegram& rhs) const
{
    return (m_dispatchTime < rhs.dispatchTime());
}

} // namespace core
