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

#include "Ship.hpp"

#include <core/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Ship.hpp>
#include <core/builder/part/TurrelBuilder.hpp>
#include <core/part/Turrel.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <client/view/effect/Shield.hpp>
#include <client/view/part/Turrel.hpp>
#include <client/view/effect/Jet.hpp>
#include <client/resources/Utils.hpp>

#include <jeti/Render.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>
#include <jeti/PathVisual.hpp>

#include <meti/RandUtils.hpp>

namespace view {

Ship::Ship(core::control::Ship* control)
    :
      Base(control)
    , m_control(control)
{
    _setOrientation(control);

    for(core::ItemSlot* slot: control->weaponSlots()) {
        // don't create resources, try to get existed from cache
        std::cout<<"WARNING: Turrel is commented"<<std::endl;
//        core::control::Turrel* turrel_control = core::TurrelBuilder().gen();
//        glm::vec3 pos(meti::rand::gen_float(-0.7f, 0.7f), meti::rand::gen_float(-0.7f, 0.7f), 0);
//        turrel_control->setPosition(pos);

//        Turrel* turrel = new Turrel(turrel_control);
//        _addChild(turrel);
//        m_slots_turrels.insert(std::make_pair(slot, turrel));
    }

    {
        effect::Shield* shield = _createShield();
        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::SHIELD_EFFECT);
        shield->setMaterial(material);
        shield->dissipate();
    }

    std::vector<meti::vec3> positions;
    int num = meti::rand::gen_int(1,3);
    float offset_x = 0.7f;
    float offset_y = 0.8f;
    if (num == 1) {
        positions.emplace_back(0.0f, -offset_y-0.1f, 0.0f);
    }
    if (num == 2) {
        positions.emplace_back(-offset_x, -offset_y, 0.0f);
        positions.emplace_back(offset_x, -offset_y, 0.0f);
    }
    if (num == 3) {
        positions.emplace_back(-offset_x,-offset_y, 0.0f);
        positions.emplace_back(0.0f, -offset_y-0.1f, 0.0f);
        positions.emplace_back(offset_x, -offset_y, 0.0f);
    }

    for (int i=0; i<num; ++i) {
        view::effect::Jet* driveJet = new view::effect::Jet(this, positions[i], 30.0f/*control->collisionRadius()*/);
        m_driveJets.push_back(driveJet);
    }

    _createPath(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR));
}

Ship::~Ship()
{
    for (view::effect::Jet* driveJet: m_driveJets) {
        delete driveJet;
    }
}

void Ship::_drawSelectedWeaponsRadius(const jeti::Render& render) const
{
    const std::vector<int> radiuses = m_control->weapons().radiusesOfSelectedWeapons();
    for (int radius: radiuses) {
        render.drawDebugCircle(position(), radius);
    }
}

void Ship::draw(const jeti::Render& render) const
{
    // draw path
    const auto& path = m_control->navigator().path();
    if (path.centers().size()) {
        _path()->update(path.centers(), path.directions());
        _drawPath(render);
    }

    // draw grapple jet
    if (m_control->properties().grab_radius > 0) {
        //RenderGrabTrail(render);
    }

    // draw korpus
    render.draw(mesh(), material(), modelMatrix());

    // draw children
    if (m_control->properties().draw_decors) {
        _drawChildren(render);
    }

    // draw jets
    if (m_control->properties().speed > 0) {
        for (view::effect::Jet* driveJet: m_driveJets) {
            driveJet->draw(render);
        }
    }

    //if (m_control->properties().shield_effect_enabled) {
        _drawShield(render);
    //}

    _drawSelectedWeaponsRadius(render);
}

/* virtual override final */
//void ShipDrawable::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("SHIP");
//    if (starsystem())    { GetInfo().addNameStr("id/ss_id:"); GetInfo().addValueStr( std::to_string(id()) + " / " + std::to_string(starsystem()->id()) ); }
//    else                     { GetInfo().addNameStr("id:");       GetInfo().addValueStr( std::to_string(id()) ); }
//    // alpitodorender GetInfo().addNameStr("race:");          GetInfo().addValueStr( getRaceStr(textureOb().GetAssociation().race_id) );
//    GetInfo().addNameStr("class:");         GetInfo().addValueStr( getStr(subSubTypeId()) );
//    GetInfo().addNameStr("armor/max:");     GetInfo().addValueStr( std::to_string(dataLife().armor) + "/" + std::to_string(GetDataKorpus().armor) );
////    alpitodorender GetInfo().addNameStr("size id:");       GetInfo().addValueStr( std::to_string(textureOb().GetData().size_id) );
//    GetInfo().addNameStr("space/free:");    GetInfo().addValueStr( std::to_string(GetDataKorpus().space) + "/" + std::to_string(GetProperties().free_space) );
//    GetInfo().addNameStr("mass:");          GetInfo().addValueStr( std::to_string(mass()) );
//    GetInfo().addNameStr("speedx100:");     GetInfo().addValueStr( std::to_string(GetProperties().speed*100) );
//    GetInfo().addNameStr("speed dmx100:");  GetInfo().addValueStr( std::to_string(mass()*MASS_DECREASE_SPEED_RATE*100));
//    GetInfo().addNameStr("energy:");        GetInfo().addValueStr( std::to_string(GetProperties().energy) );
//    GetInfo().addNameStr("temp.:");         GetInfo().addValueStr( std::to_string(GetDataKorpus().temperature) );
//    GetInfo().addNameStr("radar:");         GetInfo().addValueStr( std::to_string(GetProperties().radar) );
//    GetInfo().addNameStr("protect:");       GetInfo().addValueStr( std::to_string(GetProperties().protection) );
//    GetInfo().addNameStr("repair:");        GetInfo().addValueStr( std::to_string(GetProperties().repair) );
//    GetInfo().addNameStr("scan:");          GetInfo().addValueStr( std::to_string(GetProperties().scan) );
//    GetInfo().addNameStr("price:");         GetInfo().addValueStr( std::to_string(GetDataKorpus().price) );
//    GetInfo().addNameStr("pos:");           GetInfo().addValueStr( str(center()) );
        
//    if (GetProperties().grab_radius > 0)
//    {
//        std::string grab_str = GetSlotGrapple()->GetGrappleEquipment()->GetTargetStr();
//        if (grab_str.size() > 0)
//        {
//            GetInfo().addNameStr("grab_id:");           GetInfo().addValueStr( grab_str );
//        }
//    }

//    //info.addNameStr("attackR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.attack_rate_normalized) );
//    //info.addNameStr("defenceR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.defence_rate_normalized) );
//}

//void ShipDrawable::RenderAtPlanet(const jeti::Renderer& render, const glm::vec3& center)
//{
////    setCenter(center);
////    //SetAngleZ(0);
////    updateOrientation();
    
////    RenderKorpus(render);
    
////    if (GetDataKorpus().draw_turrels == true)
////    {
////        GetComplexWeapon().RenderTurrels();
////    }
//}

} // namespace view
