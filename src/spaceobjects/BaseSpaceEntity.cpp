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

#include "BaseSpaceEntity.hpp"
#include "../resources/MeshCollector.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include <math/rand.hpp>
#include "../common/myStr.hpp"
#include "../render/Render.hpp"


#include <render/Screen.hpp>


BaseSpaceEntity::BaseSpaceEntity():
m_Starsystem(nullptr), 
m_Mass(0), 
m_GiveExpirience(0),
m_Parent(nullptr)
{}

/* virtual override */
BaseSpaceEntity::~BaseSpaceEntity()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseSpaceEntity("+int2str(GetId())+")");
    #endif
}

void BaseSpaceEntity::ApplyImpulse(const glm::vec3& force_dir, float strength)
{
    m_AppliedForce += force_dir * strength;
}

/* virtual */
void BaseSpaceEntity::Hit(int damage, bool show_effect)
{
    m_DataLife.armor -= damage;
    if (m_DataLife.armor <= 0)
    {
        m_DataLife.is_alive = false; 
        m_DataLife.dying_time -= 3;
    }

//    if (show_effect == true)
//    {
//        VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, vec3ToVec2(GetCenter()), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
//        m_Starsystem->Add(text);
//    }

}

void BaseSpaceEntity::SilentKill()
{
    m_DataLife.is_alive      = false;  
    m_DataLife.garbage_ready = true;
}

void BaseSpaceEntity::CheckDeath(bool show_effect)
{
    if (m_DataLife.is_alive == false)
    {
        m_DataLife.dying_time--;
        if (m_DataLife.dying_time < 0)
        {
            if (m_DataLife.garbage_ready == false)
            {   
                PostDeathUniqueEvent(show_effect);
                m_DataLife.garbage_ready = true;
            }
        }
    }  
}

/* virtual */        
void BaseSpaceEntity::RenderInfoInSpace(const Renderer&, const glm::vec2& scroll_coords, float scale)
{ 
//    UpdateInfo(); // virtual
//    glm::vec2 pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
//    drawInfoIn2Column(m_Info.title_list, m_Info.value_list, pos/scale);
}

void BaseSpaceEntity::RenderInfo(const glm::vec2& center)
{ 
//    UpdateInfo(); // virtual
//    drawInfoIn2Column(m_Info.title_list, m_Info.value_list, center);
}
    






