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


#include "Planet.hpp"

#include <core/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Planet.hpp>

#include <client/resources/Utils.hpp>
#include <client/view/effect/Atmosphere.hpp>

#include <jeti/Render.hpp>

#include <jeti/animation/ConstantRotation.hpp>
#include <meti/RandUtils.hpp>

namespace view {

Planet::Planet(control::Planet* planet)
    :
      Base(planet)
    , m_control(planet)
{
    _setOrientation(planet);

    atmosphere = new effect::Atmosphere(this);
    jeti::Mesh* mesh = utils::createMeshByDescriptorType(mesh::Type::SPHERE);
    jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::ATMOSPHERE);
    atmosphere->setMesh(mesh);
    atmosphere->setMaterial(material);
    jeti::animation::ConstantRotation* animation = new jeti::animation::ConstantRotation(meti::OY, meti::rand::gen_float(0.001, 0.01));
    atmosphere->setAnimationRotation(animation);
    //atmosphere->setDescriptorMaterialId(m_control->descriptor()->atmosphereMaterial());
    _addChild(atmosphere);
}

Planet::~Planet()
{  
//    for (BaseDecor* decor : m_Decorations) {
//        delete decor;
//    }
//    m_Decorations.clear();
}

/* virtual override final */
//void Planet::UpdateInfo()
//{
//    GetInfo().clear();
    
//    GetInfo().addTitleStr("PLANET");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("population:");  GetInfo().addValueStr(std::to_string(m_Population));
//    GetInfo().addNameStr("dock_veh:");    GetInfo().addValueStr(m_Land->GetDockVehicleStr());
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
//}

void Planet::update()
{
    Base::update();
    for (Base* child: children()) {
        child->update();
    }
}

void Planet::draw(const jeti::Render& render) const
{
    render.draw(mesh(), material(), modelMatrix());
    for (Base* child: children()) {
        child->draw(render);
    }
}

} // namespace view
