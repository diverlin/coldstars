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
#include <core/manager/DescriptorManager.hpp>

#include <client/view/part/Turrel.hpp>
#include <client/resources/Utils.hpp>

#include <jeti/Render.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>

namespace view {

Ship::Ship(control::Ship* ship)
    :
      Base(ship)
    , m_ship(ship)
{
    setOrientation(ship);

    for(slot::Item* slot: ship->weaponSlots()) {
        // don't create resources, try to get existed from cache
        control::Turrel* turrel_control = builder::Turrel().gen();
        view::Turrel* turrel = new view::Turrel(slot, turrel_control);
        addDecor(turrel);
    }

    {
        effect::Shield* shield = createShieldEffect();
        jeti::control::Material* material = utils::createMaterialByDescriptorType(texture::Type::SHIELD_EFFECT);
        shield->setMaterial(material);
        shield->dissipate();
    }
}

Ship::~Ship()
{}

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

void Ship::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), _modelMatrix());
    //if (GetDataKorpus().draw_turrels) {
        //GetComplexWeapon().RenderTurrels();
        _drawDecors(render);
    //}

    //if (GetProperties().grab_radius > 0) {
        //RenderGrabTrail(render);
    //}
        
    ///////RenderKorpus(render);
    



    
    //if (GetProperties().speed > 0) {
        //RenderDriveEffect(scale , 1.0 - color().a);
        //starsystem()->RestoreSceneColor();
    //}
    
    //if (ship()->properties().shield_effect_enabled) {
        _drawShield(render);
        //RenderShieldEffect(render, 1.0f - color().a);
    //}
}

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
