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
	       	bool is_alive;
        	bool is_dying; 
        	bool is_explosed;

        	int dying_time;

        	bool in_SPACE;
        	bool is_COLLECTED;
        	bool draw_grabbing_ICON;

        	int armor;

        	TextureOb* pTo_texOb;
        	GLuint texture;
        	int w, h;
        	int minus_half_w, minus_half_h, plus_half_w, plus_half_h;
        	int size;
        
        	float dx, dy;
        	//self.owner = None

        	//if self.animated == True:
        		//   self.renderInSpace = self._renderDynamicFramesLoopRot
        	//   self.renderInSlot = self._renderStaticFramesLoopOnRect
        	//else:
        		//self.renderInSpace = self._renderDynamicFrameRot
        	//   self.renderInSlot = self._renderStaticFrameOnRect
        	int speed;

        	//self.hunters_list = []
        	//self.info         = []


        	//########  init values  #######
        	float angle_x_inD;
        	float angle_y_inD;
        	float angle_z_inD;
        	float d_angle_z_inD;
        	float pos_z;

        	float target_pos_x;
        	float target_pos_y;
        
        	float step;


        	bool keep_moving;

        	CommonForSpaceItems();
        	void CommonForSpaceItems_init(TextureOb* _texOb, vec2f _start_pos);
    
        	Points* getPoints();
        	void setStarSystem(StarSystem* _starsystem);
            	StarSystem* getStarSystem();
            	int getCollisionRadius() const;
            	
        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();
        	void stepCalculation();

        	void hit_TRUE(int damage);
        	void hit_FALSE(int damage);
        	void death_TRUE();
        	void death_FALSE();

        	void updateWHRenderConstants();
        	void render2D();
        	

        
        protected:
               	Points points;
                StarSystem* starsystem;
                
                int collision_radius;
};     

#endif 
