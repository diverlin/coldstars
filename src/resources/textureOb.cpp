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

#include "../common/constants.hpp"
#include "../render/Screen.hpp"

TextureOb :: TextureOb()
{}

TextureOb :: TextureOb(int _type_id, std::string _path, bool _use_alpha, std::vector<int>* pTo_arg, int _columns_num, int _rows_num, int _fps)
{
    	// textureOb attributes INIT
    	race_id = -1;
    	tech_level_id = -1;

    	color_id = -1;
    	is_rotated = false;
    	//

    	type_id = _type_id; 
    	id      = TextureIdGenerator::Instance().GetNextId();
    
    	path      = _path;
    	use_alpha = _use_alpha;
    
    
    	if ( ((_columns_num == 1) and (_rows_num == 1)) or (_fps == 0) )
    	{
        	is_animated = false;
    	}
    	else
    	{
        	is_animated = true;
   	}   
    	
    	loadToVRAM(); 
        createTextureCoords(_columns_num, _rows_num, _fps); 
        //removeFromVRAM();     
       
   	is_loaded = false;
    	is_shared = false;

        size_id = returnObjectSize(w, h);

	switch(type_id)
	{
    		case TEXTURE::ITEM_SLOT_ID:   { itemslotArgManager(pTo_arg);   break; }
    		case TEXTURE::VEHICLE_SLOT_ID: { vehicleslotArgManager(pTo_arg);   break; }
    		case TEXTURE::TURREL_ID: { turrelArgManager(pTo_arg); break; }

    		case TEXTURE::NEBULA_BACKGROUND_ID: { nebulaArgManager(pTo_arg); break; }          
    		case TEXTURE::STAR_ID:   { starArgManager(pTo_arg); break; } 
 		case TEXTURE::PLANET_ID: { planetArgManager(pTo_arg); break; }
         
    		case TEXTURE::ATMOSPHERE_ID: { atmosphereArgManager(pTo_arg); break; }
 
    		case TEXTURE::LAND_BACKGROUND_ID: { landBgArgManager(pTo_arg); break; }
    		
    		// KOSMOPORT
    		case TEXTURE::ANGAR_BACKGROUND_ID: { angarBgArgManager(pTo_arg); break; }
   		case TEXTURE::STORE_BACKGROUND_ID: { storeBgArgManager(pTo_arg); break; }
		case TEXTURE::SHOP_BACKGROUND_ID:  { shopBgArgManager(pTo_arg);  break; }
    		case TEXTURE::GOVERMENT_BACKGROUND_ID: { govermentBgArgManager(pTo_arg); break; }
    		case TEXTURE::FACE_ID:         { loadToVRAM(); faceArgManager(pTo_arg); break; }
 		
    		case TEXTURE::SPACESTATION_ID:   { loadToVRAM(); spacestationArgManager(pTo_arg); break; }    	
    		case TEXTURE::SATELLITE_ID:  { loadToVRAM(); satelliteArgManager(pTo_arg); break; }
		case TEXTURE::SHIP_ID:     { loadToVRAM(); shipArgManager(pTo_arg); break; }
          	case TEXTURE::PARTICLE_EFFECT_ID: { loadToVRAM(); particleArgManager(pTo_arg); break; }

		case TEXTURE::DISTANTSTAR_ID:   { loadToVRAM(); distStarArgManager(pTo_arg); break; }
    		case TEXTURE::SHIELD_EFFECT_ID: { loadToVRAM(); shieldEffectArgManager(pTo_arg); break; }

    		// ITEMS
    		case TEXTURE::DRIVE_EQUIPMENT_ID:  { loadToVRAM(); DriveEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::LAZER_EQUIPMENT_ID:  { loadToVRAM(); LazerEquipmentArgManager(pTo_arg); break; }
    		case TEXTURE::ROCKET_EQUIPMENT_ID: { loadToVRAM(); RocketEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::PROTECTOR_EQUIPMENT_ID: { loadToVRAM(); ProtectorEquipmentArgManager(pTo_arg); break; }
   		case TEXTURE::DROID_EQUIPMENT_ID:  { loadToVRAM(); DroidEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::GRAPPLE_EQUIPMENT_ID: { loadToVRAM(); GrappleEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::BAK_EQUIPMENT_ID:     { loadToVRAM(); BakEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::ENERGIZER_EQUIPMENT_ID: { loadToVRAM(); energyBlockItemArgManager(pTo_arg); break; }
     		case TEXTURE::FREEZER_EQUIPMENT_ID: { loadToVRAM(); FreezerEquipmentArgManager(pTo_arg);  break; }
    		case TEXTURE::RADAR_EQUIPMENT_ID:   { loadToVRAM(); RadarEquipmentArgManager(pTo_arg); break; }
		case TEXTURE::SCANER_EQUIPMENT_ID:  { loadToVRAM(); ScanerEquipmentArgManager(pTo_arg); break; }
		
		// BULLETS
    		case TEXTURE::ROCKET_BULLET_ID: { loadToVRAM(); rocketBulletArgManager(pTo_arg); break; }
    		case TEXTURE::LAZER_EFFECT_ID:  { loadToVRAM(); lazerEffectArgManager(pTo_arg); break; }

		// ASTEROIDS/MINERALS
    		case TEXTURE::ASTEROID_ID: { loadToVRAM(); asteroidArgManager(pTo_arg); break; }
		case TEXTURE::MINERAL_ID:  { loadToVRAM(); mineralArgManager(pTo_arg); break; }
    		case TEXTURE::CONTAINER_ID: { loadToVRAM(); containerArgManager(pTo_arg); break; }
		case TEXTURE::BOMB_ID: { loadToVRAM(); bombArgManager(pTo_arg); break; }
		case TEXTURE::BLACKHOLE_ID: { loadToVRAM(); blackholeArgManager(pTo_arg); break; }
	}
}  

int TextureOb :: GetFrameWidth() const  { return w_slice; }
int TextureOb :: GetFrameHeight() const { return h_slice;}
        	
void TextureOb :: loadToVRAM()
{
     	sf::Image Image;
     	Image.LoadFromFile(path);
     	w = Image.GetWidth();
     	h = Image.GetHeight();

     	glGenTextures(1, &texture);
     	glBindTexture(GL_TEXTURE_2D, texture);
     	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
        
     	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}         

void TextureOb :: removeFromVRAM()
{}         


void TextureOb :: createTextureCoords(int _columns_num, int _rows_num, int _fps)
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


void TextureOb :: addTexCoordQuad(float _w_start, float _h_start, float _w_end, float _h_end)
{
     	texCoord_bottomLeft_vec.push_back( vec2f(_w_start, _h_start));   // (0, 0)
     	texCoord_bottomRight_vec.push_back(vec2f(_w_end,   _h_start));   // (1, 0)
     	texCoord_topLeft_vec.push_back(    vec2f(_w_start, _h_end));     // (0, 1)
     	texCoord_topRight_vec.push_back(   vec2f(_w_end,   _h_end));     // (1, 1)
}

int TextureOb :: updateAnimationFrame()
{
	if (is_animated)
	{
		float elapsed_time = Screen::Instance().GetPreciseClock().GetElapsedTime();
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


void TextureOb :: itemslotArgManager(std::vector<int>* arg)
{}

void TextureOb :: vehicleslotArgManager(std::vector<int>* arg)
{}
   
void TextureOb :: turrelArgManager(std::vector<int>* arg)
{}
   

// SPACE OBJECTS
void TextureOb :: spacestationArgManager(std::vector<int>* arg)
{}

void TextureOb :: satelliteArgManager(std::vector<int>* arg)
{}
   
void TextureOb :: shipArgManager(std::vector<int>* arg)
{
     	race_id    = (*arg)[0];
     	subtype_id = (*arg)[1];   // warrior/trader and so on
     	mod_id     = 0;
}

void TextureOb :: nebulaArgManager(std::vector<int>* arg)
{
     	color_id    = (*arg)[0];
    	is_rotated =  (*arg)[1];
}

void TextureOb :: starArgManager(std::vector<int>* arg)
{
	color_id        = (*arg)[0];
	brightThreshold = (float)(*arg)[1]/1000;
}

void TextureOb :: planetArgManager(std::vector<int>* arg)
{}

void TextureOb :: atmosphereArgManager(std::vector<int>* arg)
{}


void TextureOb :: asteroidArgManager(std::vector<int>* arg)
{}

void TextureOb :: mineralArgManager(std::vector<int>* arg)
{}

void TextureOb :: containerArgManager(std::vector<int>* arg)
{}

void TextureOb :: bombArgManager(std::vector<int>* arg)
{}

void TextureOb :: blackholeArgManager(std::vector<int>* arg)
{}

//######### IN KOSMOPORT
void TextureOb :: landBgArgManager(std::vector<int>* arg)
{}

void TextureOb :: angarBgArgManager(std::vector<int>* arg)
{}

void TextureOb :: storeBgArgManager(std::vector<int>* arg)
{}

void TextureOb :: shopBgArgManager(std::vector<int>* arg)
{}

void TextureOb :: govermentBgArgManager(std::vector<int>* arg)
{}

void TextureOb :: faceArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	subtype_id    = (*arg)[1];   // warrior/trader and so on
}


// ITEMS
void TextureOb :: DriveEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: LazerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
   	color_id      = (*arg)[2];
}

void TextureOb :: RocketEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
  	 color_id      = (*arg)[2];
}

void TextureOb :: ProtectorEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: DroidEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: GrappleEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: BakEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: energyBlockItemArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: FreezerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: RadarEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}

void TextureOb :: ScanerEquipmentArgManager(std::vector<int>* arg)
{
   	race_id       = (*arg)[0];
   	tech_level_id = (*arg)[1];
}


//# BULLETS
void TextureOb :: rocketBulletArgManager(std::vector<int>* arg)
{}

void TextureOb :: torpedBulletArgManager(std::vector<int>* arg)
{}

void TextureOb :: particleArgManager(std::vector<int>* arg)
{
        color_id = (*arg)[0];
}

//int TextureOb :: getParticleFrameNumByColorId(int _color_id)
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

void TextureOb :: distStarArgManager(std::vector<int>* arg)
{
	color_id        = (*arg)[0];
}

void TextureOb :: lazerEffectArgManager(std::vector<int>* arg)
{
   	tech_level_id = (*arg)[0];
   	color_id      = (*arg)[1];
}

void TextureOb :: shieldEffectArgManager(std::vector<int>* arg)
{
   	color_id = (*arg)[0];
}







