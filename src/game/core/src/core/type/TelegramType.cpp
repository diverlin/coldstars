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

std::string to_string(const TELEGRAM& type_id)
{
    switch (type_id) {
    /** CREATE */
    case TELEGRAM::CREATE_STARSYSTEM:  { return "TELEGRAM::CREATE_STARSYSTEM"; break; }
    case TELEGRAM::CREATE_SHIP:  { return "TELEGRAM::CREATE_SHIP"; break; }
    case TELEGRAM::CREATE_CONTAINER:  { return "TELEGRAM::CREATE_CONTAINER"; break; }

    // items
    case TELEGRAM::CREATE_BAK:  { return "TELEGRAM::CREATE_BAK"; break; }
    case TELEGRAM::CREATE_DRIVE:  { return "TELEGRAM::CREATE_DRIVE"; break; }
    case TELEGRAM::CREATE_DROID:  { return "TELEGRAM::CREATE_DROID"; break; }
    case TELEGRAM::CREATE_GRAPPLE:  { return "TELEGRAM::CREATE_GRAPPLE"; break; }
    case TELEGRAM::CREATE_SCANER:  { return "TELEGRAM::CREATE_SCANER"; break; }
    case TELEGRAM::CREATE_RADAR:  { return "TELEGRAM::CREATE_RADAR"; break; }
    case TELEGRAM::CREATE_PROTECTOR:  { return "TELEGRAM::CREATE_PROTECTOR"; break; }
    /** */

    /** TRANSITION */
    case TELEGRAM::STARSYSTEM_ADD_SHIP: { return "TELEGRAM::STARSYSTEM_ADD_SHIP"; break; }
    case TELEGRAM::STARSYSTEM_ADD_CONTAINER: { return "TELEGRAM::STARSYSTEM_ADD_CONTAINER"; break; }
    case TELEGRAM::INSERT:  { return "TELEGRAM::INSERT"; break; }
    case TELEGRAM::REMOVE:  { return "TELEGRAM::REMOVE"; break; }
    case TELEGRAM::DELETE:  { return "TELEGRAM::DELETE"; break; }
    /** */

    case TELEGRAM::HIT:     { return "TELEGRAM::HIT"; break; }
    case TELEGRAM::EXPLOSION: { return "TELEGRAM::EXPLOSION"; break; }

    default: return "TELEGRAM::UKNOWN"; break;
    }
}

