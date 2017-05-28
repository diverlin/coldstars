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

class Renderer
{
private:
    const std::string ZNEAR_TITLE = "znear";
    const std::string ZFAR_TITLE = "zfar";
    const std::string QUAD_SCREEN_Z_TITLE = "quad_screen_z";
    const std::string SCALE_TITLE = "scale";
    const std::string WIDTH_TITLE = "width";
    const std::string HEIGHT_TITLE = "height";

    enum {
        ZNEAR,
        ZFAR,
        QUAD_SCREEN_Z,
        SCALE,
        WIDTH,
        HEIGHT
    };

public:
    Renderer();
    ~Renderer() = default;

    void setZNear(const std::string&);
    void setZFar(const std::string&);
    void setScreenQuadZ(const std::string&);
    void setScale(const std::string&);
    void setWidth(const std::string&);
    void setHeight(const std::string&);

    sfg::Table::Ptr mainWidget() const { return m_table; }

private:
    sfg::Table::Ptr m_table;
    std::map<int, gui::Row*> m_rows;

    gui::Row* __getRowByTitle(int);
};

} // namespace info

