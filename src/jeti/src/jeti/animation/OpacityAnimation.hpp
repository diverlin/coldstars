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

namespace jeti {
namespace animation {

class Opacity
{  
    enum move {STOP, UP, DOWN};
public:
    Opacity(float, float, float, float);
    ~Opacity() = default;

    void setCyclic(bool cyclic) { m_cyclic = cyclic; }
    float opacity() const { return m_opacity; }

    void run() { m_move = UP; }
    void stop() { m_move = STOP; }
    void update();

private:
    float m_opacity = 1.0f;
    bool m_cyclic = false;
    move m_move = STOP;

    float m_min = 0.0f;
    float m_max = 1.0f;
    float m_downFactor = 0.99f;
    float m_upFactor = 1.01f;
};

} // namespace animation
} // namespace jeti

