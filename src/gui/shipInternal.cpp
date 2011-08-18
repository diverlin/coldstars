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


#include "shipInternal.h"

ShipInternal :: ShipInternal()
{
     pTo_increment_attack_button   = NULL;  
     pTo_decrement_attack_button   = NULL;  
                
     pTo_increment_defence_button  = NULL;  
     pTo_decrement_defence_button  = NULL;  
        
     pTo_increment_leader_button   = NULL;  
     pTo_decrement_leader_button   = NULL; 
      
     pTo_increment_trader_button   = NULL;  
     pTo_decrement_trader_button   = NULL; 
    
     pTo_increment_technic_button  = NULL;  
     pTo_decrement_technic_button  = NULL; 
     
     pTo_increment_diplomat_button = NULL;  
     pTo_decrement_diplomat_button = NULL;
}

ShipInternal :: ~ShipInternal()
{}


void ShipInternal :: bindShip(Ship* _pTo_ship)
{
     pTo_ship = _pTo_ship;
}

void ShipInternal :: bindSkill(Skill* _pTo_skill)
{
     pTo_skill = _pTo_skill;
     createControlSkillButtons();
}

void ShipInternal :: createControlSkillButtons()
{
     int x = 10; //self.korpus.kontur_rect.right
     int y = 50; //self.korpus.kontur_rect.centery
     int w = 20;  //skill_w

     TextureOb* pTo_plus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
     TextureOb* pTo_minus_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(BLUE_COLOR_ID);

     pTo_increment_attack_button   = new Button(pTo_plus_texOb,  x, y - w,   w, w, "");  
     pTo_decrement_attack_button   = new Button(pTo_minus_texOb, x, y - 2*w, w, w, "");  
                
     pTo_increment_defence_button  = new Button(pTo_plus_texOb,  x + w, y - w,   w, w, "");  
     pTo_decrement_defence_button  = new Button(pTo_minus_texOb, x + w, y - 2*w, w, w, "");  
        
     pTo_increment_leader_button   = new Button(pTo_plus_texOb,  x + 2*w, y - w,   w, w, "");  
     pTo_decrement_leader_button   = new Button(pTo_minus_texOb, x + 2*w, y - 2*w, w, w, ""); 
      
     pTo_increment_trader_button   = new Button(pTo_plus_texOb,  x + 3*w, y - w,   w, w, "");  
     pTo_decrement_trader_button   = new Button(pTo_minus_texOb, x + 3*w, y - 2*w, w, w, ""); 
    
     pTo_increment_technic_button  = new Button(pTo_plus_texOb,  x + 4*w, y - w,   w, w, "");  
     pTo_decrement_technic_button  = new Button(pTo_minus_texOb, x + 4*w, y - 2*w, w, w, ""); 
     
     pTo_increment_diplomat_button = new Button(pTo_plus_texOb,  x + 5*w, y - w,   w, w, "");  
     pTo_decrement_diplomat_button = new Button(pTo_minus_texOb, x + 5*w, y - 2*w, w, w, "");
}

void ShipInternal :: manageSkill(bool allow_full_control)
{
     bool CURSOR_INTERSECT_OBJECT = false;

     int mxvp = g_MOUSE_POS_X;
     int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y;         
     int lmb  = g_MOUSE_LEFT_BUTTON;


     //### ATTACK
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_attack_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementAttack();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_attack_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementAttack();
           }
        }
     }
     //### ATTACK


     //### DEFENCE
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_defence_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementDefence();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_defence_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementDefence();
           }
        }
     }
     //### DEFENCE


     //### LEADER 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_leader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementLeader();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_leader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementLeader();
           }
        }
     }
     //### LEADER 



     //### TRADER 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_trader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementTrader();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_trader_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementTrader();
           }
        }
     }
     //### TRADER 



     //### TECHNIC 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_technic_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementTechnic();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_technic_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementTechnic();
           }
        }
     }
     //### TECHNIC 



     //### DIPLOMAT 
     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_increment_diplomat_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->incrementDiplomat();
           }
        }
     }

     if (CURSOR_INTERSECT_OBJECT == false)
     { 
        if (pTo_decrement_diplomat_button->interaction(mxvp, myvp) == true)
        {
           CURSOR_INTERSECT_OBJECT = true;
           if (lmb == true)
           {
               pTo_skill->decrementDiplomat();
           }
        }
     }
     //### DIPLOMAT 
}

void ShipInternal :: renderSkill()
{
     int w = 15;
     int h = 15;

     for (int i = 0; i < pTo_skill->attack; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_attack_button->rect.center_x - 10, pTo_increment_attack_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_attack_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_attack_button->render();
     pTo_decrement_attack_button->render();
                    
     for (int i = 0; i < pTo_skill->defence; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_defence_button->rect.center_x - 10, pTo_increment_defence_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_defence_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_defence_button->render();
     pTo_decrement_defence_button->render();

     for (int i = 0; i < pTo_skill->leader; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_leader_button->rect.center_x - 10, pTo_increment_leader_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_leader_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_leader_button->render();
     pTo_decrement_leader_button->render();
        
     for (int i = 0; i < pTo_skill->trader; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_trader_button->rect.center_x - 10, pTo_increment_trader_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_trader_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_trader_button->render();
     pTo_decrement_trader_button->render();
        
     for (int i = 0; i < pTo_skill->technic; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_technic_button->rect.center_x - 10, pTo_increment_technic_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_technic_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_technic_button->render();
     pTo_decrement_technic_button->render();
                    
     for (int i = 0; i < pTo_skill->diplomat; i++) 
     { 
         Rect tmp_rect = Rect(pTo_increment_diplomat_button->rect.center_x - 10, pTo_increment_diplomat_button->rect.center_y + i*h, w, h);
         drawTexturedRect(pTo_increment_diplomat_button->pTo_texOb->texture, tmp_rect, -1.0);
     }
     pTo_increment_diplomat_button->render();
     pTo_decrement_diplomat_button->render();
}












void ShipInternal :: resetSlotsRenderInfoFlag()
{
    for (unsigned int i = 0; i < pTo_ship->weapon_slot_pList.size(); i++)
    { 
         pTo_ship->weapon_slot_pList[i]->is_CURSORED = false;
    } 
 
    //pTo_ship->drive_slot.is_CURSORED     = false;
    //pTo_ship->bak_slot.is_CURSORED       = false;
    //pTo_ship->radar_slot.is_CURSORED     = false;
    //pTo_ship->scaner_slot.is_CURSORED    = false;
    //pTo_ship->energizer_slot.is_CURSORED = false;
    //pTo_ship->grapple_slot.is_CURSORED   = false;
    //pTo_ship->protector_slot.is_CURSORED = false;
    //pTo_ship->droid_slot.is_CURSORED     = false;
    //pTo_ship->freezer_slot.is_CURSORED   = false;

    for(VEC_pOtsecSlot_type::iterator it = pTo_ship->total_slot_pList.begin(); it != pTo_ship->total_slot_pList.end(); it++)
    { 
       (*it)->is_CURSORED = false;
    }
   
    pTo_ship->gate_slot.is_CURSORED = false;
}






void ShipInternal :: mouseControl(bool allow_full_control, bool in_store)
{
    bool lmb = g_MOUSE_LEFT_BUTTON; 
    bool rmb = g_MOUSE_RIGHT_BUTTON; 

    bool cursor_has_target = false;

    Store* pTo_store = NULL;     // move to ship class             
    if (in_store == true) 
       pTo_store = pTo_ship->pTo_npc_owner->pTo_kosmoport->pTo_store;    // this is used only for player


    resetSlotsRenderInfoFlag();

    // WEAPON SLOT
    for (unsigned int i = 0; i < pTo_ship->weapon_slot_pList.size(); i++)
    { 
        if (pTo_ship->weapon_slot_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
        {  
            pTo_ship->weapon_slot_pList[i]->is_CURSORED = true;
            cursor_has_target = true;
  
            if (pTo_ship->weapon_slot_pList[i]->is_EQUIPED == true)      
            {   // SLOT IS EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) ) 
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item 
                        if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_lazerEquipment);
                            pTo_ship->weapon_slot_pList[i]->removeLazerEquipment();
                        }

                        if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_rocketEquipment);
                            pTo_ship->weapon_slot_pList[i]->removeRocketEquipment();
                        } 
                    }
                    else  
                    {   // merge module with item                    
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
                        {
                            if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ID)
                            {
                                if (pTo_ship->weapon_slot_pList[i]->pTo_lazerEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_lazerModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }   

                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                        {
                            if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ID)
                            {
                                if (pTo_ship->weapon_slot_pList[i]->pTo_rocketEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_rocketModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }                         
                    }
                }
                
                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyWeaponSlotItem(pTo_ship->weapon_slot_pList[i]);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 
            }  

            
            else                              
            {   // SLOT IS EMPTY     
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item 
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
                        {
                            pTo_ship->weapon_slot_pList[i]->insertLazerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_lazerEquipment);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                        {
                            pTo_ship->weapon_slot_pList[i]->insertRocketEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_rocketEquipment);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }                     
                    } 
                }    
            }

           
        }
    }


    //// DRIVE SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->drive_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->drive_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->drive_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item 
                        //if (pTo_ship->drive_slot.item_subtype_id == DRIVE_ITEM_ID)
                        //{   
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->drive_slot.pTo_driveEquipment);
                            //pTo_ship->drive_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_MODULE_ID)
                        //{   
                            //if (pTo_ship->drive_slot.item_subtype_id == DRIVE_ITEM_ID)
                            //{
                                //if (pTo_ship->drive_slot.pTo_driveEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_driveModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}          
                    //}
                //}
                
                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyDriveSlotItem(&pTo_ship->drive_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 
            //}
          
            //else
            //{   // slot is EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ITEM_ID)
                        //{
                            //pTo_ship->drive_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //} 
                //}    
            //}

        //} 
    //}


    //// BAK SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->bak_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->bak_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->bak_slot.is_EQUIPED == true)
            //{   // SLOT IS EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{   
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item 
                        //if (pTo_ship->bak_slot.item_subtype_id == BAK_ITEM_ID)
                        //{   
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->bak_slot.pTo_bakEquipment);
                            //pTo_ship->bak_slot.removeItem();
                        //}
                    //}    
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_MODULE_ID)
                        //{   
                            //if (pTo_ship->bak_slot.item_subtype_id == BAK_ITEM_ID)
                            //{
                                //if (pTo_ship->bak_slot.pTo_bakEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_bakModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}                          
                    //}
                
                //}
                    
                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item 
                    //int earn_price = pTo_store->buyBakSlotItem(&pTo_ship->bak_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 
            //}
        
            //else
            //{   // SLOT IS EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ITEM_ID)
                        //{   
                            //pTo_ship->bak_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //} 
                //}    
            //}
        //}
    //}

    //// RADAR SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->radar_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->radar_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->radar_slot.is_EQUIPED == true)
            //{   // slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->radar_slot.item_subtype_id == RADAR_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->radar_slot.pTo_radarEquipment);
                            //pTo_ship->radar_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_MODULE_ID)
                        //{   
                            //if (pTo_ship->radar_slot.item_subtype_id == RADAR_ITEM_ID)
                            //{
                                //if (pTo_ship->radar_slot.pTo_radarEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}  
                    //}
                //}    

                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyRadarSlotItem(&pTo_ship->radar_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 
            //}
            //else
            //{             
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ITEM_ID)
                        //{
                            //pTo_ship->radar_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //}
                //}     
            //}

       //} 
    //}



    //// SCANER SLOT
    //if (cursor_has_target == false)
    //{
       //if (pTo_ship->scaner_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
       //{
            //pTo_ship->scaner_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->scaner_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->scaner_slot.item_subtype_id == SCANER_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->scaner_slot.pTo_scanerEquipment);
                            //pTo_ship->scaner_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_MODULE_ID)
                        //{   
                            //if (pTo_ship->scaner_slot.item_subtype_id == SCANER_ITEM_ID)
                            //{
                                //if (pTo_ship->scaner_slot.pTo_scanerEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_scanerModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}  
                    //}
                //}
                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyScanerSlotItem(&pTo_ship->scaner_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 
            //}
            //else
            //{   // slot is EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ITEM_ID)
                        //{
                           //pTo_ship->scaner_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerEquipment);
                           //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //}
                //}     
            //}


       //} 
    //}


    //// ENERGIZER SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->energizer_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->energizer_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->energizer_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->energizer_slot.item_subtype_id == ENERGIZER_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->energizer_slot.pTo_energizerEquipment);
                            //pTo_ship->energizer_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_MODULE_ID)
                        //{   
                            //if (pTo_ship->energizer_slot.item_subtype_id == ENERGIZER_ITEM_ID)
                            //{
                                //if (pTo_ship->energizer_slot.pTo_energizerEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_energizerModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}  
                    //}
                //}    
                
                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item 
                    //int earn_price = pTo_store->buyEnergizerSlotItem(&pTo_ship->energizer_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 

            //}
            //else
            //{   // slot is EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ITEM_ID)
                        //{
                            //pTo_ship->energizer_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //}
                //}     
            //}


        //} 
    //}

    //// GRAPPLE SLOT
    //if (pTo_ship->inhibit_GRAPPLE == false)
    //{
        //if (cursor_has_target == false)
        //{
            //if (pTo_ship->grapple_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
            //{
                //pTo_ship->grapple_slot.is_CURSORED = true;
                //cursor_has_target = true;

                //if (pTo_ship->grapple_slot.is_EQUIPED == true)
                //{ 
                    //// slot is EQUIPED
                    //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                    //{
                        //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                        //{   // take item
                            //if (pTo_ship->grapple_slot.item_subtype_id == GRAPPLE_ITEM_ID)
                            //{
                                //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->grapple_slot.pTo_grappleEquipment);
                                //pTo_ship->grapple_slot.removeItem();
                            //}
                        //}
                        //else
                        //{   // merge module with item
                            //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_MODULE_ID)
                            //{   
                                //if (pTo_ship->grapple_slot.item_subtype_id == GRAPPLE_ITEM_ID)
                                //{
                                    //if (pTo_ship->grapple_slot.pTo_grappleEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_grappleModule) == true)
                                    //{
                                        //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                    //}    
                                //}
                            //}   
                        //}
                    //}

                    //if ( (lmb == true) && (in_store == true) )
                    //{   // sell item
                        //int earn_price = pTo_store->buyGrappleSlotItem(&pTo_ship->grapple_slot);
                        //pTo_PLAYER->pTo_npc->credits += earn_price;
                    //} 

                //}
                //else
                //{   // slot is EMPTY           
                    //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                    //{
                        //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                        //{   // insert item
                            //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ITEM_ID)
                            //{
                                //pTo_ship->grapple_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleEquipment);
                                //pTo_CURSOR->pTo_otsec_slot->removeItem();
                            //}
                        //}
                    //}     
                //}


            //} 
        //}
    //}


    //// PROTECTOR SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->protector_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->protector_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->protector_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->protector_slot.item_subtype_id == PROTECTOR_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->protector_slot.pTo_protectorEquipment);
                            //pTo_ship->protector_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_MODULE_ID)
                        //{   
                            //if (pTo_ship->protector_slot.item_subtype_id == PROTECTOR_ITEM_ID)
                            //{
                                //if (pTo_ship->protector_slot.pTo_protectorEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_protectorModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}   
                    //}
                //}    

                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyProtectorSlotItem(&pTo_ship->protector_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 

            //}
            //else
            //{   // slot is EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ITEM_ID)
                        //{
                            //pTo_ship->protector_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //} 
                //}    
            //}

        //} 
    //}


    //// DROID SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->droid_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->droid_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->droid_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->droid_slot.item_subtype_id == DROID_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->droid_slot.pTo_droidEquipment);
                            //pTo_ship->droid_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_MODULE_ID)
                        //{   
                            //if (pTo_ship->droid_slot.item_subtype_id == DROID_ITEM_ID)
                            //{
                                //if (pTo_ship->droid_slot.pTo_droidEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_droidModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}   
                    //}
                //}    
                //// sell item
                //if ( (lmb == true) && (in_store == true) )
                //{
                    //int earn_price = pTo_store->buyDroidSlotItem(&pTo_ship->droid_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //} 

            //}
            //// slot is EMPTY
            //else
            //{             
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ITEM_ID)
                        //{
                            //pTo_ship->droid_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //} 
                //}    
            //}

        //} 
    //}


    //// FREEZER SLOT
    //if (cursor_has_target == false)
    //{
        //if (pTo_ship->freezer_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        //{
            //pTo_ship->freezer_slot.is_CURSORED = true;
            //cursor_has_target = true;

            //if (pTo_ship->freezer_slot.is_EQUIPED == true)
            //{ 
                //// slot is EQUIPED
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    //{   // take item
                        //if (pTo_ship->freezer_slot.item_subtype_id == FREEZER_ITEM_ID)
                        //{
                            //pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->freezer_slot.pTo_freezerEquipment);
                            //pTo_ship->freezer_slot.removeItem();
                        //}
                    //}
                    //else
                    //{   // merge module with item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_MODULE_ID)
                        //{   
                            //if (pTo_ship->freezer_slot.item_subtype_id == FREEZER_ITEM_ID)
                            //{
                                //if (pTo_ship->freezer_slot.pTo_freezerEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_freezerModule) == true)
                                //{
                                    //pTo_CURSOR->pTo_otsec_slot->removeItem();
                                //}    
                            //}
                        //}  
                    //}
                //}    

                //if ( (lmb == true) && (in_store == true) )
                //{   // sell item
                    //int earn_price = pTo_store->buyFreezerSlotItem(&pTo_ship->freezer_slot);
                    //pTo_PLAYER->pTo_npc->credits += earn_price;
                //}  

            //}
            //else
            //{   // slot is EMPTY          
                //if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                //{
                    //if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    //{   // insert item
                        //if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ITEM_ID)
                        //{
                            //pTo_ship->freezer_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerEquipment);
                            //pTo_CURSOR->pTo_otsec_slot->removeItem();
                        //}
                    //}
                //}     
            //}
            
        //} 
    //}


    // TOTAL SLOT START
    for(unsigned int i = 0; i < pTo_ship->total_slot_pList.size(); i++)
    { 
       if (pTo_ship->total_slot_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
       {  
            pTo_ship->total_slot_pList[i]->is_CURSORED = true;
            cursor_has_target = true;


            //// TAKE ITEM ////
            if (pTo_ship->total_slot_pList[i]->is_EQUIPED == true)
            { 
                // INSERT ITEM TO CURSOR //
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {
                        // weapons
                        if (pTo_ship->total_slot_pList[i]->item_subtype_id == LAZER_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_lazerEquipment);
                            pTo_ship->total_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->total_slot_pList[i]->item_subtype_id == ROCKET_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_rocketEquipment);
                            pTo_ship->total_slot_pList[i]->removeItem();
                        }

                        // items
                        if (pTo_ship->total_slot_pList[i]->item_type_id == EQUIPMENT_ID)
                        {
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == RADAR_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_radarEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == DRIVE_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_driveEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == BAK_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_bakEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == ENERGIZER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_energizerEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == PROTECTOR_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_protectorEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == DROID_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_droidEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == FREEZER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_freezerEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == SCANER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_scanerEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == GRAPPLE_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_grappleEquipment) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                     	}
                     	
                        // modules
                        if (pTo_ship->total_slot_pList[i]->item_type_id == MODULE_ID)
                        {
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == LAZER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_lazerModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == ROCKET_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_rocketModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == RADAR_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_radarModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == DRIVE_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_driveModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == BAK_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_bakModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == ENERGIZER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_energizerModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == PROTECTOR_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_protectorModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == DROID_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_droidModule) == true)
                           			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == FREEZER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_freezerModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == SCANER_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_scanerModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        	if (pTo_ship->total_slot_pList[i]->item_subtype_id == GRAPPLE_ID)
                        	{
                            		if (pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->total_slot_pList[i]->pTo_grappleModule) == true)
                            			pTo_ship->total_slot_pList[i]->removeItem();
                        	}
                        }
                        	
                        // artifacts
                        // bomb
                    }
                    else
                    {   // merge module with equipment
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ID)
                        {   
                            if (pTo_ship->total_slot_pList[i]->item_subtype_id == RADAR_ID)
                            {
                                if (pTo_ship->total_slot_pList[i]->pTo_radarEquipment->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }   
                    }
                }
                    
                // SELL ITEM TO STORE //
                if ( (lmb == true) && (in_store == true) )
                {
                    int earn_price = pTo_store->buyOtsecSlotItem(pTo_ship->total_slot_pList[i]);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 

            }
		//// PUT ITEM ////
		else
		{             
                	if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                	{
				if ( (pTo_ship->total_slot_pList[i]->type_id == pTo_CURSOR->pTo_otsec_slot->item_subtype_id) || (pTo_ship->total_slot_pList[i]->type_id == OTSEC_SLOT_ID) )
				{
					if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
					{             
						if (pTo_CURSOR->pTo_otsec_slot->item_type_id == EQUIPMENT_ID)
						{       
							// weapons
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
							{
								pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerEquipment);
								pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
							{
								pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketEquipment);
								pTo_CURSOR->pTo_otsec_slot->removeItem();
							}

                    
							// items
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}	
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakEquipment) == true)
								pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
							if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ID)
							{
								if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleEquipment) == true)
									pTo_CURSOR->pTo_otsec_slot->removeItem();
							}
						}
						
						// modules	
						if (pTo_CURSOR->pTo_otsec_slot->item_type_id == MODULE_ID)
						{
	                        			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
        	                			{
                	            				if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerModule) == true)
                        	    					pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                        				if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                        				{
	                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketModule) == true)
        	                    					pTo_CURSOR->pTo_otsec_slot->removeItem();
                	        			}
                        				if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ID)
                        				{ printf("(pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ID)\n");
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule) == true)
                            					{printf("(pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule) == true)\n");
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                            					}
                        				}
   		                     			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ID)
                	        			{
                        	    				if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
              		          			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                	        			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                 		       			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                  		      			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                  		      			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                    		    			if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}	
                        				if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ID)
                        				{
                            					if (pTo_ship->total_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleModule) == true)
                            						pTo_CURSOR->pTo_otsec_slot->removeItem();
                        				}
                        			}
                        			// artifacts
                        			// bomb
                        			
                        			
                    			} 
                		}    
            		}


        	}
        	
        }
    }

    // GATE SLOT
    if (cursor_has_target == false)
    {
       if (pTo_ship->gate_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
       {
          pTo_ship->gate_slot.is_CURSORED = true;
          cursor_has_target = true;

          //// DROP ITEM TO OUTERSPACE ////
          if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
              if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
              {
                  TextureOb* pTo_containerTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.container_texOb_pList); 
                  Container* pTo_container = new Container(pTo_ship->pTo_starsystem, pTo_containerTexOb, pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_ship->points.center_x + randIntInRange(50, 250), pTo_ship->points.center_y + randIntInRange(50, 250));
                  pTo_ship->pTo_starsystem->CONTAINER_pList.push_back(pTo_container); 

                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ID)
                  {     
                      pTo_container->packLazerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_lazerEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ID)
                  {             
                      pTo_container->packRocketEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_rocketEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();  
                  }

                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ID)
                  {                      
                      pTo_container->packRadarEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_radarEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ID)
                  {               
                      pTo_container->packDriveEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_driveEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem(); 
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ID)
                  {                      
                      pTo_container->packBakEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_bakEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ID)
                  {       
                      pTo_container->packEnergizerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_energizerEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();              
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ID)
                  {            
                      pTo_container->packProtectorEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_protectorEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();         
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ID)
                  {          
                      pTo_container->packDroidEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_droidEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();          
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ID)
                  {                  
                      pTo_container->packFreezerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_freezerEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();   
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ID)
                  {      
                      pTo_container->packScanerEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_scanerEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();            
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ID)
                  {                     
                      pTo_container->packGrappleEquipment(pTo_CURSOR->pTo_otsec_slot->pTo_grappleEquipment); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
              } 
       }
    }

}




void ShipInternal :: renderItemInfo()
{
	// WEAPON SLOT
	for(unsigned int i = 0; i < pTo_ship->weapon_slot_pList.size(); i++)
	{ 
		if (pTo_ship->weapon_slot_pList[i]->is_CURSORED == true)
		{
			if (pTo_ship->weapon_slot_pList[i]->is_EQUIPED == true)
			{
				pTo_ship->weapon_slot_pList[i]->renderItemInfo();
				break;
			}
		}	
	}

	// TOTAL SLOT
	for(unsigned int i = 0; i < pTo_ship->total_slot_pList.size(); i++)
	{ 
		if (pTo_ship->total_slot_pList[i]->is_CURSORED == true)
		{
			if (pTo_ship->total_slot_pList[i]->is_EQUIPED == true)
			{
				pTo_ship->total_slot_pList[i]->renderItemInfo();
				break;
			}
		}	
	}
}





void ShipInternal :: renderInternaly()
{
	glLoadIdentity();    // !!!!

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	drawTexturedRect(pTo_ship->pTo_texOb->texture, pTo_ship->kontur_rect, -1.0);

	for (unsigned int i = 0; i < pTo_ship->weapon_slot_pList.size(); i++)
	{ 
	pTo_ship->weapon_slot_pList[i]->renderFrame(-1);
	}

	for(unsigned int i = 0; i < pTo_ship->total_slot_pList.size(); i++)
	{
	pTo_ship->total_slot_pList[i]->renderFrame(-1);
	}
	
	pTo_ship->gate_slot.renderFrame(-1);
}



