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

#include "TelegramCreator.hpp"

#include <core/common/Global.hpp>
#include <core/communication/Telegram.hpp>
#include <core/communication/descriptor/MoveVehicle.hpp>
#include <core/communication/TelegramHub.hpp>

namespace client {

TelegramCreator&
TelegramCreator::get()
{
    static TelegramCreator instance;
    return instance;
}

TelegramCreator::TelegramCreator()
    :
    m_telegramHub(core::global::get().telegramHub())
{

}

void TelegramCreator::playerRequestMove(int_t player, const glm::vec3& position)
{
    descriptor::comm::MoveVehicle telegram_descriptor(player, position);
    m_telegramHub.add(core::comm::ClientTelegram(telegram::Type::PLAYER_REQUEST_MOVE, telegram_descriptor.data()));
}

} // namespace client
