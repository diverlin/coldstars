#include "TelegrammManager.hpp"

#include <jeti/particlesystem/Explosion.hpp>

namespace client {
namespace comm {

namespace {

bool createExplosionEffectEvent(const core::comm::Telegramm& telegramm) {
//    descriptor::comm::effect::Explosion descriptor(telegramm.data());
//    jeti::particlesystem::Explosion* explosion = jeti::particlesystem::genExplosion(descriptor.size());
//    client::global::get().view().add(explosion, descriptor.position());
    return true;
}

} // namespace

bool TelegrammManager::_process(const core::comm::Telegramm& telegramm)
{
    if (core::comm::TelegrammManager::_process(telegramm)) {
        return true;
    }

    switch(telegramm.type()) {
    case core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT: return createExplosionEffectEvent(telegramm);
    }

    assert(false);
    return false;
}

} // namespace comm
} // namespace client


