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


#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid : public CommonForPlanet
{
	public:
        	bool is_alive;
        	bool is_dying;
        	bool is_explosed;
       
       		int dying_time;
                
        	int armor;
        	int mass;
		
		
		Asteroid(TextureOb* _pTo_texOb,
		         ObjMeshInstance* _mesh,
		         float _size, 
		         vec2f _orbit_center, 
		         int _radius_A, 
		         int _radius_B, 
		         float _orbit_phi_inD, 
		         float _speed);
		     
        	~Asteroid();


        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();             		

        	void hit_TRUE(int damage);
        	void hit_FALSE(int damage);
        	
        	void death_TRUE();
        	void death_FALSE();

        	void updateInfo();
        	void renderInfo();
        	
        private:
		InfoTable info;
}; 


Asteroid* createAsteroid();

#endif 
