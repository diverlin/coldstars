#include "TelegrammManager.hpp"

//#include <common/Global.hpp>
//#include <core/manager/EntityManager.hpp>

//#include <common/constants.hpp>

//#include <core/type/EntityType.hpp> // test

//#include <core/descriptor/comm/Hit.hpp>
//#include <core/descriptor/comm/Dock.hpp>
//#include <core/descriptor/comm/AddToStarsystemDescriptor.hpp>

//#include <core/manager/DescriptorManager.hpp>
//#include <core/manager/Garbage.hpp>

//#include <core/descriptor/Base.hpp>
//#include <core/descriptor/comm/Creation.hpp>

//#include <core/generator/DescriptorGenerator.hpp>
//#include <core/descriptor/spaceobject/Container.hpp> // ??
//#include <core/descriptor/ExplosionDescriptor.hpp>

//#include <core/spaceobject/ALL>
//#include <core/item/equipment/Weapon.hpp>

//#include <core/world/starsystem.hpp>
//#include <core/world/HyperSpace.hpp>

//#include <core/builder/spaceobject/ALL>

//#include <core/builder/item/equipment/ALL>
//#ifdef USE_MODULES
//#include <core/builder/item/module/ALL>
//#endif // USE_MODULES
//#ifdef USE_ARTEFACTS
//#include <core/builder/item/artefact/ALL>
//#endif // USE_ARTEFACTS
//#include <core/builder/item/other/ALL>

//#include <core/builder/world/StarSystemBuilder.hpp>

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


