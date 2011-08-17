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
 
    pTo_ship->drive_slot.is_CURSORED     = false;
    pTo_ship->bak_slot.is_CURSORED       = false;
    pTo_ship->radar_slot.is_CURSORED     = false;
    pTo_ship->scaner_slot.is_CURSORED    = false;
    pTo_ship->energizer_slot.is_CURSORED = false;
    pTo_ship->grapple_slot.is_CURSORED   = false;
    pTo_ship->protector_slot.is_CURSORED = false;
    pTo_ship->droid_slot.is_CURSORED     = false;
    pTo_ship->freezer_slot.is_CURSORED   = false;

    for(unsigned int i = 0; i < pTo_ship->otsec_slot_pList.size(); i++)
    { 
       pTo_ship->otsec_slot_pList[i]->is_CURSORED = false;
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
                        if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_lazerItem);
                            pTo_ship->weapon_slot_pList[i]->removeLazerItem();
                        }

                        if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->weapon_slot_pList[i]->pTo_rocketItem);
                            pTo_ship->weapon_slot_pList[i]->removeRocketItem();
                        } 
                    }
                    else  
                    {   // merge module with item                    
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_MODULE_ID)
                        {
                            if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == LAZER_ITEM_ID)
                            {
                                if (pTo_ship->weapon_slot_pList[i]->pTo_lazerItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_lazerModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }   

                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_MODULE_ID)
                        {
                            if (pTo_ship->weapon_slot_pList[i]->item_subtype_id == ROCKET_ITEM_ID)
                            {
                                if (pTo_ship->weapon_slot_pList[i]->pTo_rocketItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_rocketModule) == true)
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
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ITEM_ID)
                        {
                            pTo_ship->weapon_slot_pList[i]->insertLazerItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ITEM_ID)
                        {
                            pTo_ship->weapon_slot_pList[i]->insertRocketItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }                     
                    } 
                }    
            }

           
        }
    }


    // DRIVE SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->drive_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->drive_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->drive_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item 
                        if (pTo_ship->drive_slot.item_subtype_id == DRIVE_ITEM_ID)
                        {   
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->drive_slot.pTo_driveItem);
                            pTo_ship->drive_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_MODULE_ID)
                        {   
                            if (pTo_ship->drive_slot.item_subtype_id == DRIVE_ITEM_ID)
                            {
                                if (pTo_ship->drive_slot.pTo_driveItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_driveModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }          
                    }
                }
                
                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyDriveSlotItem(&pTo_ship->drive_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 
            }
          
            else
            {   // slot is EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ITEM_ID)
                        {
                            pTo_ship->drive_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    } 
                }    
            }

        } 
    }


    // BAK SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->bak_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->bak_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->bak_slot.is_EQUIPED == true)
            {   // SLOT IS EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {   
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item 
                        if (pTo_ship->bak_slot.item_subtype_id == BAK_ITEM_ID)
                        {   
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->bak_slot.pTo_bakItem);
                            pTo_ship->bak_slot.removeItem();
                        }
                    }    
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_MODULE_ID)
                        {   
                            if (pTo_ship->bak_slot.item_subtype_id == BAK_ITEM_ID)
                            {
                                if (pTo_ship->bak_slot.pTo_bakItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_bakModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }                          
                    }
                
                }
                    
                if ( (lmb == true) && (in_store == true) )
                {   // sell item 
                    int earn_price = pTo_store->buyBakSlotItem(&pTo_ship->bak_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 
            }
        
            else
            {   // SLOT IS EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ITEM_ID)
                        {   
                            pTo_ship->bak_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    } 
                }    
            }
        }
    }

    // RADAR SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->radar_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->radar_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->radar_slot.is_EQUIPED == true)
            {   // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->radar_slot.item_subtype_id == RADAR_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->radar_slot.pTo_radarItem);
                            pTo_ship->radar_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_MODULE_ID)
                        {   
                            if (pTo_ship->radar_slot.item_subtype_id == RADAR_ITEM_ID)
                            {
                                if (pTo_ship->radar_slot.pTo_radarItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }  
                    }
                }    

                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyRadarSlotItem(&pTo_ship->radar_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 
            }
            else
            {             
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ITEM_ID)
                        {
                            pTo_ship->radar_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    }
                }     
            }

       } 
    }



    // SCANER SLOT
    if (cursor_has_target == false)
    {
       if (pTo_ship->scaner_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
       {
            pTo_ship->scaner_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->scaner_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->scaner_slot.item_subtype_id == SCANER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->scaner_slot.pTo_scanerItem);
                            pTo_ship->scaner_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_MODULE_ID)
                        {   
                            if (pTo_ship->scaner_slot.item_subtype_id == SCANER_ITEM_ID)
                            {
                                if (pTo_ship->scaner_slot.pTo_scanerItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_scanerModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }  
                    }
                }
                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyScanerSlotItem(&pTo_ship->scaner_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 
            }
            else
            {   // slot is EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ITEM_ID)
                        {
                           pTo_ship->scaner_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerItem);
                           pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    }
                }     
            }


       } 
    }


    // ENERGIZER SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->energizer_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->energizer_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->energizer_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->energizer_slot.item_subtype_id == ENERGIZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->energizer_slot.pTo_energizerItem);
                            pTo_ship->energizer_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_MODULE_ID)
                        {   
                            if (pTo_ship->energizer_slot.item_subtype_id == ENERGIZER_ITEM_ID)
                            {
                                if (pTo_ship->energizer_slot.pTo_energizerItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_energizerModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }  
                    }
                }    
                
                if ( (lmb == true) && (in_store == true) )
                {   // sell item 
                    int earn_price = pTo_store->buyEnergizerSlotItem(&pTo_ship->energizer_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 

            }
            else
            {   // slot is EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ITEM_ID)
                        {
                            pTo_ship->energizer_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    }
                }     
            }


        } 
    }

    // GRAPPLE SLOT
    if (pTo_ship->inhibit_GRAPPLE == false)
    {
        if (cursor_has_target == false)
        {
            if (pTo_ship->grapple_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
            {
                pTo_ship->grapple_slot.is_CURSORED = true;
                cursor_has_target = true;

                if (pTo_ship->grapple_slot.is_EQUIPED == true)
                { 
                    // slot is EQUIPED
                    if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                    {
                        if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                        {   // take item
                            if (pTo_ship->grapple_slot.item_subtype_id == GRAPPLE_ITEM_ID)
                            {
                                pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->grapple_slot.pTo_grappleItem);
                                pTo_ship->grapple_slot.removeItem();
                            }
                        }
                        else
                        {   // merge module with item
                            if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_MODULE_ID)
                            {   
                                if (pTo_ship->grapple_slot.item_subtype_id == GRAPPLE_ITEM_ID)
                                {
                                    if (pTo_ship->grapple_slot.pTo_grappleItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_grappleModule) == true)
                                    {
                                        pTo_CURSOR->pTo_otsec_slot->removeItem();
                                    }    
                                }
                            }   
                        }
                    }

                    if ( (lmb == true) && (in_store == true) )
                    {   // sell item
                        int earn_price = pTo_store->buyGrappleSlotItem(&pTo_ship->grapple_slot);
                        pTo_PLAYER->pTo_npc->credits += earn_price;
                    } 

                }
                else
                {   // slot is EMPTY           
                    if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                    {
                        if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                        {   // insert item
                            if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ITEM_ID)
                            {
                                pTo_ship->grapple_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleItem);
                                pTo_CURSOR->pTo_otsec_slot->removeItem();
                            }
                        }
                    }     
                }


            } 
        }
    }


    // PROTECTOR SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->protector_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->protector_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->protector_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->protector_slot.item_subtype_id == PROTECTOR_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->protector_slot.pTo_protectorItem);
                            pTo_ship->protector_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_MODULE_ID)
                        {   
                            if (pTo_ship->protector_slot.item_subtype_id == PROTECTOR_ITEM_ID)
                            {
                                if (pTo_ship->protector_slot.pTo_protectorItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_protectorModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }   
                    }
                }    

                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyProtectorSlotItem(&pTo_ship->protector_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 

            }
            else
            {   // slot is EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ITEM_ID)
                        {
                            pTo_ship->protector_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    } 
                }    
            }

        } 
    }


    // DROID SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->droid_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->droid_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->droid_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->droid_slot.item_subtype_id == DROID_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->droid_slot.pTo_droidItem);
                            pTo_ship->droid_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_MODULE_ID)
                        {   
                            if (pTo_ship->droid_slot.item_subtype_id == DROID_ITEM_ID)
                            {
                                if (pTo_ship->droid_slot.pTo_droidItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_droidModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }   
                    }
                }    
                // sell item
                if ( (lmb == true) && (in_store == true) )
                {
                    int earn_price = pTo_store->buyDroidSlotItem(&pTo_ship->droid_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 

            }
            // slot is EMPTY
            else
            {             
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ITEM_ID)
                        {
                            pTo_ship->droid_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    } 
                }    
            }

        } 
    }


    // FREEZER SLOT
    if (cursor_has_target == false)
    {
        if (pTo_ship->freezer_slot.interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)  
        {
            pTo_ship->freezer_slot.is_CURSORED = true;
            cursor_has_target = true;

            if (pTo_ship->freezer_slot.is_EQUIPED == true)
            { 
                // slot is EQUIPED
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {   // take item
                        if (pTo_ship->freezer_slot.item_subtype_id == FREEZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->freezer_slot.pTo_freezerItem);
                            pTo_ship->freezer_slot.removeItem();
                        }
                    }
                    else
                    {   // merge module with item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_MODULE_ID)
                        {   
                            if (pTo_ship->freezer_slot.item_subtype_id == FREEZER_ITEM_ID)
                            {
                                if (pTo_ship->freezer_slot.pTo_freezerItem->insertModule(pTo_CURSOR->pTo_otsec_slot->pTo_freezerModule) == true)
                                {
                                    pTo_CURSOR->pTo_otsec_slot->removeItem();
                                }    
                            }
                        }  
                    }
                }    

                if ( (lmb == true) && (in_store == true) )
                {   // sell item
                    int earn_price = pTo_store->buyFreezerSlotItem(&pTo_ship->freezer_slot);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                }  

            }
            else
            {   // slot is EMPTY          
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {   // insert item
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ITEM_ID)
                        {
                            pTo_ship->freezer_slot.insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                    }
                }     
            }
            
        } 
    }


    // OTSEC SLOT START
    for(unsigned int i = 0; i < pTo_ship->otsec_slot_pList.size(); i++)
    { 
       if (pTo_ship->otsec_slot_pList[i]->interaction(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y)) == true)
       {  
            pTo_ship->otsec_slot_pList[i]->is_CURSORED = true;
            cursor_has_target = true;


            //// TAKE ITEM ////
            if (pTo_ship->otsec_slot_pList[i]->is_EQUIPED == true)
            { 
                // INSERT ITEM TO CURSOR //
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == false)
                    {
                        // weapons
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == LAZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_lazerItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == ROCKET_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_rocketItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }

                        // items
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == RADAR_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_radarItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == DRIVE_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_driveItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == BAK_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_bakItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == ENERGIZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_energizerItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == PROTECTOR_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_protectorItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == DROID_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_droidItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == FREEZER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_freezerItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == SCANER_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_scanerItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == GRAPPLE_ITEM_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_grappleItem);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                     
                        // modules
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == LAZER_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_lazerModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == ROCKET_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_rocketModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == RADAR_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_radarModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == DRIVE_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_driveModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == BAK_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_bakModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == ENERGIZER_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_energizerModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == PROTECTOR_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_protectorModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == DROID_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_droidModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == FREEZER_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_freezerModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == SCANER_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_scanerModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        if (pTo_ship->otsec_slot_pList[i]->item_subtype_id == GRAPPLE_MODULE_ID)
                        {
                            pTo_CURSOR->pTo_otsec_slot->insertItem(pTo_ship->otsec_slot_pList[i]->pTo_grappleModule);
                            pTo_ship->otsec_slot_pList[i]->removeItem();
                        }
                        // artifacts
                        // bomb
                    }
                // SELL ITEM TO STORE //
                if ( (lmb == true) && (in_store == true) )
                {
                    int earn_price = pTo_store->buyOtsecSlotItem(pTo_ship->otsec_slot_pList[i]);
                    pTo_PLAYER->pTo_npc->credits += earn_price;
                } 

            }
            //// PUT ITEM ////
            else
            {             
                if ( (lmb == true) && (allow_full_control == true) && (in_store == false) )
                {
                    if (pTo_CURSOR->pTo_otsec_slot->is_EQUIPED == true)
                    {                    
                        // weapons
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }

                    
                        // items
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ITEM_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleItem);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }

                        // modules
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_MODULE_ID)
                        {
                            pTo_ship->otsec_slot_pList[i]->insertItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleModule);
                            pTo_CURSOR->pTo_otsec_slot->removeItem();
                        }
                        // artifacts
                        // bomb
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

                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == LAZER_ITEM_ID)
                  {     
                      pTo_container->packLazerItem(pTo_CURSOR->pTo_otsec_slot->pTo_lazerItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ROCKET_ITEM_ID)
                  {             
                      pTo_container->packRocketItem(pTo_CURSOR->pTo_otsec_slot->pTo_rocketItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();  
                  }

                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == RADAR_ITEM_ID)
                  {                      
                      pTo_container->packRadarItem(pTo_CURSOR->pTo_otsec_slot->pTo_radarItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DRIVE_ITEM_ID)
                  {               
                      pTo_container->packDriveItem(pTo_CURSOR->pTo_otsec_slot->pTo_driveItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem(); 
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == BAK_ITEM_ID)
                  {                      
                      pTo_container->packBakItem(pTo_CURSOR->pTo_otsec_slot->pTo_bakItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == ENERGIZER_ITEM_ID)
                  {       
                      pTo_container->packEnergizerItem(pTo_CURSOR->pTo_otsec_slot->pTo_energizerItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();              
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == PROTECTOR_ITEM_ID)
                  {            
                      pTo_container->packProtectorItem(pTo_CURSOR->pTo_otsec_slot->pTo_protectorItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();         
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == DROID_ITEM_ID)
                  {          
                      pTo_container->packDroidItem(pTo_CURSOR->pTo_otsec_slot->pTo_droidItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();          
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == FREEZER_ITEM_ID)
                  {                  
                      pTo_container->packFreezerItem(pTo_CURSOR->pTo_otsec_slot->pTo_freezerItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();   
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == SCANER_ITEM_ID)
                  {      
                      pTo_container->packScanerItem(pTo_CURSOR->pTo_otsec_slot->pTo_scanerItem); 
                      pTo_CURSOR->pTo_otsec_slot->removeItem();            
                  }
                  if (pTo_CURSOR->pTo_otsec_slot->item_subtype_id == GRAPPLE_ITEM_ID)
                  {                     
                      pTo_container->packGrappleItem(pTo_CURSOR->pTo_otsec_slot->pTo_grappleItem); 
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
          if (pTo_ship->weapon_slot_pList[i]->is_EQUIPED == true)
          {
              pTo_ship->weapon_slot_pList[i]->renderItemInfo();
              break;
          }
    }

    // DRIVE SLOT
    if (pTo_ship->drive_slot.is_CURSORED == true)
       if (pTo_ship->drive_slot.is_EQUIPED == true)
           pTo_ship->drive_slot.renderItemInfo();


    // BAK SLOT
    if (pTo_ship->bak_slot.is_CURSORED == true)
       if (pTo_ship->bak_slot.is_EQUIPED == true)
           pTo_ship->bak_slot.renderItemInfo();


    // RADAR SLOT
    if (pTo_ship->radar_slot.is_CURSORED == true)
       if (pTo_ship->radar_slot.is_EQUIPED == true)
           pTo_ship->radar_slot.renderItemInfo();


    // SCANER SLOT
    if (pTo_ship->scaner_slot.is_CURSORED == true)
       if (pTo_ship->scaner_slot.is_EQUIPED == true)
           pTo_ship->scaner_slot.renderItemInfo();


    // ENERGYBLOCK SLOT
    if (pTo_ship->energizer_slot.is_CURSORED == true)
       if (pTo_ship->energizer_slot.is_EQUIPED == true)
           pTo_ship->energizer_slot.renderItemInfo();


    // GRAPPLE SLOT
    if (pTo_ship->inhibit_GRAPPLE == false)
       if (pTo_ship->grapple_slot.is_CURSORED == true)
          if (pTo_ship->grapple_slot.is_EQUIPED == true)
              pTo_ship->grapple_slot.renderItemInfo();


    // PROTECTOR SLOT
    if (pTo_ship->protector_slot.is_CURSORED == true)
       if (pTo_ship->protector_slot.is_EQUIPED == true)
           pTo_ship->protector_slot.renderItemInfo();


    // DROID SLOT
    if (pTo_ship->droid_slot.is_CURSORED == true)
       if (pTo_ship->droid_slot.is_EQUIPED == true)
           pTo_ship->droid_slot.renderItemInfo();


    // FREEZER SLOT
    if (pTo_ship->freezer_slot.is_CURSORED == true)
       if (pTo_ship->freezer_slot.is_EQUIPED == true)
           pTo_ship->freezer_slot.renderItemInfo();


    // OTSEC SLOT
    for(unsigned int i = 0; i < pTo_ship->otsec_slot_pList.size(); i++)
    { 
       if (pTo_ship->otsec_slot_pList[i]->is_CURSORED == true)
          if (pTo_ship->otsec_slot_pList[i]->is_EQUIPED == true)
          {
              pTo_ship->otsec_slot_pList[i]->renderItemInfo();
              break;
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

    pTo_ship->drive_slot.renderFrame(-1);
    pTo_ship->bak_slot.renderFrame(-1);
    pTo_ship->radar_slot.renderFrame(-1);
    pTo_ship->scaner_slot.renderFrame(-1);
    pTo_ship->energizer_slot.renderFrame(-1);
    if (pTo_ship->inhibit_GRAPPLE == false)
       pTo_ship->grapple_slot.renderFrame(-1);
    pTo_ship->protector_slot.renderFrame(-1);
    pTo_ship->droid_slot.renderFrame(-1);
    pTo_ship->freezer_slot.renderFrame(-1);

    for(unsigned int i = 0; i < pTo_ship->otsec_slot_pList.size(); i++)
    {
       pTo_ship->otsec_slot_pList[i]->renderFrame(-1);
    }

    pTo_ship->gate_slot.renderFrame(-1);
}



