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

      
      		float orbit_center_x;
      		float orbit_center_y;
      		int radius_A;
      		int radius_B;
      		float orbit_phi_inD;
      		float speed;    
     
      		float pos_z;

      		float angle_x;
      		float angle_y;
      		float angle_z;
      		float d_angle_z;
      
                float scale;
                
                VEC_float_type orbit_vector_x;
    		VEC_float_type orbit_vector_y;
                int orbit_len;
                int orbit_it; 

		// !!!!
    		float rate;                                            
    		int w, h;
    		int collision_radius; 
    		// !!!!
    		
    		CommonForPlanet();
    		~CommonForPlanet();
                
                
                
                int getId() const;
                int getType() const;
                int getSubType() const;
                
                Points* getPoints();
                
                void setStarSystem(StarSystem* _starsystem);
                StarSystem* getStarSystem();
                
                
    		
                void CommonForPlanet_init(TextureOb* _texOb, 
    	   				  ObjMeshInstance* _mesh, 
    	   				  float _size, 
    	   			          float _orbit_center_x, 
    	   			          float _orbit_center_y, 
    	   			          int _radius_A,
    	   				  int _radius_B, 
    	   				  float _orbit_phi_inD,
    	   			          float _speed);
    		
    		void detailedEllipceOrbitFormation();
    		void updatePosition();
    		
    		void render_NEW();
    		void render_OLD();
                
        protected:
                int id, type_id, subtype_id;
                
                TextureOb* texOb;

    		Points points;
    		ObjMeshInstance* mesh; 
    
              	StarSystem* starsystem;
};

#endif 
