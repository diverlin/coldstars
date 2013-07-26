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

void DistantStarEffect::Render(float vx, float vy)
{   
	glPointSize(size.x);
	//glColor4<float>(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	
	glBegin(GL_POINTS);
		glVertex3f(center.x - vx*parallax_rate, center.y - vy*parallax_rate , center.z);
	glEnd();
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
	if (color_id == NONE_ID) textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::DISTANTSTAR_ID);
	else    	    	 textureOb = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::DISTANTSTAR_ID, color_id);
        
	float size_x = (float)getRandInt(ENTITY::GALAXY::DISTANTSTAR_SIZE_MIN, ENTITY::GALAXY::DISTANTSTAR_SIZE_MAX);
	Vec3<float> size(size_x, size_x, 1.0);
	Vec3<float> center(getRandInt(0, 1000), getRandInt(0, 1000), -2.0);        
			
	DistantStarEffect* ds = new DistantStarEffect();
	ds->SetTextureOb(textureOb);
	ds->SetCenter(center);
	ds->SetSize(size);
	ds->SetParallaxRate(size_x/1000.f);
	
	return ds;
}
