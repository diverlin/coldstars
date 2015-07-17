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

#include "SpaceStationDrawable.hpp"

SpaceStationDrawable::SpaceStationDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
    :
      VehicleDrawable(texture, mesh)
{}

/* virtual override final */
SpaceStationDrawable::~SpaceStationDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~SpaceStationDrawable("+std::to_string(id())+")");
    #endif
}    
 
/* virtual override final */          
//void SpaceStationDrawable::UpdateInSpace(int time, bool show_effect)
//{
//    checkDeath(show_effect);
//    if (time > 0)
//    {
//        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
//    }
//}

/* virtual override final */
//void SpaceStationDrawable::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("StarBase" + getStr(subTypeId()));

//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("id:");          GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
//}

//void SpaceStationDrawable::UpdateRenderStuff_2D()
//{
//    //points.update();
//    GetComplexProtector().GetShieldEffect()->Update();
    
//    //if (ableTo.DRIVE == true)
//    //{
//        //drive_trail->update();
//    //}
//}

void SpaceStationDrawable::RenderInSpace(const jeti::Renderer& render, float scale)
{     
    //UpdateRenderStuff_2D();
        
    RenderKorpus(render);
        
    //if (GetDataKorpus().draw_turrels == true)
    //{
        //GetComplexWeapon().RenderTurrels();
    //}
    
    //if (GetComplexProtector().GetProtectorSlot()->GetItem() != nullptr)
    //{
        //RenderShieldEffect(1.0 - color().a); 
        //starsystem()->RestoreSceneColor();
    //}
}
