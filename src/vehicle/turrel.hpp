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

#ifndef TURREL_H
#define TURREL_H

class Turrel
{
        public:
                TextureOb* texOb;
                Turrel();
                ~Turrel();

                void bindSlot(ItemSlot*);
                void setTexOb(TextureOb*);
                
                void setTarget(Ship*);
                void setTarget(Asteroid*);
                void setTarget(Mineral*);
                void setTarget(Container*);                               
                void setSelectedStatus(bool _selected);
                
                bool getSelectedStatus()  const;
                bool getHasTargetStatus() const;
                
                float getCenterX() const;
                float getCenterY() const;
                float getAngle()   const;              
       
                float* get_pCenterX() const;
                float* get_pCenterY() const;
                
                // TARGET section
                int getTargetId() const;
                bool* getTarget_pAliveStatus() const;
                float* getTarget_pCenterX() const;
                float* getTarget_pCenterY() const;
                //
                
                void placed(vec2f* _center);
       
                bool fireCheck();
                bool isTargetAchievable();
                        bool isTargetAlive();
                        bool isTargetInSpace(); 
                        bool isTargetOnTheSameStarSystem();
                        bool isAmmoAvailable();
                bool fireEvent_TRUE();
                bool fireEvent_FALSE();

                void resetTarget();
                
                void updatePosition(float _center_x, float _center_y, float _angle_inD);
                void render();      
                
        private:
                ItemSlot* slot;
                
                bool is_SELECTED;
                bool has_TARGET;
                        
                int target_type_id;
                
                // TARGET section
                bool* pTo_target_is_alive;
                float* pTo_target_pos_x;
                float* pTo_target_pos_y;
                //
                  
                float* pTo_pos_x;
                float* pTo_pos_y;
                
                Ship*      target_ship;
                Asteroid*  target_asteroid;
                Mineral*   target_mineral;                
                Container* target_container;
                
                //TextureOb* texOb;
                int w, h;
                
                Points points;
                float pos_z;                
}; 

#endif 
