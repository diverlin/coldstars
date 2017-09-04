/*
    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "TelegramType.hpp"

#include <cassert>

namespace core {
namespace comm {

std::string to_string(core::comm::Telegramm::Type type_id)
{
    switch (type_id) {
    /** CREATE */
    case Telegramm::Type::CREATE_GALAXY:  { return "Telegramm::Type::CREATE_GALAXY"; }
    case Telegramm::Type::CREATE_SECTOR:  { return "Telegramm::Type::CREATE_SECTOR"; }
    case Telegramm::Type::CREATE_STARSYSTEM:  { return "Telegramm::Type::CREATE_STARSYSTEM"; }
    case Telegramm::Type::CREATE_PLAYER:  { return "Telegramm::Type::CREATE_PLAYER"; }
    case Telegramm::Type::CREATE_NPC:  { return "Telegramm::Type::CREATE_NPC"; }
    // spaceobjects
    case Telegramm::Type::CREATE_STAR:  { return "Telegramm::Type::CREATE_STAR"; }
    case Telegramm::Type::CREATE_PLANET:  { return "Telegramm::Type::CREATE_PLANET"; }
    case Telegramm::Type::CREATE_ASTEROID:  { return "Telegramm::Type::CREATE_ASTEROID"; }
    case Telegramm::Type::CREATE_SHIP:  { return "Telegramm::Type::CREATE_SHIP"; }
    case Telegramm::Type::CREATE_GOODS:  { return "Telegramm::Type::CREATE_GOODS"; }
    case Telegramm::Type::CREATE_CONTAINER:  { return "Telegramm::Type::CREATE_CONTAINER"; }
    case Telegramm::Type::CREATE_BULLET: { return "Telegramm::Type::CREATE_BULLET"; }

    // items
    case Telegramm::Type::CREATE_BAK:  { return "Telegramm::Type::CREATE_BAK"; }
    case Telegramm::Type::CREATE_DRIVE:  { return "Telegramm::Type::CREATE_DRIVE"; }
    case Telegramm::Type::CREATE_DROID:  { return "Telegramm::Type::CREATE_DROID"; }
    case Telegramm::Type::CREATE_GRAPPLE:  { return "Telegramm::Type::CREATE_GRAPPLE"; }
    case Telegramm::Type::CREATE_SCANER:  { return "Telegramm::Type::CREATE_SCANER"; }
    case Telegramm::Type::CREATE_RADAR:  { return "Telegramm::Type::CREATE_RADAR"; }
    case Telegramm::Type::CREATE_PROTECTOR:  { return "Telegramm::Type::CREATE_PROTECTOR"; }

    // effects
    case Telegramm::Type::CREATE_EXPLOSION_EFFECT:  { return "Telegramm::Type::CREATE_EXPLOSION_EFFECT"; }
    /** */

    /** TRANSITION */
    case Telegramm::Type::ADD_SECTOR_TO_GALAXY: { return "Telegramm::Type::ADD_SECTOR_TO_GALAXY"; }
    case Telegramm::Type::ADD_STARSYSTEM_TO_SECTOR: { return "Telegramm::Type::ADD_STARSYSTEM_TO_SECTOR"; }
    case Telegramm::Type::ADD_SHIP_TO_STARSYSTEM: { return "Telegramm::Type::ADD_SHIP_TO_STARSYSTEM"; }
    case Telegramm::Type::ADD_STAR_TO_STARSYSTEM: { return "Telegramm::Type::ADD_STAR_TO_STARSYSTEM"; }
    case Telegramm::Type::ADD_PLANET_TO_STARSYSTEM: { return "Telegramm::Type::ADD_PLANET_TO_STARSYSTEM"; }
    case Telegramm::Type::ADD_ASTEROID_TO_STARSYSTEM: { return "Telegramm::Type::ADD_PLANET_TO_STARSYSTEM"; }
    case Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM: { return "Telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM"; }
    case Telegramm::Type::ADD_NPC_TO_SHIP: { return "Telegramm::Type::ADD_NPC_TO_SHIP"; }
    case Telegramm::Type::INSERT:  { return "Telegramm::Type::INSERT"; }
    case Telegramm::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM:  { return "Telegramm::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM"; }
    case Telegramm::Type::DELETE:  { return "Telegramm::Type::DELETE"; }
    /** */

    case Telegramm::Type::HIT:     { return "Telegramm::Type::HIT"; }

    // garbage
    case Telegramm::Type::ADD_SPACEOBJECT_TO_GARBAGE: { return "Telegramm::Type::GARBAGE"; }
    }
    assert(false);
    return "Telegramm::Type::UKNOWN";
}

} // namespace comm
} // namespace core
