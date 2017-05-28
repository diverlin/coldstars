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

#include "Renderer.hpp"

#include <cassert>

namespace info {

Renderer::Renderer() {
    m_table = sfg::Table::Create();

    std::vector<std::pair<int, std::string>> titles;
    titles.push_back(std::pair<int, std::string>(ZNEAR, ZNEAR_TITLE));
    titles.push_back(std::pair<int, std::string>(ZFAR, ZFAR_TITLE));
    titles.push_back(std::pair<int, std::string>(QUAD_SCREEN_Z, QUAD_SCREEN_Z_TITLE));
    titles.push_back(std::pair<int, std::string>(SCALE, SCALE_TITLE));
    titles.push_back(std::pair<int, std::string>(WIDTH, WIDTH_TITLE));
    titles.push_back(std::pair<int, std::string>(HEIGHT, HEIGHT_TITLE));

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

void Renderer::setZNear(const std::string& value) {
    __getRowByTitle(ZNEAR)->setValue(value);
}
void Renderer::setZFar(const std::string& value) {
    __getRowByTitle(ZFAR)->setValue(value);
}
void Renderer::setScreenQuadZ(const std::string& value) {
    __getRowByTitle(QUAD_SCREEN_Z)->setValue(value);
}
void Renderer::setScale(const std::string& value) {
    __getRowByTitle(SCALE)->setValue(value);
}
void Renderer::setWidth(const std::string& value) {
    __getRowByTitle(WIDTH)->setValue(value);
}
void Renderer::setHeight(const std::string& value) {
    __getRowByTitle(HEIGHT)->setValue(value);
}

gui::Row*
Renderer::__getRowByTitle(int key) {
    gui::Row* row = nullptr;
    auto it = m_rows.find(key);
    if (it != m_rows.end()) {
        row = it->second;
    }
    assert(row);
    return row;
}

} // namespace info

