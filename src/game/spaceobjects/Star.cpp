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
#include "../common/constants.hpp"
#include "../world/EntityManager.hpp"
#include "../common/myStr.hpp"
#include "../common/common.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../resources/ShaderCollector.hpp"

#include "../common/Logger.hpp"

   
Star::Star(int id)
{ 
	data_id.id = id;
	data_id.type_id = ENTITY::STAR_ID;
	
   	texture_offset1 = 0.0;
    	texture_offset2 = 0.0;
    	
    	d_color = 0.0;
    	
    	spark_active = false;
    	spark_grows = false;
    	
    	turn_since_last_spark_counter = 0;
    	turn_spark_threshold = getRandInt(STARSPAK_TURN_THRESHOLD_MIN, STARSPAK_TURN_THRESHOLD_MAX);
}
  
/* virtual */  
Star::~Star()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Star("+int2str(GetId())+")");
	#endif	
}
    
void Star::CalcColor()
{
	color = getColor4fById(textureOb->color_id);
}
       
void Star::InitiateSpark()
{
	spark_active = true;
	spark_grows = true;
    	turn_since_last_spark_counter = 0;
}

void Star::UpdateInSpaceInStatic()
{
	if (turn_since_last_spark_counter > turn_spark_threshold)
	{
		if (getRandInt(1, 2) == 1) 
		{
			InitiateSpark(); 
		}
	}
	else
	{
		turn_since_last_spark_counter++;	
	}
}
       		
void Star::UpdateInSpace(int time, bool show_effect)
{
        texture_offset1 += 0.0002;
        texture_offset2 += 0.0003;

	if (spark_active == true)
	{
		if (show_effect == true)
		{
			if (spark_grows == true)
			{
				d_color += 0.02;
				scale += 0.2;
				if (d_color > 1.0)
				{
					d_color = 1.0;
					starsystem->StarSparkEvent(getRandInt(600, 1200));
					spark_grows = false;
				}
			} 
			else
			{		
				d_color -= 0.005;	
				scale -= 0.05;
				if (d_color < 0.0)
				{
					d_color = 0;
					spark_active = false;
				}

			}
		}
		else
		{
			starsystem->StarSparkEvent(getRandInt(600, 1200));
			spark_active = false;
		}
	}

	//UpdateRotation(); // not relevant for render NEW
}    
    
void Star::Render_NEW() const
{
        glUseProgram(ShaderCollector::Instance().multitexturing);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, textureOb->texture);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "Texture_0"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, textureOb->texture);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "Texture_1"), 1);
        
	glUniform2f(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "displ"), texture_offset1, texture_offset2);

	renderMesh(mesh, points.GetCenter3f(), angle, scale, false);

        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
}
        
void Star::Render_OLD() const
{    
     	glBindTexture(GL_TEXTURE_2D, textureOb->texture);      		
	renderMesh(mesh, points.GetCenter3f(), angle, scale, ZYX);
}

void Star::UpdateInfo()
{ 
	info.clear();
    	info.addTitleStr("STAR");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
}

void Star::PostDeathUniqueEvent(bool)
{}

   
void Star::SaveDataUniqueStar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Star("+int2str(GetId())+")::SaveDataUniqueStar", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"turn_since_last_spark_counter", turn_since_last_spark_counter);
	save_ptree.put(root+"turn_spark_threshold", turn_spark_threshold);
}

void Star::LoadDataUniqueStar(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Star("+int2str(GetId())+")::LoadDataUniqueStar", SAVELOAD_LOG_DIP);
	#endif
	
	turn_since_last_spark_counter = load_ptree.get<int>("turn_since_last_spark_counter");
	turn_spark_threshold = load_ptree.get<int>("turn_spark_threshold");	
}

void Star::ResolveDataUniqueStar()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Star("+int2str(GetId())+")::ResolveDataUniqueStar", SAVELOAD_LOG_DIP);
	#endif
	
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this); 	
}


void Star::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "star." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniqueStar(save_ptree, root);
}

void Star::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniqueStar(load_ptree);
}

void Star::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniqueStar();
}
