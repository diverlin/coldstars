///*
//    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/

//#include "SatelliteDrawable.hpp"

//SatelliteDrawable::SatelliteDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
//    :
//      VehicleDrawable(texture, mesh)
//{
//}

///* virtual override final */
//SatelliteDrawable::~SatelliteDrawable()
//{
//#if CREATEDESTROY_LOG_ENABLED == 1
//    Logger::Instance().Log("___::~Satellite("+std::to_string(id())+")");
//#endif
//}

///* virtual override final */
////void SatelliteDrawable::UpdateInfo()
////{
////    GetInfo().clear();

////    GetInfo().addTitleStr("SATELLITE");

////    //GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem->id()));
////    GetInfo().addNameStr("id:");          GetInfo().addValueStr(std::to_string(id()));
////    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
////    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
////}

//void SatelliteDrawable::UpdateRenderStuff()
//{
//    //    GetComplexProtector().GetShieldEffect()->Update();
//    //    updateOrientation();
//}

//void SatelliteDrawable::RenderInSpace(const jeti::Renderer& render, float scale)
//{
//    //RenderKorpus(render);
    
//    //if (GetDataKorpus().draw_turrels == true)
//    //{
//    //GetComplexWeapon().RenderTurrels();
//    //}

//    //if (GetComplexProtector().GetProtectorSlot()->item() != nullptr)
//    //{
//    //RenderShieldEffect(1.0 - color().a);
//    //starsystem()->RestoreSceneColor();
//    //}
//}

//void SatelliteDrawable::RenderAtPlanet(const jeti::Renderer& render)
//{
//    RenderKorpus(render);
    
//    //if (GetDataKorpus().draw_turrels == true)
//    //{
//    //GetComplexWeapon().RenderTurrels();
//    //}
//}
