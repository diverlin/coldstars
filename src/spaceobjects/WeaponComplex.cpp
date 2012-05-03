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


WeaponComplex::WeaponComplex(Vehicle* vehicle)
{
        weapon_slot1 = NULL;
        weapon_slot2 = NULL;
        weapon_slot3 = NULL;
        weapon_slot4 = NULL;
        weapon_slot5 = NULL;
                
        turrel1 = NULL;
        turrel2 = NULL;
        turrel3 = NULL;
        turrel4 = NULL;
        turrel5 = NULL;       
        
        this->owner_vehicle = vehicle;
}

WeaponComplex::~WeaponComplex()
{        
        //delete weapon_slot1;
        //delete weapon_slot2;
        //delete weapon_slot3;
        //delete weapon_slot4;
        //delete weapon_slot5;
        
    	delete turrel1;
        delete turrel2;
        delete turrel3;
        delete turrel4;
        delete turrel5;
}

void WeaponComplex::PostCreateInit(int weapon_num, bool draw_turrels)
{
	this->weapon_num = weapon_num;
	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SLOT_ID); 
	TextureOb* texOb_turrel = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::TURREL_ID); 
    	
        if (weapon_num >= 1)
    	{  
                weapon_slot1 = GetNewItemSlot(SLOT::WEAPON_ID);

       		weapon_slot1->SetRect(owner_vehicle->GetGuiRect().getCenter().x + 1*GUI::SLOT::WIDTH_FOR_SHIP, 
       				      owner_vehicle->GetGuiRect().getCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
       				      GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);		
       				      	
       		slot_weapon_vec.push_back(weapon_slot1);
       		owner_vehicle->Add(weapon_slot1); 

       
       		if (draw_turrels == true)
       		{   
                        turrel1 = new Turrel(weapon_slot1, owner_vehicle->GetPoints().getpWeapon1Center()); 
                        turrel1->SetTextureOb(texOb_turrel);       
                        turrel1->GetPoints().addMainQuadPoints();
                        turrel1->GetPoints().initMainQuadPoints(texOb_turrel->getFrameWidth(), texOb_turrel->getFrameHeight());
                
                        weapon_slot1->SetTurrel(turrel1);
                
           		owner_vehicle->GetPoints().initWeapon1CenterPoint(0, owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		owner_vehicle->GetPoints().addWeapon1CenterPoint();
       		} 
    	}
   
    	//if (weapon_num >= 2)
    	//{  
                //weapon_slot2 = GetNewItemSlot(SLOT::WEAPON_ID); 
                
       		//weapon_slot2->SetRect(owner_vehicle->GetGuiRect().getCenter().x+1*GUI::SLOT::WIDTH_FOR_SHIP, 
       				      //owner_vehicle->GetGuiRect().getCenter().y+-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
       				      //GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       			    
       		//slot_weapon_vec.push_back(weapon_slot2);
       		//owner_vehicle->Add(weapon_slot2); 
       
                //turrel2 = new Turrel(weapon_slot2, owner_vehicle->GetPoints().getpWeapon2Center()); 
       		//turrel2->SetTextureOb(texOb_turrel);
                //turrel2->GetPoints().addMainQuadPoints();
                //turrel2->GetPoints().initMainQuadPoints(texOb_turrel->getFrameWidth(), texOb_turrel->getFrameHeight());
                
              	//weapon_slot2->SetTurrel(turrel2);

        
       		//if (draw_turrels == true)
       		//{  
           		//owner_vehicle->GetPoints().initWeapon2CenterPoint(0, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		//owner_vehicle->GetPoints().addWeapon2CenterPoint();
       		//}
    	//}

    	//if (weapon_num >= 3)
    	//{  
                //weapon_slot3 = GetNewItemSlot(SLOT::WEAPON_ID); 
                	
       		//weapon_slot3->SetRect(owner_vehicle->GetGuiRect().getCenter().x+1*GUI::SLOT::WIDTH_FOR_SHIP, 
                                      //owner_vehicle->GetGuiRect().getCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
       					//GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       				
       		//slot_weapon_vec.push_back(weapon_slot3);
       		//owner_vehicle->Add(weapon_slot3); 
              
       		//turrel3 = new Turrel(weapon_slot3, owner_vehicle->GetPoints().getpWeapon3Center()); 
       		//turrel3->SetTextureOb(texOb_turrel);
                //turrel3->GetPoints().addMainQuadPoints();
                //turrel3->GetPoints().initMainQuadPoints(texOb_turrel->getFrameWidth(), texOb_turrel->getFrameHeight());
                
                
              	//weapon_slot3->SetTurrel(turrel3);
       
       		//if (draw_turrels == true)
       		//{  
           		//owner_vehicle->GetPoints().initWeapon3CenterPoint(-owner_vehicle->GetTextureOb()->getFrameWidth()/5, owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		//owner_vehicle->GetPoints().addWeapon3CenterPoint();
       		//}
    	//}

    	//if (weapon_num >= 4)
    	//{  
                //weapon_slot4 = GetNewItemSlot(SLOT::WEAPON_ID); 
                
       		//weapon_slot4->SetRect(owner_vehicle->GetGuiRect().getCenter().x+2.2*GUI::SLOT::WIDTH_FOR_SHIP, 
                                      //owner_vehicle->GetGuiRect().getCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
                                      //GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);	
       			
       		//slot_weapon_vec.push_back(weapon_slot4);
       		//owner_vehicle->Add(weapon_slot4); 
              
       		//turrel4 = new Turrel(weapon_slot4, owner_vehicle->GetPoints().getpWeapon4Center()); 
       		//turrel4->SetTextureOb(texOb_turrel);
                //turrel4->GetPoints().addMainQuadPoints();
                //turrel4->GetPoints().initMainQuadPoints(texOb_turrel->getFrameWidth(), texOb_turrel->getFrameHeight());
                
                
              	//weapon_slot4->SetTurrel(turrel4);

         
       		//if (draw_turrels == true)
       		//{  
           		//owner_vehicle->GetPoints().initWeapon4CenterPoint(owner_vehicle->GetTextureOb()->getFrameWidth()/5, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		//owner_vehicle->GetPoints().addWeapon4CenterPoint();
       		//}

    	//}   

    	//if (weapon_num >= 5)
    	//{  
                //weapon_slot5 = GetNewItemSlot(SLOT::WEAPON_ID); 
                
       		//weapon_slot5->SetRect(owner_vehicle->GetGuiRect().getCenter().x+2.2*GUI::SLOT::WIDTH_FOR_SHIP, 
                                      //owner_vehicle->GetGuiRect().getCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
                                      //GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
       					
       		//slot_weapon_vec.push_back(weapon_slot5);
       		//owner_vehicle->Add(weapon_slot5); 
              
       		//turrel5 = new Turrel(weapon_slot5, owner_vehicle->GetPoints().getpWeapon5Center()); 
              	//turrel5->SetTextureOb(texOb_turrel);
                //turrel5->GetPoints().addMainQuadPoints();
                //turrel5->GetPoints().initMainQuadPoints(texOb_turrel->getFrameWidth(), texOb_turrel->getFrameHeight());
                
                
                //weapon_slot5->SetTurrel(turrel5);
       		
       		//if (draw_turrels == true)
       		//{  
           		//owner_vehicle->GetPoints().initWeapon5CenterPoint(-owner_vehicle->GetTextureOb()->getFrameWidth()/3, -owner_vehicle->GetTextureOb()->getFrameHeight()/3);
           		//owner_vehicle->GetPoints().addWeapon5CenterPoint();
       		//}
    	//} 
}

void WeaponComplex::PrepareWeapons()
{
     	// used once at the beginning of turn
	ReloadAllWeapons();
	ValidateAllReloadedWeaponsTarget();
}
    
void WeaponComplex::ReloadAllWeapons()
{
     	slot_weapon_reloaded_vec.clear();
     	for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
         	if (slot_weapon_equiped_vec[i]->GetTurrel()->CheckAmmo() == true)
                {
             		slot_weapon_reloaded_vec.push_back(slot_weapon_equiped_vec[i]);
                }
        }
            
     	fire_delay = 10;
     	d_fire_delay = 40;   
}
  
void WeaponComplex::SelectWeapons()
{
        if (weapon_num >= 1)
                weapon_slot1->GetTurrel()->SetSelectedStatus(weapon_selector.slot_1);
        if (weapon_num >= 2)
                weapon_slot2->GetTurrel()->SetSelectedStatus(weapon_selector.slot_2);
        if (weapon_num >= 3)
                weapon_slot3->GetTurrel()->SetSelectedStatus(weapon_selector.slot_3);
        if (weapon_num >= 4)
                weapon_slot4->GetTurrel()->SetSelectedStatus(weapon_selector.slot_4);
        if (weapon_num >= 5)
                weapon_slot5->GetTurrel()->SetSelectedStatus(weapon_selector.slot_5);
}

bool WeaponComplex::IsAnyWeaponSelected() const
{
	return weapon_selector.isAnySelected();
}

void WeaponComplex::SetTarget(BaseGameEntity* _target)
{                          
        float dist = distBetweenPoints(owner_vehicle->GetPoints().getCenter(), _target->GetPoints().getCenter());
        
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
        	if ( slot_weapon_equiped_vec[i]->GetTurrel()->GetSelectedStatus() == true )
        	{
           		if ( slot_weapon_equiped_vec[i]->GetTurrel()->GetTarget() == NULL )
           		{
         			slot_weapon_equiped_vec[i]->GetTurrel()->SetTarget(_target);
                                slot_weapon_equiped_vec[i]->GetTurrel()->CheckTarget();                                        
                        }
                } 
        }               

}

void WeaponComplex::Fire(int timer, bool show_effect)
{
     	if (timer < TURN_TIME - fire_delay)
     	{
        	for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{	
                        slot_weapon_reloaded_vec[i]->GetTurrel()->CheckTarget();
                        if (slot_weapon_reloaded_vec[i]->GetTurrel()->GetTarget())
           		{
               			if ( slot_weapon_reloaded_vec[i]->GetTurrel()->FireEvent(show_effect) == true )
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

void WeaponComplex::ValidateAllReloadedWeaponsTarget()
{
	// in STATIC after weapons reloaded
        for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        {	
        	slot_weapon_reloaded_vec[i]->GetTurrel()->CheckTarget();
	}
}



void WeaponComplex::ResetDeselectedWeaponTargets()
{
        for (unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
        {
            	if (slot_weapon_equiped_vec[i]->GetTurrel()->GetSelectedStatus() == false)
            	{
                	slot_weapon_equiped_vec[i]->GetTurrel()->ResetTarget();
                }
        }
}


bool WeaponComplex::UpdateFireAbility()
{
     	slot_weapon_equiped_vec.clear();

     	//total_damage = 0;
     	//avr_damage =
     	//avr_radius =  
     	
     	//int sum_fire_radius = 0;
     	
     	for (unsigned int i = 0; i < slot_weapon_vec.size(); i++)
     	{ 
        	if (slot_weapon_vec[i]->GetEquipedStatus() == true)
        	{
           		if (slot_weapon_vec[i]->GetItem()->GetCondition() > 0)
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

void WeaponComplex::RenderTurrels() const
{
    	for(unsigned int i = 0; i < slot_weapon_equiped_vec.size(); i++)
    	{
        	slot_weapon_equiped_vec[i]->GetTurrel()->Render(owner_vehicle->GetPoints().getAngleDegree());        
    	} 
}

void WeaponComplex::RenderWeaponsRange()
{
	glPushMatrix();
		glTranslatef(owner_vehicle->GetPoints().getCenter().x, owner_vehicle->GetPoints().getCenter().y, 0.0f);
		for (unsigned int i = 0; i < slot_weapon_reloaded_vec.size(); i++)
        	{
         		if (slot_weapon_reloaded_vec[i]->GetTurrel()->GetSelectedStatus() == true)
                	{
                		slot_weapon_reloaded_vec[i]->UpdateRange(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_red);
             			slot_weapon_reloaded_vec[i]->DrawRange();
             		}

        	}
	glPopMatrix();
}

void WeaponComplex::RenderWeaponIcons() const
{
        enable_BLEND();
        
        int offset = 0;
        for (unsigned int i = 0; i < slot_weapon_vec.size(); i++)
        {
                Turrel* _turrel = slot_weapon_vec[i]->GetTurrel();
                if (_turrel->GetTarget() != NULL )
                {       
                        Rect _rect(_turrel->GetTarget()->GetPoints().getpCenter()->x - 40/2 + 23*offset, _turrel->GetTarget()->GetPoints().getpCenter()->y + 40/2, 20, 20);
                        drawTexturedRect(slot_weapon_vec[i]->GetItem()->GetTextureOb(), _rect, -2.0);
                        offset++;
                }        
        }
        
        disable_BLEND();
}
