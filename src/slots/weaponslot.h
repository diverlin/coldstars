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


#ifndef WEAPONSLOT_H
#define WEAPONSLOT_H


class WeaponSlot : public CommonForSlot
{   public:
        bool is_READY_TO_FIRE;

        RocketEquipment*      pTo_rocketEquipment;
        LazerEquipment*       pTo_lazerEquipment;

        float* pTo_pos_x;
        float* pTo_pos_y;

        // TARGET section
        bool has_TARGET;
        int target_type_id;

        Ship*      pTo_shipTarget;
        Asteroid*  pTo_asteroidTarget;
        Mineral*   pTo_mineralTarget;
        Container* pTo_containerTarget;

        bool* pTo_target_is_alive;
        float* pTo_target_pos_x;
        float* pTo_target_pos_y;
        //
 
        bool is_SELECTED;
        //self.GL_LIST_slot_ID = None
          
        WeaponSlot();
        WeaponSlot(Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y);
        
        void placed(float* _pTo_pos_x, float* _pTo_pos_y);

        void updateTurrelPosition(float _pos_x, float _pos_y, float angle_inD);
        void renderTurrel();          

        void insertLazerEquipment(LazerEquipment* pTo_item);
        void removeLazerEquipment();
          
        void insertRocketEquipment(RocketEquipment* pTo_item);
        void removeRocketEquipment();

        int returnEquipedItemDamage();
        int returnEquipedItemRadius();
        int returnEquipedItemCondition();
        int returnEquipedItemMass(); 

        bool fireCheck();
             bool isTargetAchievable();
                  bool isTargetAlive();
                  bool isTargetInSpace(); 
                  bool isTargetOnTheSameStarSystem();
             bool isAmmoAvailable();
        bool fireEvent_TRUE();
        bool fireEvent_FALSE();

        int returnTargetId();
     
        void setShipTarget(Ship* _pTo_ship);
        void setAsteroidTarget(Asteroid* _pTo_asteroid);
        void setMineralTarget(Mineral* _pTo_mineral);
        void setContainerTarget(Container* _pTo_container);

        void resetTarget();

        void renderFrame(GLuint flash_tex);
        void renderFrames(GLuint flash_tex);

        void renderItemInfo();
}; 

#endif
