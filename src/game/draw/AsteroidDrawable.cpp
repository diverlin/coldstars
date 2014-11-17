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

#include "AsteroidDrawable.hpp"

#include <common/Logger.hpp>
 
AsteroidDrawable::AsteroidDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
    :
      BasePlanetDrawable(texture, mesh)
{   

}
    
/* virtual override final */
AsteroidDrawable::~AsteroidDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~AsteroidDrawable("+int2str(GetId())+")");
    #endif
}

/* virtual override final */
//void AsteroidDrawable::UpdateInfo()
//{
//    m_Info.clear();

//    m_Info.addTitleStr("ASTEROID");
//    m_Info.addNameStr("id/ss_id:");    m_Info.addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
//    m_Info.addNameStr("armor:");       m_Info.addValueStr(int2str(GetDataLife().armor));
//    m_Info.addNameStr("mass:");        m_Info.addValueStr(int2str(GetMass()));
//    m_Info.addNameStr("speed x 100:"); m_Info.addValueStr(int2str(int(GetDataPlanet().speed*100)));
//    m_Info.addNameStr("pos:");         m_Info.addValueStr( str(GetCenter()) );
//}
