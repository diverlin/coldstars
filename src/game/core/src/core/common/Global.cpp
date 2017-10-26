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

#include "Global.hpp"
#include <ai/God.hpp>
#include <core/manager/EntityManager.hpp>
#include <communication/TelegramHub.hpp>
#include <communication/TelegramHandler.hpp>
#include <common/Config.hpp>
#include <common/TurnTimer.hpp>
#include <common/GameDate.hpp>
#include <descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>

namespace core {

global& global::get()
{
    static global instance;
    return instance;
}

global::global()
    :
      m_god(new God)
    , m_messageHub(new comm::TelegramHub)
    , m_telegramHandler(new comm::TelegramHandler)
    , m_config(new Config)
    , m_turnTimer(new TurnTimer)
    , m_gameDate(new GameDate)
    , m_raceDescriptors(new RaceDescriptors)
{
}

global::~global()
{
    delete m_god;
    delete m_config;
    delete m_turnTimer;
    delete m_gameDate;
    delete m_raceDescriptors;
}

} // namespace core
