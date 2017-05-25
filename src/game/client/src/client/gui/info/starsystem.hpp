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

namespace info {

class StarSystem
{
public:
    StarSystem();
    ~StarSystem() = default;

    void setStarsNum(int);
    void setPlanetsNum(int);
    void setAsteroidsNum(int);
    void setShipsNum(int);
    void setSatellitesNum(int);
    void setSpaceStationsNum(int);
    void setContainersNum(int);

    void setVisibleStarsNum(int);
    void setVisiblePlanetsNum(int);
    void setVisibleAsteroidsNum(int);
    void setVisibleShipsNum(int);
    void setVisibleSatellitesNum(int);
    void setVisibleSpaceStationsNum(int);
    void setVisibleContainersNum(int);

    sfg::Table::Ptr mainWidget() const { return m_table; }

private:
    sfg::Table::Ptr m_table;

    sfg::Label::Ptr m_labelTitleStars;
    sfg::Label::Ptr m_labelTitlePlanets;
    sfg::Label::Ptr m_labelTitleAsteroids;
    sfg::Label::Ptr m_labelTitleShips;
    sfg::Label::Ptr m_labelTitleSatellites;
    sfg::Label::Ptr m_labelTitleSpaceStations;
    sfg::Label::Ptr m_labelTitleContainers;

    sfg::Label::Ptr m_labelValueStarsNum;
    sfg::Label::Ptr m_labelValuePlanetsNum;
    sfg::Label::Ptr m_labelValueAsteroidsNum;
    sfg::Label::Ptr m_labelValueShipsNum;
    sfg::Label::Ptr m_labelValueSatellitesNum;
    sfg::Label::Ptr m_labelValueSpaceStationsNum;
    sfg::Label::Ptr m_labelValueContainersNum;

    sfg::Label::Ptr m_labelValueVisibleStarsNum;
    sfg::Label::Ptr m_labelValueVisiblePlanetsNum;
    sfg::Label::Ptr m_labelValueVisibleAsteroidsNum;
    sfg::Label::Ptr m_labelValueVisibleShipsNum;
    sfg::Label::Ptr m_labelValueVisibleSatellitesNum;
    sfg::Label::Ptr m_labelValueVisibleSpaceStationsNum;
    sfg::Label::Ptr m_labelValueVisibleContainersNum;

    int m_starsNum = 0;
    int m_planetsNum = 0;
    int m_asteroidsNum = 0;
    int m_shipsNum = 0;
    int m_satellitesNum = 0;
    int m_spaceStationsNum = 0;
    int m_containersNum = 0;

    int m_visibleStarsNum = 0;
    int m_visiblePlanetsNum = 0;
    int m_visibleAsteroidsNum = 0;
    int m_visibleShipsNum = 0;
    int m_visibleSatellitesNum = 0;
    int m_visibleSpaceStationsNum = 0;
    int m_visibleContainersNum = 0;
};

} // namespace info

