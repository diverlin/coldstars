#include "TelegrammManager.hpp"

#include <core/descriptor/comm/Creation.hpp>
#include <core/pilot/Npc.hpp>

#include <client/resources/Utils.hpp>
#include <client/common/global.hpp>
#include <client/view/StarSystem.hpp>

//#include <core/builder/pilot/PlayerBuilder.hpp>
#include <client/pilot/Player.hpp>

#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>

#include <jeti/particlesystem/Explosion.hpp>

#include <memory>

namespace client {
namespace comm {

namespace {

// player
void createPlayerEvent(const core::comm::Telegramm& telegramm) {
    descriptor::comm::CreatePlayer data(telegramm.data());

    client::Player* player = new client::Player(data.player());
    control::Npc* npc = core::Sessions::get().session()->entity()->npc(data.npc());
    player->setNpc(npc);
    client::global::get().setPlayer(player);
}

void createExplosionEffectEvent(const core::comm::Telegramm& telegramm) {
    descriptor::comm::effect::Explosion descriptor(telegramm.data());
    std::shared_ptr<jeti::particlesystem::Explosion> explosion(jeti::particlesystem::genExplosion(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), descriptor.size()));
    client::global::get().view().add(explosion, descriptor.position());
}

} // namespace

bool TelegrammManager::_process(const core::comm::Telegramm& telegramm)
{
    if (core::comm::TelegrammManager::_process(telegramm)) {
        return true;
    }

    switch(telegramm.type()) {
    case core::comm::Telegramm::Type::CREATE_PLAYER: createPlayerEvent(telegramm); return true;
    case core::comm::Telegramm::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegramm); return true;
    }

    assert(false);
    return false;
}

} // namespace comm
} // namespace client


