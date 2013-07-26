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

#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include "textureOb.hpp"
#include <types/TextureTypes.hpp>
#include "../common/IdGenerator.hpp"
#include "../common/common.hpp"
#include "../render/Screen.hpp"

TextureOb::TextureOb()
{}

TextureOb::TextureOb(TYPE::TEXTURE type_id, const std::string& path, bool use_alpha, std::vector<int>* args, int columns_num, int rows_num, int fps)
{
	const std::string path_normalmap = "";
	Manage(type_id, path, path_normalmap, use_alpha, args, columns_num, rows_num, fps);
}

TextureOb::TextureOb(TYPE::TEXTURE type_id, const std::string& path, const std::string& path_normalmap, bool use_alpha, std::vector<int>* args, int columns_num, int rows_num, int fps)
{
	Manage(type_id, path, path_normalmap, use_alpha, args, columns_num, rows_num, fps);
}

void TextureOb::Manage(TYPE::TEXTURE type_id, const std::string& path, const std::string& path_normalmap, bool use_alpha, std::vector<int>* args, int columns_num, int rows_num, int fps)
{
    	// textureOb attributes INIT
    	race_id = TYPE::RACE::NONE_ID;
    	tech_level_id = NONE_ID;

    	color_id = NONE_ID;
    	is_rotated = false;
    	//

    	this->type_id = type_id; 
    	id = TextureIdGenerator::Instance().GetNextId();
    
    	this->path = path;
    	this->use_alpha = use_alpha;
    
    
    	if ( ((columns_num == 1) and (rows_num == 1)) or (fps == 0) )
    	{
        	is_animated = false;
    	}
    	else
    	{
        	is_animated = true;
   	}   
    	
    	if (path_normalmap != "")
    	{
    		loadToVRAM(path_normalmap, normalmap, w, h); 
    	}
    	loadToVRAM(path, texture, w, h); 
        createTextureCoords(columns_num, rows_num, fps); 
        //removeFromVRAM();     
       
   	is_loaded = false;
    	is_shared = false;

        size_id = getObjectSize(w, h);

	switch(type_id)
	{
        case TYPE::TEXTURE::ITEM_SLOT_ID:   { itemslotArgManager(args);   break; }
        case TYPE::TEXTURE::VEHICLE_SLOT_ID: { vehicleslotArgManager(args);   break; }
        case TYPE::TEXTURE::TURREL_ID: { turrelArgManager(args); break; }

        case TYPE::TEXTURE::NEBULA_BACKGROUND_ID: { nebulaArgManager(args); break; }          
        case TYPE::TEXTURE::STAR_ID:   { starArgManager(args); break; } 
 		case TYPE::TEXTURE::PLANET_ID: { planetArgManager(args); break; }
         
        case TYPE::TEXTURE::ATMOSPHERE_ID: { atmosphereArgManager(args); break; }

        case TYPE::TEXTURE::NATURELAND_BACKGROUND_ID: { landBgArgManager(args); break; }
        
        // KOSMOPORT
        case TYPE::TEXTURE::ANGAR_BACKGROUND_ID: { angarBgArgManager(args); break; }
   		case TYPE::TEXTURE::STORE_BACKGROUND_ID: { storeBgArgManager(args); break; }
		case TYPE::TEXTURE::SHOP_BACKGROUND_ID:  { shopBgArgManager(args);  break; }
        case TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID: { govermentBgArgManager(args); break; }
        case TYPE::TEXTURE::FACE_ID:         { faceArgManager(args); break; }
    
        case TYPE::TEXTURE::SPACESTATION_ID:   { spacestationArgManager(args); break; }    	
        case TYPE::TEXTURE::SATELLITE_ID:  { satelliteArgManager(args); break; }
        case TYPE::TEXTURE::SHIP_ID:     { shipArgManager(args); break; }
        case TYPE::TEXTURE::PARTICLE_EFFECT_ID: { particleArgManager(args); break; }
        
        case TYPE::TEXTURE::DISTANTSTAR_ID:   { distStarArgManager(args); break; }
        case TYPE::TEXTURE::SHIELD_EFFECT_ID: { shieldEffectArgManager(args); break; }
        
        // ITEMS
        case TYPE::TEXTURE::DRIVE_EQUIPMENT_ID:  { DriveEquipmentArgManager(args); break; }
        case TYPE::TEXTURE::LAZER_EQUIPMENT_ID:  { LazerEquipmentArgManager(args); break; }
        case TYPE::TEXTURE::ROCKET_EQUIPMENT_ID: { RocketEquipmentArgManager(args); break; }
		case TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID: { ProtectorEquipmentArgManager(args); break; }
   		case TYPE::TEXTURE::DROID_EQUIPMENT_ID:  { DroidEquipmentArgManager(args); break; }
		case TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID: { GrappleEquipmentArgManager(args); break; }
		case TYPE::TEXTURE::BAK_EQUIPMENT_ID:     { BakEquipmentArgManager(args); break; }
		case TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID: { energyBlockItemArgManager(args); break; }
        case TYPE::TEXTURE::FREEZER_EQUIPMENT_ID: { FreezerEquipmentArgManager(args);  break; }
        case TYPE::TEXTURE::RADAR_EQUIPMENT_ID:   { RadarEquipmentArgManager(args); break; }
        case TYPE::TEXTURE::SCANER_EQUIPMENT_ID:  { ScanerEquipmentArgManager(args); break; }
        
        // BULLETS
        case TYPE::TEXTURE::ROCKET_BULLET_ID: { rocketBulletArgManager(args); break; }
        case TYPE::TEXTURE::LAZER_EFFECT_ID:  { lazerEffectArgManager(args); break; }
        
        // ASTEROIDS/MINERALS
        case TYPE::TEXTURE::ASTEROID_ID: { asteroidArgManager(args); break; }
        case TYPE::TEXTURE::MINERAL_ID:  { mineralArgManager(args); break; }
        case TYPE::TEXTURE::CONTAINER_ID: { containerArgManager(args); break; }
        case TYPE::TEXTURE::BOMB_ID: { bombArgManager(args); break; }
        case TYPE::TEXTURE::BLACKHOLE_ID: { blackholeArgManager(args); break; }
        
        case TYPE::TEXTURE::NONE_ID: { break; }
		
	}
}  

int TextureOb::GetFrameWidth() const  { return w_slice; }
int TextureOb::GetFrameHeight() const { return h_slice;}
 
void TextureOb::removeFromVRAM()
{}         


void TextureOb::createTextureCoords(int _columns_num, int _rows_num, int _fps)
{
	frame = 0;
     	frames_total_num = 0;

     	w_slice = w/_columns_num;
     	h_slice = h/_rows_num;

     	float w_slicef, h_slicef;
     	w_slicef = (float)w_slice/w;  
     	h_slicef = (float)h_slice/h;

     	float w_offsetf, h_offsetf;

     	h_offsetf = 0;
     	int r = 0;
     	while (r < _rows_num)
     	{
           	w_offsetf = 0;
           	int c = 0;
           	while (c < _columns_num)
           	{
               		addTexCoordQuad(w_offsetf, h_offsetf, w_offsetf + w_slicef, h_offsetf + h_slicef);
               		w_offsetf += w_slicef;
               		frames_total_num++;
               		c++;
           	}
           	h_offsetf += h_slicef;
           	r++;
     	}

     	last_update_time = 0;
     	
     	if (_fps == 0) 
     	{
        	fps = frames_total_num*1.3;
     	}
     	else 
        {
        	fps = _fps;
        }
     	
     	delay = 1.f/fps;
}


void TextureOb::addTexCoordQuad(float _w_start, float _h_start, float _w_end, float _h_end)
{
     	texCoord_bottomLeft_vec.push_back( Vec2<float>(_w_start, _h_start));   // (0, 0)
     	texCoord_bottomRight_vec.push_back(Vec2<float>(_w_end,   _h_start));   // (1, 0)
     	texCoord_topLeft_vec.push_back(    Vec2<float>(_w_start, _h_end));     // (0, 1)
     	texCoord_topRight_vec.push_back(   Vec2<float>(_w_end,   _h_end));     // (1, 1)
}

int TextureOb::updateAnimationFrame()
{
	if (is_animated)
	{
		float elapsed_time = Screen::Instance().GetElapsedTimeInSeconds();
     		if (elapsed_time - last_update_time > delay)
     		{
         		frame++;
         		if ( frame >= frames_total_num )
         		{
              			frame = 0;
              		}
         		last_update_time = elapsed_time;
     		} 
	
     		return frame;
     	}
     	else
     	{
     		return 0;
     	} 
}


void TextureOb::itemslotArgManager(std::vector<int>* arg)
{}

void TextureOb::vehicleslotArgManager(std::vector<int>* arg)
{}
   
void TextureOb::turrelArgManager(std::vector<int>* arg)
{}
   

// SPACE OBJECTS
void TextureOb::spacestationArgManager(std::vector<int>* arg)
{}

void TextureOb::satelliteArgManager(std::vector<int>* arg)
{}
   
void TextureOb::shipArgManager(std::vector<int>* arg)
{
    race_id    = (TYPE::RACE)(*arg)[0];
    subtype_id = (TYPE::ENTITY)(*arg)[1];   // warrior/trader and so on
    mod_id     = 0;
}

void TextureOb::nebulaArgManager(std::vector<int>* arg)
{
    color_id    = (*arg)[0];
    is_rotated =  (*arg)[1];
}

void TextureOb::starArgManager(std::vector<int>* arg)
{
	color_id        = (*arg)[0];
	brightThreshold = (float)(*arg)[1]/1000;
}

void TextureOb::planetArgManager(std::vector<int>* arg)
{}

void TextureOb::atmosphereArgManager(std::vector<int>* arg)
{}


void TextureOb::asteroidArgManager(std::vector<int>* arg)
{}

void TextureOb::mineralArgManager(std::vector<int>* arg)
{}

void TextureOb::containerArgManager(std::vector<int>* arg)
{}

void TextureOb::bombArgManager(std::vector<int>* arg)
{}

void TextureOb::blackholeArgManager(std::vector<int>* arg)
{}

//######### IN KOSMOPORT
void TextureOb::landBgArgManager(std::vector<int>* arg)
{}

void TextureOb::angarBgArgManager(std::vector<int>* arg)
{}

void TextureOb::storeBgArgManager(std::vector<int>* arg)
{}

void TextureOb::shopBgArgManager(std::vector<int>* arg)
{}

void TextureOb::govermentBgArgManager(std::vector<int>* arg)
{}

void TextureOb::faceArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	subtype_id    = (TYPE::ENTITY)(*arg)[1];   // warrior/trader and so on
}


// ITEMS
void TextureOb::DriveEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::LazerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
   	color_id      = (*arg)[2];
}

void TextureOb::RocketEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
  	 color_id      = (*arg)[2];
}

void TextureOb::ProtectorEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::DroidEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::GrappleEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::BakEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::energyBlockItemArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::FreezerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::RadarEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb::ScanerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (TYPE::RACE)(*arg)[0];
   	tech_level_id = (*arg)[1];
}


//# BULLETS
void TextureOb::rocketBulletArgManager(std::vector<int>* arg)
{}

void TextureOb::torpedBulletArgManager(std::vector<int>* arg)
{}

void TextureOb::particleArgManager(std::vector<int>* arg)
{
        color_id = (*arg)[0];
}

//int TextureOb::getParticleFrameNumByColorId(int _color_id)
//{
        //for(unsigned int i = 0; i < color_id_vec.size(); i++)
        //{
                //if (color_id_vec[i] == _color_id)
                //{
                        //return i;
                //}                
        //}
        
        //return 0;           
//}

void TextureOb::distStarArgManager(std::vector<int>* arg)
{
	color_id        = (*arg)[0];
}

void TextureOb::lazerEffectArgManager(std::vector<int>* arg)
{
   	tech_level_id = (*arg)[0];
   	color_id      = (*arg)[1];
}

void TextureOb::shieldEffectArgManager(std::vector<int>* arg)
{
   	color_id = (*arg)[0];
}






       	
void loadToVRAM(const std::string& path, GLuint& texture, int& w, int& h)
{
    sf::Image image;
    if (!image.loadFromFile(path))
 	{
 		std::cout<<"FAULT: Not abe to open file:"<<path;
 		exit(EXIT_FAILURE);
 	}
     	
    image.flipVertically();
    
    w = image.getSize().x;
    h = image.getSize().y;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}         




