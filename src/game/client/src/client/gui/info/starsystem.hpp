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

#include <SFGUI/Widgets.hpp>

#include <ceti/type/IdType.hpp>

#include <client/gui/info/Row2.hpp>

#include <map>

namespace info {

class StarSystem
{
private:
    const std::string STARS_TITLE = "stars";
    const std::string PLANETS_TITLE = "planets";
    const std::string WORMHOLES_TITLE = "wormholes";
    const std::string ASTEROIDS_TITLE = "asteroids";
    const std::string CONTAINERS_TITLE = "containers";
    const std::string SPACESTATIONS_TITLE = "spacestations";
    const std::string SHIPS_TITLE = "ships";
    const std::string SATELLITES_TITLE = "satellites";
    const std::string BULLETS_TITLE = "bullets";

    enum {
        STARS,
        PLANETS,
        WORMHOLES,
        ASTEROIDS,
        CONTAINERS,
        SPACESTATIONS,
        SHIPS,
        SATELLITES,
        BULLETS
    };

public:
    StarSystem();
    ~StarSystem() = default;

    void setStarsNum(int);
    void setPlanetsNum(int);
    void setWormHolesNum(int);
    void setAsteroidsNum(int);
    void setContainersNum(int);
    void setSpaceStationsNum(int);
    void setShipsNum(int);
    void setSatellitesNum(int);
    void setBulletsNum(int);

    void setVisibleStarsNum(int);
    void setVisiblePlanetsNum(int);
    void setVisibleWormHolesNum(int);
    void setVisibleAsteroidsNum(int);
    void setVisibleContainersNum(int);
    void setVisibleSpaceStationsNum(int);
    void setVisibleShipsNum(int);
    void setVisibleSatellitesNum(int);
    void setVisibleBulletsNum(int);

    sfg::Table::Ptr mainWidget() const { return m_table; }

private:
    sfg::Table::Ptr m_table;
    std::map<int, gui::Row2*> m_rows;

    gui::Row2* __getRowByTitle(int);
};

} // namespace info

