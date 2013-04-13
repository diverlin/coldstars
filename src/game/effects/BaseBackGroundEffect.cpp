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

BaseBackGroundEffect::BaseBackGroundEffect():textureOb(NULL), scale(1.f), parallax_rate(1.f)
{
	counter++;
	id = counter;
}

BaseBackGroundEffect::~BaseBackGroundEffect()
{}

void BaseBackGroundEffect::SaveDataUniqueBaseBackGroundEffect(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"textureOb_path", textureOb->path);
	
	save_ptree.put(root+"center.x", center.x);
	save_ptree.put(root+"center.y", center.y);	
	save_ptree.put(root+"center.z", center.z);
	
	save_ptree.put(root+"scale", scale);	
}

void BaseBackGroundEffect::LoadDataUniqueBaseBackGroundEffect(const boost::property_tree::ptree& load_ptree)
{
	textureOb_path = load_ptree.get<std::string>("textureOb_path");
				
	center.x = load_ptree.get<float>("center.x");
	center.y = load_ptree.get<float>("center.y");
	center.z = load_ptree.get<float>("center.z");
	scale = load_ptree.get<float>("scale");
}
		
void BaseBackGroundEffect::ResolveDataUniqueBaseBackGroundEffect()
{
	textureOb = TextureManager::Instance().GetTextureObByPath(textureOb_path);
}
              
