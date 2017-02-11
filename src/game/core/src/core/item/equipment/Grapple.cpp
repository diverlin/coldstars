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

#include "Grapple.hpp"

#ifdef USE_MODULES
#include <core/item/modules/GrappleModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace descriptor {
namespace item {

const int Grapple::STRENGTH_MIN = 6;
const int Grapple::STRENGTH_MAX = 50;
const float Grapple::STRENGTH_TECH_RATE = 0.1f;

const int Grapple::RADIUS_MIN = 100;
const int Grapple::RADIUS_MAX = 200;
const float Grapple::RADIUS_TECH_RATE = 0.1f;

const int Grapple::SPEED_MIN = 100;
const int Grapple::SPEED_MAX = 170;
const float Grapple::SPEED_TECH_RATE = 0.1f;

const int Grapple::MODULES_NUM_MIN = 0;
const int Grapple::MODULES_NUM_MAX = 2;
const int Grapple::MASS_MIN = 10;
const int Grapple::MASS_MAX = 40;
const int Grapple::CONDITION_MIN = 100;
const int Grapple::CONDITION_MAX = 1000;

const float Grapple::STRENGTH_WEIGHT = 0.4f;
const float Grapple::RADIUS_WEIGHT = 0.3f;
const float Grapple::SPEED_WEIGHT = 0.2f;
const float Grapple::MAXNUMITEM_WEIGHT = 0.1f;
const float Grapple::MODULES_NUM_WEIGHT = 0.1f;

Grapple::Grapple()
{
    setDescriptor(descriptor::type::GRAPPLE_EQUIPMENT);
}

Grapple::Grapple(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Grapple::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor


namespace model {
namespace item {

Grapple::Grapple()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::GRAPPLE_EQUIPMENT_ID);
}

Grapple::Grapple(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Grapple::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model


namespace control {
namespace item {

Grapple::Grapple(model::item::Grapple* model)
    :
      m_model_grapple(model)
{}

///* virtual */
//Grapple::~Grapple()
//{}

//bool Grapple::CheckIfTargetAlreadyExistInQueue(model::SpaceObject* target) const
//{
//    assert(false);
////    for (unsigned int i=0; i<m_targets.size(); i++) {
////        if (m_targets[i]->id() == target->id()) {
////            return true;
////        }
////    }
    
//    return false;
//}

//void Grapple::AddTarget(model::SpaceObject* target)
//{
//    // avoiding dublicated items in the vector
//    if (CheckIfTargetAlreadyExistInQueue(target)) {
//        return;
//    }

//    if (m_free_strength > target->mass()) {
//        m_targets.push_back(target);
//        m_free_strength -= target->mass();

//        //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr(target->typeId()) + " id = " + std::to_string(target->id()) + " grapple->AddTarget()", 2);
//    }
//}

//void Grapple::RemoveTarget(model::SpaceObject* target)
//{
//    for (unsigned int i=0; i<m_targets.size(); i++) {
//        if (m_targets[i]->id() == target->id()) {
//            m_targets.erase(m_targets.begin()+i);
//            m_free_strength += target->mass();
            
//            return;
//        }
//    }
//}

//void Grapple::RemoveAllTargets()
//{
//    m_targets.clear();
//    m_free_strength = m_strength;
//}

//std::string Grapple::GetTarstr() const
//{
//    std::string str = "";
    
//    for (unsigned int i=0; i<m_targets.size(); i++)
//    {
//        str += std::to_string(m_targets[i]->id()) + ", ";
//    }

//    return str;
//}

//void Grapple::UpdateGrabScenarioProgram_inDynamic()
//{
//        assert(false);
////    for (std::vector<model::SpaceObject*>::iterator it = m_targets.begin(); it != m_targets.end(); ++it)
////    {
////        Vehicle& vehicle = *slot()->vehicleOwner(); // shortcut
////        model::SpaceObject& target = **it;
        
////        if (slot()->checkTarget(&target) == STATUS::TARGET_OK)
////        {
////            glm::vec3 impulse_dir = glm::normalize(vehicle.position() - target.position());


////            target.addImpulse(impulse_dir, 0.001* strength());

////            float dist = meti::distance(vehicle.position(), target.position());
////            if (dist < 0.5*vehicle.collisionRadius())
////            {
////                switch(target.type())
////                {
////                case entity::Type::CONTAINER_ID:
////                {
////                    Container* container = reinterpret_cast<Container*>(&target);
////                    if (vehicle.unpackContainerItemToCargoSlot(container) == true)
////                    {
////                        it = m_targets.erase(it);
////                        return; // hack
////                    }
                    
////                    break;
////                }
                    
////                    //case ENTITY::VEHICLE_ID:
////                    //{
////                    //ItemSlot* _slot = GetEmptyOtsecSlot();
////                    //Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
////                    //if (_slot != nullptr)
////                    //{
////                    ////_slot->InsertItem(_vehicle);
////                    //starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
////                    //}
////                    //grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
////                    //break;
////                    //}
////                }
////            }
////        }
////        else
////        {
////            //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr((*it)->typeId()) + " id = " + std::to_string((*it)->id()) + " grapple->RemoveTarget()", 2);

////            it = m_targets.erase(it);
////            return; // hack
////        }
////    }
//}

////void GrappleEquipment::RenderGrabTrail(const jeti::Renderer& render)
////{
////    //for (unsigned int i=0; i<target_vec.size(); i++)
////    //{
////    //float xl = target_vec[i]->position().x - item_slot->GetOwnerVehicle()->center().x;
////    //float yl = target_vec[i]->position().y - item_slot->GetOwnerVehicle()->center().y;

////    //float len = sqrt((xl*xl) + (yl*yl));

////    //float angle_inR = atan2(yl, xl);

////    //float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;

////    //drawLine(GuiTextureObCollector::Instance().grapple_trail,
////    //item_slot->GetOwnerVehicle()->center(),
////    //len,
////    //angle_inD,
////    //8);
////    //}
////}


/* virtual */
void Grapple::updateProperties()
{
    m_strength_add   = 0;
    m_radius_add     = 0;
    m_speed_add      = 0;
    
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        strength_add   += ((GrappleModule*)modules_vec[i])->GetStrengthAdd();
        radius_add     += ((GrappleModule*)modules_vec[i])->GetRadiusAdd();
        speed_add      += ((GrappleModule*)modules_vec[i])->GetSpeedAdd();
    }
#endif
    model()->setStrength(descriptor()->strength() + m_strength_add);
    model()->setRadius(descriptor()->radius() + m_radius_add);
    model()->setSpeed(descriptor()->speed() + m_speed_add);
    
    //RemoveAllTargets();
}

void Grapple::CountPrice()
{
    float strength_rate      = (float)descriptor()->strength() / descriptor::item::Grapple::STRENGTH_MIN;
    float radius_rate        = (float)descriptor()->radius() / descriptor::item::Grapple::RADIUS_MIN;
    float speed_rate         = (float)descriptor()->speed() / descriptor::item::Grapple::SPEED_MIN;

    float modules_num_rate   = (float)modulesNum() / descriptor::item::Grapple::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Grapple::STRENGTH_WEIGHT * strength_rate +
            descriptor::item::Grapple::RADIUS_WEIGHT * radius_rate +
            descriptor::item::Grapple::SPEED_WEIGHT * speed_rate +
            descriptor::item::Grapple::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Grapple::MASS_MIN;
    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Grapple::CONDITION_MIN;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Grapple::addUniqueInfo()
{        
    //    info.addTitleStr("GRAPPLE");

    //    info.addNameStr("strength:");        info.addValueStr(GetStrengthStr() + "/" + std::to_string(free_strength));
    //    info.addNameStr("radius:");          info.addValueStr(GetRadiusStr());
    //    info.addNameStr("speed:");           info.addValueStr(GetSpeedStr());
}

std::string Grapple::strengthStr()
{
    if (m_strength_add) {
        return std::to_string(descriptor()->strength()) + "+" + std::to_string(m_strength_add);
    } else {
        return std::to_string(descriptor()->strength());
    }
}

std::string Grapple::radiusStr()
{
    if (m_radius_add) {
        return std::to_string(descriptor()->radius()) + "+" + std::to_string(m_radius_add);
    } else {
        return std::to_string(descriptor()->radius());
    }
}

std::string Grapple::speedStr()
{
    if (m_speed_add) {
        return std::to_string(descriptor()->speed()) + "+" + std::to_string(m_speed_add);
    } else {
        return std::to_string(descriptor()->speed());
    }
}

} // namespace item
} // namespace control
