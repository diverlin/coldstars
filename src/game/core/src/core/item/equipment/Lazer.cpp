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

#include <core/spaceobject/SpaceObject.hpp>
#include <core/slot/ItemSlot.hpp>

#ifdef USE_MODULES
#include <core/item/modules/LazerModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Lazer::Lazer(descriptor::item::Lazer* descr, model::item::Lazer* model)
    :
      Weapon(descr, model)
    , m_descriptor_lazer(descr)
    , m_model_lazer(model)
{
    //TextureOb lazerEffect_texOb   = TEXTURE_MANAGER.returnLazerEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id);
//    texOb_turrel      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::TURREL);
//    texOb_lazerEffect = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::LAZER_EFFECT);
}

bool Lazer::checkAmmo() const
{
    /*if check energy */
    return true;
}

void Lazer::fire(float rate)
{
    assert(target());
    if (subtarget()) {
        if (subtarget()->item()) {
            subtarget()->item()->doLock(1);
            rate /= 3;
        }
    }

    target()->hit(damage() * rate);
    deteriorationEvent();
}

void Lazer::addUniqueInfo()
{
//    info.addTitleStr("LAZER");

//    info.addNameStr("damage:");     info.addValueStr(GetDamageStr());
//    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

//void Lazer::FireEvent(SpaceObject* target, slot::ItemSlot* subtarget, float damage_rate, bool show_effect)
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
