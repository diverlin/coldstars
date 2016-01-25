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
#include <items/equipment/GrappleEquipment.hpp>
#include <items/modules/GrappleModule.hpp>

#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <slots/ItemSlot.hpp>
#include <spaceobjects/Vehicle.hpp>
//#include <resources/GuiTextureObCollector.hpp>


GrappleEquipment::GrappleEquipment(const id_type& id)
:
strength_orig(0),
radius_orig(0),
speed_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);  
    setSubTypeId(TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID);
}

/* virtual */
GrappleEquipment::~GrappleEquipment()
{}

bool GrappleEquipment::CheckIfTargetAlreadyExistInQueue(SpaceObject* target) const
{
    for (unsigned int i=0; i<target_vec.size(); i++)
    {
        if (target_vec[i]->id() == target->id())
        {
            return true;  
        }    
    }  
    
    return false;    
}

void GrappleEquipment::AddTarget(SpaceObject* target)
{
    // avoiding dublicated items in the vector
    if (CheckIfTargetAlreadyExistInQueue(target) == true)    
    {
        return;
    }         
                
    if (free_strength > target->mass())
    {
        target_vec.push_back(target);
        free_strength -= target->mass();
            
        //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr(target->typeId()) + " id = " + std::to_string(target->id()) + " grapple->AddTarget()", 2);
    }        
}

void GrappleEquipment::RemoveTarget(SpaceObject* target)
{
    for (unsigned int i=0; i<target_vec.size(); i++)
    {
        if (target_vec[i]->id() == target->id())
        {
            target_vec.erase(target_vec.begin()+i);
            free_strength += target->mass();
            
            return;  
        }    
    }  
}     
 
void GrappleEquipment::RemoveAllTargets()
{
    target_vec.clear(); 
    free_strength = strength;
}
                              
std::string GrappleEquipment::GetTarstr() const
{
    std::string str = "";
    
    for (unsigned int i=0; i<target_vec.size(); i++)
    {
        str += std::to_string(target_vec[i]->id()) + ", ";
    }
            
    return str;
}
 
void GrappleEquipment::UpdateGrabScenarioProgram_inDynamic()
{                      
    for (std::vector<SpaceObject*>::iterator it = target_vec.begin(); it != target_vec.end(); ++it)
    {
        Vehicle& vehicle = *itemSlot()->GetOwnerVehicle(); // shortcut
        SpaceObject& target = **it;
        
        if (itemSlot()->checkTarget(&target) == STATUS::TARGET_OK)
        {
            glm::vec3 impulse_dir = glm::normalize(vehicle.center() - target.center());

        
            target.addImpulse(impulse_dir, 0.001* GetStrength());
                
            float dist = meti::distance(vehicle.center(), target.center());
            if (dist < 0.5*vehicle.collisionRadius())
            {
                switch(target.typeId())
                {
                    case TYPE::ENTITY::CONTAINER_ID:
                    {
                        Container* container = reinterpret_cast<Container*>(&target);
                        if (vehicle.UnpackContainerItemToCargoSlot(container) == true)
                        {
                            it = target_vec.erase(it);
                            return; // hack
                        }
                    
                        break;
                    }
                    
                    //case ENTITY::VEHICLE_ID:
                    //{
                        //ItemSlot* _slot = GetEmptyOtsecSlot();
                                        //Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
                            //if (_slot != nullptr)
                        //{
                            ////_slot->InsertItem(_vehicle);
                            //starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
                        //}
                    //grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
                        //break;
                    //}
                }
            }
        }
        else
        {
            //LOG("vehicle_id=" + std::to_string(item_slot->GetOwnerVehicle()->id()) + " " + getTypeStr((*it)->typeId()) + " id = " + std::to_string((*it)->id()) + " grapple->RemoveTarget()", 2);
                    
            it = target_vec.erase(it);
            return; // hack
        }
    }
}

void GrappleEquipment::RenderGrabTrail(const jeti::Renderer& render)
{
    //for (unsigned int i=0; i<target_vec.size(); i++)
    //{
        //float xl = target_vec[i]->center().x - item_slot->GetOwnerVehicle()->center().x;
        //float yl = target_vec[i]->center().y - item_slot->GetOwnerVehicle()->center().y;
        
        //float len = sqrt((xl*xl) + (yl*yl));
        
        //float angle_inR = atan2(yl, xl);
        
        //float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;
        
        //drawLine(GuiTextureObCollector::Instance().grapple_trail, 
                 //item_slot->GetOwnerVehicle()->center(), 
                 //len, 
                 //angle_inD, 
                 //8);
    //}
}


/* virtual */
void GrappleEquipment::updateProperties()
{
    strength_add   = 0;
    radius_add     = 0;
    speed_add      = 0;
    
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        strength_add   += ((GrappleModule*)modules_vec[i])->GetStrengthAdd();
        radius_add     += ((GrappleModule*)modules_vec[i])->GetRadiusAdd();
        speed_add      += ((GrappleModule*)modules_vec[i])->GetSpeedAdd();
    }
                    
    strength   = strength_orig   + strength_add;
    radius     = radius_orig     + radius_add;
    speed      = speed_orig      + speed_add;
    
    RemoveAllTargets();
}

void GrappleEquipment::CountPrice()
{
    float strength_rate      = (float)strength_orig / EQUIPMENT::GRAPPLE::STRENGTH_MIN;
    float radius_rate        = (float)radius_orig / EQUIPMENT::GRAPPLE::RADIUS_MIN;
    float speed_rate         = (float)speed_orig / EQUIPMENT::GRAPPLE::SPEED_MIN;

    float modules_num_rate   = (float)m_data_item.modules_num_max / EQUIPMENT::GRAPPLE::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::GRAPPLE::STRENGTH_WEIGHT * strength_rate + 
                   EQUIPMENT::GRAPPLE::RADIUS_WEIGHT * radius_rate + 
                   EQUIPMENT::GRAPPLE::SPEED_WEIGHT * speed_rate + 
                   EQUIPMENT::GRAPPLE::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::GRAPPLE::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void GrappleEquipment::addUniqueInfo()
{        
//    info.addTitleStr("GRAPPLE");

//    info.addNameStr("strength:");        info.addValueStr(GetStrengthStr() + "/" + std::to_string(free_strength));
//    info.addNameStr("radius:");          info.addValueStr(GetRadiusStr());
//    info.addNameStr("speed:");           info.addValueStr(GetSpeedStr());
}

std::string GrappleEquipment::GetStrengthStr()
{
     if (strength_add == 0)
        return std::to_string(strength_orig);
     else
        return std::to_string(strength_orig) + "+" + std::to_string(strength_add);
}

std::string GrappleEquipment::GetRadiusStr()
{
     if (radius_add == 0)
        return std::to_string(radius_orig);
     else
        return std::to_string(radius_orig) + "+" + std::to_string(radius_add);
}

std::string GrappleEquipment::GetSpeedStr()
{
     if (speed_add == 0)
        return std::to_string(speed_orig);
     else
        return std::to_string(speed_orig) + "+" + std::to_string(speed_add);
}

/*virtual*/
void GrappleEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "grapple_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    GrappleEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void GrappleEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    GrappleEquipment::LoadData(load_ptree);
}

/*virtual*/
void GrappleEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    GrappleEquipment::ResolveData();
}

void GrappleEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" GrappleEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"strength_orig", strength_orig);
    save_ptree.put(root+"radius_orig", radius_orig);
    save_ptree.put(root+"speed_orig", speed_orig);
}
                
void GrappleEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" GrappleEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
    strength_orig = load_ptree.get<int>("strength_orig");     
    radius_orig = load_ptree.get<int>("radius_orig");   
    speed_orig = load_ptree.get<int>("speed_orig");           
}                

void GrappleEquipment::ResolveData()
{
    LOG(" GrappleEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

