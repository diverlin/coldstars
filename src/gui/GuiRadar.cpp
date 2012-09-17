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

GuiRadar::GuiRadar()
{		
	textureOb_background 	= GuiTextureObCollector::Instance().radar_background;
	textureOb_bar	 	= GuiTextureObCollector::Instance().radar_bar;
	textureOb_screenrect	= GuiTextureObCollector::Instance().radar_screenrect;
	textureOb_range		= GuiTextureObCollector::Instance().radar_range;
			
	scale = RADAR_SCALE;
	int screen_w = Screen::Instance().GetWindow().GetWidth();
    	int screen_h = Screen::Instance().GetWindow().GetHeight();
    	Resize(screen_w, screen_h);
}

GuiRadar::~GuiRadar()
{}

void GuiRadar::Resize(int screen_w, int screen_h)
{
	rect.Set(0, 0, 250, 250);
}
     	
void GuiRadar::Reset()
{
	entity_vec.clear();
}
    
void GuiRadar::Update()
{
	screenrect.Set(rect.GetCenter() + Screen::Instance().GetBottomLeftGlobalCoord() * scale, (int)(Screen::Instance().GetWindow().GetWidth() * scale), (int)(Screen::Instance().GetWindow().GetWidth() * scale));
}

bool GuiRadar::UpdateMouseInteraction(const MouseData& data_mouse)
{		
       	if (rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
        {
        	if (data_mouse.left_press == true)
           	{
           		vec2f new_global_coord( (data_mouse.mx - rect.GetCenter().x - screenrect.GetWidth()/2)/scale, (data_mouse.my - rect.GetCenter().y - screenrect.GetHeight()/2)/scale);
           		Screen::Instance().SetBottomLeftGlobalCoord(new_global_coord);
       			return true;
        	}
     	}
     	
     	return false;
}
     		
void GuiRadar::Add(BaseGameEntity* object)
{
	entity_vec.push_back(object);
}

void GuiRadar::AddIfWithinRadarRange(BaseGameEntity* object, const Vehicle& vehicle)
{
 	if (vehicle.IsObjectWithinRadarRange(object) == true) 
       	{    	
       		Add(object); 
	}
}     		
    		
void GuiRadar::Render() const
{
	float range_diameter = 2*player->GetNpc()->GetVehicle()->GetPropetries().radar;
	Rect range_rect(0, 0, scale*range_diameter, scale*range_diameter);
	range_rect.SetCenter(rect.GetCenter() + player->GetNpc()->GetVehicle()->GetPoints().GetCenter() * scale);
	
	drawTexturedRect(textureOb_background, rect, -2.0);
	drawTexturedRect(textureOb_bar, rect, -2.0);
	drawTexturedRect(textureOb_screenrect, screenrect, -2.0);
	drawTexturedRect(textureOb_range, range_rect, -2.0);
			
	float size, size_base = 7;
	enable_POINTSPRITE();       	
		for (unsigned int i=0; i<entity_vec.size(); i++)
		{
			switch(entity_vec[i]->GetTypeId())
			{
				case ENTITY::STAR_ID:
				{
					glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_yellow->texture);
					size = 2*size_base;
					break;
				}
				case ENTITY::PLANET_ID:
				{
					glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_blue->texture);
					size = 1.5*size_base;
					break;				
				}
				case ENTITY::ASTEROID_ID:
				{
					glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_red->texture);
					size = 1.25*size_base;
					break;				
				}
				case ENTITY::BLACKHOLE_ID:
				{
					glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_purple->texture);
					size = 1.5*size_base;
					break;				
				}
				case ENTITY::VEHICLE_ID:
				{
					glBindTexture(GL_TEXTURE_2D, GuiTextureObCollector::Instance().dot_green->texture);
					size = 1*size_base;
					break;				
				}
			}
			
			drawParticle(size, rect.GetCenter() + entity_vec[i]->GetPoints().GetCenter()*scale);			
		}
	disable_POINTSPRITE(); 
}
