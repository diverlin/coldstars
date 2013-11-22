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
#include <math/rand.hpp>
#include "../common/constants.hpp"
#include "../common/myStr.hpp"

#include "../resources/TextureManager.hpp"

#include "../render/Render.hpp"

#include "../resources/textureOb.hpp"


DistantNebulaEffect::DistantNebulaEffect()
{}
   
DistantNebulaEffect::~DistantNebulaEffect()
{}
   
void DistantNebulaEffect::Update()
{
    m_Angle += m_DeltaAngle;  
}        

void DistantNebulaEffect::Render(const Renderer& render)
{   
    render.DrawQuad(*m_TextureOb, GetActualModelMatrix());
}
              
void DistantNebulaEffect::Save(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    std::string droot = root + "distant_nebula_effect."+int2str(id)+".";
    
    BaseBackGroundEffect::SaveData(save_ptree, droot);
    DistantNebulaEffect::SaveData(save_ptree, droot);
}    

void DistantNebulaEffect::Load(const boost::property_tree::ptree& load_ptree)
{
    BaseBackGroundEffect::LoadData(load_ptree);
    DistantNebulaEffect::LoadData(load_ptree);
}

void DistantNebulaEffect::Resolve()
{
    BaseBackGroundEffect::ResolveData();
    DistantNebulaEffect::ResolveData();
}

void DistantNebulaEffect::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const        
{
    save_ptree.put(root+"m_Angle", m_Angle);
    save_ptree.put(root+"m_DeltaAngle", m_DeltaAngle);
}

void DistantNebulaEffect::LoadData(const boost::property_tree::ptree& load_ptree)
{
    m_Angle = load_ptree.get<float>("m_Angle");
    m_DeltaAngle = load_ptree.get<float>("m_DeltaAngle");
}

void DistantNebulaEffect::ResolveData()
{}     

DistantNebulaEffect* GetNewDistantNebulaEffect(int color_id)
{
    TextureOb* textureOb = nullptr;
    if (color_id == NONE_ID)     textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::NEBULA_BACKGROUND_ID);
    else                         textureOb = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::NEBULA_BACKGROUND_ID, color_id);    
           
    float angle = getRandInt(0, 360);
    float delta_angle = 0.0;
    if(textureOb->GetData().is_rotated)
    {
        delta_angle = getRandInt(8,12)*0.001 * getRandSign();        
    }
    
    float z = -getRandInt(200, 499);
    float rate = abs(z)/100.0;
    
    glm::vec3 center(getRandSign()*(float)getRandInt(0, 500*rate), getRandSign()*(float)getRandInt(0, 500*rate), z);
    
    DistantNebulaEffect* dn = new DistantNebulaEffect();
    dn->SetTextureOb(textureOb, glm::vec3(rate));
    dn->SetCenter(center);
    dn->SetAngle(angle);
    dn->SetDeltaAngle(delta_angle);
    
    return dn;
}
