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

namespace gui {
namespace info {

class Camera
{
private:
    const std::string LOOKFROM_TITLE = "lookFrom";
    const std::string LOOKAT_TITLE = "lookAt";
    const std::string UP_TITLE = "up";
    const std::string SPEED_TITLE = "speed";

    enum {
        LOOKFROM,
        LOOKAT,
        UP,
        SPEED
    };

public:
    Camera();
    ~Camera() = default;

    void setLookFrom(const std::string&);
    void setLookAt(const std::string&);
    void setUp(const std::string&);
    void setSpeed(const std::string&);

    sfg::Table::Ptr mainWidget() const { return m_table; }

private:
    sfg::Table::Ptr m_table;
    std::map<int, gui::Row*> m_rows;

    gui::Row* __getRowByTitle(int);
};

} // namespace info
} // namespace gui
