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


#include "PlanetDrawable.hpp"

////#include <ceti/StringUtils.hpp>
//#include <common/Logger.hpp>
  
#include <effects/BaseDecor.hpp>

#include <jeti/Render.hpp>


PlanetDrawable::PlanetDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
    :
      PlanetoidDrawable(texture, mesh)
{    
}

/* virtual */
PlanetDrawable::~PlanetDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~PlanetDrawable("+std::to_string(id())+")");
    #endif
   
//    for (BaseDecor* decor : m_Decorations)
//    {
//        delete decor;
//    }
//    m_Decorations.clear();
}


/* virtual override final */
//void Planet::UpdateInfo()
//{
//    GetInfo().clear();
    
//    GetInfo().addTitleStr("PLANET");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("population:");  GetInfo().addValueStr(std::to_string(m_Population));
//    GetInfo().addNameStr("dock_veh:");    GetInfo().addValueStr(m_Land->GetDockVehicleStr());
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
//}

//void Planet::Render_NEW(const Renderer& render)
//{
//    //alpitodorender render.DrawMeshLightNormalMap(GetMesh(), GetTextureOb(), GetActualModelMatrix());
//    for (BaseDecor* decor : m_Decorations)
//    {
//        decor->Render(render, center());
//    }
//}
