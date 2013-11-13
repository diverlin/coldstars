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

#include "DistantStarEffect.hpp"
#include "../common/myStr.hpp"
#include "../common/constants.hpp"
#include "../common/rand.hpp"

#include "../resources/TextureManager.hpp"

DistantStarEffect::DistantStarEffect()
{}

DistantStarEffect::~DistantStarEffect()
{}

void DistantStarEffect::Render(const Renderer& render) const
{   
    render.DrawParticleTextured(m_TextureOb, m_Center, m_Size.x);
}

   
void DistantStarEffect::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    std::string droot = root + "distant_star_effect."+int2str(id)+".";
    
    SaveDataUniqueBaseBackGroundEffect(save_ptree, droot);
    SaveDataUniqueDistantStarEffect(save_ptree, droot);
}    

void DistantStarEffect::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBaseBackGroundEffect(load_ptree);
    LoadDataUniqueDistantStarEffect(load_ptree);
}

void DistantStarEffect::ResolveData()
{
    ResolveDataUniqueBaseBackGroundEffect();
    ResolveDataUniqueDistantStarEffect();
}


        

void DistantStarEffect::SaveDataUniqueDistantStarEffect(boost::property_tree::ptree&, const std::string&) const        
{}

void DistantStarEffect::LoadDataUniqueDistantStarEffect(const boost::property_tree::ptree&)
{}

void DistantStarEffect::ResolveDataUniqueDistantStarEffect()
{}        
        
   
DistantStarEffect* GetNewDistantStarEffect(int color_id)
{
    TextureOb* textureOb = nullptr;
    if (color_id == NONE_ID)    textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::DISTANTSTAR_ID);
    else                        textureOb = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::DISTANTSTAR_ID, color_id);
        
    float size_x = (float)getRandInt(ENTITY::GALAXY::DISTANTSTAR_SIZE_MIN, ENTITY::GALAXY::DISTANTSTAR_SIZE_MAX);
    glm::vec3 size(size_x, size_x, 1.0);
    glm::vec3 center(getRandSign()*getRandInt(0, 1000), getRandSign()*getRandInt(0, 1000), -getRandInt(200, 499));        
            
    DistantStarEffect* ds = new DistantStarEffect();
    ds->SetTextureOb(textureOb);
    ds->SetCenter(center);
    ds->SetSize(size);
    
    return ds;
}
