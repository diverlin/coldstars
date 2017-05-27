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

#include "starsystem.hpp"

#include <cassert>

namespace info {

StarSystem::StarSystem() {
    m_table = sfg::Table::Create();

    std::vector<std::pair<int, std::string>> titles;
    titles.push_back(std::pair<int, std::string>(STARS, STARS_TITLE));
    titles.push_back(std::pair<int, std::string>(PLANETS, PLANETS_TITLE));
    titles.push_back(std::pair<int, std::string>(WORMHOLES, WORMHOLES_TITLE));
    titles.push_back(std::pair<int, std::string>(ASTEROIDS, ASTEROIDS_TITLE));
    titles.push_back(std::pair<int, std::string>(CONTAINERS, CONTAINERS_TITLE));
    titles.push_back(std::pair<int, std::string>(SPACESTATIONS, SPACESTATIONS_TITLE));
    titles.push_back(std::pair<int, std::string>(SHIPS, SHIPS_TITLE));
    titles.push_back(std::pair<int, std::string>(SATELLITES, SATELLITES_TITLE));
    titles.push_back(std::pair<int, std::string>(BULLETS, BULLETS_TITLE));

    for(auto title: titles) {
        m_rows.insert(std::make_pair(title.first, new gui::Row2(title.second)));
    }

    /// fill table
    // first column
    int col = 0;
    int row = 0;
    for(auto rowData: m_rows) {
        m_table->Attach( rowData.second->labelTitle(), sf::Rect<sf::Uint32>( col, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        row++;
    }

    // second column
    col++;
    row = 0;

    for(auto rowData: m_rows) {
        m_table->Attach( rowData.second->labelFirstNum(), sf::Rect<sf::Uint32>( col, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        row++;
    }

    // third column
    col++;
    row = 0;
    for(row=0; row < m_rows.size(); ++row) {
        m_table->Attach( sfg::Label::Create("/"), sf::Rect<sf::Uint32>( col, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    }

    // forth column
    col++;
    row = 0;
    for(auto rowData: m_rows) {
        m_table->Attach( rowData.second->labelSecondNum(), sf::Rect<sf::Uint32>( col, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        row++;
    }
}

void StarSystem::setStarsNum(int num) {
    __getRowByTitle(STARS)->setFirstNum(num);
}
void StarSystem::setPlanetsNum(int num) {
    __getRowByTitle(PLANETS)->setFirstNum(num);
}
void StarSystem::setWormHolesNum(int num) {
    __getRowByTitle(WORMHOLES)->setFirstNum(num);
}
void StarSystem::setAsteroidsNum(int num) {
    __getRowByTitle(ASTEROIDS)->setFirstNum(num);
}
void StarSystem::setContainersNum(int num) {
    __getRowByTitle(CONTAINERS)->setFirstNum(num);
}
void StarSystem::setSpaceStationsNum(int num) {
    __getRowByTitle(SPACESTATIONS)->setFirstNum(num);
}
void StarSystem::setShipsNum(int num) {
    __getRowByTitle(SHIPS)->setFirstNum(num);
}
void StarSystem::setSatellitesNum(int num) {
    __getRowByTitle(SATELLITES)->setFirstNum(num);
}
void StarSystem::setBulletsNum(int num) {
    __getRowByTitle(BULLETS)->setFirstNum(num);
}

void StarSystem::setVisibleStarsNum(int num) {
    __getRowByTitle(STARS)->setSecondNum(num);
}
void StarSystem::setVisiblePlanetsNum(int num) {
    __getRowByTitle(PLANETS)->setSecondNum(num);
}
void StarSystem::setVisibleWormHolesNum(int num) {
    __getRowByTitle(WORMHOLES)->setSecondNum(num);
}
void StarSystem::setVisibleAsteroidsNum(int num) {
    __getRowByTitle(ASTEROIDS)->setSecondNum(num);
}
void StarSystem::setVisibleContainersNum(int num) {
    __getRowByTitle(CONTAINERS)->setSecondNum(num);
}
void StarSystem::setVisibleSpaceStationsNum(int num) {
    __getRowByTitle(SPACESTATIONS)->setSecondNum(num);
}
void StarSystem::setVisibleShipsNum(int num) {
    __getRowByTitle(SHIPS)->setSecondNum(num);
}
void StarSystem::setVisibleSatellitesNum(int num) {
    __getRowByTitle(SATELLITES)->setSecondNum(num);
}
void StarSystem::setVisibleBulletsNum(int num) {
    __getRowByTitle(BULLETS)->setSecondNum(num);
}

gui::Row2*
StarSystem::__getRowByTitle(int key) {
    gui::Row2* row = nullptr;
    auto it = m_rows.find(key);
    if (it != m_rows.end()) {
        row = it->second;
    }
    assert(row);
    return row;
}

} // namespace info

