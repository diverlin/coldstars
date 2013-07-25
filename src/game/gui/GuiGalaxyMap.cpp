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

#include "GuiGalaxyMap.hpp"
#include "MouseData.hpp"
#include "../config/config.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"
#include "../world/starsystem.hpp"
#include "../world/Sector.hpp"
#include "../world/galaxy.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../resources/TextureManager.hpp"
#include "../ai/Task.hpp"
#include "../ai/StateMachine.hpp"

#include "../spaceobjects/Star.hpp"
#include "../pilots/Npc.hpp"
#include "../spaceobjects/Vehicle.hpp"

GuiGalaxyMap::GuiGalaxyMap():galaxy(nullptr)
{ 
	rect.Set(GUI::MAP::BORDER_X, GUI::MAP::BORDER_Y, 
	Config::Instance().SCREEN_WIDTH  - 2 * GUI::MAP::BORDER_X, 
	Config::Instance().SCREEN_HEIGHT - 2 * GUI::MAP::BORDER_X);
	
	texOb_background = GuiTextureObCollector::Instance().text_background;
	scale_parsec2screencoord = 2*Config::Instance().SCREEN_WIDTH/(float)ENTITY::GALAXY::PARSEC;
}

GuiGalaxyMap::~GuiGalaxyMap()
{}

void GuiGalaxyMap::BindGalaxy(Galaxy* galaxy)
{
	this->galaxy = galaxy;
}
                
void GuiGalaxyMap::UnbindGalaxy()
{
	galaxy = nullptr;
}
                
bool GuiGalaxyMap::UpdateMouseInteraction(const MouseData& data_mouse)
{
	if (m_Player->GetNpc()->GetVehicle()->GetProperties().hyper > 0)
	{      
		for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
		{
			for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
			{
				StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
				
				if (starsystem->GetId() != m_Player->GetNpc()->GetVehicle()->GetStarSystem()->GetId())
				{	            			
					float ss_cursor_dist = distanceBetween(starsystem->GetCenter(), data_mouse.pos_screencoord);
					if (ss_cursor_dist < 10)
					{ 
						int ss_ss_dist = distanceBetween(starsystem->GetCenter(), m_Player->GetNpc()->GetStarSystem()->GetCenter());
						if (ss_ss_dist < m_Player->GetNpc()->GetVehicle()->GetProperties().hyper)
						{
							if (data_mouse.left_click == true)
							{ 
								Task microtask(MICROSCENARIO::JUMP_ID, starsystem->GetId());
								m_Player->GetNpc()->GetStateMachine().SetCurrentMicroTask(microtask);
								m_Player->GetNpc()->GetVehicle()->GetComplexDrive().UpdatePath();
								
								return true;
							} 
							if (data_mouse.right_click == true)
							{
								// DEBUG WAY
								m_Player->GetNpc()->GetVehicle()->HyperJumpEvent(starsystem);
							}
						}
					}
				}
			}
		}
	}
	
	return false;
}



void GuiGalaxyMap::Render()
{
	drawTexturedRect(texOb_background, rect, -1.0);
	
	enable_POINTSPRITE();
	{
		for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
		{   		
			for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
			{   	
				StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
				
				TextureOb* texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::DISTANTSTAR_ID, starsystem->STAR_vec[0]->GetColorId()); 
				
				drawParticleTextured(texOb_particle->texture, starsystem->GetCenter()*scale_parsec2screencoord, 30.0, -2.0);
				
				if (starsystem->GetConquerorRaceId() != NONE_ID)
				{
					drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, starsystem->GetCenter()*scale_parsec2screencoord, 20.0, -2.0);
				}
				
				if (starsystem->GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR_ID)
				{
					drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_war->texture, starsystem->GetCenter()*scale_parsec2screencoord + Vec3<float>(0.0,-13.0, 0.0), 20.0, -2.0);
				}        		
			}           	
		}	 
		drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_player->texture, m_Player->GetNpc()->GetStarSystem()->GetCenter()*scale_parsec2screencoord, 40.0, -2.0);
		
		visual_hyperjump_range.FillData(GuiTextureObCollector::Instance().dot_yellow, 
		scale_parsec2screencoord*m_Player->GetNpc()->GetVehicle()->GetProperties().hyper, 
		10);
		visual_hyperjump_range.Draw(m_Player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*scale_parsec2screencoord);
		
		if (m_Player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() ==  MICROSCENARIO::JUMP_ID)
		{
			visual_hyperjump_path.FillData(GuiTextureObCollector::Instance().dot_green,
			m_Player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*scale_parsec2screencoord,
			m_Player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTarget()->GetCenter()*scale_parsec2screencoord,
			10,
			10);
			visual_hyperjump_path.Draw();       	
		}
	}
	disable_POINTSPRITE();
	
	int font_size = 10;     
	for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
	{   		
		for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
		{   	
			StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
			
			Vec2<float> pos(starsystem->GetCenter().x*scale_parsec2screencoord - 20, starsystem->GetCenter().y*scale_parsec2screencoord - 20);
			Screen::Instance().DrawText(int2str(starsystem->GetId()), font_size, pos);
		}
	} 
}
