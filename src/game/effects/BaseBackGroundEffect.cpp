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

#include "BaseBackGroundEffect.hpp"
#include "../resources/TextureManager.hpp"
#include "../render/Render.hpp"

unsigned long int BaseBackGroundEffect::counter;

BaseBackGroundEffect::BaseBackGroundEffect()
:
m_TextureOb(nullptr)
{
    counter++;
    id = counter;
}

BaseBackGroundEffect::~BaseBackGroundEffect()
{}

void BaseBackGroundEffect::SetTextureOb(TextureOb* textureOb, const glm::vec3& scale_factor)
{
    m_TextureOb = textureOb; 
    m_Size.x = m_TextureOb->GetFrameWidth()  * scale_factor.x;
    m_Size.y = m_TextureOb->GetFrameHeight() * scale_factor.y;
    m_Size.z = 1.0 * scale_factor.z; 
};
            
void BaseBackGroundEffect::SaveDataUniqueBaseBackGroundEffect(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"textureOb_path", m_TextureOb->path);
    
    save_ptree.put(root+"center.x", m_Center.x);
    save_ptree.put(root+"center.y", m_Center.y);    
    save_ptree.put(root+"center.z", m_Center.z);

    save_ptree.put(root+"size.x", m_Size.x);
    save_ptree.put(root+"size.y", m_Size.y);    
    save_ptree.put(root+"size.z", m_Size.z);
}

void BaseBackGroundEffect::LoadDataUniqueBaseBackGroundEffect(const boost::property_tree::ptree& load_ptree)
{
    m_TextureObPath = load_ptree.get<std::string>("textureOb_path");
                
    m_Center.x = load_ptree.get<float>("center.x");
    m_Center.y = load_ptree.get<float>("center.y");
    m_Center.z = load_ptree.get<float>("center.z");
    
    m_Size.x = load_ptree.get<float>("size.x");
    m_Size.y = load_ptree.get<float>("size.y");
    m_Size.z = load_ptree.get<float>("size.z");
}
        
void BaseBackGroundEffect::ResolveDataUniqueBaseBackGroundEffect()
{
    m_TextureOb = TextureManager::Instance().GetTextureObByPath(m_TextureObPath);
}
              
