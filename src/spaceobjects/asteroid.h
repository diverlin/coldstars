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


class Asteroid
{
        TextureOb* pTo_texOb;
       public:
        StarSystem* pTo_starsystem;
                
        int type_id, id;

        bool is_alive;
        bool is_dying;
        bool is_explosed;
       
        int dying_time;
        
        Points points;
        //LoadObjMesh lMesh; 
        GLuint texture;
    
        float orbit_center_x;
        float orbit_center_y;
        int radius_A;
        int radius_B;
        float speed;    
        float orbitPhiInDegree;
 
        int orbit_len;
        int orbit_it; 
 
        float angle_x;
        float angle_y;
        float angle_z;
        float d_angle_z;
    
        float scale;
        float pos_z;

        VEC_float_type orbit_vector_x;
        VEC_float_type orbit_vector_y;
        int len_orbit_array;

        int w, h;
        int minus_half_w, minus_half_h, plus_half_w, plus_half_h;
        int size;
        
        int armor;
        int mass;

        // INFO 
        std::string info_title_0;
        std::string info_title_1;   std::string info_value_1;
        std::string info_title_2;   std::string info_value_2; 
        std::string info_title_3;   std::string info_value_3;
        std::string info_title_4;   std::string info_value_4;
        VEC_pString_type info_title_pList;        
        VEC_pString_type info_value_pList;
    public:

        //Asteroid();
        Asteroid(TextureOb* _pTo_texOb, StarSystem* _pTo_starsystem, float _size, float _orbit_center_x, float _orbit_center_y, int _radius_A, int _radius_B, float _orbitPhiInDegree, float _speed);
        ~Asteroid();

        void detailedEllipceOrbitFormation();
        void update_inSpace_inDynamic_TRUE();
        void update_inSpace_inDynamic_FALSE();
             void updatePosition();

        void updateWHRenderConstants();
        void hit_TRUE(int damage);
        void hit_FALSE(int damage);
        void death_TRUE();
        void death_FALSE();

        void render2D();

        void updateInfo();
        void renderInfo();
}; 

#endif 
