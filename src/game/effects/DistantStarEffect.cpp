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
#include <math/rand.hpp>

#include "../resources/TextureManager.hpp"                                           
#include <render/Mesh.hpp>


DistantStarEffect::DistantStarEffect(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors)
{
    for (unsigned int i=0; i<positions.size(); i++)
    {
        m_Positions.push_back(positions[i]);
        m_Colors.push_back(colors[i]);
    }

    m_Mesh = new Mesh();
    m_Mesh->FillPointVertices(m_Positions, m_Colors);
}

DistantStarEffect::~DistantStarEffect()
{
    delete m_Mesh;
}

void DistantStarEffect::Render(const Renderer& render) const
{   
    //render.DrawParticles(GetMesh(), GetTextureOb());
}
            

void DistantStarEffect::SaveData(boost::property_tree::ptree&, const std::string&) const        
{}

void DistantStarEffect::LoadData(const boost::property_tree::ptree&)
{}

void DistantStarEffect::ResolveData()
{}        
        
  
 
void DistantStarEffect::Save(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    std::string droot = root + "distant_star_effect."+int2str(id)+".";
    
    BaseBackGroundEffectSaveData(save_ptree, droot);
    DistantStarEffect::SaveData(save_ptree, droot);
}    

void DistantStarEffect::Load(const boost::property_tree::ptree& load_ptree)
{
    BaseBackGroundEffect::LoadData(load_ptree);
    DistantStarEffect::LoadData(load_ptree);
}

void DistantStarEffect::Resolve()
{
    BaseBackGroundEffect::ResolveData();
    DistantStarEffect::ResolveData();
}

 
DistantStarEffect* GetNewDistantStarEffect(int color_id)
{
    int distStar_num = getRandInt(DISTANT_STAR_MIN, DISTANT_STAR_MAX);

    TextureOb* textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::DISTANTSTAR_ID);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;

    for (int i=0; i<distStar_num; i++)
    {
        float z = -getRandInt(200, 499);
        glm::vec3 position = getRandXYVec3f(0, 3000, z);

        float r = getRandFloat(0.5, 1.0);
        float g = getRandFloat(0.5, 1.0);
        float b = getRandFloat(0.5, 1.0);
        
        positions.push_back(position);
        colors.push_back(glm::vec4(r, g, b, 1.0f));
    }
            
    DistantStarEffect* ds = new DistantStarEffect(positions, colors);
    ds->SetTextureOb(textureOb);
    
    return ds;
}
