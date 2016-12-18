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
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>

#include <resources/TextureCollector.hpp>

#include <ceti/descriptor/Collector.hpp>
#include <jeti/Render.hpp>
#include <jeti/TextureOb.hpp>


DistantNebulaEffect::DistantNebulaEffect()
{}
   
DistantNebulaEffect::~DistantNebulaEffect()
{}
   
void DistantNebulaEffect::Update()
{
    //m_Angle += m_DeltaAngle;  
}        

/* virtual override */
void DistantNebulaEffect::Render(const jeti::Renderer& render, const glm::vec3&)
{   
    // alpitodorender render.DrawMesh(mesh(), textureOb(), actualModelMatrix());
}
              
void DistantNebulaEffect::Save(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    std::string droot = root + "distant_nebula_effect."+std::to_string(id())+".";
    
    //BaseBackGroundEffect::SaveData(save_ptree, droot);
    DistantNebulaEffect::SaveData(save_ptree, droot);
}    

void DistantNebulaEffect::Load(const boost::property_tree::ptree& load_ptree)
{
    //BaseBackGroundEffect::LoadData(load_ptree);
    DistantNebulaEffect::LoadData(load_ptree);
}

void DistantNebulaEffect::Resolve()
{
    //BaseBackGroundEffect::ResolveData();
    DistantNebulaEffect::ResolveData();
}

void DistantNebulaEffect::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const        
{
    //save_ptree.put(root+"m_Angle", m_Angle);
    //save_ptree.put(root+"m_DeltaAngle", m_DeltaAngle);
}

void DistantNebulaEffect::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //m_Angle = load_ptree.get<float>("m_Angle");
    //m_DeltaAngle = load_ptree.get<float>("m_DeltaAngle");
}

void DistantNebulaEffect::ResolveData()
{}     

DistantNebulaEffect* GetNewDistantNebulaEffect(int color_id)
{
    jeti::Mesh* mesh = nullptr; //MeshCollector::get().get(type::mesh::PLANE_ID);
    assert(mesh);
    jeti::control::Material* textureOb = nullptr;
    if (color_id == NONE)     textureOb = TextureCollector::get().getTextureByTypeId(type::texture::NEBULA_BACKGROUND_ID);
    else                      textureOb = TextureCollector::get().getTextureByColorId(type::texture::NEBULA_BACKGROUND_ID, color_id);
           
    float angle = meti::getRandInt(0, 360);
    float delta_angle = 0.0;
    if(textureOb->model().is_rotated)
    {
        delta_angle = meti::getRandInt(8,12)*0.001 * meti::getRandSign();
    }
    
    float z = -meti::getRandInt(200, 499);
    float rate = 5;
    
    glm::vec3 center(meti::getRandSign()*(float)meti::getRandInt(100, 500*rate), meti::getRandSign()*(float)meti::getRandInt(100, 500*rate), z);
    
    DistantNebulaEffect* dn = new DistantNebulaEffect();
    glm::vec3 size = textureOb->size();
    // alpitodorender dn->SetRenderData(mesh, textureOb, size*=3);

    dn->setPosition(center);
    //dn->SetAngle(angle);
    //dn->SetDeltaAngle(delta_angle);
    
    return dn;
}
