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


#ifndef COMMONFORPLANET_H
#define COMMONFORPLANET_H


class CommonForPlanet
{
	public:      
   		CommonForPlanet();
    		~CommonForPlanet();
                                
                // accessors
                void setStarSystem(StarSystem* _starsystem);
                
                int getId() const;
                int getTypeId() const;
                int getSubTypeId() const;
                int getCollisionRadius() const;
                vec2f getNextTurnPosition() const;
                Points* getPoints();
                StarSystem* getStarSystem();

               	bool getGarbageReady() const;               
               	bool getAlive() const;
		bool* getpAlive();
                int* getpPlaceTypeId();
                
    		// other methods
                void CommonForPlanet_init(IdData,
                			  LifeData,                
                			  TextureOb* _texOb, 
    	   				  ObjMeshInstance* _mesh, 
    	   				  PlanetData _planet_data);
    	   				  
 		void hit_TRUE(int);
 		void hit_FALSE(int);
    		
   		void render_NEW();
    		void render_OLD();
                
        protected:
                IdData data_id;
                LifeData data_life;
                
                TextureOb* texOb;

    		Points points;
    		ObjMeshInstance* mesh; 
    
              	StarSystem* starsystem;
              	
              	InfoTable info;
              	
              	// !!!!
    		float rate;                                            
    		int w, h;
    		int collision_radius; 
    		// !!!!
              	      		
		vec3f center_pos;
		vec3f angle;
		vec3f d_angle;
     		
     		int place_type_id;
      		PlanetData data;
     		
      		std::vector<float> orbit_vector_x;
    		std::vector<float> orbit_vector_y;
                int orbit_len;
                int orbit_it; 
                
                void detailedEllipceOrbitFormation();
    		void updatePosition();
    		void updateRotation();
};

#endif 
