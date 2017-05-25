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

namespace info {

StarSystem::StarSystem() {
    const std::string title_id = "title";
    const std::string value_id = "value";

    m_table = sfg::Table::Create();

    m_labelTitleStars = sfg::Label::Create("stars:");
    m_labelTitlePlanets = sfg::Label::Create("planets:");
    m_labelTitleAsteroids = sfg::Label::Create("asteroids:");
    m_labelTitleShips = sfg::Label::Create("ships:");
    m_labelTitleSatellites = sfg::Label::Create("satellites:");
    m_labelTitleSpaceStations = sfg::Label::Create("spacestations:");
    m_labelTitleContainers = sfg::Label::Create("containers:");

    m_labelTitleStars->SetId(title_id);
    m_labelTitlePlanets->SetId(title_id);
    m_labelTitleAsteroids->SetId(title_id);
    m_labelTitleShips->SetId(title_id);
    m_labelTitleSatellites->SetId(title_id);
    m_labelTitleSpaceStations->SetId(title_id);
    m_labelTitleContainers->SetId(title_id);

    m_labelValueStarsNum = sfg::Label::Create(std::to_string(m_starsNum));
    m_labelValuePlanetsNum = sfg::Label::Create(std::to_string(m_planetsNum));
    m_labelValueAsteroidsNum = sfg::Label::Create(std::to_string(m_asteroidsNum));
    m_labelValueShipsNum = sfg::Label::Create(std::to_string(m_shipsNum));
    m_labelValueSatellitesNum = sfg::Label::Create(std::to_string(m_satellitesNum));
    m_labelValueSpaceStationsNum = sfg::Label::Create(std::to_string(m_spaceStationsNum));
    m_labelValueContainersNum = sfg::Label::Create(std::to_string(m_containersNum));

    m_labelValueStarsNum->SetId(value_id);
    m_labelValuePlanetsNum->SetId(value_id);
    m_labelValueAsteroidsNum->SetId(value_id);
    m_labelValueShipsNum->SetId(value_id);
    m_labelValueSatellitesNum->SetId(value_id);
    m_labelValueSpaceStationsNum->SetId(value_id);
    m_labelValueContainersNum->SetId(value_id);

    m_labelValueVisibleStarsNum = sfg::Label::Create(std::to_string(m_visibleStarsNum));
    m_labelValueVisiblePlanetsNum = sfg::Label::Create(std::to_string(m_visiblePlanetsNum));
    m_labelValueVisibleAsteroidsNum = sfg::Label::Create(std::to_string(m_visibleAsteroidsNum));
    m_labelValueVisibleShipsNum = sfg::Label::Create(std::to_string(m_visibleShipsNum));
    m_labelValueVisibleSatellitesNum = sfg::Label::Create(std::to_string(m_visibleSatellitesNum));
    m_labelValueVisibleSpaceStationsNum = sfg::Label::Create(std::to_string(m_visibleSpaceStationsNum));
    m_labelValueVisibleContainersNum = sfg::Label::Create(std::to_string(m_visibleContainersNum));

    m_labelValueVisibleStarsNum->SetId(value_id);
    m_labelValueVisiblePlanetsNum->SetId(value_id);
    m_labelValueVisibleAsteroidsNum->SetId(value_id);
    m_labelValueVisibleShipsNum->SetId(value_id);
    m_labelValueVisibleSatellitesNum->SetId(value_id);
    m_labelValueVisibleSpaceStationsNum->SetId(value_id);
    m_labelValueVisibleContainersNum->SetId(value_id);

    // fill table
    int col = 0;
    m_table->Attach( m_labelTitleStars,         sf::Rect<sf::Uint32>( col, 0, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitlePlanets,       sf::Rect<sf::Uint32>( col, 1, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitleAsteroids,     sf::Rect<sf::Uint32>( col, 2, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitleShips,         sf::Rect<sf::Uint32>( col, 3, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitleSatellites,    sf::Rect<sf::Uint32>( col, 4, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitleSpaceStations, sf::Rect<sf::Uint32>( col, 5, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelTitleContainers,    sf::Rect<sf::Uint32>( col, 6, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );

    col++;
    m_table->Attach( m_labelValueStarsNum,         sf::Rect<sf::Uint32>( col, 0, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValuePlanetsNum,       sf::Rect<sf::Uint32>( col, 1, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueAsteroidsNum,     sf::Rect<sf::Uint32>( col, 2, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueShipsNum,         sf::Rect<sf::Uint32>( col, 3, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueSatellitesNum,    sf::Rect<sf::Uint32>( col, 4, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueSpaceStationsNum, sf::Rect<sf::Uint32>( col, 5, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueContainersNum,    sf::Rect<sf::Uint32>( col, 6, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );

    col++;
    for(int i=0;i<=6;++i) {
        m_table->Attach( sfg::Label::Create("/"), sf::Rect<sf::Uint32>( col, i, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    }

    col++;
    m_table->Attach( m_labelValueVisibleStarsNum,         sf::Rect<sf::Uint32>( col, 0, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisiblePlanetsNum,       sf::Rect<sf::Uint32>( col, 1, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisibleAsteroidsNum,     sf::Rect<sf::Uint32>( col, 2, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisibleShipsNum,         sf::Rect<sf::Uint32>( col, 3, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisibleSatellitesNum,    sf::Rect<sf::Uint32>( col, 4, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisibleSpaceStationsNum, sf::Rect<sf::Uint32>( col, 5, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    m_table->Attach( m_labelValueVisibleContainersNum,    sf::Rect<sf::Uint32>( col, 6, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
}

void StarSystem::setStarsNum(int num) {
    if (m_starsNum == num) {
        return;
    }
    m_labelValueStarsNum->SetText(std::to_string(num));
    m_starsNum = num;
}

void StarSystem::setPlanetsNum(int num) {
    if (m_planetsNum == num) {
        return;
    }
    m_labelValuePlanetsNum->SetText(std::to_string(num));
    m_planetsNum = num;
}
void StarSystem::setAsteroidsNum(int num) {
    if (m_asteroidsNum == num) {
        return;
    }
    m_labelValueAsteroidsNum->SetText(std::to_string(num));
    m_asteroidsNum = num;
}
void StarSystem::setShipsNum(int num) {
    if (m_shipsNum == num) {
        return;
    }
    m_labelValueShipsNum->SetText(std::to_string(num));
    m_shipsNum = num;
}
void StarSystem::setSatellitesNum(int num) {
    if (m_satellitesNum == num) {
        return;
    }
    m_labelValueSatellitesNum->SetText(std::to_string(num));
    m_satellitesNum = num;
}
void StarSystem::setSpaceStationsNum(int num) {
    if (m_spaceStationsNum == num) {
        return;
    }
    m_labelValueSpaceStationsNum->SetText(std::to_string(num));
    m_spaceStationsNum = num;
}
void StarSystem::setContainersNum(int num) {
    if (m_containersNum == num) {
        return;
    }
    m_labelValueContainersNum->SetText(std::to_string(num));
    m_containersNum = num;
}

void StarSystem::setVisibleStarsNum(int num) {
    if (m_visibleStarsNum == num) {
        return;
    }
    m_labelValueVisibleStarsNum->SetText(std::to_string(num));
    m_visibleStarsNum = num;
}
void StarSystem::setVisiblePlanetsNum(int num) {
    if (m_visiblePlanetsNum == num) {
        return;
    }
    m_labelValueVisiblePlanetsNum->SetText(std::to_string(num));
    m_visiblePlanetsNum = num;
}
void StarSystem::setVisibleAsteroidsNum(int num) {
    if (m_visibleAsteroidsNum == num) {
        return;
    }
    m_labelValueVisibleAsteroidsNum->SetText(std::to_string(num));
    m_visibleAsteroidsNum = num;
}
void StarSystem::setVisibleShipsNum(int num) {
    if (m_visibleShipsNum == num) {
        return;
    }
    m_labelValueVisibleShipsNum->SetText(std::to_string(num));
    m_visibleShipsNum = num;
}
void StarSystem::setVisibleSatellitesNum(int num) {
    if (m_visibleSatellitesNum == num) {
        return;
    }
    m_labelValueVisibleSatellitesNum->SetText(std::to_string(num));
    m_visibleSatellitesNum = num;
}
void StarSystem::setVisibleSpaceStationsNum(int num) {
    if (m_visibleSpaceStationsNum == num) {
        return;
    }
    m_labelValueVisibleSpaceStationsNum->SetText(std::to_string(num));
    m_visibleSpaceStationsNum = num;
}
void StarSystem::setVisibleContainersNum(int num) {
    if (m_visibleContainersNum == num) {
        return;
    }
    m_labelValueVisibleContainersNum->SetText(std::to_string(num));
    m_visibleContainersNum = num;
}

} // namespace info

