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

#include "StarDrawable.hpp"

StarDrawable::StarDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh, Star* star)
    :
      PlanetoidDrawable(texture, mesh)
    , m_star(star)
    , m_DeltaColor(0.0)
    , m_SparkActive(false)
    , m_SparkGrows(false)
    , m_TurnSinceLastSparkCounter(0)
{ 
}
  
/* virtual override final */
StarDrawable::~StarDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Star("+std::to_string(id())+")");
    #endif    
}


//alpitodorender
/*
int Star::GetColorId() const { return textureOb().GetData().color_id; }

float Star::GetBrightThreshold() const { return textureOb().GetData().brightThreshold; }
            
void Star::CalcColor()
{
    SetColor(getColor4fById(textureOb().GetData().color_id));
}
*/
void StarDrawable::InitiateSpark()
{
    m_SparkActive = true;
    m_SparkGrows = true;
    m_TurnSinceLastSparkCounter = 0;
}

void StarDrawable::UpdateInSpace(int time, bool show_effect)
{
    if (m_SparkActive == true)
    {
        if (show_effect == true)
        {
            if (m_SparkGrows == true)
            {
                m_DeltaColor += 0.02;
                //scale += 0.2;
                if (m_DeltaColor > 1.0)
                {
                    m_DeltaColor = 1.0;
                    //starsystem()->StarSparkEvent(getRandInt(600, 1200));
                    m_SparkGrows = false;
                }
            } 
            else
            {        
                m_DeltaColor -= 0.005;    
                //scale -= 0.05;
                if (m_DeltaColor < 0.0)
                {
                    m_DeltaColor = 0;
                    m_SparkActive = false;
                } 
            }
        }
        else
        {
            //starsystem()->StarSparkEvent(getRandInt(600, 1200));
            m_SparkActive = false;
        }
    }

    //UpdateRotation(); // not relevant for render NEW
}    
    
/* virtual override final */
//void Star::UpdateInfo()
//{
//    GetInfo().clear();
//    GetInfo().addTitleStr("STAR");
//    GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");     GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("pos:");       GetInfo().addValueStr( str(center()) );
//}
