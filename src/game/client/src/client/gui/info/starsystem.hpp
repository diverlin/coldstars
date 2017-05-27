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

#include <map>

namespace info {

const std::string title_id = "title";
const std::string value_id = "value";

class Row {
public:
    Row(const std::string& title) {
        m_labelTitle = sfg::Label::Create(title+":");
        m_labelTitle->SetId(title_id);

        m_labelFirstNum = sfg::Label::Create(std::to_string(m_firstNum));
        m_labelFirstNum->SetId(value_id);
    }

    void setFirstNum(int num) {
        if (m_firstNum == num) {
            return;
        }
        m_labelFirstNum->SetText(std::to_string(num));
        m_firstNum = num;
    }

    sfg::Label::Ptr labelTitle() const { return m_labelTitle; }
    sfg::Label::Ptr labelFirstNum() const { return m_labelFirstNum; }

private:
    std::string m_title = "";
    int m_firstNum = 0;

    sfg::Label::Ptr m_labelTitle;
    sfg::Label::Ptr m_labelFirstNum;
};

class Row2 : public Row {
public:
    Row2(const std::string& title): Row(title) {
        m_labelSecondNum = sfg::Label::Create(std::to_string(m_secondNum));
        m_labelSecondNum->SetId(value_id);
    }

    void setSecondNum(int num) {
        if (m_secondNum == num) {
            return;
        }
        m_labelSecondNum->SetText(std::to_string(num));
        m_secondNum = num;
    }

    sfg::Label::Ptr labelSecondNum() const { return m_labelSecondNum; }

private:
    int m_secondNum = 0;
    sfg::Label::Ptr m_labelSecondNum;
};

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
    std::map<int, Row2*> m_rows;

    Row2* __getRowByTitle(int);
};

} // namespace info

