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

#include <core/type/EntityType.hpp>

#include <ceti/type/IdType.hpp>

#include <jeti/view/Base.hpp>

namespace jeti {

class Point;

namespace view {
class Path;
} // namespace view

namespace control {
class Material;
} // namespace control

} // namespace jeti

namespace core {
namespace control {
class Base;
} // namespace control
} // namespace core

namespace view {

namespace effect {
class Shield;
} // namespace effect

class Base : public jeti::view::Base
{
public:
    Base(); // used for effects
    Base(core::control::Base*);
    ~Base();

    // check all these in jeti::view::Base
    int_t id() const;
    entity::Type type() const;
    entity::Type group() const;
    int_t descriptorMeshId() const;
    int_t descriptorMaterialId() const;
    void setDescriptorMaterialId(int_t id);
    //

    const std::vector<Base*>& children() const { return m_children; }
    void update();

    core::control::Base* control() const { return m_control_base; }

protected:
    void _updatePoints() const;
    void _drawChildren(const jeti::Render&) const;
    void _drawShield(const jeti::Render&) const;
    void _drawPath(const jeti::Render&) const;

    void _addPoint(jeti::Point* point) { m_points.push_back(point); }
    void _addChild(Base*);
    effect::Shield* _createShield();
    void _createPath(jeti::control::Material*);

    jeti::view::Path* _path() const { return m_path; }

private:
    core::control::Base* m_control_base = nullptr;
    std::vector<jeti::Point*> m_points;
    std::vector<Base*> m_children;
    effect::Shield* m_shield = nullptr;
    jeti::view::Path* m_path = nullptr;
};

} // namespace view
