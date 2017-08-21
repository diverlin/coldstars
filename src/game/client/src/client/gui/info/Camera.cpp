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

#include "Camera.hpp"

#include <cassert>

namespace gui {
namespace info {

Camera::Camera() {
    m_table = sfg::Table::Create();

    std::vector<std::pair<int, std::string>> titles;
    titles.push_back(std::pair<int, std::string>(LOOKFROM, LOOKFROM_TITLE));
    titles.push_back(std::pair<int, std::string>(LOOKAT, LOOKAT_TITLE));
    titles.push_back(std::pair<int, std::string>(UP, UP_TITLE));
    titles.push_back(std::pair<int, std::string>(SPEED, SPEED_TITLE));

    for(auto title: titles) {
        m_rows.insert(std::make_pair(title.first, new gui::Row(title.second)));
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
        m_table->Attach( rowData.second->labelValue(), sf::Rect<sf::Uint32>( col, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        row++;
    }
}

void Camera::setLookFrom(const std::string& lookFrom) {
    __getRowByTitle(LOOKFROM)->setValue(lookFrom);
}
void Camera::setLookAt(const std::string& lookAt) {
    __getRowByTitle(LOOKAT)->setValue(lookAt);
}
void Camera::setUp(const std::string& up) {
    __getRowByTitle(UP)->setValue(up);
}
void Camera::setSpeed(const std::string& speed) {
    __getRowByTitle(SPEED)->setValue(speed);
}

gui::Row*
Camera::__getRowByTitle(int key) {
    gui::Row* row = nullptr;
    auto it = m_rows.find(key);
    if (it != m_rows.end()) {
        row = it->second;
    }
    assert(row);
    return row;
}

} // namespace info
} // namespace gui
