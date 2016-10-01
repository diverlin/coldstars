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


#include <gui/GuiGalaxyMap.hpp>
#include <gui/MouseData.hpp>

#include <common/Global.hpp>
#include <jeti/Config.hpp>

#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>
#include <types/AiScenarioTypes.hpp>

#include <resources/GuiTextureObCollector.hpp>
#include <resources/TextureCollector.hpp>

#include <world/starsystem.hpp>
#include <world/Sector.hpp>
#include <world/galaxy.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include <meti/RandUtils.hpp>

#include <ai/Task.hpp>
#include <ai/StateMachine.hpp>

#include <spaceobjects/Star.hpp>
#include <spaceobjects/Vehicle.hpp>

#include <pilots/Npc.hpp>
#include <pilots/Player.hpp>


GuiGalaxyMap::GuiGalaxyMap()
:
BaseGuiElement(type::GUI::GALAXYMAP_ID, type::GUI::GALAXYMAP_ID),
m_Galaxy(nullptr)
{ 
//    int w = global::get().config().width;
//    int h = global::get().config().height;
int w = 400;
int h = 300;
    GetBox().setSize(w  - 2 * GUI::MAP::BORDER_X, h - 2 * GUI::MAP::BORDER_X);
    
    SetTextureOb(GuiTextureObCollector::Instance().text_background);
    m_ScaleParsecToScreenCoord = w/(float)ENTITY::GALAXY::PARSEC;
}

GuiGalaxyMap::~GuiGalaxyMap()
{}

glm::vec3 GuiGalaxyMap::GetAbsoluteStarSystemPosition(const Starsystem& starsystem) const
{
    glm::vec3 starsystem_pos = (starsystem.sector()->position() + starsystem.position())*m_ScaleParsecToScreenCoord;
    starsystem_pos.x += GetBox().center().x;
    starsystem_pos.y += GetBox().center().y;
    
    return starsystem_pos;       
}

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
    const MouseData& data_mouse = player->GetCursor().GetMouseData();
    
    int radius = player->GetNpc()->vehicle()->properties().hyper * m_ScaleParsecToScreenCoord;
    m_VisualHyperJumpRange.FillData(GuiTextureObCollector::Instance().dot_yellow, radius, /*dot_size=*/6);

    glm::vec3 player_starsystem_pos = GetAbsoluteStarSystemPosition(*player->GetNpc()->vehicle()->starsystem());
//    if (player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() == type::AISCENARIO::MICRO_JUMP_ID)
//    {
//        Starsystem* player_starsystem_target = dynamic_cast<Starsystem*>(player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTarget());
//        glm::vec3 player_target_starsystem_pos = GetAbsoluteStarSystemPosition(*player_starsystem_target);
                
//        m_VisualHyperJumpPath.FillData(GuiTextureObCollector::Instance().dot_green, player_starsystem_pos, player_target_starsystem_pos, /*dot_offset=*/5, /*dot_size=*/6);
//    }
        
//    if (player->GetNpc()->vehicle()->properties().hyper > 0)
//    {
//        for (unsigned int i=0; i<m_Galaxy->SECTOR_vec.size(); i++)
//        {
//            for (unsigned int j=0; j<m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
//            {
//                StarSystem& starsystem = *m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
//                glm::vec3 starsystem_pos = GetAbsoluteStarSystemPosition(starsystem);
//                if (starsystem.id() != player->GetNpc()->vehicle()->starsystem()->id())
//                {
//                    float ss_cursor_dist = meti::distance(starsystem_pos, data_mouse.pos_screencoord);
//                    if (ss_cursor_dist < 10)
//                    {
//                        int ss_ss_dist = meti::distance(starsystem_pos, player_starsystem_pos);
//                        if (ss_ss_dist < player->GetNpc()->vehicle()->properties().hyper * m_ScaleParsecToScreenCoord)
//                        {
//                            if (data_mouse.left_click == true)
//                            {
//                                Task microtask(type::AISCENARIO::MICRO_JUMP_ID, starsystem.id());
//                                player->GetNpc()->GetStateMachine().SetCurrentMicroTask(microtask);
//                                player->GetNpc()->vehicle()->GetComplexDrive().UpdatePath();
//                            }
//                            if (data_mouse.right_click == true)
//                            {
//                                // DEBUG WAY
//                                player->GetNpc()->vehicle()->HyperJumpEvent(&starsystem);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
}


/* vitual override final */
void GuiGalaxyMap::RenderUnique(const jeti::Renderer& render, Player* player) const
{
    render.drawQuad(textureOb(), GetBox());    

//    for (unsigned int i=0; i<m_Galaxy->SECTOR_vec.size(); i++)
//    {
//        for (unsigned int j=0; j<m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
//        {
//            const StarSystem& starsystem = *m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
//            glm::vec2 starsystem_pos = meti::vec2(GetAbsoluteStarSystemPosition(starsystem));
                                   
//            //TextureOb* texOb_particle = TextureCollector::Instance().GetTexObByColorId(type::TEXTURE::DISTANTSTAR_ID, starsystem.STAR_vec[0]->GetColorId());
            
//            //render.enable_POINTSPRITE();
//            {
//                //drawParticleTextured(texOb_particle->texture, starsystem_pos, 30.0, -2.0);
                
//                if (starsystem.GetConquerorRaceId() != type::RACE::NONE_ID)
//                {
//                    //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, starsystem_pos, 20.0, -2.0);
//                }
                
//                if (starsystem.GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR_ID)
//                {
//                    glm::vec2 offset(0.0, -13.0);
//                    //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_war->texture, starsystem_pos + offset, 20.0, -2.0);
//                }
//            }
//            //render.disable_POINTSPRITE();

//            int font_size = 8;
//            glm::vec2 offset(0.0, 13.0);
//            jeti::Screen::get().DrawText(std::to_string(starsystem.id()), font_size, starsystem_pos + offset);
//        }
//    }
    
    //render.enable_POINTSPRITE();
    {
        glm::vec2 player_starsystem_pos = meti::vec2(GetAbsoluteStarSystemPosition(*player->GetNpc()->vehicle()->starsystem()));
        
        //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_player->texture, player_starsystem_pos, 40.0, -2.0);
        
        //m_VisualHyperJumpRange.Draw(player_starsystem_pos);
        
        //if (player->GetNpc()->stateMachine().microTaskManager().task().scenarioTypeId() == type::AISCENARIO::MICRO_JUMP_ID)
        {
            //m_VisualHyperJumpPath.Draw();           
        }
    }
    //render.disable_POINTSPRITE();  
}
