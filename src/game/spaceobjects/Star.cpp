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

#include "Star.hpp"

#include <common/myStr.hpp>
#include <math/rand.hpp>


#include <resources/textureOb.hpp>

#include <glm/gtx/transform.hpp>

#include "resources/MeshCollector.hpp"
#include "resources/TextureManager.hpp"
   
#include <common/constants.hpp>

glm::vec4 getColor4fById(int color_id)
{
    glm::vec4 color;
    switch(color_id)
    {
        case COLOR::YELLOW_ID:
        {
            color.r = 255/255.0;
            color.g = 255/255.0;
            color.b = 235/255.0; // 235
            color.a = 1.0;

            break;
        }

        case COLOR::BLUE_ID:
        {
            color.r = 220/255.0; // 220
            color.g = 255/255.0;
            color.b = 255/255.0;
            color.a = 1.0;

            break;
        }
    }

    return color;
}


Star::Star(int id)
:
m_Offset(0.0),
m_DeltaColor(0.0)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::STAR_ID);
}
  
/* virtual */  
Star::~Star()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Star("+int2str(GetId())+")");
    #endif    
}

int Star::GetColorId() const { return GetTextureOb().GetData().color_id; }

float Star::GetBrightThreshold() const { return GetTextureOb().GetData().brightThreshold; }
            
void Star::CalcColor()
{
    SetColor(getColor4fById(GetTextureOb().GetData().color_id));
}
       
void Star::UpdateInSpaceInStatic()
{

}
               
void Star::UpdateInSpace(int time, bool show_effect)
{

}    

void Star::Update()
{
   m_Offset += getRandFloat(0.0001, 0.0005);
}

/* virtual override final */
void Star::PostDeathUniqueEvent(bool)
{}  

Star* GetNewStar()
{
    Star* star = new Star(0);
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPHERE_ID);

    LifeData data_life;
    data_life.armor = 1000000;

    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::STAR_ID);

    star->SetLifeData(data_life);
    float scale_comp = getRandInt(100, 200);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    star->SetRenderData(mesh, texOb, scale);

    star->CalcColor();

    return star;
}
