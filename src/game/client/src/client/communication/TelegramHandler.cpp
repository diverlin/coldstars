#include "TelegramHandler.hpp"

#include <core/descriptor/comm/Creation.hpp>
#include <core/pilot/Npc.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>

#include <client/resources/Utils.hpp>
#include <client/common/global.hpp>
#include <client/view/StarSystem.hpp>

//#include <core/builder/pilot/PlayerBuilder.hpp>
#include <client/pilot/Player.hpp>

#include <ceti/Logger.hpp>

#include <jeti/particlesystem/Explosion.hpp>

#include <memory>

namespace client {
namespace comm {

namespace {

// player
void createPlayerEvent(const core::comm::Telegram& telegramm) {
    descriptor::comm::CreatePlayer data(telegramm.data());

    client::Player* player = new client::Player(data.player());
    control::Npc* npc = core::shortcuts::entities()->npc(data.npc());
    player->setNpc(npc);
    client::global::get().setPlayer(player);
}

void createExplosionEffectEvent(const core::comm::Telegram& telegramm) {
    descriptor::comm::effect::Explosion descriptor(telegramm.data());
    std::shared_ptr<jeti::particlesystem::Explosion> explosion(jeti::particlesystem::genExplosion(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), descriptor.size()));
    client::global::get().view().add(explosion, descriptor.position());
}

} // namespace

void TelegramHandler::_process(const core::comm::Telegram& telegram) const
{
    LOG_COMM("--client: process telegramm="+telegram::to_string(telegram.type()));

    switch(telegram.type()) {




    // unique client
    case telegram::Type::CREATE_PLAYER: createPlayerEvent(telegram); break;
    case telegram::Type::CREATE_EXPLOSION_EFFECT: createExplosionEffectEvent(telegram); break;
    default: {
        assert(false);
        break;
    }
    }
}

} // namespace comm
} // namespace client


