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


#ifndef SHIP_H
#define SHIP_H


struct NeedsToDo
{
   bool REPAIR;
   bool CHARGE;
   bool GETBULLETS;
   bool BUY;
   bool SELL;
};

struct Abilities
{
   bool RADAR;
   bool DRIVE;
   bool HJUMP;
   bool ENERGIZE;
   bool PROTECT;
   bool REPAIR;
   bool FREEZE;
   bool GRAB;
   bool SCAN;
   bool FIRE;
};

    
    
class Navigator
{
   public:
      Ship* pTo_ship;
   
      Planet*     pTo_target_planet;
      Ship*       pTo_target_ship;
      StarSystem* pTo_target_starsystem;  
      
      float target_pos_x;
      float target_pos_y;

      float* pTo_target_pos_x;
      float* pTo_target_pos_y;
      int docking_radius;
      
      Navigator(Ship* _pTo_ship);
      ~Navigator();
      
      void setStaticTargetCoords(float _target_pos_x, float _target_pos_y);
      
      void setTargetPlanet(Planet* _pTo_planet); 
      void setTargetShip(Ship* _pTo_ship);    
      void setTargetStarSystem(StarSystem* _pTo_starsystem);
      
      void removeTargetPlanet();
      void removeTargetShip(); 
      void removeTargetStarSystem();  
      
      bool updateTargetCoords();
      
      bool checkDocking();
      bool getDockingPermission();

};







class Ship
{   
    public:
        VEC_pTurrel_type turrel_pList;
    
        bool is_alive, is_dying, is_explosed;
        int type_id, id;

        int dying_time;

        bool in_SPACE;

        bool is_FOLLOWING_PLANET;
        bool is_FOLLOWING_SHIP;
        bool is_FOLLOWING_STARSYSTEM;

        Navigator* pTo_navigator;

        TextureOb* pTo_texOb;
        GLuint texture;
        int w, h;
        int size;
        float collision_radius;

        int w_orig, h_orig;

        float angle_inD;
        Points points;

        bool controlled_by_player;
        Npc* pTo_npc_owner;
        PlayerInstance* pTo_playerOwner;

        StarSystem* pTo_starsystem;

        int space;
        int armor_max;
        int armor;
        int korpus_protection;
        int nominal_temperature;

        int race_id;
        int subtype_id;
        int size_id;
        int mod_id;

        int color_id;
        int price;


        //######### KONTUR RECT 
        int w_kontur, h_kontur;
        Rect kontur_rect; 


        //######### SLOT
        TextureOb* pTo_slotTexOb;

        bool render_TURRELS;
        VEC_pFloat_type turrel_center_x_pList;
        VEC_pFloat_type turrel_center_y_pList;


        // WEPONS
        int fire_delay, d_fire_delay;
        //VEC_pWeaponSlot_type weapon_slot_pList;
        //VEC_pWeaponSlot_type equiped_weapon_slot_pList;
        //VEC_pWeaponSlot_type reloaded_weapon_pList;

        int total_weapon_slot_num;
        ItemSlot weapon_slot1;
        ItemSlot weapon_slot2;
        ItemSlot weapon_slot3;
        ItemSlot weapon_slot4;
        ItemSlot weapon_slot5;
        
        VEC_pTurrel_type turrel_total_pList;
        VEC_pTurrel_type turrel_reloaded_pList;
        VEC_pTurrel_type turrel_equiped_pList;
        
        Turrel turrel1;
        Turrel turrel2;
        Turrel turrel3;
        Turrel turrel4;
        Turrel turrel5;
        
        //######### EQUPMENT SLOT
        ItemSlot drive_slot;
        ItemSlot bak_slot;
        ItemSlot radar_slot;
        ItemSlot scaner_slot;
        ItemSlot energizer_slot;
        ItemSlot grapple_slot;
        ItemSlot protector_slot;
        ItemSlot droid_slot;
        ItemSlot freezer_slot;
                                                
        //######### OTSEC SLOT
        //VEC_pOtsecSlot_type otsec_slot_pList;
        VEC_pItemSlot_type slot_total_pList;
        VEC_pItemSlot_type slot_otsec_pList;
        
        //######### GATE SLOT
        ItemSlot gate_slot;

        ///////////////////////////////
        Abilities ableTo;
        NeedsToDo needsToDo;


        bool inhibit_GRAPPLE;

        //////////////////////////////
        /////// PROPERTIES depends on items
        int protection;
        int radius;
        int mass;   // depends on all items mass
        int speed;  // depends on mass and drive

        int hyper;  // depends on drive and bak
        int repair; // depends on droid
        int freeze; // depends on freezer
        int scan;   // depends on scaner
        
        int energy;
        int temperature;

        int dist2star_rate;
        int energy_restoration_rate;


        // INFO 
        std::string info_title_0;
        std::string info_title_1;   std::string info_value_1;
        std::string info_title_2;   std::string info_value_2; 
        std::string info_title_3;   std::string info_value_3;
        std::string info_title_4;   std::string info_value_4;
        std::string info_title_5;   std::string info_value_5;
        std::string info_title_6;   std::string info_value_6;
        std::string info_title_7;   std::string info_value_7;
        std::string info_title_8;   std::string info_value_8;
        std::string info_title_9;   std::string info_value_9;
        std::string info_title_10;  std::string info_value_10;
        std::string info_title_11;  std::string info_value_11;
        VEC_pString_type info_title_pList;        
        VEC_pString_type info_value_pList;  


        //////// TARGET COORDINATES //////
        //self.Gl_LIST_direction_ID = None

        VEC_float_type direction_x_list;
        VEC_float_type direction_y_list;
        VEC_float_type angle_inD_list;

        int len_direction_list;
        bool direction_list_END;
        int move_it;

        //self.turn_list_END      = True

        float target_pos_x;
        float target_pos_y;
        
        float jump_pos_x;
        float jump_pos_y;
        //////////////////////////////////

        // simplification
        int average_damage;
        int average_fire_radius;

        //VEC_pLazerTrace_type effect_LAZERTRACE_pList;

        DriveTrailEffect* pTo_drive_jet; 
        ShieldEffect* pTo_shield;

        Ship(TextureOb* _pTo_texOb, int _max_weapons, bool _grapple_INHIBIT, int _space, int _armor_max, int _protection, int _nominal_temperature);
        ~Ship();    

        void calculateDetaledWayToPosition();
        void updatePosition();

        void reloadAllWeapons();
        void setWeaponsToShipTarget(Ship*           pTo_ship,      bool wslot_1_SELECTED, bool wslot_2_SELECTED, bool wslot_3_SELECTED, bool wslot_4_SELECTED, bool wslot_5_SELECTED);
        void setWeaponsToAsteroidTarget(Asteroid*   pTo_asteroid,  bool wslot_1_SELECTED, bool wslot_2_SELECTED, bool wslot_3_SELECTED, bool wslot_4_SELECTED, bool wslot_5_SELECTED);
        void setWeaponsToMineralTarget(Mineral*     pTo_mineral,   bool wslot_1_SELECTED, bool wslot_2_SELECTED, bool wslot_3_SELECTED, bool wslot_4_SELECTED, bool wslot_5_SELECTED);
        void setWeaponsToContainerTarget(Container* pTo_container, bool wslot_1_SELECTED, bool wslot_2_SELECTED, bool wslot_3_SELECTED, bool wslot_4_SELECTED, bool wslot_5_SELECTED);
       
        void weaponsFire_TRUE(int timer);
        void weaponsFire_FALSE(int timer);

        void resetDeselectedWeaponTargets(bool wslot_1_SELECTED, bool wslot_2_SELECTED, bool wslot_3_SELECTED, bool wslot_4_SELECTED, bool wslot_5_SELECTED);
        void removeWeaponSlotDeadTargets();


        void update_inSpace_inDynamic_TRUE();
        void update_inSpace_inDynamic_FALSE();

        void hit_TRUE(int _damage);
        void hit_FALSE(int _damage);

        void death(); 

        void updateAllStuff();
             void updateFireAbility();
             void updateRadarAbility();
             void calculateMass();
             void updateDriveAbility();
             void updateJumpAbility();
             void updateEnergyAbility();
             void updateProtectionAbility();
             void updateRepairAbility();
             void updateFreezeAbility();
             void updateGrabAbility();
             void updateScanAbility();


        ItemSlot* return_pToEmptyOtsecSlot();

        void setMaxArmor();
        void setMaxFuel();

        void updateInfo();
             std::string returnProtectionStr();
             int returnOwnerRaceId();

        //// docking/launching
        bool checkDocking();
        bool getDockingPermission();
        bool dockingEvent();

        bool launchingEvent();
        //// docking/launching

        void renderInSpace();
             void renderKorpus();
             void renderTurrels();
             void renderShield();
        void renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y);

        void renderInternaly();
};

void equip(Ship* pTo_ship);
Ship* shipGenerator(int race_id, int subtype_id, int size_id);
#endif 
