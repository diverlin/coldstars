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


#ifndef TEXTUREOB_H
#define TEXTUREOB_H

#include <string>
#include <vector>
#include "GL/glew.h"

#include "../common/myVector.hpp"

class TextureOb
{
    	public:
        	// textureOb attributes
        	int type_id;
        	int subtype_id;   //# warrior/trader and so on
        	int mod_id;       // is not used for now
        	int race_id;
        	int tech_level_id;
        	int size_id;      // counting from wxh of sprite
        
        	int color_id;     // probably color_rgb will be more usefull
                //std::vector<int> color_id_vec; // used for particles sprite sheet
        	bool is_rotated;
        
        	float brightThreshold;
        	//

        	int id;

        	std::string path;
        	bool use_alpha; 
		
		std::vector<vec2f> texCoord_bottomLeft_vec;
        	std::vector<vec2f> texCoord_bottomRight_vec;
        	std::vector<vec2f> texCoord_topLeft_vec;
        	std::vector<vec2f> texCoord_topRight_vec;

        	GLuint texture;

        	bool is_loaded, is_shared;
        
        	TextureOb();
        	TextureOb(int type_id, const std::string& path, bool use_alpha, std::vector<int>* pTo_arg = NULL, int columns_num = 1, int rows_num = 1, int fps = 0);

        	int GetFrameWidth() const;
        	int GetFrameHeight() const;
        	
        	void loadToVRAM();
        	void removeFromVRAM();

        	int updateAnimationFrame();
        	
                //int getParticleFrameNumByColorId(int);


	private:
	        int w, h;
        	int w_slice, h_slice;
        	
	        bool is_animated;
        	float fps;

        	unsigned int frame;
        	unsigned int frames_total_num; 
        	float last_update_time;
        	float delay; 
        	
        	void createTextureCoords(int _rows_num, int _columns_num, int _fps);
             	void addTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);
             	        	
        	void itemslotArgManager(std::vector<int>*);
        	void vehicleslotArgManager(std::vector<int>*);
        	void turrelArgManager(std::vector<int>*);
        	
        	// SPACE OBJECTS
        	void spacestationArgManager(std::vector<int>*); 
        	void satelliteArgManager(std::vector<int>*); 
        	void shipArgManager(std::vector<int>*); 

        	void nebulaArgManager(std::vector<int>*);
        	void starArgManager(std::vector<int>*); 

        	void planetArgManager(std::vector<int>*);
       		void atmosphereArgManager(std::vector<int>*);
        	void asteroidArgManager(std::vector<int>*); 
        	void mineralArgManager(std::vector<int>*); 
        	void containerArgManager(std::vector<int>*); 
        	void bombArgManager(std::vector<int>*); 
        	void blackholeArgManager(std::vector<int>*); 

        	// KOSMOPORT
        	void landBgArgManager(std::vector<int>*);
        	void angarBgArgManager(std::vector<int>*);
        	void storeBgArgManager(std::vector<int>*);
        	void shopBgArgManager(std::vector<int>*);
        	void govermentBgArgManager(std::vector<int>*);
        	void faceArgManager(std::vector<int>*); 

        	// ITEMS
        	void DriveEquipmentArgManager(std::vector<int>*); 
        	void LazerEquipmentArgManager(std::vector<int>*); 
        	void RocketEquipmentArgManager(std::vector<int>*); 
        	void ProtectorEquipmentArgManager(std::vector<int>*); 
        	void DroidEquipmentArgManager(std::vector<int>*);
        	void GrappleEquipmentArgManager(std::vector<int>*); 
        	void BakEquipmentArgManager(std::vector<int>*); 
        	void energyBlockItemArgManager(std::vector<int>*); 
        	void FreezerEquipmentArgManager(std::vector<int>*); 
        	void RadarEquipmentArgManager(std::vector<int>*); 
        	void ScanerEquipmentArgManager(std::vector<int>*); 

         	// BULLETS
        	void rocketBulletArgManager(std::vector<int>*); 
        	void torpedBulletArgManager(std::vector<int>*); 
        	void particleArgManager(std::vector<int>*); 
        	void distStarArgManager(std::vector<int>*); 
        	void lazerEffectArgManager(std::vector<int>*); 
        	void shieldEffectArgManager(std::vector<int>*); 
};

#endif 
