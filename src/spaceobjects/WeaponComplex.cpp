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


WeaponComplex :: WeaponComplex(Vehicle* vehicle)
{
        turrel1 = NULL;
        turrel2 = NULL;
        turrel3 = NULL;
        turrel4 = NULL;
        turrel5 = NULL;       
        
        this->owner_vehicle = vehicle;
}

WeaponComplex :: ~WeaponComplex()
{        
    	delete turrel1;
        delete turrel2;
        delete turrel3;
        delete turrel4;
        delete turrel5;
}
  
ItemSlot& WeaponComplex :: GetWeaponSlot1() { return weapon_slot1; }
ItemSlot& WeaponComplex :: GetWeaponSlot2() { return weapon_slot2; }
ItemSlot& WeaponComplex :: GetWeaponSlot3() { return weapon_slot3; }
ItemSlot& WeaponComplex :: GetWeaponSlot4() { return weapon_slot4; }
ItemSlot& WeaponComplex :: GetWeaponSlot5() { return weapon_slot5; }
      		
void WeaponComplex :: PostCreateInit(int weapon_num, bool draw_turrels)
{
	this->weapon_num = weapon_num;
	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::SLOT_ID); 
	TextureOb* texOb_turrel = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::TURREL_ID); 
    	
        if (weapon_num >= 1)
    	{  
       		weapon_slot1.SetSubTypeId(SLOT::WEAPON_ID);       		
       		weapon_slot1.SetTextureOb(texOb_slot);
       		weapon_slot1.SetOwnerVehicle(owner_vehicle);
       		weapon_slot1.setRect(  owner_vehicle->GetGuiRect().getCenter().x + 1*GUI::SLOT::WIDTH_FOR_SHIP, 
       				        owner_vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2,
       				        GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);		
       				      	
       		slot_weapon_vec.push_back(&weapon_slot1);
       		owner_vehicle->Add(&weapon_slot1); 

       		turrel1 = new Turrel(&weapon_slot1, owner_vehicle->GetPoints().getpWeapon1Center());       
       		turrel1->setTexOb(texOb_turrel); // remove
                
       		weapon_slot1.bindTurrel(turrel1);

       
       		if (draw_turrels == true)
       		{   
           		owner_vehicle->GetPoints().initWeapon1CenterPoint(0, owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon1CenterPoint();
       		} 
    	}
   
    	if (weapon_num >= 2)
    	{  
       		weapon_slot2.SetSubTypeId(SLOT::WEAPON_ID);      
       		weapon_slot2.SetTextureOb(texOb_slot);
       		weapon_slot2.SetOwnerVehicle(owner_vehicle);
       		weapon_slot2.setRect( owner_vehicle->GetGuiRect().getCenter().x + 1*GUI::SLOT::WIDTH_FOR_SHIP, 
       				      owner_vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
       				      GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       			    
       		slot_weapon_vec.push_back(&weapon_slot2);
       		owner_vehicle->Add(&weapon_slot2); 
       
                turrel2 = new Turrel(&weapon_slot2, owner_vehicle->GetPoints().getpWeapon2Center()); 
       		turrel2->setTexOb(texOb_turrel);
                
              	weapon_slot2.bindTurrel(turrel2);

        
       		if (draw_turrels == true)
       		{  
           		owner_vehicle->GetPoints().initWeapon2CenterPoint(0, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon2CenterPoint();
       		}
    	}

    	if (weapon_num >= 3)
    	{  
       		weapon_slot3.SetSubTypeId(SLOT::WEAPON_ID); 
       		weapon_slot3.SetTextureOb(texOb_slot); 
       		weapon_slot3.SetOwnerVehicle(owner_vehicle);	
       		weapon_slot3.setRect(  owner_vehicle->GetGuiRect().getCenter().x + 1*GUI::SLOT::WIDTH_FOR_SHIP, 
       					owner_vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
       					GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       				
       		slot_weapon_vec.push_back(&weapon_slot3);
       		owner_vehicle->Add(&weapon_slot3); 
              
       		turrel3 = new Turrel(&weapon_slot3, owner_vehicle->GetPoints().getpWeapon3Center()); 
       		turrel3->setTexOb(texOb_turrel);
                
              	weapon_slot3.bindTurrel(turrel3);
       
       		if (draw_turrels == true)
       		{  
           		owner_vehicle->GetPoints().initWeapon3CenterPoint(-owner_vehicle->GetTextureOb()->getFrameWidth()/5, owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon3CenterPoint();
       		}
    	}

    	if (weapon_num >= 4)
    	{  
       		weapon_slot4.SetSubTypeId(SLOT::WEAPON_ID); 
       		weapon_slot4.SetTextureOb(texOb_slot); 
       		weapon_slot4.SetOwnerVehicle(owner_vehicle);		
       		weapon_slot4.setRect(  owner_vehicle->GetGuiRect().getCenter().x + 2.2*GUI::SLOT::WIDTH_FOR_SHIP, 
       					owner_vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
       					GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);	
       			
       		slot_weapon_vec.push_back(&weapon_slot4);
       		owner_vehicle->Add(&weapon_slot4); 
              
       		turrel4 = new Turrel(&weapon_slot4, owner_vehicle->GetPoints().getpWeapon4Center()); 
       		turrel4->setTexOb(texOb_turrel);
                
              	weapon_slot4.bindTurrel(turrel4);

         
       		if (draw_turrels == true)
       		{  
           		owner_vehicle->GetPoints().initWeapon4CenterPoint(owner_vehicle->GetTextureOb()->getFrameWidth()/5, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon4CenterPoint();
       		}

    	}   

    	if (weapon_num >= 5)
    	{  
       		weapon_slot5.SetSubTypeId(SLOT::WEAPON_ID); 
       		weapon_slot5.SetTextureOb(texOb_slot); 
       		weapon_slot5.SetOwnerVehicle(owner_vehicle);
       		weapon_slot5.setRect(  owner_vehicle->GetGuiRect().getCenter().x + 2.2*GUI::SLOT::WIDTH_FOR_SHIP, 
       					owner_vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
       					GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       					
       		slot_weapon_vec.push_back(&weapon_slot5);
       		owner_vehicle->Add(&weapon_slot5); 
              
       		turrel5 = new Turrel(&weapon_slot5, owner_vehicle->GetPoints().getpWeapon5Center()); 
              	turrel5->setTexOb(texOb_turrel);
       
                weapon_slot5.bindTurrel(turrel5);
       		
       		if (draw_turrels == true)
       		{  
           		owner_vehicle->GetPoints().initWeapon5CenterPoint(-owner_vehicle->GetTextureOb()->getFrameWidth()/3, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon5CenterPoint();           		
       		}
    	} 
}

void WeaponComplex :: PrepareWeapons()
{
     	// used once at the beginning of turn
	ReloadAllWeapons();
	ValidateAllReloadedWeaponsTarget();
}
    
void WeaponComplex :: ReloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->getTurrel()->isAmmoOk() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
            
     	fire_delay = 10;
     	d_fire_delay = 40;   
}
  




void WeaponComplex :: SelectWeapons()
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


bool WeaponComplex :: IsAnyWeaponSelected() const
{
	return weapon_selector.isAnySelected();
}


void WeaponComplex :: SetTarget(BaseGameEntity* _target)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().getCenter(), _target->GetPoints().getCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
        	if ( slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->getTurrel()->getTarget() == NULL )
           		{
         			slot_weapon_equiped_vec[i]->getTurrel()->setTarget(_target);
                                slot_weapon_equiped_vec[i]->getTurrel()->validateTarget();                                        
                        }
                } 
        }               

}



void WeaponComplex :: Fire(int timer, bool show_effect)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{	
           		if ( slot_weapon_reloaded_vec[i]->getTurrel()->isTargetOk() == true )
           		{	
               			if ( slot_weapon_reloaded_vec[i]->getTurrel()->fireEvent(show_effect) == true )
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

void WeaponComplex :: ValidateAllReloadedWeaponsTarget()
{
	// in STATIC after weapons reloaded
        for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        {	
        	slot_weapon_reloaded_vec[i]->getTurrel()->validateTarget();
	}
}



void WeaponComplex :: ResetDeselectedWeaponTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
            	if (slot_weapon_equiped_vec[i]->getTurrel()->getSelectedStatus() == false)
            	{
                	slot_weapon_equiped_vec[i]->getTurrel()->resetTarget();
                }
        }
}


bool WeaponComplex :: UpdateFireAbility()
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
           		if (slot_weapon_vec[i]->getItem()->GetCondition() > 0)
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


void WeaponComplex :: RenderTurrels() const
{
    	for(unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->getTurrel()->render(owner_vehicle->GetPoints().getAngleDegree());        
    	} 
}



void WeaponComplex :: RenderWeaponsRange()
{
	glPushMatrix();
		glTranslatef(owner_vehicle->GetPoints().getCenter().x, owner_vehicle->GetPoints().getCenter().y, 0.0f);
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

void WeaponComplex :: RenderWeaponIcons() const
{
        enable_BLEND();
        
        int offset = 0;
        for (unsigned int wi = 0; wi < slot_weapon_vec.size(); wi++)
        {
                Turrel* _turrel = slot_weapon_vec[wi]->getTurrel();
                if (_turrel->getTarget() != NULL )
                {       
                        Rect _rect(_turrel->getTarget()->GetPoints().getpCenter()->x - 40/2 + 23*offset, _turrel->getTarget()->GetPoints().getpCenter()->y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[wi]->getItem()->GetTextureOb(), _rect, -2.0);
                        offset++;
                }        
        }
        
        disable_BLEND();
}
