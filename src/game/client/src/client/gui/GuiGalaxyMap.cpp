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


#include <client/gui/GuiGalaxyMap.hpp>
#include <client/gui/MouseData.hpp>

#include <common/Global.hpp>
#include <jeti/Config.hpp>

#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>
#include <core/type/AiScenarioType.hpp>

#include <client/resources/GuiTextureObCollector.hpp>
#include <client/resources/TextureCollector.hpp>

#include <world/starsystem.hpp>
#include <world/Sector.hpp>
#include <world/galaxy.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include <meti/RandUtils.hpp>

#include <ai/Task.hpp>
#include <ai/StateMachine.hpp>

#include <core/spaceobject/Star.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <core/pilot/Npc.hpp>
#include <client/pilot/Player.hpp>


GuiGalaxyMap::GuiGalaxyMap()
:
BaseGuiElement(gui::type::GALAXYMAP, gui::type::GALAXYMAP),
m_Galaxy(nullptr)
{ 
//    int w = core::global::get().config().width;
//    int h = core::global::get().config().height;
int w = 400;
int h = 300;
    GetBox().setSize(w  - 2 * GUI::MAP::BORDER_X, h - 2 * GUI::MAP::BORDER_X);
    
    SetTextureOb(GuiTextureObCollector::Instance().text_background);
    m_ScaleParsecToScreenCoord = w/(float)ENTITY::GALAXY::PARSEC;
}

GuiGalaxyMap::~GuiGalaxyMap()
{}

glm::vec3 GuiGalaxyMap::GetAbsoluteStarSystemPosition(const model::Starsystem& starsystem) const
{
    assert(false);
//    glm::vec3 starsystem_pos = (starsystem.sector()->position() + starsystem.position())*m_ScaleParsecToScreenCoord;
//    starsystem_pos.x += GetBox().center().x;
//    starsystem_pos.y += GetBox().center().y;
    
//    return starsystem_pos;
}

void GuiGalaxyMap::BindGalaxy(model::Galaxy* galaxy)
{
    m_Galaxy = galaxy;
}
                
void GuiGalaxyMap::UnbindGalaxy()
{
    m_Galaxy = nullptr;
}
        
/* virtual override final */
void GuiGalaxyMap::UpdateUnique(client::Player* player)
{    
//    const MouseData& data_mouse = player->cursor().mouseData();
    
//    int radius = player->GetNpc()->vehicle()->properties().hyper * m_ScaleParsecToScreenCoord;
//    m_VisualHyperJumpRange.FillData(GuiTextureObCollector::Instance().dot_yellow, radius, /*dot_size=*/6);

//    glm::vec3 player_starsystem_pos = GetAbsoluteStarSystemPosition(*player->GetNpc()->vehicle()->starsystem());
//    if (player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() == type::AISCENARIO::MICRO_JUMP)
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
//                                Task microtask(type::AISCENARIO::MICRO_JUMP, starsystem.id());
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
void GuiGalaxyMap::RenderUnique(const jeti::Render& render, client::Player* player) const
{
    render.drawQuad(textureOb(), GetBox());    

//    for (unsigned int i=0; i<m_Galaxy->SECTOR_vec.size(); i++)
//    {
//        for (unsigned int j=0; j<m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
//        {
//            const StarSystem& starsystem = *m_Galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
//            glm::vec2 starsystem_pos = meti::vec2(GetAbsoluteStarSystemPosition(starsystem));
                                   
//            //TextureOb* texOb_particle = TextureCollector::Instance().GetTexObByColorId(type::TEXTURE::DISTANTSTAR, starsystem.STAR_vec[0]->GetColorId());
            
//            //render.enable_POINTSPRITE();
//            {
//                //drawParticleTextured(texOb_particle->texture, starsystem_pos, 30.0, -2.0);
                
//                if (starsystem.GetConquerorRaceId() != race::Type::NONE)
//                {
//                    //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, starsystem_pos, 20.0, -2.0);
//                }
                
//                if (starsystem.GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR)
//                {
//                    glm::vec2 offset(0.0, -13.0);
//                    //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_war->texture, starsystem_pos + offset, 20.0, -2.0);
//                }
//            }
//            //render.disable_POINTSPRITE();

//            int font_size = 8;
//            glm::vec2 offset(0.0, 13.0);
//            client::global::get().screen().DrawText(std::to_string(starsystem.id()), font_size, starsystem_pos + offset);
//        }
//    }
    
    //render.enable_POINTSPRITE();
    {
        assert(false);
//        glm::vec2 player_starsystem_pos = meti::vec2(GetAbsoluteStarSystemPosition(*player->GetNpc()->vehicle()->starsystem()));
        
        //drawParticleTextured(GuiTextureObCollector::Instance().starsystem_mark_player->texture, player_starsystem_pos, 40.0, -2.0);
        
        //m_VisualHyperJumpRange.Draw(player_starsystem_pos);
        
        //if (player->GetNpc()->stateMachine().microTaskManager().task().scenarioTypeId() == type::AISCENARIO::MICRO_JUMP)
        {
            //m_VisualHyperJumpPath.Draw();           
        }
    }
    //render.disable_POINTSPRITE();  
}
