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

DistantNebulaEffect::DistantNebulaEffect():angle_inD(0.f), d_angle_inD(0.f)
{}
   
DistantNebulaEffect::~DistantNebulaEffect()
{}
   
void DistantNebulaEffect::Update()
{
     	angle_inD += d_angle_inD;  
}        

void DistantNebulaEffect::Render(float vx, float vy)
{ 
   	drawQuad(textureOb, Vec3<float>(center.x - vx*parallax_rate, center.y - vy*parallax_rate, center.z), size, angle_inD);
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
	save_ptree.put(root+"angle_inD", angle_inD);
	save_ptree.put(root+"d_angle_inD", d_angle_inD);
}

void DistantNebulaEffect::LoadDataUniqueDistantNebulaEffect(const boost::property_tree::ptree& load_ptree)
{
	angle_inD = load_ptree.get<float>("angle_inD");
	d_angle_inD = load_ptree.get<float>("d_angle_inD");
}

void DistantNebulaEffect::ResolveDataUniqueDistantNebulaEffect()
{}

DistantNebulaEffect* GetNewDistantNebulaEffect(int color_id)
{
	TextureOb* textureOb = nullptr;
	if (color_id == NONE_ID) 	textureOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::NEBULA_BACKGROUND_ID);
	else    	    	 		textureOb = TextureManager::Instance().GetTexObByColorId(TEXTURE::NEBULA_BACKGROUND_ID, color_id);	
	   	
	float parallax_rate;
	if(textureOb->GetFrameWidth() * textureOb->GetFrameHeight() > 300000)
    {
		parallax_rate =  1.0/getRandInt(50, 70); 
	}
    else
    {
		parallax_rate =  1.0/getRandInt(30, 50);
	}
    
	float angle_inD = getRandInt(0, 360);
	float d_angle_inD = 0.0;
	if(textureOb->is_rotated)
    {
		d_angle_inD = getRandInt(8,12)*0.001 * getRandSign();    	
	}
	
	Vec3<float> center((float)getRandInt(0, 1000), (float)getRandInt(0, 1000), -999.0);
	
	DistantNebulaEffect* dn = new DistantNebulaEffect();
	dn->SetTextureOb(textureOb);
	dn->SetCenter(center);
	dn->SetParallaxRate(parallax_rate);
	dn->SetAngle(angle_inD);
	dn->SetDAngle(d_angle_inD);
	
	return dn;
}
