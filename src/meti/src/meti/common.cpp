#include "common.hpp"

#include <algorithm>
      
namespace meti {

float clamp(float x, float lower, float upper)
{
    return std::min(std::max(x, lower), upper);
}

} // namespace meti
