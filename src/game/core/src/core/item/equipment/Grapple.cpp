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

//#include <jeti/Render.hpp>
#include "Grapple.hpp"
#ifdef USE_MODULES
#include <item/modules/GrappleModule.hpp>
#endif

#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <slots/ItemSlot.hpp>
#include <spaceobjects/Vehicle.hpp>
#include <core/spaceobjects/SpaceObject.hpp>
//#include <client/resources/GuiTextureObCollector.hpp>

namespace item {

Grapple::Grapple(int_t id)
    :
      m_strength_orig(0),
      m_radius_orig(0),
      m_speed_orig(0)
{
    assert(false);
//    setId(id);
//    setTypeId(entity::Type::EQUIPMENT_ID);
//    setSubTypeId(entity::Type::GRAPPLE_EQUIPMENT_ID);
}

/* virtual */
Grapple::~Grapple()
{}

bool Grapple::CheckIfTargetAlreadyExistInQueue(model::SpaceObject* target) const
{
    assert(false);
//    for (unsigned int i=0; i<m_targets.size(); i++) {
//        if (m_targets[i]->id() == target->id()) {
//            return true;
//        }
//    }
    
    return false;
}

void Grapple::AddTarget(model::SpaceObject* target)
{
    // avoiding dublicated items in the vector
    if (CheckIfTargetAlreadyExistInQueue(target)) {
        return;
    }

    if (m_free_strength > target->mass()) {
        m_targets.push_back(target);
        m_free_strength -= target->mass();

        //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr(target->typeId()) + " id = " + std::to_string(target->id()) + " grapple->AddTarget()", 2);
    }
}

void Grapple::RemoveTarget(model::SpaceObject* target)
{
    for (unsigned int i=0; i<m_targets.size(); i++) {
        if (m_targets[i]->id() == target->id()) {
            m_targets.erase(m_targets.begin()+i);
            m_free_strength += target->mass();
            
            return;
        }
    }
}     

void Grapple::RemoveAllTargets()
{
    m_targets.clear();
    m_free_strength = m_strength;
}

std::string Grapple::GetTarstr() const
{
    std::string str = "";
    
    for (unsigned int i=0; i<m_targets.size(); i++)
    {
        str += std::to_string(m_targets[i]->id()) + ", ";
    }

    return str;
}

void Grapple::UpdateGrabScenarioProgram_inDynamic()
{                      
        assert(false);
//    for (std::vector<model::SpaceObject*>::iterator it = m_targets.begin(); it != m_targets.end(); ++it)
//    {
//        Vehicle& vehicle = *slot()->vehicleOwner(); // shortcut
//        model::SpaceObject& target = **it;
        
//        if (slot()->checkTarget(&target) == STATUS::TARGET_OK)
//        {
//            glm::vec3 impulse_dir = glm::normalize(vehicle.position() - target.position());


//            target.addImpulse(impulse_dir, 0.001* strength());

//            float dist = meti::distance(vehicle.position(), target.position());
//            if (dist < 0.5*vehicle.collisionRadius())
//            {
//                switch(target.type())
//                {
//                case entity::Type::CONTAINER_ID:
//                {
//                    Container* container = reinterpret_cast<Container*>(&target);
//                    if (vehicle.unpackContainerItemToCargoSlot(container) == true)
//                    {
//                        it = m_targets.erase(it);
//                        return; // hack
//                    }
                    
//                    break;
//                }
                    
//                    //case ENTITY::VEHICLE_ID:
//                    //{
//                    //ItemSlot* _slot = GetEmptyOtsecSlot();
//                    //Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
//                    //if (_slot != nullptr)
//                    //{
//                    ////_slot->InsertItem(_vehicle);
//                    //starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
//                    //}
//                    //grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
//                    //break;
//                    //}
//                }
//            }
//        }
//        else
//        {
//            //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr((*it)->typeId()) + " id = " + std::to_string((*it)->id()) + " grapple->RemoveTarget()", 2);

//            it = m_targets.erase(it);
//            return; // hack
//        }
//    }
}

//void GrappleEquipment::RenderGrabTrail(const jeti::Renderer& render)
//{
//    //for (unsigned int i=0; i<target_vec.size(); i++)
//    //{
//    //float xl = target_vec[i]->position().x - item_slot->GetOwnerVehicle()->center().x;
//    //float yl = target_vec[i]->position().y - item_slot->GetOwnerVehicle()->center().y;

//    //float len = sqrt((xl*xl) + (yl*yl));

//    //float angle_inR = atan2(yl, xl);

//    //float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;

//    //drawLine(GuiTextureObCollector::Instance().grapple_trail,
//    //item_slot->GetOwnerVehicle()->center(),
//    //len,
//    //angle_inD,
//    //8);
//    //}
//}


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
    m_strength   = m_strength_orig   + m_strength_add;
    m_radius     = m_radius_orig     + m_radius_add;
    m_speed      = m_speed_orig      + m_speed_add;
    
    RemoveAllTargets();
}

void Grapple::CountPrice()
{
    float strength_rate      = (float)m_strength_orig / EQUIPMENT::GRAPPLE::STRENGTH_MIN;
    float radius_rate        = (float)m_radius_orig / EQUIPMENT::GRAPPLE::RADIUS_MIN;
    float speed_rate         = (float)m_speed_orig / EQUIPMENT::GRAPPLE::SPEED_MIN;

    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::GRAPPLE::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::GRAPPLE::STRENGTH_WEIGHT * strength_rate +
            EQUIPMENT::GRAPPLE::RADIUS_WEIGHT * radius_rate +
            EQUIPMENT::GRAPPLE::SPEED_WEIGHT * speed_rate +
            EQUIPMENT::GRAPPLE::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::GRAPPLE::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Grapple::addUniqueInfo()
{        
    //    info.addTitleStr("GRAPPLE");

    //    info.addNameStr("strength:");        info.addValueStr(GetStrengthStr() + "/" + std::to_string(free_strength));
    //    info.addNameStr("radius:");          info.addValueStr(GetRadiusStr());
    //    info.addNameStr("speed:");           info.addValueStr(GetSpeedStr());
}

std::string Grapple::GetStrengthStr()
{
    if (m_strength_add == 0)
        return std::to_string(m_strength_orig);
    else
        return std::to_string(m_strength_orig) + "+" + std::to_string(m_strength_add);
}

std::string Grapple::GetRadiusStr()
{
    if (m_radius_add == 0)
        return std::to_string(m_radius_orig);
    else
        return std::to_string(m_radius_orig) + "+" + std::to_string(m_radius_add);
}

std::string Grapple::GetSpeedStr()
{
    if (m_speed_add == 0)
        return std::to_string(m_speed_orig);
    else
        return std::to_string(m_speed_orig) + "+" + std::to_string(m_speed_add);
}

/*virtual*/
void Grapple::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "grapple_equipment." + std::to_string(id()) + ".";

//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Grapple::SaveData(save_ptree, root);
}

/*virtual*/
void Grapple::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Grapple::LoadData(load_ptree);
}

/*virtual*/
void Grapple::Resolve()
{
//    Base::ResolveData();
//    Base::ResolveData();
//    Base::ResolveData();
//    Grapple::ResolveData();
}

void Grapple::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
//    LOG(" GrappleEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
//    save_ptree.put(root+"strength_orig", m_strength_orig);
//    save_ptree.put(root+"radius_orig", m_radius_orig);
//    save_ptree.put(root+"speed_orig", m_speed_orig);
}

void Grapple::LoadData(const boost::property_tree::ptree& load_ptree)
{
//    LOG(" GrappleEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
//    m_strength_orig = load_ptree.get<int>("strength_orig");
//    m_radius_orig = load_ptree.get<int>("radius_orig");
//    m_speed_orig = load_ptree.get<int>("speed_orig");
}                

void Grapple::ResolveData()
{
//    LOG(" GrappleEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace item
