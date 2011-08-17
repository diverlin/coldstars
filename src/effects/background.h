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


#ifndef BACKGROUND_H
#define BACKGROUND_H


class distantStarBgEffect
{   
    public:
       TextureOb* pTo_texOb;
       GLuint texture;
       float center_x; 
       float center_y;
       float particleSize;
       float distance_rate;

       distantStarBgEffect(TextureOb* _pTo_texOb, float _center_x, float _center_y, float _particleSize);
       void render(float vx, float vy);
}; 
typedef std::vector<distantStarBgEffect*> VEC_pDistantStarBgEffect_type; 

    

class distantNebulaBgEffect
{
    public:
        TextureOb* pTo_texOb;
        GLuint texture;
        int w,h;
        int minus_half_w, minus_half_h, plus_half_w, plus_half_h;
        
        float angleInDegree;
        float d_angleInDegree;
        bool is_rotated;


        float distance_rate;
        float center_x;
        float center_y;

        float pos_z;

        distantNebulaBgEffect(TextureOb* _pTo_texOb, float _center_x, float _center_y);
        void update();
        void updateWHRenderConstants();
        void render(float vx, float vy);
};
typedef std::vector<distantNebulaBgEffect*> VEC_pDistantNebulaBgEffect_type; 


#endif /* BACKGROUND_H */
