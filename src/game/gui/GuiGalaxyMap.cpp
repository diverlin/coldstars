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

#include <common/constants.hpp>
#include <common/myStr.hpp>
#include <types/AiScenarioTypes.hpp>

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


GuiGalaxyMap::GuiGalaxyMap()
:
BaseGuiElement(TYPE::GUI::GALAXYMAP_ID, TYPE::GUI::GALAXYMAP_ID),
m_Galaxy(nullptr)
{ 
	GetBox().SetCenter(400, 300);
	GetBox().SetSize(Config::Instance().SCREEN_WIDTH  - 2 * GUI::MAP::BORDER_X, Config::Instance().SCREEN_HEIGHT - 2 * GUI::MAP::BORDER_X);
	
	SetTextureOb(GuiTextureObCollector::Instance().text_background);
	m_ScaleParsecToScreenCoord = Config::Instance().SCREEN_WIDTH/(float)ENTITY::GALAXY::PARSEC;
}

GuiGalaxyMap::~GuiGalaxyMap()
{}

void GuiGalaxyMap::BindGalaxy(Galaxy* galaxy)
{
	m_Galaxy = galaxy;
}
                
void GuiGalaxyMap::UnbindGalaxy()
{
	m_Galaxy = nullptr;
}
        
/* virtual override final */
void GuiGalaxyMap::UpdateUnique(Player* player)
{    
    //m_VisualHyperJumpRange.FillData(GuiTextureObCollector::Instance().dot_yellow, 
    //m_ScaleParsecToScreenCoord*player->GetNpc()->GetVehicle()->GetProperties().hyper, 
    //10);

    if (player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() == TYPE::AISCENARIO::MICRO_JUMP_ID)
    {
        //m_VisualHyperJumpPath.FillData(GuiTextureObCollector::Instance().dot_green,
        //player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*m_ScaleParsecToScreenCoord,
        //player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTarget()->GetCenter()*m_ScaleParsecToScreenCoord,
        //10, 
        //20);    	
    }
        
	/*
	if (GetPlayer()->GetNpc()->GetVehicle()->GetProperties().hyper > 0)
	{      
		for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
		{
			for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
			{
				StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
				
				if (starsystem->GetId() != player->GetNpc()->GetVehicle()->GetStarSystem()->GetId())
				{	            			
					float ss_cursor_dist = distanceBetween(starsystem->GetCenter(), data_mouse.pos_screencoord);
					if (ss_cursor_dist < 10)
					{ 
						int ss_ss_dist = distanceBetween(starsystem->GetCenter(), player->GetNpc()->GetStarSystem()->GetCenter());
						if (ss_ss_dist < player->GetNpc()->GetVehicle()->GetProperties().hyper)
						{
							if (data_mouse.left_click == true)
							{ 
								Task microtask(TYPE::AISCENARIO::MICRO_JUMP_ID, starsystem->GetId());
								player->GetNpc()->GetStateMachine().SetCurrentMicroTask(microtask);
								player->GetNpc()->GetVehicle()->GetComplexDrive().UpdatePath();
								
								return true;
							} 
							if (data_mouse.right_click == true)
							{
								// DEBUG WAY
								player->GetNpc()->GetVehicle()->HyperJumpEvent(starsystem);
							}
						}
					}
				}
			}
		}
	}
	*/
}


/* vitual override final */
void GuiGalaxyMap::RenderUnique(Player* player) const
{
	drawQuad(GetTextureOb(), GetBox());
	

    for (unsigned int i=0; i<m_Galaxy->SECTOR_vec.size(); i++)
    {   		
        for (unsigned int j=0; j<m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
        {   	
            const StarSystem& starsystem = *m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
            Vec3<float> starsystem_pos = (starsystem.GetSector()->GetCenter() + starsystem.GetCenter())*m_ScaleParsecToScreenCoord;
            starsystem_pos.x += GetBox().GetCenter().x;
            starsystem_pos.y += GetBox().GetCenter().y;
                        
            TextureOb* texOb_particle = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::DISTANTSTAR_ID, starsystem.STAR_vec[0]->GetColorId()); 
            
            enable_POINTSPRITE();
            {                        
                drawParticleTextured(texOb_particle->texture, starsystem_pos, 30.0, -2.0);
                
                if (starsystem.GetConquerorRaceId() != TYPE::RACE::NONE_ID)
                {
                    drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, starsystem_pos, 20.0, -2.0);
                }
                
                if (starsystem.GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR_ID)
                {
                    Vec3<float> offset(0.0, -13.0, 0.0);
                    drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_war->texture, starsystem_pos + offset, 20.0, -2.0);
                } 
            }               
            disable_POINTSPRITE();   

            int font_size = 10;  
            Vec3<float> offset(0.0, 13.0, 0.0);
            Screen::Instance().DrawText(int2str(starsystem.GetId()), font_size, starsystem_pos + offset);
        }           	
    }	 
    
    enable_POINTSPRITE();
    {
        drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_player->texture, player->GetNpc()->GetStarSystem()->GetCenter()*m_ScaleParsecToScreenCoord, 40.0, -2.0);
        
        m_VisualHyperJumpRange.Draw(player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*m_ScaleParsecToScreenCoord);
        
        if (player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() == TYPE::AISCENARIO::MICRO_JUMP_ID)
        {
            m_VisualHyperJumpPath.Draw();       	
        }
    }
    disable_POINTSPRITE();  
}
