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


#ifndef SHIELD_H
#define SHIELD_H

class ProtectorItem;
class TextureOb;

class ShieldEffect
{  
     public:
        Ship* pTo_ship;
        
        TextureOb* pTo_texOb;
        GLuint texture;

        float angle_inD;
        float d_angle_inD;

        float alpha_start;
        float d_alpha;

        float alpha;

        float pos_z;

        //ShieldEffect();
        ShieldEffect(Ship* _pTo_ship, TextureOb* _pTo_texOb);
        ~ShieldEffect();

        //void renderDynamicFramesLoopRot();
        void render();
};

#endif 




