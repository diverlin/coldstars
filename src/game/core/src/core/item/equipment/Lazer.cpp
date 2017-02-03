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

#include "Lazer.hpp"

#include <common/constants.hpp>
#include <ceti/Logger.hpp>

#include <meti/RandUtils.hpp>

#ifdef USE_MODULES
#include <item/modules/LazerModule.hpp>
#endif
#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"
#include "../../world/starsystem.hpp"
#include "../../parts/Turrel.hpp"

namespace item {

Lazer::Lazer(int_t id)
    :
      m_damage_orig(0),
      m_radius_orig(0)
{
    assert(false);
//    setId(id);
//    setTypeId(type::entity::EQUIPMENT_ID);
//    setSubTypeId(type::entity::LAZER_EQUIPMENT_ID);

    //TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
//    texOb_turrel      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL_ID);
//    texOb_lazerEffect = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EFFECT_ID);
}

/* virtual */
Lazer::~Lazer()
{}

/* virtual */
void Lazer::updateProperties()
{
    m_damage_add  = 0;
    m_radius_add  = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        m_damage_add   += ((LazerModule*)modules_vec[i])->GetDamageAdd();
        m_radius_add   += ((LazerModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif

    m_damage = m_damage_orig + m_damage_add;
    m_radius = m_radius_orig + m_radius_add;
} 

void Lazer::CountPrice()
{
    float damage_rate        = (float)m_damage_orig / EQUIPMENT::LAZER::DAMAGE_MIN;
    float radius_rate        = (float)m_radius_orig / EQUIPMENT::LAZER::RADIUS_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::LAZER::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::LAZER::DAMAGE_WEIGHT * damage_rate +
            EQUIPMENT::LAZER::RADIUS_WEIGHT * radius_rate +
            EQUIPMENT::LAZER::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::LAZER::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Lazer::addUniqueInfo()
{
//    info.addTitleStr("LAZER");

//    info.addNameStr("damage:");     info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string Lazer::GetDamageStr()
{
    if (m_damage_add == 0)
        return std::to_string(m_damage_orig);
    else
        return std::to_string(m_damage_orig) + "+" + std::to_string(m_damage_add);
}

std::string Lazer::GetRadiusStr()
{
    if (m_radius_add == 0)
        return std::to_string(m_radius_orig);
    else
        return std::to_string(m_radius_orig) + "+" + std::to_string(m_radius_add);
}

void Lazer::FireEvent(SpaceObject* target, ItemSlot* subtarget, float damage_rate, bool show_effect)
{ 
    assert(false);
//    if (slot()->vehicleOwner()->tryConsumeEnergy(m_damage) == true)
//    {
//        if (subtarget != nullptr) // precise fire
//        {
//            if (meti::isActionShouldHappen(slot()->hitProbability()) == true) {
//                subtarget->item()->doLock(1);
//            }
//            damage_rate /= 3; // lower damage is used for precise fire
            
//        }

//        target->hit(m_damage*damage_rate);
//        deteriorationEvent();

//        if (show_effect)
//        {
//            // LazerTraceEffect
//            //LazerTraceEffect* _lazer_trace_effect = nullptr;
//            //if (item_slot->GetOwnerVehicle()->GetVehicleDescriptor().draw_turrels == true)
//            //{
//            //_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
//            //item_slot->GetTurrel()->pCenter(),
//            //item_slot->GetTarget()->pCenter());
//            //}
//            //else
////            {
////                _lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
////                                                              item_slot->GetOwnerVehicle()->pCenter(),
////                                                              item_slot->GetTarget()->pCenter());
////            }
////            item_slot->GetOwnerVehicle()->starsystem()->Add(_lazer_trace_effect);
            
//            // DamageEffect
//            //DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, item_slot->GetTarget());
//            //_lazer_trace_effect->SetDamageEffect(_damage_effect);
//            //item_slot->GetOwnerVehicle()->starsystem()->Add(_damage_effect);
//        }
//    }
} 

/*virtual*/
void Lazer::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "lazer_equipment." + std::to_string(id()) + ".";
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Base::SaveData(save_ptree, root);
//    Lazer::SaveData(save_ptree, root);
}

/*virtual*/
void Lazer::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Base::LoadData(load_ptree);
//    Lazer::LoadData(load_ptree);
}

/*virtual*/
void Lazer::Resolve()
{
//    Base::ResolveData();
//    Base::ResolveData();
//    Base::ResolveData();
//    Lazer::ResolveData();
}

void Lazer::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
//    LOG(" LazerEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
//    save_ptree.put(root+"damage_orig", m_damage_orig);
//    save_ptree.put(root+"radius_orig", m_radius_orig);
}

void Lazer::LoadData(const boost::property_tree::ptree& load_ptree)
{
//    LOG(" LazerEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
//    m_damage_orig = load_ptree.get<int>("damage_orig");
//    m_radius_orig = load_ptree.get<int>("radius_orig");
}                

void Lazer::ResolveData()
{
//    LOG(" LazerEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace item
