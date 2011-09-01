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


#ifndef STAR_H
#define STAR_H


class Star
{
	public:
    		int id;
    
    		TextureOb* pTo_texOb;
    		StarSystem* starsystem;

    		ObjMeshInstance* pTo_mesh; 
    		GLuint texture;
    		
    		float texture_offset1, texture_offset2; 
    
    		float angle_x;
    		float angle_y;
    		float angle_z;
    		float d_angle_x;
    		float d_angle_y;
    		float d_angle_z;
                 
    		float pos_z;
    		
    		float scale;
    
    		// !!!!
    		float rate;   
		int w, h;
    		int collision_radius; 
    		// !!!!
      


   
    		Star(TextureOb* _pTo_texOb, ObjMeshInstance* _pTo_mesh, float _size);
    		~Star();
                
                Points* getPoints();
                
                void setStarSystem(StarSystem* _starsystem);
    		
    		void update_inSpace_inDynamic();
    		
    		void render_NEW();
    		void render_OLD();
    		
    		void updateInfo();
    		void renderInfo();
                
        private:
                Points points;
                
                InfoTable info;
}; 


Star* createStar();

#endif 
    

        


