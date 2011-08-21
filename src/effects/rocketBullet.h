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


#ifndef ROCKETBULLET_H
#define ROCKETBULLET_H


class RocketBullet
{
    public:
        int type_id;
       
        bool is_alive;
        bool is_explosed;

        TextureOb* pTo_texOb;
        GLuint texture;
        int w, h;

        StarSystem* pTo_starsystem;

        //CommonInstance.__init__(self, texOb.texture, (texOb.w, texOb.h))
        //if self.animated == True:
        //   self.render = self.renderInSpace
        //else:
        //   self.render = self.renderInSpace

        int owner_id;
        
        float* pTo_target_pos_x;
        float* pTo_target_pos_y;
        bool target_is_alive;    
        bool* pTo_target_is_alive;

        int damage;

        int size;
        int armor;

        float speed_init;
        float speed_max;
        float d_speed;  
        float angular_speed;
        float speed;
        float step;

        int live_time;

        Points points;

        RocketBullet(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _start_pos_x, float _start_pos_y, float _angle_inD, float* _pTo_target_pos_x, float* _pTo_target_pos_y, bool* _pTo_target_is_alive, int _owner_id, int _damage, int _size, int _armor, float _speed_init, float _speed_max, float _d_speed, float _angular_speed, int _live_time);
        ~RocketBullet();
        
        void update_inSpace_inDynamic();
        void updateDebugWay(int _timer);   // DEBUG
        void stepCalculation();
        void hit(int _damage);
        void death();

        float dx, dy;
        float angle_inD;

        void renderDriveJet();
        void renderInSpace();
};


#endif 
