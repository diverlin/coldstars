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


#ifndef SPACEITEMBASE_H
#define SPACEITEMBASE_H


class SpaceItemBase : public SpaceObjectBase
{   
	public:
        	SpaceItemBase();
        	~SpaceItemBase();
        	        	
        	void postCreateInit();

    		void moveToSpace(StarSystem*, vec2f);   
            	
        	void update_inSpace(int, bool);
        	
		void silentKill();
		virtual void postDeathUniqueEvent(bool);

        	void render2D();
        
        protected:     	
        	vec2f target_pos;        	
        	vec2f d_pos;
        	
        	float velocity;
        	bool keep_moving;
    	
          	void calcCollisionrRadius();
};     

#endif 
