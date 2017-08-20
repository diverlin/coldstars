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

#include <client/view/Base.hpp>

namespace control {
class Satellite;
} // namespace descriptor

namespace view {

class Satellite : public Base
{
public:
    Satellite(control::Satellite*);
    ~Satellite() override final;

    //        void RenderInSpace(const jeti::Renderer&, float);
    //        void RenderAtPlanet(const jeti::Renderer&, const glm::vec3&);
    void draw(const jeti::Render& render) const override final;

    control::Satellite* control() const { return m_satellite; }

private:
    control::Satellite* m_satellite = nullptr;
};

} // namespace view
