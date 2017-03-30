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

std::string to_string(comm::Message::Type type_id)
{
    switch (type_id) {
    /** CREATE */
    case comm::Message::Type::CREATE_STARSYSTEM:  { return "comm::Message::Type::CREATE_STARSYSTEM"; }
    case comm::Message::Type::CREATE_SHIP:  { return "comm::Message::Type::CREATE_SHIP"; }
    case comm::Message::Type::CREATE_CONTAINER:  { return "comm::Message::Type::CREATE_CONTAINER"; }

    // items
    case comm::Message::Type::CREATE_BAK:  { return "comm::Message::Type::CREATE_BAK"; }
    case comm::Message::Type::CREATE_DRIVE:  { return "comm::Message::Type::CREATE_DRIVE"; }
    case comm::Message::Type::CREATE_DROID:  { return "comm::Message::Type::CREATE_DROID"; }
    case comm::Message::Type::CREATE_GRAPPLE:  { return "comm::Message::Type::CREATE_GRAPPLE"; }
    case comm::Message::Type::CREATE_SCANER:  { return "comm::Message::Type::CREATE_SCANER"; }
    case comm::Message::Type::CREATE_RADAR:  { return "comm::Message::Type::CREATE_RADAR"; }
    case comm::Message::Type::CREATE_PROTECTOR:  { return "comm::Message::Type::CREATE_PROTECTOR"; }
    /** */

    /** TRANSITION */
    case comm::Message::Type::ADD_SHIP_TO_STARSYSTEM: { return "comm::Message::Type::STARSYSTEM_ADD_SHIP"; }
    case comm::Message::Type::ADD_CONTAINER_TO_STARSYSTEM: { return "comm::Message::Type::STARSYSTEM_ADD_CONTAINER"; }
    case comm::Message::Type::INSERT:  { return "comm::Message::Type::INSERT"; }
    case comm::Message::Type::REMOVE:  { return "comm::Message::Type::REMOVE"; }
    case comm::Message::Type::DELETE:  { return "comm::Message::Type::DELETE"; }
    /** */

    case comm::Message::Type::HIT:     { return "comm::Message::Type::HIT"; }
    case comm::Message::Type::EXPLOSION: { return "comm::Message::Type::EXPLOSION"; }

    }

    return "comm::Message::Type::UKNOWN";
}


