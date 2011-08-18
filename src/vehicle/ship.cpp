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


#include "ship.h"


Navigator :: Navigator(Ship* _pTo_ship)
{
    pTo_ship = _pTo_ship;
   
    pTo_target_planet     = NULL;
    pTo_target_ship       = NULL;
    pTo_target_starsystem = NULL; 

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 

    docking_radius = 50;
}

Navigator :: ~Navigator()
{}
      
      
void Navigator :: setStaticTargetCoords(float _target_pos_x, float _target_pos_y)
{
    target_pos_x = _target_pos_x;
    target_pos_y = _target_pos_y;
    
    removeTargetPlanet();
    removeTargetShip(); 
    removeTargetStarSystem(); 
    
    pTo_ship->calculateDetaledWayToPosition();
}
      
      
void Navigator :: setTargetPlanet(Planet* _pTo_planet)
{
    removeTargetShip();
    removeTargetStarSystem(); 

    pTo_target_planet = _pTo_planet;
    pTo_ship->is_FOLLOWING_PLANET = true;

    pTo_target_pos_x = &pTo_target_planet->points.center_x;
    pTo_target_pos_y = &pTo_target_planet->points.center_y;

    docking_radius = 100;
}

void Navigator :: setTargetShip(Ship* _pTo_ship)
{    
    removeTargetPlanet();
    removeTargetStarSystem(); 

    pTo_target_ship = _pTo_ship;
    pTo_ship->is_FOLLOWING_SHIP = true;

    pTo_target_pos_x = &pTo_target_ship->points.center_x;
    pTo_target_pos_y = &pTo_target_ship->points.center_y;
}
    
void Navigator :: setTargetStarSystem(StarSystem* _pTo_starsystem)
{
    //target_pos_x = xxx;   jump point 
    //target_pos_y = yyy;

    removeTargetPlanet();
    removeTargetShip(); 

    pTo_target_starsystem = _pTo_starsystem;
    pTo_ship->is_FOLLOWING_STARSYSTEM = true;
}



void Navigator :: removeTargetPlanet()
{
    pTo_target_planet = NULL;
    pTo_ship->is_FOLLOWING_PLANET = false;

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetShip()
{
    pTo_target_ship = NULL;
    pTo_ship->is_FOLLOWING_SHIP = false;

    pTo_target_pos_x = NULL;
    pTo_target_pos_y = NULL; 
}

void Navigator :: removeTargetStarSystem()
{
    pTo_target_starsystem = NULL;
    pTo_ship->is_FOLLOWING_STARSYSTEM = false;
}


bool Navigator :: updateTargetCoords()
{
    if (pTo_ship->is_FOLLOWING_PLANET == true)
    {
        target_pos_x = pTo_target_planet->orbit_vector_x[pTo_target_planet->step+TURN_TIME];   
        target_pos_y = pTo_target_planet->orbit_vector_y[pTo_target_planet->step+TURN_TIME];  
        pTo_ship->calculateDetaledWayToPosition();

        return true;
    } 
     
    if (pTo_ship->is_FOLLOWING_SHIP = true)
    {
        return true;    
    }      

    if (pTo_ship->is_FOLLOWING_STARSYSTEM = true)
    {
        return true;    
    }       
}


bool Navigator :: checkDocking()
{
     if (collisionBetweenCenters(pTo_ship->points.center_x, pTo_ship->points.center_y, (*pTo_target_pos_x), (*pTo_target_pos_y), docking_radius) == true)
        return true;
     else    
        return false;
}


bool Navigator :: getDockingPermission()
{
    if (pTo_ship->is_FOLLOWING_PLANET == true)
       return pTo_target_planet->getPermissionToLand();

    //if (pTo_ship->is_FOLLOWING_SHIP == true)
    //   return pTo_target_ship->getPermissionToLand();

    //if (pTo_ship->is_FOLLOWING_SPACESTATION == true)
    //   return pTo_target_spacestation->getPermissionToLand();
}







Ship :: Ship(TextureOb* _pTo_texOb, int _max_weapons, bool _inhibit_GRAPPLE, int _space, int _armor_max, int _protection, int _nominal_temperature)
{
    is_alive    = true;
    is_dying    = false;
    is_explosed = false;

    in_SPACE = true;    // will be improved
    pTo_navigator = new Navigator(this);  
    
    is_FOLLOWING_PLANET = false;
    is_FOLLOWING_SHIP = false;
    is_FOLLOWING_STARSYSTEM = false;       

    dying_time = 60;

    id      = g_ENTITY_ID_GENERATOR.returnNextId(); 
    type_id = SHIP_ID;
    //subtype_id = ;

    pTo_starsystem = NULL; 

    pTo_texOb = _pTo_texOb;
    texture   = pTo_texOb->texture;
    w = _pTo_texOb->w;
    h = _pTo_texOb->h;

    size = returnObjectSize(w, h);
    collision_radius = (w+h)/3;

    angle_inD = 0;
   

    inhibit_GRAPPLE = _inhibit_GRAPPLE;


    ////// Points creation
    points = Points();

    points.initCenterPoint();
    points.addCenterPoint();

    points.initMainQuadPoints(w, h);
    points.addMainQuadPoints();

    points.initShieldQuadPoints();
    points.addShieldQuadPoints();

    points.initMidLeftPoint();
    points.addMidLeftPoint();

    points.initMidFarLeftPoint();
    points.addMidFarLeftPoint();

    //points.setCenter(randIntInRange(0, 800), randIntInRange(0, 600));    // debug
    points.setAngle(0);
    points.setCenter(300, 300); 

    w_orig = w;
    h_orig = h;

    space               = _space;
    armor_max           = _armor_max;
    armor               = _armor_max;
    korpus_protection   = _protection;
    nominal_temperature = _nominal_temperature;

    race_id         = (*pTo_texOb).race_id;
    subtype_id      = (*pTo_texOb).subtype_id;
    size_id         = (*pTo_texOb).size_id;
    mod_id          = (*pTo_texOb).mod_id;

    pTo_npc_owner = NULL;
    pTo_playerOwner = NULL;

    price = randIntInRange(200, 400);
    //color = (*pTo_texOb).color_id;


    /////////////////////////////////////////////////
    ///////////////////// KONTUR RECT ///////////////  
    float kontur_w, kontur_h;
    if (w > h)
    {
        kontur_w = 500; 
        kontur_h = h * kontur_w / (float)w;
    }
    else
    {
        kontur_h = 500; 
        kontur_w = w * kontur_h / (float)h;
    }               

    kontur_rect = Rect(0, 0, kontur_w, kontur_h); 
    kontur_rect.setNewCenter(g_VIEW_WIDTH/2, g_VIEW_HEIGHT/2); 
    /////////////////////////////////////////////////


    /////////////////////////////////////////////////
    //////////////////////// WEAPONS SLOT ///////////
    pTo_slotTexOb   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);

    int size_threshold = 2; 
    if (size > size_threshold)
       render_TURRELS = true; 
    else
       render_TURRELS = false; 
 
    if (_max_weapons >= 1)
    {  
       weapon_slot1 = WeaponSlot(this, pTo_slotTexOb, kontur_rect.center_x + 1*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2);
       weapon_slot1.placed(&points.weapon1_center_x, &points.weapon1_center_y);
       weapon_slot_pList.push_back(&weapon_slot1); 

       if (render_TURRELS == true)
       {   
           points.initWeapon1CenterPoint(0, h/3);
           points.addWeapon1CenterPoint();
           turrel_center_x_pList.push_back(&points.weapon1_center_x);
           turrel_center_y_pList.push_back(&points.weapon1_center_y);
       } 
    }
   
    if (_max_weapons >= 2)
    {  
       weapon_slot2 = WeaponSlot(this, pTo_slotTexOb, kontur_rect.center_x + 1*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h);    
       weapon_slot2.placed(&points.weapon2_center_x, &points.weapon2_center_y);      
       weapon_slot_pList.push_back(&weapon_slot2);  
       if (render_TURRELS == true)
       {  
           points.initWeapon2CenterPoint(0, -h/3);
           points.addWeapon2CenterPoint();
           turrel_center_x_pList.push_back(&points.weapon2_center_x);
           turrel_center_y_pList.push_back(&points.weapon2_center_y);
       }
    }

    if (_max_weapons >= 3)
    {  
       weapon_slot3 = WeaponSlot(this, pTo_slotTexOb, kontur_rect.center_x + 1*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h); 
       weapon_slot3.placed(&points.weapon3_center_x, &points.weapon3_center_y);  
       weapon_slot_pList.push_back(&weapon_slot3);  
       if (render_TURRELS == true)
       {  
           points.initWeapon3CenterPoint(-w/5, h/3);
           points.addWeapon3CenterPoint();
           turrel_center_x_pList.push_back(&points.weapon3_center_x);
           turrel_center_y_pList.push_back(&points.weapon3_center_y);
       }
    }

    if (_max_weapons >= 4)
    {  
       weapon_slot4 = WeaponSlot(this, pTo_slotTexOb, kontur_rect.center_x + 2.2*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h/2);
       weapon_slot4.placed(&points.weapon4_center_x, &points.weapon4_center_y);
       weapon_slot_pList.push_back(&weapon_slot4);  
       if (render_TURRELS == true)
       {  
           points.initWeapon4CenterPoint(w/5, -h/3);
           points.addWeapon4CenterPoint();
           turrel_center_x_pList.push_back(&points.weapon4_center_x);
           turrel_center_y_pList.push_back(&points.weapon4_center_y);

       }

    }   

    if (_max_weapons >= 5)
    {  
       weapon_slot5 = WeaponSlot(this, pTo_slotTexOb, kontur_rect.center_x + 2.2*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h/2);
       weapon_slot5.placed(&points.weapon5_center_x, &points.weapon5_center_y);
       weapon_slot_pList.push_back(&weapon_slot5);  
       if (render_TURRELS == true)
       {  
           points.initWeapon5CenterPoint(-w/3, -h/3);
           points.addWeapon5CenterPoint();
           turrel_center_x_pList.push_back(&points.weapon5_center_x);
           turrel_center_y_pList.push_back(&points.weapon5_center_y);
       }
    } 

    total_weapon_slot_num = weapon_slot_pList.size();
    ///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//////////// EQUPMENT SLOT ////////////////////////
	drive_slot       = OtsecSlot(DRIVE_ID,     this, pTo_slotTexOb, kontur_rect.center_x - 5*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h/2);
	total_slot_pList.push_back(&drive_slot);
	
	bak_slot         = OtsecSlot(BAK_ID,       this, pTo_slotTexOb, kontur_rect.center_x - 5*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h/2);
	total_slot_pList.push_back(&bak_slot);
	
	radar_slot       = OtsecSlot(RADAR_ID,     this, pTo_slotTexOb, kontur_rect.center_x + 4*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h/2);
	total_slot_pList.push_back(&radar_slot);	
	
	scaner_slot      = OtsecSlot(SCANER_ID,    this, pTo_slotTexOb, kontur_rect.center_x + 4*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h/2);
	total_slot_pList.push_back(&scaner_slot);
	
	energizer_slot   = OtsecSlot(ENERGIZER_ID, this, pTo_slotTexOb, kontur_rect.center_x - 2*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2);
    	total_slot_pList.push_back(&energizer_slot);
    		
	if (inhibit_GRAPPLE == false)
	{
		grapple_slot  = OtsecSlot(GRAPPLE_ID, this, pTo_slotTexOb, kontur_rect.center_x - 3*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h);
    		total_slot_pList.push_back(&grapple_slot); 
    	}
    	
	protector_slot   = OtsecSlot(PROTECTOR_ID, this, pTo_slotTexOb, kontur_rect.center_x - 3*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h);
    	total_slot_pList.push_back(&protector_slot); 
	
	droid_slot       = OtsecSlot(DROID_ID,     this, pTo_slotTexOb, kontur_rect.center_x - 1*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 + 1.1*(*pTo_slotTexOb).h);
    	total_slot_pList.push_back(&droid_slot); 
    	
	freezer_slot     = OtsecSlot(FREEZER_ID,   this, pTo_slotTexOb, kontur_rect.center_x - 1*(*pTo_slotTexOb).w, kontur_rect.center_y - (*pTo_slotTexOb).h/2 - 1.1*(*pTo_slotTexOb).h);
	total_slot_pList.push_back(&freezer_slot);   
	////////////////////////////////////////////////////


    ////////////////////////////////////////////////////
    //////// OTSEC SLOT ////////////////////////////////
    for (int i = 0; i <= 10; i++)
    {
         OtsecSlot* pTo_otsec_slot = new OtsecSlot(OTSEC_SLOT_ID, this, pTo_slotTexOb, kontur_rect.center_x + (i-6) * (*pTo_slotTexOb).w, kontur_rect.center_y - 3*(*pTo_slotTexOb).h);
         otsec_slot_pList.push_back(pTo_otsec_slot); 
         total_slot_pList.push_back(pTo_otsec_slot);         
    }
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    //////////// GATE SLOT /////////////////////////////
    gate_slot = OtsecSlot(GATE_SLOT_ID, this, pTo_slotTexOb, kontur_rect.center_x - 5*(*pTo_slotTexOb).w, kontur_rect.center_y + 3*(*pTo_slotTexOb).h);
    ////////////////////////////////////////////////////


   direction_list_END = true;


   //TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList);
   TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);

   int pNum       = 5;
   int pSize      = 25;
   float pVelocity  = 1.2;
   float pAlphaInit = 0.6;
   float pAlphaEnd  = 0.0;
   float pd_alpha   = 0.05;

   //drive_jet = DriveTrailEffect(TextureOb* _pTo_texOb, float* _pTo_OB_angle_inD, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_target_pos_x, float* _pTo_target_pos_y, int _num_particles, float _size, float _velocity_orig, float _alpha_start, float _alpha_end, float _d_alpha)
   pTo_drive_jet = new DriveTrailEffect(pTo_particleTexOb, &(points.angle_inD), &(points.midLeft_x), &(points.midLeft_y),  &(points.midFarLeft_x), &(points.midFarLeft_y), pNum, pSize, pVelocity, pAlphaInit, pAlphaEnd, pd_alpha);

   needsToDo.REPAIR = false;
   needsToDo.CHARGE = false;
   needsToDo.GETBULLETS = false;
   needsToDo.BUY = false;
   needsToDo.SELL = false;
   
   //self.shield_texOb = TEXTURE_MANAGER.returnShieldEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id)
   TextureOb* pTo_shieldTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shieldEffect_texOb_pList); 
   pTo_shield = new ShieldEffect(this, pTo_shieldTexOb);
}



Ship :: ~Ship()
{
     //for (unsigned int lei = 0; lei < effect_LAZERTRACE_pList.size(); lei++)   
         //delete effect_LAZERTRACE_pList[lei];
            
} 


//void Ship :: calculateWayToCoord(float _pos_x, float _pos_y)
//{    
//    setTargetPosCoord(_pos_x, _pos_y);
//    calculateDetaledWayToPosition();  // under constraction
    //calculateTurnWayToPosition();     // remove (perform if ship is selected by cursor)
    //calculateWayVisualisation();      // remove (perform if ship is selected by cursor)
//}


    
void Ship :: calculateDetaledWayToPosition()
{   
    direction_x_list.clear();
    direction_y_list.clear();
    angle_inD_list.clear();
  
    float last_pos_x = points.center_x;
    float last_pos_y = points.center_y;

    float step = speed/100.0;

    if ( ((last_pos_x != pTo_navigator->target_pos_x) || (last_pos_y != pTo_navigator->target_pos_y)) && (speed != 0))
    {
       float xl = pTo_navigator->target_pos_x - last_pos_x;
       float yl = pTo_navigator->target_pos_y - last_pos_y;

       float l = sqrt(xl*xl + yl*yl);
       float x_normalized = xl/l;
       float y_normalized = yl/l;

       int it = l / step;

       float x_step = x_normalized * step;
       float y_step = y_normalized * step;

       for(unsigned int i = 0; i < it; i++)
       {
            last_pos_x += x_step;
            last_pos_y += y_step;
            float angleInD = atan2(pTo_navigator->target_pos_y - last_pos_y, pTo_navigator->target_pos_x - last_pos_x) * RADIAN_TO_DEGREE_RATE;

            direction_x_list.push_back(last_pos_x);
            direction_y_list.push_back(last_pos_y);
            angle_inD_list.push_back(angleInD);
       }
    }
    
    move_it = 0;
    len_direction_list = direction_x_list.size();

    direction_list_END = false;
    
    //self.shield_texOb = TEXTURE_MANAGER.returnShieldEffectTexObBy_RevisionID_and_ColorID(self.item_texOb.revision_id, self.item_texOb.color_id)
    TextureOb* pTo_shieldTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shieldEffect_texOb_pList); 
    pTo_shield = new ShieldEffect(this, pTo_shieldTexOb);
}


void Ship :: updatePosition()
{
     if (direction_list_END == false)
     {
        if (move_it < (len_direction_list - 1))
        {
           points.setCenter(direction_x_list[move_it], direction_y_list[move_it]);
           points.setAngle(angle_inD_list[move_it]);
           move_it++;
        }
        else
           direction_list_END = true;
     }
}




void Ship :: reloadAllWeapons()
{
     // reload wepons
     // used once at the beginning of turn

     reloaded_weapon_pList.clear();
     for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
         if ((*equiped_weapon_slot_pList[i]).isAmmoAvailable() == true)
            reloaded_weapon_pList.push_back(equiped_weapon_slot_pList[i]);
            
     fire_delay = 10;
     d_fire_delay = 40;   // 0;
}






void Ship :: setWeaponsToShipTarget(Ship* pTo_ship, bool wslot_1_SELECTED = true, bool wslot_2_SELECTED = true, bool wslot_3_SELECTED = true, bool wslot_4_SELECTED = true, bool wslot_5_SELECTED = true)
{
        // set Target for selected non-targeted weapon slots 
        if (total_weapon_slot_num >= 1)
           weapon_slot1.is_SELECTED = wslot_1_SELECTED;
        if (total_weapon_slot_num >= 2)
           weapon_slot2.is_SELECTED = wslot_2_SELECTED;
        if (total_weapon_slot_num >= 3)
           weapon_slot3.is_SELECTED = wslot_3_SELECTED;
        if (total_weapon_slot_num >= 4)
           weapon_slot4.is_SELECTED = wslot_4_SELECTED;
        if (total_weapon_slot_num >= 5)
           weapon_slot5.is_SELECTED = wslot_5_SELECTED;

        float dist_to_target = lengthBetweenPoints(points.center_x, points.center_y, pTo_ship->points.center_x, pTo_ship->points.center_y);
        for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
            if ( equiped_weapon_slot_pList[i]->is_SELECTED == true )
               if ( equiped_weapon_slot_pList[i]->has_TARGET == false )
                  if ( dist_to_target < equiped_weapon_slot_pList[i]->returnEquipedItemRadius() )
                     equiped_weapon_slot_pList[i]->setShipTarget(pTo_ship);
                 

}






void Ship :: setWeaponsToAsteroidTarget(Asteroid* pTo_asteroid, bool wslot_1_SELECTED = true, bool wslot_2_SELECTED = true, bool wslot_3_SELECTED = true, bool wslot_4_SELECTED = true, bool wslot_5_SELECTED = true)
{
        // set Target for selected non-targeted weapon slots 
        if (total_weapon_slot_num >= 1)
           weapon_slot1.is_SELECTED = wslot_1_SELECTED;
        if (total_weapon_slot_num >= 2)
           weapon_slot2.is_SELECTED = wslot_2_SELECTED;
        if (total_weapon_slot_num >= 3)
           weapon_slot3.is_SELECTED = wslot_3_SELECTED;
        if (total_weapon_slot_num >= 4)
           weapon_slot4.is_SELECTED = wslot_4_SELECTED;
        if (total_weapon_slot_num >= 5)
           weapon_slot5.is_SELECTED = wslot_5_SELECTED;

        float dist_to_target = lengthBetweenPoints(points.center_x, points.center_y, pTo_asteroid->points.center_x, pTo_asteroid->points.center_y);
        for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
            if ( equiped_weapon_slot_pList[i]->is_SELECTED == true )
               if ( equiped_weapon_slot_pList[i]->has_TARGET == false )
                  if ( dist_to_target < equiped_weapon_slot_pList[i]->returnEquipedItemRadius() )
                     equiped_weapon_slot_pList[i]->setAsteroidTarget(pTo_asteroid);
                       
                  
}








void Ship :: setWeaponsToMineralTarget(Mineral* pTo_mineral, bool wslot_1_SELECTED = true, bool wslot_2_SELECTED = true, bool wslot_3_SELECTED = true, bool wslot_4_SELECTED = true, bool wslot_5_SELECTED = true)
{
        // set Target for selected non-targeted weapon slots 
        if (total_weapon_slot_num >= 1)
           weapon_slot1.is_SELECTED = wslot_1_SELECTED;
        if (total_weapon_slot_num >= 2)
           weapon_slot2.is_SELECTED = wslot_2_SELECTED;
        if (total_weapon_slot_num >= 3)
           weapon_slot3.is_SELECTED = wslot_3_SELECTED;
        if (total_weapon_slot_num >= 4)
           weapon_slot4.is_SELECTED = wslot_4_SELECTED;
        if (total_weapon_slot_num >= 5)
           weapon_slot5.is_SELECTED = wslot_5_SELECTED;

        float dist_to_target = lengthBetweenPoints(points.center_x, points.center_y, pTo_mineral->points.center_x, pTo_mineral->points.center_y);
        for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
            if ( equiped_weapon_slot_pList[i]->is_SELECTED == true )
               if ( equiped_weapon_slot_pList[i]->has_TARGET == false )
                  if ( dist_to_target < equiped_weapon_slot_pList[i]->returnEquipedItemRadius() )
                     equiped_weapon_slot_pList[i]->setMineralTarget(pTo_mineral);

}


void Ship :: setWeaponsToContainerTarget(Container* pTo_container, bool wslot_1_SELECTED = true, bool wslot_2_SELECTED = true, bool wslot_3_SELECTED = true, bool wslot_4_SELECTED = true, bool wslot_5_SELECTED = true)
{
        // set Target for selected non-targeted weapon slots 
        if (total_weapon_slot_num >= 1)
           weapon_slot1.is_SELECTED = wslot_1_SELECTED;
        if (total_weapon_slot_num >= 2)
           weapon_slot2.is_SELECTED = wslot_2_SELECTED;
        if (total_weapon_slot_num >= 3)
           weapon_slot3.is_SELECTED = wslot_3_SELECTED;
        if (total_weapon_slot_num >= 4)
           weapon_slot4.is_SELECTED = wslot_4_SELECTED;
        if (total_weapon_slot_num >= 5)
           weapon_slot5.is_SELECTED = wslot_5_SELECTED;

        //printf("inside setWeaponsToAsteroidTarget\n ");
        float dist_to_target = lengthBetweenPoints(points.center_x, points.center_y, pTo_container->points.center_x, pTo_container->points.center_y);
        for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
            if ( equiped_weapon_slot_pList[i]->is_SELECTED == true )
               if ( equiped_weapon_slot_pList[i]->has_TARGET == false )
                  if ( dist_to_target < equiped_weapon_slot_pList[i]->returnEquipedItemRadius() )
                     equiped_weapon_slot_pList[i]->setContainerTarget(pTo_container);
}







void Ship :: weaponsFire_TRUE(int timer)
{
     if (timer < TURN_TIME - fire_delay)
        for (unsigned int wi = 0; wi < reloaded_weapon_pList.size(); wi++)
        {
            if ( reloaded_weapon_pList[wi]->fireCheck() == true )
               if ( reloaded_weapon_pList[wi]->fireEvent_TRUE() == true )
               {
                   reloaded_weapon_pList.erase(reloaded_weapon_pList.begin() + wi);
                   fire_delay += d_fire_delay;
                   break;
               }
            else
            {
               reloaded_weapon_pList.erase(reloaded_weapon_pList.begin() + wi);
               break;
            }
        }
}


void Ship :: weaponsFire_FALSE(int timer)
{
     if (timer < TURN_TIME - fire_delay)
        for (unsigned int wi = 0; wi < reloaded_weapon_pList.size(); wi++)
        {
            if ( reloaded_weapon_pList[wi]->fireCheck() == true )
               if ( reloaded_weapon_pList[wi]->fireEvent_FALSE() == true )
               {
                   reloaded_weapon_pList.erase(reloaded_weapon_pList.begin() + wi);
                   fire_delay += d_fire_delay;
                   break;
               }
            else
            {
               reloaded_weapon_pList.erase(reloaded_weapon_pList.begin() + wi);
               break;
            }
        }
}




void Ship :: resetDeselectedWeaponTargets(bool wslot_1_SELECTED = false, bool wslot_2_SELECTED = false, bool wslot_3_SELECTED = false, bool wslot_4_SELECTED = false, bool wslot_5_SELECTED = false)
{
        // reset Target for selected targeted weapon slots 
        if (weapon_slot_pList.size() >= 1)
           weapon_slot1.is_SELECTED = wslot_1_SELECTED;
        if (weapon_slot_pList.size() >= 2)
           weapon_slot2.is_SELECTED = wslot_2_SELECTED;
        if (weapon_slot_pList.size() >= 3)
           weapon_slot3.is_SELECTED = wslot_3_SELECTED;
        if (weapon_slot_pList.size() >= 4)
           weapon_slot4.is_SELECTED = wslot_4_SELECTED;
        if (weapon_slot_pList.size() >= 5)
           weapon_slot5.is_SELECTED = wslot_5_SELECTED;

        for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
            if ((*equiped_weapon_slot_pList[i]).is_SELECTED == false)
               (*equiped_weapon_slot_pList[i]).resetTarget();
}


void Ship :: removeWeaponSlotDeadTargets()
{
     for (unsigned int i = 0; i < equiped_weapon_slot_pList.size(); i++)
         if (equiped_weapon_slot_pList[i]->has_TARGET == true)
            if (equiped_weapon_slot_pList[i]->isTargetAlive() == false)
                equiped_weapon_slot_pList[i]->resetTarget();
}



OtsecSlot* Ship :: return_pToEmptyOtsecSlot()
{
      for (unsigned int si = 0; si < otsec_slot_pList.size(); si++)
          if (otsec_slot_pList[si]->is_EQUIPED == false)
             return otsec_slot_pList[si];
      return NULL;
}


void Ship :: update_inSpace_inDynamic_TRUE()
{   
    if (ableTo.DRIVE == true) 
    { 
       updatePosition();
    }
    
    //for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)   // moved to ship
       //effect_LAZERTRACE_pList[i]->update(); 

    if (is_dying == true)
    {
       dying_time--;
       if (dying_time < 0)
           death();
    }    
}

void Ship :: update_inSpace_inDynamic_FALSE()
{   
    if (ableTo.DRIVE == true) 
       updatePosition();
}





//// ******** DOCKING/LAUNCHING ******** 
bool Ship :: checkDocking()
{  
     if (pTo_navigator->checkDocking() == true)
        return true;
     else    
        return false;
}

bool Ship :: getDockingPermission()
{
     if (pTo_navigator->getDockingPermission() == true) 
        return true;
     else
        return false;
}

bool Ship :: dockingEvent()
{
     printf("id = %i, dockingEvent()\n", id);
     pTo_starsystem->removeShipById(id);
     pTo_starsystem->removeNpc(pTo_npc_owner->id, pTo_npc_owner->race_id, pTo_npc_owner->subtype_id);

     pTo_navigator->pTo_target_planet->addShip(this);
     pTo_navigator->pTo_target_planet->addNpc(pTo_npc_owner);

     return true;
}

bool Ship :: launchingEvent()
{
     printf("id = %i, launchingEvent()\n", id);

     pTo_starsystem->addShip(this);
     pTo_starsystem->addNpc(pTo_npc_owner);

     pTo_navigator->pTo_target_planet->removeShipById(this->id);
     pTo_navigator->pTo_target_planet->removeNpcById(pTo_npc_owner->id);

     pTo_navigator->removeTargetPlanet();
}

//// ******** DOCKING/LAUNCHING ******** 







void Ship :: hit_TRUE(int _damage)
{
    armor -= _damage;
    if (ableTo.PROTECT == true)
       pTo_shield->alpha = 1.0;

    if (armor < 0)
       is_dying = true; 
}

void Ship :: hit_FALSE(int _damage)
{
    armor -= _damage;

    if (armor < 0)
       death();
}


void Ship :: death()
{
     is_alive = false;   

     if (is_explosed == false)
     {   
        pTo_starsystem->addExplosion(points.center_x, points.center_y, size);
        is_explosed = true;
     }
}



void Ship :: updateAllStuff()
{
    // this function set actual ship propretries relying to all equipment placed in slots
    // used when ship change items in slot
    // !!! all this stuff can be called separately by item deterioration function if item becomes broken !!!

    updateDriveAbility();
    updateRadarAbility();
    updateJumpAbility();
    updateEnergyAbility();  // make reurtn true, and add below if condition 
    updateProtectionAbility(); // because energy shield depends on energy and consume it much
    updateFireAbility();

    updateRepairAbility();
    updateFreezeAbility();
    updateGrabAbility();
    updateScanAbility();
}




void Ship :: updateFireAbility()
{
     equiped_weapon_slot_pList.clear();

     int sum_damage = 0;
     int sum_fire_radius = 0;

     for (unsigned int i = 0; i < weapon_slot_pList.size(); i++)
     { 
        if (weapon_slot_pList[i]->is_EQUIPED == true)
           if (weapon_slot_pList[i]->returnEquipedItemCondition() > 0)
           {
              equiped_weapon_slot_pList.push_back(weapon_slot_pList[i]);
              sum_damage += weapon_slot_pList[i]->returnEquipedItemDamage(); 
              sum_fire_radius += weapon_slot_pList[i]->returnEquipedItemRadius(); 
           }
     }

     if (equiped_weapon_slot_pList.size() != 0)
     {
        average_fire_radius = sum_fire_radius/equiped_weapon_slot_pList.size();
        ableTo.FIRE = true;
     }
     else
     {
        average_fire_radius = 0;
        ableTo.FIRE = false;
     } 
}






void Ship :: calculateMass()
{
     mass = 0;   

     ////////////// WEAPON SLOT ////////////////////////
     for (unsigned int i = 0; i < weapon_slot_pList.size(); i++)
     { 
        if (weapon_slot_pList[i]->is_EQUIPED == true)
           mass += weapon_slot_pList[i]->returnEquipedItemMass(); 
     }



    ////////////// EQUPMENT SLOT ////////////////////////
    //if (drive_slot.is_EQUIPED == true)
       //mass += drive_slot.pTo_driveEquipment->mass;

    //if (bak_slot.is_EQUIPED == true)
       //mass += bak_slot.pTo_bakEquipment->mass;

    //if (radar_slot.is_EQUIPED == true)
       //mass += radar_slot.pTo_radarEquipment->mass;

    //if (scaner_slot.is_EQUIPED == true)
       //mass += scaner_slot.pTo_scanerEquipment->mass;

    //if (energizer_slot.is_EQUIPED == true)
       //mass += energizer_slot.pTo_energizerEquipment->mass;

    //if (inhibit_GRAPPLE == false)
       //if (grapple_slot.is_EQUIPED == true)
          //mass += grapple_slot.pTo_grappleEquipment->mass;

    //if (protector_slot.is_EQUIPED == true)
       //mass += protector_slot.pTo_protectorEquipment->mass;

    //if (droid_slot.is_EQUIPED == true)
       //mass += droid_slot.pTo_droidEquipment->mass;

    //if (freezer_slot.is_EQUIPED == true)
       //mass += freezer_slot.pTo_freezerEquipment->mass;


    //////// OTSEC SLOT ////////////////////////////////
    for (unsigned int i = 0; i < total_slot_pList.size(); i++)
    {
        if (total_slot_pList[i]->is_EQUIPED == true)
           mass += total_slot_pList[i]->getItemMass();      
    }
}


void Ship :: updateDriveAbility()
{
     //// calculate mass and then actual ship speed depending on drive power and actual mass
     //// used each time when ship picked up/bought or drop/sold something.
     calculateMass();

     //// speed calculation ////
     speed = 0;
     ableTo.DRIVE = false;

     if (drive_slot.is_EQUIPED == true) 
        if (drive_slot.pTo_driveEquipment->condition > 0)  
        {
           float val = (drive_slot.pTo_driveEquipment->speed - mass/70);
           if (val > 0)
           { 
              speed = val;
              ableTo.DRIVE = true;              
           }
        }
     //speed = 200;    // debug
     //printf("speed= %i\n,", speed); 
     //// constants for direction visualization ////
     //   self.turn_step = self.speed * TURN_TIME
     //   self.draw_step = self.turn_step/ int(4*self.speed/DRIVE_SPEED_MIN)
}


void Ship :: updateRadarAbility()
{
   if (radar_slot.is_EQUIPED == true) 
      if (radar_slot.pTo_radarEquipment->condition > 0)  
      {
          radius = radar_slot.pTo_radarEquipment->radius;
          ableTo.RADAR = true;
      }
      
      else
      {
          radius = VISIBLE_DISTANCE_WITHOUT_RADAR;
          ableTo.RADAR = false;
      }
}



void Ship :: updateJumpAbility()
{    
     hyper = 0;
     ableTo.HJUMP = false;

     if (drive_slot.is_EQUIPED == true)
        if (drive_slot.pTo_driveEquipment->condition > 0)
           if (bak_slot.is_EQUIPED == true)
              if (bak_slot.pTo_bakEquipment->condition > 0)
              {
                 if (drive_slot.pTo_driveEquipment->hyper > bak_slot.pTo_bakEquipment->fuel)
                    hyper = drive_slot.pTo_driveEquipment->hyper;
                 else
                    hyper = bak_slot.pTo_bakEquipment->fuel;

                 ableTo.HJUMP = true;
              }    
}


void Ship :: updateEnergyAbility()
{
     energy = 0;
     ableTo.ENERGIZE = false;

     if (energizer_slot.is_EQUIPED == true)
        if (energizer_slot.pTo_energizerEquipment->condition > 0)
        {
           energy = energizer_slot.pTo_energizerEquipment->energy;
           ableTo.ENERGIZE = true;
        }
}



void Ship :: updateProtectionAbility()
{
     protection = korpus_protection;
     ableTo.PROTECT = false;

     if (protector_slot.is_EQUIPED == true)
     {
        if (protector_slot.pTo_protectorEquipment->condition > 0)
        {
           protection = protector_slot.pTo_protectorEquipment->protection + korpus_protection;
           ableTo.PROTECT = true;
        }
     }   
}




void Ship :: updateRepairAbility()
{
     repair = 0;
     ableTo.REPAIR = false;

     if (droid_slot.is_EQUIPED == true)
        if (droid_slot.pTo_droidEquipment->condition > 0)
        {
            repair = droid_slot.pTo_droidEquipment->repair;
            ableTo.REPAIR = true;
        }
}


void Ship :: updateFreezeAbility()
{
     freeze = 0;
     ableTo.FREEZE = false;

     if (freezer_slot.is_EQUIPED == true)
        if (freezer_slot.pTo_freezerEquipment->condition > 0)
        {
           freeze = freezer_slot.pTo_freezerEquipment->freeze;
           ableTo.FREEZE = true;
        }
}



void Ship :: updateGrabAbility()
{
     ableTo.GRAB = false;

     if (inhibit_GRAPPLE == false)
        if (grapple_slot.is_EQUIPED == true)
           if (grapple_slot.pTo_grappleEquipment->condition > 0)
              ableTo.GRAB = true;
}



void Ship :: updateScanAbility()
{
     scan = 0;
     ableTo.SCAN = false;

     if (scaner_slot.is_EQUIPED == true)
        if (scaner_slot.pTo_scanerEquipment->condition > 0)
        {
           scan = scaner_slot.pTo_scanerEquipment->scan;
           ableTo.SCAN = true;
        }
}



void Ship :: setMaxArmor()
{
     armor = armor_max;
}

void Ship :: setMaxFuel()
{
     if (bak_slot.is_EQUIPED == true)
        bak_slot.pTo_bakEquipment->fuel = bak_slot.pTo_bakEquipment->fuel_max;
}


void Ship :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "SHIP";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(pTo_starsystem->id);
    
    info_title_2 = "ship/pilot race:";
    int owner_race_id = returnOwnerRaceId();
    info_value_2 = returnRaceStringByRaceId(race_id) + "/" + returnRaceStringByRaceId(owner_race_id); 

    //str3.info.append('name:' + str(self.name))
    //str4.info.append('type:' + self.returnTypeStr())

    info_title_5 = "armor/max/size";
    info_value_5 = int2str(armor) + "/" + int2str(armor_max) + "/" + int2str(size);

    info_title_6 = "space/free/mass:";
    info_value_6 = int2str(space) + "/" + int2str(space - mass) + "/" + int2str(mass);

    info_title_7 = "speed x 100:";
    info_value_7 = int2str((int)(speed*100));

    info_title_8 = "energy:";
    info_value_8 = int2str(energy);

    info_title_9 = "temperature:";
    info_value_9 = int2str(nominal_temperature);

    info_title_10 = "observe radius:";
    info_value_10 = int2str(radius);

    info_title_11 = "protection:";
    info_value_11 = returnProtectionStr();

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    //info_pList.push_back(&str3);
    //info_pList.push_back(&str4);
    info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
    info_title_pList.push_back(&info_title_6);   info_value_pList.push_back(&info_value_6);
    info_title_pList.push_back(&info_title_7);   info_value_pList.push_back(&info_value_7);
    info_title_pList.push_back(&info_title_8);   info_value_pList.push_back(&info_value_8);
    info_title_pList.push_back(&info_title_9);   info_value_pList.push_back(&info_value_9);
    info_title_pList.push_back(&info_title_10);  info_value_pList.push_back(&info_value_10);
    info_title_pList.push_back(&info_title_11);  info_value_pList.push_back(&info_value_11);


    //info_pList.push_back(&str5);
    //if self.name != 'plr':
       //self.info.append(self.returnCurTaskStr(self.task_id_being_exec))   # debug
       //self.info.append(self.returnQuestTaskListStr())                    # debug
       //self.info.append(self.returnNeedsTaskListStr())                    # debug
}


   //def returnQuestTaskListStr(self):
        //str = 'QTL: '
        //for task in self.QUEST_TASK_queue:
            //str += self.returnCurTaskStr(task) + ";   "
        //return str

    //def returnNeedsTaskListStr(self):
        //str = 'NTL: '
        //for task in self.NEEDS_TASK_queue:
            //str += self.returnCurTaskStr(task) + ";   "
        //return str

    //def returnCurTaskStr(self, task_id):
        //if task_id == HYPER_JUMP_task_id:
           //return 'HYPER_JUMP_to_' + self.returnTargetSsnameStr()
        //elif task_id == DESTROY_ALIEN_task_id:
             //return 'DESTROY_ALIEN_task_id'
        //elif task_id == LANDING_task_id:
             //return 'LANDING_task_id'
        //elif task_id == LAUNCHING_task_id:
             //return 'LAUNCHING_task_id'
        //elif task_id == AREST_REQUEST_task_id:
             //return 'AREST_REQUEST_task_id'
        //elif task_id == TERROR_REQUEST_task_id:
             //return 'TERROR_REQUEST_task_id'
        //elif task_id == FIRE_LOW_task_id:
             //return 'FIRE_LOW_task_id'
        //elif task_id == FIRE_HIGH_task_id:
             //return 'FIRE_HIGH_task_id'
        //elif task_id == FIND_PLACE_TO_SELL_GOODS_task_id:
             //return 'FIND_PLACE_TO_SELL_GOODS_task_id'
        //elif task_id == BUY_GOODS_task_id:
             //return 'BUY_GOODS_task_id'
        //elif task_id == SELL_GOODS_task_id:
             //return 'SELL_GOODS_task_id'
        //elif task_id == GRABBING_MINERAL_task_id:
             //return 'GRABBING_MINERAL_task_id, items:' + str(len(self.korpus.grapple_slot.item.grapple_list))
        //elif task_id == GRABBING_CONTAINER_task_id:
             //return 'GRABBING_CONTAINER_task_id, items:'+ str(len(self.korpus.grapple_slot.item.grapple_list))
        //elif task_id == None:
             //return 'None'
        //else:
             //return 'unknown'

    //def returnTargetSsnameStr(self):
        //if self.target_starsystem != None:
           //return self.target_starsystem.name
        //else:
           //return ''

    //def returnTypeStr(self):
        //if self.subtype == RANGER_ID:
           //if self.subsubtype == WARRIOR_ID:
              //return 'ranger-warrior'
           //elif self.subsubtype == PIRAT_ID:
                //return 'ranger-pirat'
           //elif self.subsubtype == TRADER_ID:
                //return 'ranger-trader'
           //elif self.subsubtype == DIPLOMAT_ID:
                //return 'ranger-diplomat'

           //else:
                //return "ranger-unknown"

        //elif self.subtype == WARRIOR_ID:
             //return 'warrior'
        //elif self.subtype == PIRAT_ID:
             //return 'pirat'
        //elif self.subtype == TRADER_ID:
             //return 'trader'
        //elif self.subtype == DIPLOMAT_ID:
             //return 'diplomat'

        //else:
             //return "unknown"


std::string Ship :: returnProtectionStr()
{
    if (ableTo.PROTECT == true)
       return int2str(protector_slot.pTo_protectorEquipment->protection) + '+' + int2str(korpus_protection);
    else
       return int2str(korpus_protection);
}




int Ship :: returnOwnerRaceId()
{
    return pTo_npc_owner->race_id;
}





void Ship :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
     drawInfoIn2Column(&info_title_pList, &info_value_pList, _pos_x, _pos_y, _offset_x, _offset_y);
}


void Ship :: renderInSpace()
{   
    renderKorpus();

    //for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)
       //effect_LAZERTRACE_pList[i]->render(); 

    if (ableTo.PROTECT == true)
        renderShield(); 

    if (ableTo.DRIVE == true)
    {
       pTo_drive_jet->update();

       glEnable(GL_POINT_SPRITE);
       pTo_drive_jet->render();
       glDisable(GL_POINT_SPRITE);
    }
}

void Ship :: renderKorpus()
{
    points.update();   
                             
    glBindTexture(GL_TEXTURE_2D, texture); 
    drawFlatQuadPerVertexIn2D(points.bottomLeft_x, points.bottomLeft_y, points.bottomRight_x, points.bottomRight_y, points.topRight_x, points.topRight_y, points.topLeft_x, points.topLeft_y, -500);

    if (render_TURRELS == true)
        renderTurrels();
}


void Ship :: renderTurrels()
{
    for(unsigned int i = 0; i < weapon_slot_pList.size(); i++)
    {
        if (weapon_slot_pList[i]->is_EQUIPED == true)
        {
           float tur_angle_inD;
           if (weapon_slot_pList[i]->has_TARGET == true)
           {
              float tur_xl = (*(weapon_slot_pList[i]->pTo_target_pos_x)) - (*turrel_center_x_pList[i]);
              float tur_yl = (*(weapon_slot_pList[i]->pTo_target_pos_y)) - (*turrel_center_y_pList[i]);

              float tur_angle_inR = atan2(tur_yl, tur_xl);
              tur_angle_inD = tur_angle_inR * RADIAN_TO_DEGREE_RATE;
           }
           else
           {
              tur_angle_inD = points.angle_inD;
           } 

           weapon_slot_pList[i]->updateTurrelPosition((*turrel_center_x_pList[i]), (*turrel_center_y_pList[i]), tur_angle_inD); 
           weapon_slot_pList[i]->renderTurrel();
        }
    } 
}



void Ship :: renderShield()
{
     if (protector_slot.pTo_protectorEquipment == NULL)
         printf("pTo_protector = NULL\n");
     pTo_shield->render();
}






void equip(Ship* pTo_ship)
{
    if (pTo_ship->total_weapon_slot_num >= 1)
    {
       LazerEquipment* pTo_lazer1 = lazerGenerator(RACE_0_ID);    
       pTo_ship->weapon_slot1.insertLazerEquipment(pTo_lazer1); 
    }   

    if (pTo_ship->total_weapon_slot_num >= 2)
    {
       LazerEquipment* pTo_lazer2 = lazerGenerator(RACE_0_ID);    
       pTo_ship->weapon_slot2.insertLazerEquipment(pTo_lazer2); 
    }   
    
    if (pTo_ship->total_weapon_slot_num >= 3)
    {
       //LazerEquipment* pTo_lazer3 = lazerGenerator(RACE_0_ID);    
       //pTo_ship->weapon_slot3.insertLazerEquipment(pTo_lazer3); 
       RocketEquipment* pTo_rocket3 = rocketGenerator(RACE_0_ID);    
       pTo_ship->weapon_slot3.insertRocketEquipment(pTo_rocket3); 
    }   
        
    if (pTo_ship->total_weapon_slot_num >= 4)
    {
       LazerEquipment* pTo_lazer4 = lazerGenerator(RACE_0_ID);    
       pTo_ship->weapon_slot4.insertLazerEquipment(pTo_lazer4);         
       //RocketEquipment* pTo_rocket4 = rocketGenerator(RACE_0_ID);    
       //(*pTo_ship).weapon_slot4.insertRocketEquipment(pTo_rocket4); 
    }   
    
    if (pTo_ship->total_weapon_slot_num >= 5) 
    {
       LazerEquipment* pTo_lazer5 = lazerGenerator(RACE_0_ID);    
       pTo_ship->weapon_slot5.insertLazerEquipment(pTo_lazer5); 
       //RocketEquipment* pTo_rocket5 = rocketGenerator(RACE_0_ID);    
       //(*pTo_ship).weapon_slot5.insertRocketEquipment(pTo_rocket5); 
    }   
    
    
    
    
    RadarEquipment* pTo_radar = radarGenerator(RACE_0_ID);    
    pTo_ship->radar_slot.insertItem(pTo_radar); 
    
    DriveEquipment* pTo_drive = driveGenerator(RACE_0_ID);    
    pTo_ship->drive_slot.insertItem(pTo_drive); 

    BakEquipment* pTo_bak = bakGenerator(RACE_0_ID);    
    pTo_ship->bak_slot.insertItem(pTo_bak); 
            
    EnergizerEquipment* pTo_energizer = energizerGenerator(RACE_0_ID);    
    pTo_ship->energizer_slot.insertItem(pTo_energizer); 
    
    ProtectorEquipment* pTo_protector = protectorGenerator(RACE_0_ID);    
    pTo_ship->protector_slot.insertItem(pTo_protector); 
        
    DroidEquipment* pTo_droid = droidGenerator(RACE_0_ID);    
    pTo_ship->droid_slot.insertItem(pTo_droid); 
    
    
    FreezerEquipment* pTo_freezer = freezerGenerator(RACE_0_ID);    
    pTo_ship->freezer_slot.insertItem(pTo_freezer);     

    ScanerEquipment* pTo_scaner = ScanerEquipmentGenerator(RACE_0_ID);    
    pTo_ship->scaner_slot.insertItem(pTo_scaner); 
    
    if (pTo_ship->inhibit_GRAPPLE == false) 
    {
       GrappleEquipment* pTo_grapple = grappleGenerator(RACE_0_ID);    
       pTo_ship->grapple_slot.insertItem(pTo_grapple); 
    }
    
                             
    for (unsigned int i = 0; i < 3; i++) //pTo_ship->otsec_slot_pList.size(); i++)
    {        
        LazerEquipment* pTo_lazer = lazerGenerator(RACE_0_ID);              
        pTo_ship->otsec_slot_pList[i]->insertItem(pTo_lazer);
    }
    

    for (unsigned int i = 3; i < 6; i++) //pTo_ship->otsec_slot_pList.size(); i++)
    {        
        RadarModule* pTo_radarModule = radarModuleGenerator();              
        pTo_ship->otsec_slot_pList[i]->insertItem(pTo_radarModule);
    }
    
}






Ship* shipGenerator(int race_id, int subtype_id, int size_id)
{
    TextureOb* pTo_shipTexOb = g_TEXTURE_MANAGER.returnPointerToRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 

    int max_weapons = randIntInRange(1,5);
    bool inhibit_GRAPPLE = false;
    int space      = 600;
    int armor_max  = 600;
    int protection = 3;
    int nominal_temperature = 100;
                         
    Ship* pTo_ship = new Ship(pTo_shipTexOb, max_weapons, inhibit_GRAPPLE, space, armor_max, protection, nominal_temperature);
    
    return pTo_ship;
}
