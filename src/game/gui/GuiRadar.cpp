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

#include "GuiRadar.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../render/Screen.hpp"
#include "../render/Render.hpp"

#include "../spaceobjects/BaseSpaceEntity.hpp"
#include "../spaceobjects/Vehicle.hpp"

#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"
#include <math/myVector.hpp>

GuiRadar::GuiRadar()
{
    SetSubTypeId(TYPE::GUI::GUI_RADAR_ID);
    
    textureOb_background     = GuiTextureObCollector::Instance().radar_background;
    textureOb_bar             = GuiTextureObCollector::Instance().radar_bar;
    textureOb_screenrect    = GuiTextureObCollector::Instance().radar_screenrect;
    textureOb_range            = GuiTextureObCollector::Instance().radar_range;
        
    scale = RADAR_SCALE;
    int screen_w = Screen::Instance().GetWidth();
    int screen_h = Screen::Instance().GetHeight();
    Resize(screen_w, screen_h);
}

GuiRadar::~GuiRadar()
{}

void GuiRadar::Resize(int screen_w, int screen_h)
{
    rect.Set(0, 0, 250, 250);
}
         
void GuiRadar::ResetData()
{
    entity_vec.clear();
}
   
/*virtual final*/ 
void GuiRadar::UpdateUnique(Player* player)
{        
    screenrect.Set(rect.GetCenter() + Screen::Instance().GetBottomLeftScreenWC() * scale, (int)(Screen::Instance().GetWidth() * scale), (int)(Screen::Instance().GetHeight() * scale));
    const MouseData& data_mouse = player->GetCursor().GetMouseData();
    if (rect.CheckRoundInteraction(data_mouse.pos_screencoord, /*radius=*/70.0) == true)
    {
        if (data_mouse.left_press == true)
        {
            glm::vec2 new_global_coord( ( data_mouse.pos_screencoord.x - rect.GetCenter().x - screenrect.GetWidth()/2)/scale, ( data_mouse.pos_screencoord.y - rect.GetCenter().y - screenrect.GetHeight()/2)/scale);
            Screen::Instance().SetBottomLeftScreenWC(new_global_coord);
        }
    }
}
             
void GuiRadar::Add(BaseSpaceEntity* object)
{
    entity_vec.push_back(object);
}

void GuiRadar::AddIfWithinRadarRange(BaseSpaceEntity* object, const Vehicle& vehicle)
{
    if (vehicle.IsObjectWithinRadarRange(object) == true) 
    {        
        Add(object); 
    }
}             
            
/* virtual override final */
void GuiRadar::RenderUnique(const Renderer& render, Player* player) const
{
    float range_diameter = 2*player->GetNpc()->GetVehicle()->GetProperties().radar;
    Rect range_rect(0, 0, scale*range_diameter, scale*range_diameter);
    
    range_rect.SetCenter(rect.GetCenter() + vec3ToVec2(player->GetNpc()->GetVehicle()->GetCenter()) * scale);
    
    //drawTexturedRect(textureOb_background, rect, -2.0);
    //drawTexturedRect(textureOb_bar, rect, -2.0);
    //drawTexturedRect(textureOb_screenrect, screenrect, -2.0);
    //drawTexturedRect(textureOb_range, range_rect, -2.0);
            
    float size, size_base = 7;
    //render.enable_POINTSPRITE();  
    {         
        for (unsigned int i=0; i<entity_vec.size(); i++)
        {
            switch(entity_vec[i]->GetTypeId())
            {
                case TYPE::ENTITY::STAR_ID:
                {
                    glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_yellow->GetData().texture);
                    size = 2*size_base;
                    break;
                }
                case TYPE::ENTITY::PLANET_ID:
                {
                    glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_blue->GetData().texture);
                    size = 1.5*size_base;
                    break;                
                }
                case TYPE::ENTITY::ASTEROID_ID:
                {
                    glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_red->GetData().texture);
                    size = 1.25*size_base;
                    break;                
                }
                case TYPE::ENTITY::BLACKHOLE_ID:
                {
                    glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_purple->GetData().texture);
                    size = 1.5*size_base;
                    break;                
                }
                case TYPE::ENTITY::VEHICLE_ID:
                {
                    glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_green->GetData().texture);
                    size = 1*size_base;
                    break;                
                }
            }
            
            //float scale_render = Screen::Instance().GetScale();
            //drawParticle(rect.GetCenter() + vec3ToVec2(entity_vec[i]->GetCenter()*scale)/scale_render, size);            
        }
    }
    //render.disable_POINTSPRITE(); 
}
