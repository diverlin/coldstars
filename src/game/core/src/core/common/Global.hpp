
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

#pragma once

namespace core {
namespace comm {
class TelegramHub;
} // namespace comm
} // namespace core

class Config;
//class TurnTimer;
class GameDate;
class RaceDescriptors;

namespace core {
class Descriptors;
} // namespace descriptor

namespace core {

class God;

class global
{
public:
    static global& get();

    God& god() { return *m_god; }
    comm::TelegramHub& telegramHub() { return *m_telegramHub; }
    Config& config() { return *m_config; }
//    TurnTimer& turnTimer() { return *m_turnTimer; }
    GameDate& gameDate() { return *m_gameDate; }
    RaceDescriptors& raceDescriptors() { return *m_raceDescriptors; }

private:
    global();
    global(const global&) = delete;
    ~global();
    global& operator=(const global&) = delete;

    God* m_god = nullptr;
    comm::TelegramHub* m_telegramHub = nullptr;
    Config* m_config = nullptr;
    GameDate* m_gameDate = nullptr;
    RaceDescriptors* m_raceDescriptors = nullptr;
};

} // namespace core
