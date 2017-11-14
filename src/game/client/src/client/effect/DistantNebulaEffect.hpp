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

#include <client/effect/Base.hpp>

namespace effect {

class DistantNebula;
class DistantNebulas {
public:
    DistantNebulas(const std::vector<DistantNebula*>&);
    ~DistantNebulas();

    void update();
    void draw(const jeti::Render&) const;

private:
    std::vector<DistantNebula*> m_nebulas;
};

class DistantNebula : public Base
{
public:
    DistantNebula(float);
    virtual ~DistantNebula();

    void update();

private:
    float m_paralaxFactor = 1.0f;
};

DistantNebulas* genDistantNebulas(int color_id = -1);

} // namespace effect
