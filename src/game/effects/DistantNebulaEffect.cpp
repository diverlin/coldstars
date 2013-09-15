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

#include "DistantNebulaEffect.hpp"
#include "../common/rand.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"

#include "../resources/TextureManager.hpp"

#include "../render/Render.hpp"

#include <glm/gtx/transform.hpp>

DistantNebulaEffect::DistantNebulaEffect()
:
m_Angle(0.f), 
m_DeltaAngle(0.f)
{}
   
DistantNebulaEffect::~DistantNebulaEffect()
{}
   
void DistantNebulaEffect::Update()
{
    m_Angle += m_DeltaAngle;  
}        

void DistantNebulaEffect::Render1(const Render& render)
{
    float rate = 2.0f;   
    glm::vec3 center(m_Center.x*rate, m_Center.y*rate, m_Center.z);
    glm::mat4 Tm = glm::translate(m_Center);
    glm::mat4 Rm = glm::rotate(m_Angle, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Sm = glm::scale(m_Size*rate);
      
    glm::mat4 Mm = Tm * Rm * Sm;
    
    render.DrawQuad(m_TextureOb, Mm);
}
              
void DistantNebulaEffect::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    std::string droot = root + "distant_nebula_effect."+int2str(id)+".";
    
    SaveDataUniqueBaseBackGroundEffect(save_ptree, droot);
    SaveDataUniqueDistantNebulaEffect(save_ptree, droot);
}    

void DistantNebulaEffect::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBaseBackGroundEffect(load_ptree);
    LoadDataUniqueDistantNebulaEffect(load_ptree);
}

void DistantNebulaEffect::ResolveData()
{
    ResolveDataUniqueBaseBackGroundEffect();
    ResolveDataUniqueDistantNebulaEffect();
}

void DistantNebulaEffect::SaveDataUniqueDistantNebulaEffect(boost::property_tree::ptree& save_ptree, const std::string& root) const        
{
    save_ptree.put(root+"m_Angle", m_Angle);
    save_ptree.put(root+"m_DeltaAngle", m_DeltaAngle);
}

void DistantNebulaEffect::LoadDataUniqueDistantNebulaEffect(const boost::property_tree::ptree& load_ptree)
{
    m_Angle = load_ptree.get<float>("m_Angle");
    m_DeltaAngle = load_ptree.get<float>("m_DeltaAngle");
}

void DistantNebulaEffect::ResolveDataUniqueDistantNebulaEffect()
{}



DistantNebulaEffect* GetNewDistantNebulaEffect(int color_id)
{
    TextureOb* textureOb = nullptr;
    if (color_id == NONE_ID)     textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::NEBULA_BACKGROUND_ID);
    else                         textureOb = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::NEBULA_BACKGROUND_ID, color_id);    
           
    float angle = getRandInt(0, 360);
    float delta_angle = 0.0;
    if(textureOb->is_rotated)
    {
        delta_angle = getRandInt(8,12)*0.001 * getRandSign();        
    }
    
    glm::vec3 center(getRandSign()*(float)getRandInt(0, 1000), getRandSign()*(float)getRandInt(0, 1000), -getRandInt(200, 499));
    
    DistantNebulaEffect* dn = new DistantNebulaEffect();
    dn->SetTextureOb(textureOb);
    dn->SetCenter(center);
    dn->SetAngle(angle);
    dn->SetDeltaAngle(delta_angle);
    
    return dn;
}
