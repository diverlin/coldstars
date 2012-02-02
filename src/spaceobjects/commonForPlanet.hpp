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


class CommonForPlanet : public BaseSpaceObject 
{
	public:      
   		CommonForPlanet();
    		~CommonForPlanet();
					     
                // accessors
                void setPlanetData(PlanetData);
                vec2f getNextTurnPosition() const;
   	   	//
   	   	void postCreateInit();
    		void createOrbit();
   	   				  
 		void hit_TRUE(int);
 		void hit_FALSE(int);
    		
   		void render_NEW();
    		void render_OLD();
    		void drawOrbit();
    		               
        protected:
                PathVisual orbit_visual;

      		PlanetData data_planet;
     		
      		std::vector<vec2f> orbit_vec;
                int orbit_len, orbit_it; 
                                
    		void updatePosition();
    		void updateRotation();
    		
    		void calcCollisionrRadius();
    		void createEllipceOrbit();
    		void createOrbitVisual();
};

#endif 
