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


#ifndef COMMONFORSPACEITEMS_H
#define COMMONFORSPACEITEMS_H


class CommonForSpaceItems
{   
	public:
        	CommonForSpaceItems();
        	void CommonForSpaceItems_init(IdData _data_id, LifeData _data_life, TextureOb* _texOb, vec2f _start_pos);
    
    		bool getAlive() const;
                int getId() const;
                int getTypeId() const;
    		bool* getpAlive();
                int* getpPlaceTypeId();
        	Points* getPoints();
        	void setStarSystem(StarSystem*);
            	StarSystem* getStarSystem();
            	int getCollisionRadius() const;
            	
        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();

        	void hit_TRUE(int damage);
        	void hit_FALSE(int damage);

        	void render2D();
        
        protected:     	
        	LifeData data_life;
                IdData data_id; 
                       
        	int mass;
                int place_type_id;
                                
        	AngleData data_angle_inD;
      	
        	TextureOb* texOb;
        	int minus_half_w, minus_half_h, plus_half_w, plus_half_h;
                int collision_radius; 
                             	
        	Points points;
                StarSystem* starsystem;

        	vec2f target_pos;        	
        	vec2f d_pos;
        	
        	float velocity;
        	bool keep_moving;
    	
        	void calcRenderConstants();
        	        	
        	void death_TRUE();
        	void death_FALSE();
};     

#endif 
