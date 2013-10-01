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

#include "Atmosphere.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../spaceobjects/BaseSpaceEntity.hpp"
#include "../world/starsystem.hpp"

#include "../common/Logger.hpp"

Atmosphere::Atmosphere()
:
m_Parent(nullptr)
{}

Atmosphere::~Atmosphere()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Atmosphere");
    #endif    
}
             
void Atmosphere::Render(const Renderer& render)
{      
    SetCenter(m_Parent->GetCenter());
    render.RenderMeshLight(GetMesh(), GetTextureOb(), GetActualModelMatrix());
       
    //angle += d_angle;
    
    //const glm::vec4& color = parent->GetStarSystem()->GetColor4f(); 
    //float ambient_factor = 0.25;
    
    //glUseProgram(ShaderCollector::Instance().light);
    
    //glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light, "lightPos"), -scroll_coords.x, -scroll_coords.y, -200.0);
    //glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light, "eyePos"), -scroll_coords.x, -scroll_coords.y, -200.0);
    //glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "diffColor"), color.r, color.g, color.b, color.a);
    //glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "ambientColor"), ambient_factor*color.r, ambient_factor*color.g, ambient_factor*color.b, ambient_factor*color.a);
    
    //glEnable(GL_BLEND);
    //glActiveTexture(GL_TEXTURE0);                                
    //glBindTexture(GL_TEXTURE_2D, textureOb->texture);
    //glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light, "Texture_0"), 0);
    //float scale_rate = 1.05;
    //glm::vec3 size(parent->GetSize()*scale_rate);
    
    //renderMesh(parent->GetMesh(), parent->GetCenter(), size, angle, false);
    //glDisable(GL_BLEND);
    
    //glUseProgram(0);
    //glActiveTexture(GL_TEXTURE0);
}

