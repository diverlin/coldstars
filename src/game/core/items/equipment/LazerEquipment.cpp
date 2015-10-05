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

#include "LazerEquipment.hpp"

#include <common/constants.hpp>
#include <ceti/Logger.hpp>

#include <meti/RandUtils.hpp>

#include "../../items/modules/LazerModule.hpp"
#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../world/starsystem.hpp"
#include "../../parts/Turrel.hpp"

LazerEquipment::LazerEquipment(int id)
    :
      damage_orig(0),
      radius_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    setSubTypeId(TYPE::ENTITY::LAZER_EQUIPMENT_ID);

    //TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
//    texOb_turrel      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL_ID);
//    texOb_lazerEffect = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EFFECT_ID);
}

/* virtual */
LazerEquipment::~LazerEquipment() 
{}

/* virtual */
void LazerEquipment::updateProperties()
{
    damage_add  = 0;
    radius_add  = 0;

    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        damage_add   += ((LazerModule*)modules_vec[i])->GetDamageAdd();
        radius_add   += ((LazerModule*)modules_vec[i])->GetRadiusAdd();
    }
    
    damage = damage_orig + damage_add;
    radius = radius_orig + radius_add;
} 

void LazerEquipment::CountPrice()
{
    float damage_rate        = (float)damage_orig / EQUIPMENT::LAZER::DAMAGE_MIN;
    float radius_rate        = (float)radius_orig / EQUIPMENT::LAZER::RADIUS_MIN;
    float modules_num_rate   = (float)m_data_item.modules_num_max / EQUIPMENT::LAZER::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::LAZER::DAMAGE_WEIGHT * damage_rate +
            EQUIPMENT::LAZER::RADIUS_WEIGHT * radius_rate +
            EQUIPMENT::LAZER::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::LAZER::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition_max;

    m_price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void LazerEquipment::AddUniqueInfo()
{
//    info.addTitleStr("LAZER");

//    info.addNameStr("damage:");     info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string LazerEquipment::GetDamageStr()
{
    if (damage_add == 0)
        return std::to_string(damage_orig);
    else
        return std::to_string(damage_orig) + "+" + std::to_string(damage_add);
}

std::string LazerEquipment::GetRadiusStr()
{
    if (radius_add == 0)
        return std::to_string(radius_orig);
    else
        return std::to_string(radius_orig) + "+" + std::to_string(radius_add);
}

void LazerEquipment::FireEvent(SpaceObject* target, ItemSlot* subtarget, float damage_rate, bool show_effect)
{ 
    if (itemSlot()->GetOwnerVehicle()->TryToConsumeEnergy(damage) == true)
    {
        if (subtarget != nullptr) // precise fire
        {
            if (meti::isActionShouldHappen(itemSlot()->hitProbability()) == true) {
                subtarget->item()->lockEvent(1);
            }
            damage_rate /= 3; // lower damage is used for precise fire
            
        }

        target->hit(damage*damage_rate, show_effect);
        deteriorationEvent();

        if (show_effect)
        {
            // LazerTraceEffect
            //LazerTraceEffect* _lazer_trace_effect = nullptr;
            //if (item_slot->GetOwnerVehicle()->GetVehicleDescriptor().draw_turrels == true)
            //{
            //_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
            //item_slot->GetTurrel()->pCenter(),
            //item_slot->GetTarget()->pCenter());
            //}
            //else
//            {
//                _lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
//                                                              item_slot->GetOwnerVehicle()->pCenter(),
//                                                              item_slot->GetTarget()->pCenter());
//            }
//            item_slot->GetOwnerVehicle()->starsystem()->Add(_lazer_trace_effect);
            
            // DamageEffect
            //DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, item_slot->GetTarget());
            //_lazer_trace_effect->SetDamageEffect(_damage_effect);
            //item_slot->GetOwnerVehicle()->starsystem()->Add(_damage_effect);
        }
    }
} 

/*virtual*/
void LazerEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "lazer_equipment." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    LazerEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void LazerEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    LazerEquipment::LoadData(load_ptree);
}

/*virtual*/
void LazerEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    LazerEquipment::ResolveData();
}

void LazerEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" LazerEquipment::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"damage_orig", damage_orig);
    save_ptree.put(root+"radius_orig", radius_orig);
}

void LazerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" LazerEquipment::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    damage_orig = load_ptree.get<int>("damage_orig");
    radius_orig = load_ptree.get<int>("radius_orig");
}                

void LazerEquipment::ResolveData()
{
    Logger::Instance().Log(" LazerEquipment::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
}

