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

#include "SpaceStation.hpp"

#include <core/spaceobject/SpaceStation.hpp>
#include <core/model/spaceobject/SpaceStation.hpp>

namespace view {

SpaceStation::SpaceStation(core::control::SpaceStation* spacestation)
    :
      Base(spacestation)
    , m_spacestation(spacestation)
{}

SpaceStation::~SpaceStation()
{}

///* virtual override final */
////void SpaceStationDrawable::UpdateInSpace(int time, bool show_effect)
////{
////    checkDeath(show_effect);
////    if (time > 0)
////    {
////        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
////    }
////}

///* virtual override final */
////void SpaceStationDrawable::UpdateInfo()
////{
////    GetInfo().clear();

////    GetInfo().addTitleStr("StarBase" + getStr(subTypeId()));

////    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
////    GetInfo().addNameStr("id:");          GetInfo().addValueStr(std::to_string(id()));
////    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
////    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
////}

////void SpaceStationDrawable::UpdateRenderStuff_2D()
////{
////    //points.update();
////    GetComplexProtector().GetShieldEffect()->Update();
    
////    //if (ableTo.DRIVE == true)
////    //{
////        //drive_trail->update();
////    //}
////}

void SpaceStation::draw(const jeti::Render& render) const
{
    jeti::view::Base::draw(render);

    //UpdateRenderStuff_2D();
        
    ////////////RenderKorpus(render);
        
    //if (GetDataKorpus().draw_turrels) {
        //GetComplexWeapon().RenderTurrels();
    //}
    
    //if (GetComplexProtector().GetProtectorSlot()->item()) {
        //RenderShieldEffect(1.0 - color().a);
        //starsystem()->RestoreSceneColor();
    //}
}

} // namespace view
