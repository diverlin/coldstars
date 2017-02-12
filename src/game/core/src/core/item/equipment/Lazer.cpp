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
#include <core/descriptor/item/equipment/Lazer.hpp>
#include <core/model/item/equipment/Lazer.hpp>

#ifdef USE_MODULES
#include <core/item/modules/LazerModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Lazer::Lazer(model::item::Lazer* model)
    :
      m_model_lazer(model)
{
    //TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
//    texOb_turrel      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL);
//    texOb_lazerEffect = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EFFECT);
}

/* virtual */
void Lazer::updateProperties()
{
    m_damage_add = 0;
    m_radius_add = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        m_damage_add   += ((LazerModule*)modules_vec[i])->GetDamageAdd();
        m_radius_add   += ((LazerModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif

    model()->setDamage(descriptor()->damage() + m_damage_add);
    model()->setRadius(descriptor()->radius() + m_radius_add);
} 

void Lazer::countPrice()
{
//    float damage_rate        = (float)descriptor()->damage() / descriptor::item::Lazer::DAMAGE_MIN;
//    float radius_rate        = (float)descriptor()->radius() / descriptor::item::Lazer::RADIUS_MIN;
//    float modules_num_rate   = (float)descriptor()->modules() / descriptor::item::Lazer::MODULES_NUM_MAX;

//    float effectiveness_rate = descriptor::item::Lazer::DAMAGE_WEIGHT * damage_rate +
//            descriptor::item::Lazer::RADIUS_WEIGHT * radius_rate +
//            descriptor::item::Lazer::MODULES_NUM_WEIGHT * modules_num_rate;

//    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Lazer::MASS_MIN;
//    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Lazer::CONDITION_MIN;

//    m_price                    = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Lazer::addUniqueInfo()
{
//    info.addTitleStr("LAZER");

//    info.addNameStr("damage:");     info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string Lazer::damageStr()
{
    if (m_damage_add) {
        return std::to_string(descriptor()->damage()) + "+" + std::to_string(m_damage_add);
    } else {
        return std::to_string(descriptor()->damage());
    }
}

std::string Lazer::radiusStr()
{
    if (m_radius_add == 0) {
        return std::to_string(descriptor()->radius()) + "+" + std::to_string(m_radius_add);
    } else {
        return std::to_string(descriptor()->radius());
    }
}

//void Lazer::FireEvent(SpaceObject* target, ItemSlot* subtarget, float damage_rate, bool show_effect)
//{
//    assert(false);
////    if (slot()->vehicleOwner()->tryConsumeEnergy(m_damage) == true)
////    {
////        if (subtarget != nullptr) // precise fire
////        {
////            if (meti::isActionShouldHappen(slot()->hitProbability()) == true) {
////                subtarget->item()->doLock(1);
////            }
////            damage_rate /= 3; // lower damage is used for precise fire
            
////        }

////        target->hit(m_damage*damage_rate);
////        deteriorationEvent();

////        if (show_effect)
////        {
////            // LazerTraceEffect
////            //LazerTraceEffect* _lazer_trace_effect = nullptr;
////            //if (item_slot->GetOwnerVehicle()->GetVehicleDescriptor().draw_turrels == true)
////            //{
////            //_lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
////            //item_slot->GetTurrel()->pCenter(),
////            //item_slot->GetTarget()->pCenter());
////            //}
////            //else
//////            {
//////                _lazer_trace_effect = new LazerTraceEffect(   texOb_lazerEffect,
//////                                                              item_slot->GetOwnerVehicle()->pCenter(),
//////                                                              item_slot->GetTarget()->pCenter());
//////            }
//////            item_slot->GetOwnerVehicle()->starsystem()->Add(_lazer_trace_effect);
            
////            // DamageEffect
////            //DamageEffect* _damage_effect = getNewDamageEffect(texOb_lazerEffect->color_id, item_slot->GetTarget());
////            //_lazer_trace_effect->SetDamageEffect(_damage_effect);
////            //item_slot->GetOwnerVehicle()->starsystem()->Add(_damage_effect);
////        }
////    }
//}

} // namespace item
} // namespace control
