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


WeaponComplex :: WeaponComplex()
{
        turrel1 = NULL;
        turrel2 = NULL;
        turrel3 = NULL;
        turrel4 = NULL;
        turrel5 = NULL;       
        
        owner_points = NULL;
}

WeaponComplex :: ~WeaponComplex()
{
    	delete turrel1;
        delete turrel2;
        delete turrel3;
        delete turrel4;
        delete turrel5;
}
  
void WeaponComplex :: postCreateInit(int weapon_num, Rect kontur_rect, Vehicle* vehicle, bool draw_turrels, TextureOb* texOb)
{
	this->weapon_num = weapon_num;
	owner_points = vehicle->getPoints();
	
	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);  
    	TextureOb* texOb_turrel = g_TEXTURE_MANAGER.getRandomTexOb(TURREL_TEXTURE_ID); 
    	
        if (weapon_num >= 1)
    	{  
       		weapon_slot1 = ItemSlot(WEAPON_SLOT_ID, 
       					vehicle, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*WEAPON_SLOT_WIDTH, 
       					kontur_rect.getCenter().y - WEAPON_SLOT_HEIGHT/2,
       					WEAPON_SLOT_WIDTH, WEAPON_SLOT_HEIGHT);
       					
       		slot_weapon_vec.push_back(&weapon_slot1);
       		vehicle->add(&weapon_slot1); 

       		turrel1 = new Turrel(&weapon_slot1, vehicle->getPoints()->getpWeapon1Center());       
       		turrel1->setTexOb(texOb_turrel); // remove
                
       		weapon_slot1.bindTurrel(turrel1);

       
       		if (draw_turrels == true)
       		{   
           		vehicle->getPoints()->initWeapon1CenterPoint(0, texOb->h/3);
           		vehicle->getPoints()->addWeapon1CenterPoint();
       		} 
    	}
   
    	if (weapon_num >= 2)
    	{  
       		weapon_slot2 = ItemSlot(WEAPON_SLOT_ID, 
       					vehicle, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*WEAPON_SLOT_WIDTH, 
       					kontur_rect.getCenter().y - WEAPON_SLOT_HEIGHT/2 + 1.1*WEAPON_SLOT_HEIGHT,
       					WEAPON_SLOT_WIDTH, WEAPON_SLOT_HEIGHT);
       					    
       		slot_weapon_vec.push_back(&weapon_slot2);
       		vehicle->add(&weapon_slot2); 
       
                turrel2 = new Turrel(&weapon_slot2, vehicle->getPoints()->getpWeapon2Center()); 
       		turrel2->setTexOb(texOb_turrel);
                
              	weapon_slot2.bindTurrel(turrel2);

        
       		if (draw_turrels == true)
       		{  
           		vehicle->getPoints()->initWeapon2CenterPoint(0, -texOb->h/3);
           		vehicle->getPoints()->addWeapon2CenterPoint();
       		}
    	}

    	if (weapon_num >= 3)
    	{  
       		weapon_slot3 = ItemSlot(WEAPON_SLOT_ID, 
       					vehicle, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 1*WEAPON_SLOT_WIDTH, 
       					kontur_rect.getCenter().y - WEAPON_SLOT_HEIGHT/2 - 1.1*WEAPON_SLOT_HEIGHT,
       					WEAPON_SLOT_WIDTH, WEAPON_SLOT_HEIGHT); 
       					
       		slot_weapon_vec.push_back(&weapon_slot3);
       		vehicle->add(&weapon_slot3); 
              
       		turrel3 = new Turrel(&weapon_slot3, vehicle->getPoints()->getpWeapon3Center()); 
       		turrel3->setTexOb(texOb_turrel);
                
              	weapon_slot3.bindTurrel(turrel3);
       
       		if (draw_turrels == true)
       		{  
           		vehicle->getPoints()->initWeapon3CenterPoint(-texOb->w/5, texOb->h/3);
           		vehicle->getPoints()->addWeapon3CenterPoint();
       		}
    	}

    	if (weapon_num >= 4)
    	{  
       		weapon_slot4 = ItemSlot(WEAPON_SLOT_ID, 
       					vehicle, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*WEAPON_SLOT_WIDTH, 
       					kontur_rect.getCenter().y - WEAPON_SLOT_HEIGHT/2 + 1.1*WEAPON_SLOT_HEIGHT/2,
       					WEAPON_SLOT_WIDTH, WEAPON_SLOT_HEIGHT);
       					
       		slot_weapon_vec.push_back(&weapon_slot4);
       		vehicle->add(&weapon_slot4); 
              
       		turrel4 = new Turrel(&weapon_slot4, vehicle->getPoints()->getpWeapon4Center()); 
       		turrel4->setTexOb(texOb_turrel);
                
              	weapon_slot4.bindTurrel(turrel4);

         
       		if (draw_turrels == true)
       		{  
           		vehicle->getPoints()->initWeapon4CenterPoint(texOb->w/5, -texOb->h/3);
           		vehicle->getPoints()->addWeapon4CenterPoint();
       		}

    	}   

    	if (weapon_num >= 5)
    	{  
       		weapon_slot5 = ItemSlot(WEAPON_SLOT_ID, 
       					vehicle, 
       					texOb_slot, 
       					kontur_rect.getCenter().x + 2.2*WEAPON_SLOT_WIDTH, 
       					kontur_rect.getCenter().y - WEAPON_SLOT_HEIGHT/2 - 1.1*WEAPON_SLOT_HEIGHT/2,
       					WEAPON_SLOT_WIDTH, WEAPON_SLOT_HEIGHT);
       					
       		slot_weapon_vec.push_back(&weapon_slot5);
       		vehicle->add(&weapon_slot5); 
              
       		turrel5 = new Turrel(&weapon_slot5, vehicle->getPoints()->getpWeapon5Center()); 
              	turrel5->setTexOb(texOb_turrel);
       
                weapon_slot5.bindTurrel(turrel5);
       		
       		if (draw_turrels == true)
       		{  
           		vehicle->getPoints()->initWeapon5CenterPoint(-texOb->w/3, -texOb->h/3);
           		vehicle->getPoints()->addWeapon5CenterPoint();           		
       		}
    	} 
}

void WeaponComplex :: prepareWeapons()
{
     	// reload wepons
     	// used once at the beginning of turn
     	
	reloadAllWeapons();
	validateAllReloadedWeaponsTarget();
}
    
void WeaponComplex :: reloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->getTurrel()->isAmmoAvailable() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
            
     	fire_delay = 10;
     	d_fire_delay = 40;   
}
  




void WeaponComplex :: selectWeapons()
{
        if (weapon_num >= 1)
                weapon_slot1.getTurrel()->setSelectedStatus(weapon_selector.slot_1);
        if (weapon_num >= 2)
                weapon_slot2.getTurrel()->setSelectedStatus(weapon_selector.slot_2);
        if (weapon_num >= 3)
                weapon_slot3.getTurrel()->setSelectedStatus(weapon_selector.slot_3);
        if (weapon_num >= 4)
                weapon_slot4.getTurrel()->setSelectedStatus(weapon_selector.slot_4);
        if (weapon_num >= 5)
                weapon_slot5.getTurrel()->setSelectedStatus(weapon_selector.slot_5);
}


bool WeaponComplex :: isAnyWeaponSelected() const
{
	return weapon_selector.isAnySelected();     	
}


template <typename TARGET_TYPE> 
void WeaponComplex :: setWeaponsTarget(TARGET_TYPE* _target)
{                          
        float dist = distBetweenPoints(owner_points->getCenter(), _target->getPoints()->getCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
        	if ( slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->getTurrel()->getTargetOb()->getValid() == false )
           		{
           	      		if ( dist < slot_weapon_equiped_vec[i]->getItemRadius() )
           	      		{
                       			slot_weapon_equiped_vec[i]->getTurrel()->setTarget(_target);
                       		}
                       	}
                } 
        }               

}



void WeaponComplex :: weaponsFire_TRUE(int timer)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{	
           		if ( slot_weapon_reloaded_vec[i]->getTurrel()->validateTarget() == true )
           		{	
               			if ( slot_weapon_reloaded_vec[i]->getTurrel()->fireEvent_TRUE() == true )
               			{
                   			slot_weapon_reloaded_vec.erase(slot_weapon_reloaded_vec.begin() + i);
                   			fire_delay += d_fire_delay;
                   			break;
               			}
            			else
            			{
               				slot_weapon_reloaded_vec.erase(slot_weapon_reloaded_vec.begin() + i);
               				break;
            			}
            		}
        	}
        }
}

void WeaponComplex :: validateAllReloadedWeaponsTarget()
{
	// in STATIC after weapons reloaded
        for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        {	
        	slot_weapon_reloaded_vec[i]->getTurrel()->validateTarget();
	}
}


void WeaponComplex :: weaponsFire_FALSE(int timer)
{
        weaponsFire_TRUE(timer);
}




void WeaponComplex :: resetDeselectedWeaponTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
            	if (slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == false)
            	{
                	slot_weapon_equiped_vec[i]->getTurrel()->getTargetOb()->reset();
                }
        }
}


bool WeaponComplex :: updateFireAbility()
{
     	slot_weapon_equiped_vec.clear();

     	//total_damage = 0;
     	//avr_damage =
     	//avr_radius =  
     	
     	//int sum_fire_radius = 0;
     	
     	for (unsigned int i = 0; i < slot_weapon_vec.size(); i++)
     	{ 
        	if (slot_weapon_vec[i]->getEquipedStatus() == true)
        	{
           		if (slot_weapon_vec[i]->getItemCondition() > 0)
           		{
              			slot_weapon_equiped_vec.push_back(slot_weapon_vec[i]);
              			//sum_damage      += slot_weapon_vec[i]->getItemDamage(); 
              			//sum_fire_radius += slot_weapon_vec[i]->getItemRadius(); 
           		}
           	}
     	}

     	//if (slot_weapon_equiped_vec.size() != 0)
     	//{
        	//propetries.average_fire_radius = sum_fire_radius/slot_weapon_equiped_vec.size();
        	//ableTo.FIRE = true;
     	//}
     	//else
     	//{
        	//propetries.average_fire_radius = 0;
        	//ableTo.FIRE = false;
     	//} 
     	
     	if (slot_weapon_equiped_vec.size() != 0)
     	{
        	return true;
     	}
     	else
     	{
        	return false;
     	} 
}


void WeaponComplex :: renderTurrels() const
{
    	for(unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->getTurrel()->render(owner_points->getAngleDegree());        
    	} 
}



void WeaponComplex :: renderWeaponsRange()
{
	glPushMatrix();
		glTranslatef(owner_points->getCenter().x, owner_points->getCenter().y, 0.0f);
		for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{
         		if (slot_weapon_reloaded_vec[i]->getTurrel()->getSelectedStatus() == true)
                	{
                		slot_weapon_reloaded_vec[i]->updateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_red);
             			slot_weapon_reloaded_vec[i]->drawRange();
             		}

        	}
	glPopMatrix();
}

void WeaponComplex :: renderWeaponIcons() const
{
        enable_BLEND();
        
        int offset = 0;
        for (unsigned int wi = 0; wi < slot_weapon_vec.size(); wi++)
        {
                Turrel* _turrel = slot_weapon_vec[wi]->getTurrel();
                if (_turrel->getTargetOb()->getValid() == true)
                {       
                        Rect _rect(_turrel->getTargetOb()->getpCenter()->x - 40/2 + 23*offset, _turrel->getTargetOb()->getpCenter()->y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[wi]->getItemTexOb(), _rect, -2.0);
                        offset++;
                }        
        }
        
        disable_BLEND();
}
