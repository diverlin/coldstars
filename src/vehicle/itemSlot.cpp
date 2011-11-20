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

#include "itemSlot.hpp"


ItemSlot :: ItemSlot()
{}


ItemSlot :: ItemSlot(int _subtype_id, Ship* _owner_ship, TextureOb* _texOb, int _pos_x, int _pos_y)
{
/* 
        The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
        Depending on slot subtype there is the rule what items can be used with slot (for example 
        Lazer weapon item cannot be inserted to drive slot and so on).
*/

        type_id    = SLOT_ID;
	subtype_id = _subtype_id;
        
        owner_ship  = _owner_ship; 

        texOb = _texOb;
     
        rect = Rect(_pos_x, _pos_y, texOb->w, texOb->h);         // create rect with size of the texture

        item_type_id    = NONE_ID;
        item_subtype_id = NONE_ID;
     
        is_EQUIPED       = false;
        is_FLASHING      = false;
        is_CURSORED      = false;      
        

        turrel              = NULL;
                
        rocket_equipment    = NULL;
        lazer_equipment     = NULL;
	radar_equipment     = NULL;
	drive_equipment     = NULL;
	bak_equipment       = NULL;
	energizer_equipment = NULL;
	protector_equipment = NULL;
	droid_equipment     = NULL;
	freezer_equipment   = NULL;
	scaner_equipment    = NULL;
	grapple_equipment   = NULL;
                
	rocket_module    = NULL;
	lazer_module     = NULL;
	radar_module     = NULL;
	drive_module     = NULL;
	bak_module       = NULL;
	energizer_module = NULL;
        protector_module = NULL;
	droid_module     = NULL;
	freezer_module   = NULL;
	scaner_module    = NULL;
	grapple_module   = NULL;
		
	goods_pack = NULL;
}

ItemSlot :: ~ItemSlot()
{
	switch (item_subtype_id)
	{
		case ROCKET_EQUIPMENT_ID:    { delete rocket_equipment; break; }
 	   	case LAZER_EQUIPMENT_ID:     { delete lazer_equipment;  break; }
           	case RADAR_EQUIPMENT_ID:     { delete radar_equipment;  break; }
        	case DRIVE_EQUIPMENT_ID:     { delete drive_equipment;  break; }
        	case BAK_EQUIPMENT_ID:       { delete bak_equipment;    break; }
        	case ENERGIZER_EQUIPMENT_ID: { delete energizer_equipment; break; }
        	case PROTECTOR_EQUIPMENT_ID: { delete protector_equipment; break; }
    	       	case DROID_EQUIPMENT_ID:     { delete droid_equipment;     break; }
        	case FREEZER_EQUIPMENT_ID:   { delete freezer_equipment;   break; }
    	        case SCANER_EQUIPMENT_ID:    { delete scaner_equipment;    break; }
    	       	case GRAPPLE_EQUIPMENT_ID:   { delete grapple_equipment;   break; }
    	       	
		case ROCKET_MODULE_ID:       { delete rocket_module;       break; }	 
        	case LAZER_MODULE_ID:        { delete lazer_module;        break; }	 
    	      	case RADAR_MODULE_ID:        { delete radar_module;        break; }	 
    	       	case DRIVE_MODULE_ID:        { delete drive_module;        break; }	 
    		case BAK_MODULE_ID:          { delete bak_module;          break; }
    	      	case ENERGIZER_MODULE_ID:    { delete energizer_module;    break; }
       		case PROTECTOR_MODULE_ID:    { delete protector_module;    break; }
        	case DROID_MODULE_ID:        { delete droid_module;        break; }
        	case FREEZER_MODULE_ID:      { delete freezer_module;      break; }	
    		case SCANER_MODULE_ID:       { delete scaner_module;       break; }
   		case GRAPPLE_MODULE_ID:      { delete grapple_module;      break; }
    	}
    	
    	if (item_type_id == GOODS_ID)
    	{
		delete goods_pack;
	}
}

void ItemSlot :: setShipOwner(Ship* _ship_owner) {  owner_ship = _ship_owner; }
                
int ItemSlot :: getTypeId()          const { return type_id; }
int ItemSlot :: getSubTypeId()       const { return subtype_id; }
int ItemSlot :: getItemTypeId()    const { return item_type_id; }
int ItemSlot :: getItemSubTypeId() const { return item_subtype_id; }

Turrel* ItemSlot :: getTurrel() const { return turrel; }
void ItemSlot :: bindTurrel( Turrel* _turrel) {turrel = _turrel; }
                                
bool ItemSlot :: getEquipedStatus() const  { return is_EQUIPED; }
bool ItemSlot :: getCursoredStatus()            const { return is_CURSORED; }
void ItemSlot :: setCursoredStatus(bool new_status) { is_CURSORED = new_status; }
bool ItemSlot :: getFlashingStatus() const { return is_FLASHING; }
void ItemSlot :: setFlashingStatus(bool new_status) { is_FLASHING = new_status; }
                
Rect& ItemSlot :: getRect() { return rect; }

Ship* ItemSlot :: getOwnerShip() { return owner_ship; }
                                
RocketEquipment*    ItemSlot :: getRocketEquipment()    const { return rocket_equipment; }
LazerEquipment*     ItemSlot :: getLazerEquipment()     const { return lazer_equipment; }
RadarEquipment*     ItemSlot :: getRadarEquipment()     const { return radar_equipment; }
DriveEquipment*     ItemSlot :: getDriveEquipment()     const { return drive_equipment; }
BakEquipment*       ItemSlot :: getBakEquipment()       const { return bak_equipment; }
EnergizerEquipment* ItemSlot :: getEnergizerEquipment() const { return energizer_equipment; }
ProtectorEquipment* ItemSlot :: getProtectorEquipment() const { return protector_equipment; }
DroidEquipment*     ItemSlot :: getDroidEquipment()     const { return droid_equipment; }
FreezerEquipment*   ItemSlot :: getFreezerEquipment()   const { return freezer_equipment; }
ScanerEquipment*    ItemSlot :: getScanerEquipment()    const { return scaner_equipment; }
GrappleEquipment*   ItemSlot :: getGrappleEquipment()   const { return grapple_equipment; }

RocketModule*       ItemSlot :: getRocketModule()       const { return rocket_module; }
LazerModule*        ItemSlot :: getLazerModule()        const { return lazer_module; }
RadarModule*        ItemSlot :: getRadarModule()        const { return radar_module; }
DriveModule*        ItemSlot :: getDriveModule()        const { return drive_module; }
BakModule*          ItemSlot :: getBakModule()          const { return bak_module; }
EnergizerModule*    ItemSlot :: getEnergizerModule()    const { return energizer_module; }
ProtectorModule*    ItemSlot :: getProtectorModule()    const { return protector_module; }
DroidModule*        ItemSlot :: getDroidModule()        const { return droid_module; }
FreezerModule*      ItemSlot :: getFreezerModule()      const { return freezer_module; }
ScanerModule*       ItemSlot :: getScanerModule()       const { return scaner_module; }
GrappleModule*      ItemSlot :: getGrappleModule()      const { return grapple_module; }



template<typename ITEM_TYPE>
bool ItemSlot :: insertItem(ITEM_TYPE* item)
{
	if (item != NULL)
	{
		if (subtype_id == CARGO_SLOT_ID) 
		{
			insert(item);
    
			item_type_id    = item->getTypeId();
			item_subtype_id = item->getSubTypeId(); 
	
			is_EQUIPED = true; 
		
			return true;
   		}
   	
		if (subtype_id == item->getFunctionalSlotSubTypeId())
		{
			insert(item);
    
			item_type_id    = item->getTypeId();
			item_subtype_id = item->getSubTypeId(); 
	
			is_EQUIPED = true; 
		
			item->bindSlot(this);
			item->updateOwnerPropetries();
		
			return true;
		}
	}

	return false;	
}


	
void ItemSlot :: insert(RocketEquipment* item) 		{ rocket_equipment = item; }     
void ItemSlot :: insert(LazerEquipment* item)  		{ lazer_equipment = item; }      
void ItemSlot :: insert(RadarEquipment* item)  		{ radar_equipment = item; }      
void ItemSlot :: insert(DriveEquipment* item)  		{ drive_equipment = item; }      
void ItemSlot :: insert(BakEquipment* item)    		{ bak_equipment = item; }        
void ItemSlot :: insert(EnergizerEquipment* item) 	{ energizer_equipment = item; }  
void ItemSlot :: insert(ProtectorEquipment* item) 	{ protector_equipment = item; } 
void ItemSlot :: insert(DroidEquipment* item)     	{ droid_equipment = item; }      
void ItemSlot :: insert(FreezerEquipment* item) 	{ freezer_equipment = item; }    
void ItemSlot :: insert(ScanerEquipment* item)		{ scaner_equipment = item; }     
void ItemSlot :: insert(GrappleEquipment* item)		{ grapple_equipment = item; }    // owner_ship->updateGrabAbility(); item->reshapeTargetObSlot(this);  GRAPPLE_ID


		
void ItemSlot :: insert(RocketModule* item) 	{ rocket_module = item; }
void ItemSlot :: insert(LazerModule* item)  	{ lazer_module = item; }
void ItemSlot :: insert(RadarModule* item)  	{ radar_module = item; }
void ItemSlot :: insert(DriveModule* item) 	{ drive_module = item; }
void ItemSlot :: insert(BakModule* item)	{ bak_module = item; }
void ItemSlot :: insert(EnergizerModule* item) 	{ energizer_module = item; }
void ItemSlot :: insert(ProtectorModule* item) 	{ protector_module = item; }
void ItemSlot :: insert(DroidModule* item)     	{ droid_module = item; }
void ItemSlot :: insert(FreezerModule* item)   	{ freezer_module = item; }
void ItemSlot :: insert(ScanerModule* item)    	{ scaner_module = item; }
void ItemSlot :: insert(GrappleModule* item)  	{ grapple_module = item; }


bool ItemSlot :: insertGoods(GoodsPack* item)
{
     	if (subtype_id == CARGO_SLOT_ID)
	{
		goods_pack = item;
        
		item_type_id    = item->getTypeId();
		item_subtype_id = item->getSubTypeId();
		
		is_EQUIPED = true; 
		return true;
	}
	else
		return false;
}
		
		

void ItemSlot :: removeItem()
{
	switch(item_subtype_id)
	{
		case ROCKET_EQUIPMENT_ID:
		{
    			rocket_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateFireAbility();
    				
    			break;
    		}
    	
    		case LAZER_EQUIPMENT_ID:
		{
    			lazer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateFireAbility();
    				
    			break;
    		}
    
        	case RADAR_EQUIPMENT_ID:
		{
    			radar_equipment = NULL;
    			resetFlags();
    			    			
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateRadarAbility();
    				
    			break;
      		}
    						
        	case DRIVE_EQUIPMENT_ID:
		{
    			drive_equipment = NULL;
    			resetFlags();
    			
    			if (subtype_id != CARGO_SLOT_ID)
    			{ 
    				owner_ship->updateDriveAbility();
    				owner_ship->updateJumpAbility();
    			}
    			
    			break;	
    		}

        	case BAK_EQUIPMENT_ID:
		{
    			bak_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    			{ 
    				owner_ship->updateDriveAbility();
    				owner_ship->updateJumpAbility();
    			}
    			
    			break;
    		}

        	case ENERGIZER_EQUIPMENT_ID:
		{
    			energizer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateEnergyAbility();
    				
    			break;
    		}

        	case PROTECTOR_EQUIPMENT_ID:
		{
    			protector_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateProtectionAbility();
    				
    			break;
    		}
    	
        	case DROID_EQUIPMENT_ID:
		{
    			droid_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateRepairAbility();
    				
    			break;
    		}

        	case FREEZER_EQUIPMENT_ID:
		{
    			freezer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateFreezeAbility();
    				
    			break;
    		}
    	

 	        case SCANER_EQUIPMENT_ID:
		{
    			scaner_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateScanAbility();
    				
    			break;
    		}
    	
        	case GRAPPLE_EQUIPMENT_ID:
		{
    			grapple_equipment = NULL;
    			resetFlags();
    			if (subtype_id != CARGO_SLOT_ID)
    				owner_ship->updateGrabAbility();
    				
    			break;
    		}


        	case ROCKET_MODULE_ID:
		{
    			rocket_module = NULL;
    			resetFlags();
    			
    			break;
    		}	 

        	case LAZER_MODULE_ID:
		{
    			lazer_module = NULL;
    			resetFlags();
    			
    			break;
    		}	 
    	
        	case RADAR_MODULE_ID:
		{
    			radar_module = NULL;
    			resetFlags();
    			
    			break;
    		}	 
    	
        	case DRIVE_MODULE_ID:
		{
    			drive_module = NULL;
    			resetFlags();
    			
    			break;
    		}	 
    		
        	case BAK_MODULE_ID:
		{
    			bak_module = NULL;
    			resetFlags();
    			
    			break;
    		}
    	
        	case ENERGIZER_MODULE_ID:
		{
    			energizer_module = NULL;
    			resetFlags();
    			
    			break;
    		}

       		case PROTECTOR_MODULE_ID:
		{
    			protector_module = NULL;
    			resetFlags();
    			
    			break;
    		}

        	case DROID_MODULE_ID:
		{
    			droid_module = NULL;
    			resetFlags();
    			
    			break;
    		}

        	case FREEZER_MODULE_ID:
		{
    			freezer_module = NULL;
    			resetFlags();
    			
    			break;
    		}	
    	
    		case SCANER_MODULE_ID:
		{
    			scaner_module = NULL;
    			resetFlags();
    			
    			break;
    		}

    		case GRAPPLE_MODULE_ID:
		{
    			grapple_module = NULL;
    			resetFlags();
    			
    			break;
    		}
    	}
    	
    	if (item_type_id == GOODS_ID)
	{
		goods_pack = NULL;
		resetFlags();
	}
}


void ItemSlot :: resetFlags()
{
	is_EQUIPED = false; 
	item_type_id    = NONE_ID;
	item_subtype_id = NONE_ID;
}


int ItemSlot :: getItemMass() const
{  
	switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:     return lazer_equipment->getMass();
		case ROCKET_EQUIPMENT_ID:    return rocket_equipment->getMass();
		case ENERGIZER_EQUIPMENT_ID: return energizer_equipment->getMass();
		case FREEZER_EQUIPMENT_ID:   return freezer_equipment->getMass();
		case GRAPPLE_EQUIPMENT_ID:   return grapple_equipment->getMass();
		case RADAR_EQUIPMENT_ID:     return radar_equipment->getMass();
		case DRIVE_EQUIPMENT_ID:     return drive_equipment->getMass();
		case PROTECTOR_EQUIPMENT_ID: return protector_equipment->getMass();
		case BAK_EQUIPMENT_ID:       return bak_equipment->getMass();
		case DROID_EQUIPMENT_ID:     return droid_equipment->getMass();
		case SCANER_EQUIPMENT_ID:    return scaner_equipment->getMass();
	}
	
	if (item_type_id == MODULE_ID)
	{
		return 1;
	}
	
        return 0;
}





int ItemSlot :: getItemPrice() const
{  
	switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:     return lazer_equipment->getPrice();
		case ROCKET_EQUIPMENT_ID:    return rocket_equipment->getPrice();
		case ENERGIZER_EQUIPMENT_ID: return energizer_equipment->getPrice();
		case FREEZER_EQUIPMENT_ID:   return freezer_equipment->getPrice();
		case GRAPPLE_EQUIPMENT_ID:   return grapple_equipment->getPrice();
		case RADAR_EQUIPMENT_ID:     return radar_equipment->getPrice();
		case DRIVE_EQUIPMENT_ID:     return drive_equipment->getPrice();
		case PROTECTOR_EQUIPMENT_ID: return protector_equipment->getPrice();
		case BAK_EQUIPMENT_ID:       return bak_equipment->getPrice();
		case DROID_EQUIPMENT_ID:     return droid_equipment->getPrice();
		case SCANER_EQUIPMENT_ID:    return scaner_equipment->getPrice();
	}
        
        return 0;
}


void ItemSlot :: renderFrame(GLuint flash_tex)
{
	drawTexturedRect(texOb->texture, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
	renderEquipedItem();
        
}


TextureOb* ItemSlot :: getItemTexOb() const
{
        switch(item_subtype_id)
	{
		//items 
		case LAZER_EQUIPMENT_ID:  return lazer_equipment->getTexOb();
		case ROCKET_EQUIPMENT_ID: return rocket_equipment->getTexOb();
        }
        
        return NULL;
}
                
                
int ItemSlot :: getItemRadius() const
{ 
        switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:   return lazer_equipment->getRadius();
		case ROCKET_EQUIPMENT_ID:  return rocket_equipment->getRadius();
		
		case GRAPPLE_EQUIPMENT_ID: return grapple_equipment->getRadius();
        }
        
        return 0;
}


int ItemSlot :: getItemDamage() const
{
        switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:  return lazer_equipment->getDamage();
		case ROCKET_EQUIPMENT_ID: return rocket_equipment->getDamage();
        }
        
        return 0;
}



int ItemSlot :: getItemCondition() const
{  
        return 1000;
}

void ItemSlot :: renderEquipedItem()
{
	switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:     { lazer_equipment->render(rect);     break; }
		case ROCKET_EQUIPMENT_ID:    { rocket_equipment->render(rect);    break; }
		case ENERGIZER_EQUIPMENT_ID: { energizer_equipment->render(rect); break; }
		case FREEZER_EQUIPMENT_ID:   { freezer_equipment->render(rect);   break; }
		case GRAPPLE_EQUIPMENT_ID:   { grapple_equipment->render(rect);   break; }
		case RADAR_EQUIPMENT_ID:     { radar_equipment->render(rect);     break; }
		case DRIVE_EQUIPMENT_ID:     { drive_equipment->render(rect);     break; }
		case PROTECTOR_EQUIPMENT_ID: { protector_equipment->render(rect); break; }
		case BAK_EQUIPMENT_ID:       { bak_equipment->render(rect);       break; }
		case DROID_EQUIPMENT_ID:     { droid_equipment->render(rect);     break; }
		case SCANER_EQUIPMENT_ID:    { scaner_equipment->render(rect);    break; }    		
    		
    		case ROCKET_MODULE_ID:       { rocket_module->render(rect);       break; }	 
        	case LAZER_MODULE_ID:        { lazer_module->render(rect);        break; }	 
    	      	case RADAR_MODULE_ID:        { radar_module->render(rect);        break; }	 
    	       	case DRIVE_MODULE_ID:        { drive_module->render(rect);        break; }	 
    		case BAK_MODULE_ID:          { bak_module->render(rect);          break; }
    	      	case ENERGIZER_MODULE_ID:    { energizer_module->render(rect);    break; }
       		case PROTECTOR_MODULE_ID:    { protector_module->render(rect);    break; }
        	case DROID_MODULE_ID:        { droid_module->render(rect);        break; }
        	case FREEZER_MODULE_ID:      { freezer_module->render(rect);      break; }	
    		case SCANER_MODULE_ID:       { scaner_module->render(rect);       break; }
   		case GRAPPLE_MODULE_ID:      { grapple_module->render(rect);      break; }
   	}
   		
	if (item_type_id == GOODS_ID)
	{
		drawTexturedRect(goods_pack->getTexOb()->texture, rect, -1.0);
	}
}





void ItemSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void ItemSlot :: renderItemInfo(float offset_x, float offset_y)
{
	switch(item_subtype_id)
	{
		case LAZER_EQUIPMENT_ID:     { lazer_equipment->renderInfo(rect, offset_x, offset_y);     break; }
		case ROCKET_EQUIPMENT_ID:    { rocket_equipment->renderInfo(rect, offset_x, offset_y);    break; }
		case ENERGIZER_EQUIPMENT_ID: { energizer_equipment->renderInfo(rect, offset_x, offset_y); break; }
		case FREEZER_EQUIPMENT_ID:   { freezer_equipment->renderInfo(rect, offset_x, offset_y);   break; }
		case GRAPPLE_EQUIPMENT_ID:   { grapple_equipment->renderInfo(rect, offset_x, offset_y);   break; }
		case RADAR_EQUIPMENT_ID:     { radar_equipment->renderInfo(rect, offset_x, offset_y);     break; }
		case DRIVE_EQUIPMENT_ID:     { drive_equipment->renderInfo(rect, offset_x, offset_y);     break; }
		case PROTECTOR_EQUIPMENT_ID: { protector_equipment->renderInfo(rect, offset_x, offset_y); break; }
		case BAK_EQUIPMENT_ID:       { bak_equipment->renderInfo(rect, offset_x, offset_y);       break; }
		case DROID_EQUIPMENT_ID:     { droid_equipment->renderInfo(rect, offset_x, offset_y);     break; }
		case SCANER_EQUIPMENT_ID:    { scaner_equipment->renderInfo(rect, offset_x, offset_y);    break; }    		
    		
    		case ROCKET_MODULE_ID:       { rocket_module->renderInfo(rect);       break; }	 
        	case LAZER_MODULE_ID:        { lazer_module->renderInfo(rect);        break; }	 
    	      	case RADAR_MODULE_ID:        { radar_module->renderInfo(rect);        break; }	 
    	       	case DRIVE_MODULE_ID:        { drive_module->renderInfo(rect);        break; }	 
    		case BAK_MODULE_ID:          { bak_module->renderInfo(rect);          break; }
    	      	case ENERGIZER_MODULE_ID:    { energizer_module->renderInfo(rect);    break; }
       		case PROTECTOR_MODULE_ID:    { protector_module->renderInfo(rect);    break; }
        	case DROID_MODULE_ID:        { droid_module->renderInfo(rect);        break; }
        	case FREEZER_MODULE_ID:      { freezer_module->renderInfo(rect);      break; }	
    		case SCANER_MODULE_ID:       { scaner_module->renderInfo(rect);       break; }
   		case GRAPPLE_MODULE_ID:      { grapple_module->renderInfo(rect);      break; }
   	}

	
	if (item_type_id == GOODS_ID)
     	{
		goods_pack->updateInfo();
		goods_pack->renderInfo(rect, offset_x, offset_y);
	}
}



bool ItemSlot :: interaction(int _x, int _y)
{        
        float dist = distBetweenPoints(rect.getCenter().x, rect.getCenter().y, _x, _y);
        if (dist < rect.getWidth()/2)
                return true;
        else
                return false;    
}


void ItemSlot :: dropItemToSpace()
{
	Container* _container = createContainer(owner_ship->getPoints()->getCenter());
	_container->getItemSlot()->SwapItemWith(this);	
	
	// update mass, and abilities if needed !!!!!!!!!!!!!!!!!!!

	removeItem();
	owner_ship->getStarSystem()->add(_container);	

	//printf("container was created in ss_id = %i, pos = %f, %f\n", _starsystem->getId(), _container->getPoints()->getCenter().x, _container->getPoints()->getCenter().y );
}




         

bool ItemSlot :: SwapItemWith(ItemSlot* _slot)
{
       	if ( (is_EQUIPED == false) and (_slot->getEquipedStatus() == true) )
       	{                	                	
		switch(_slot->getItemSubTypeId())
		{
           		case LAZER_EQUIPMENT_ID:     { if (insertItem(_slot->getLazerEquipment())     == true) { _slot->removeItem(); return true; } }                       				
                	case ROCKET_EQUIPMENT_ID:    { if (insertItem(_slot->getRocketEquipment())    == true) { _slot->removeItem(); return true; } }
                       	case RADAR_EQUIPMENT_ID:     { if (insertItem(_slot->getRadarEquipment())     == true) { _slot->removeItem(); return true; } }                       				
                	case DRIVE_EQUIPMENT_ID:     { if (insertItem(_slot->getDriveEquipment())     == true) { _slot->removeItem(); return true; } }
                        case BAK_EQUIPMENT_ID:       { if (insertItem(_slot->getBakEquipment())       == true) { _slot->removeItem(); return true; } }                  						
                       	case ENERGIZER_EQUIPMENT_ID: { if (insertItem(_slot->getEnergizerEquipment()) == true) { _slot->removeItem(); return true; } }                     				
                	case PROTECTOR_EQUIPMENT_ID: { if (insertItem(_slot->getProtectorEquipment()) == true) { _slot->removeItem(); return true; } }
                        case DROID_EQUIPMENT_ID:     { if (insertItem(_slot->getDroidEquipment())     == true) { _slot->removeItem(); return true; } }
	                case FREEZER_EQUIPMENT_ID:   { if (insertItem(_slot->getFreezerEquipment())   == true) { _slot->removeItem(); return true; } }
	                case SCANER_EQUIPMENT_ID:    { if (insertItem(_slot->getScanerEquipment())    == true) { _slot->removeItem(); return true; } }
			case GRAPPLE_EQUIPMENT_ID:   { if (insertItem(_slot->getGrappleEquipment())   == true) { _slot->removeItem(); return true; } }
			
			case ROCKET_MODULE_ID:       { if (insertItem(_slot->getRocketModule())    == true) { _slot->removeItem(); return true; } }	 
        		case LAZER_MODULE_ID:        { if (insertItem(_slot->getLazerModule())     == true) { _slot->removeItem(); return true; } }	 
    	      		case RADAR_MODULE_ID:        { if (insertItem(_slot->getRadarModule())     == true) { _slot->removeItem(); return true; } }	 
    	       		case DRIVE_MODULE_ID:        { if (insertItem(_slot->getDriveModule())     == true) { _slot->removeItem(); return true; } }	 
    			case BAK_MODULE_ID:          { if (insertItem(_slot->getBakModule())       == true) { _slot->removeItem(); return true; } }
    	      		case ENERGIZER_MODULE_ID:    { if (insertItem(_slot->getEnergizerModule()) == true) { _slot->removeItem(); return true; } }
       			case PROTECTOR_MODULE_ID:    { if (insertItem(_slot->getProtectorModule()) == true) { _slot->removeItem(); return true; } }
        		case DROID_MODULE_ID:        { if (insertItem(_slot->getDroidModule())     == true) { _slot->removeItem(); return true; } }
        		case FREEZER_MODULE_ID:      { if (insertItem(_slot->getFreezerModule())   == true) { _slot->removeItem(); return true; } }	
    			case SCANER_MODULE_ID:       { if (insertItem(_slot->getScanerModule())    == true) { _slot->removeItem(); return true; } }
   			case GRAPPLE_MODULE_ID:      { if (insertItem(_slot->getGrappleModule())   == true) { _slot->removeItem(); return true; } }
		
		}	
	}
	
	
	if ( (is_EQUIPED == true) and (_slot->getEquipedStatus() == false) )
       	{                	                	
		switch(item_subtype_id)
		{
           		case LAZER_EQUIPMENT_ID:     { if (_slot->insertItem(getLazerEquipment())     == true)  { removeItem(); return true; } }                       				
                	case ROCKET_EQUIPMENT_ID:    { if (_slot->insertItem(getRocketEquipment())    == true)  { removeItem(); return true; } }
                       	case RADAR_EQUIPMENT_ID:     { if (_slot->insertItem(getRadarEquipment())     == true)  { removeItem(); return true; } }                       				
                	case DRIVE_EQUIPMENT_ID:     { if (_slot->insertItem(getDriveEquipment())     == true)  { removeItem(); return true; } }
                        case BAK_EQUIPMENT_ID:       { if (_slot->insertItem(getBakEquipment())       == true)  { removeItem(); return true; } }                  						
                       	case ENERGIZER_EQUIPMENT_ID: { if (_slot->insertItem(getEnergizerEquipment()) == true)  { removeItem(); return true; } }                     				
                	case PROTECTOR_EQUIPMENT_ID: { if (_slot->insertItem(getProtectorEquipment()) == true)  { removeItem(); return true; } }
                        case DROID_EQUIPMENT_ID:     { if (_slot->insertItem(getDroidEquipment())     == true)  { removeItem(); return true; } }
	                case FREEZER_EQUIPMENT_ID:   { if (_slot->insertItem(getFreezerEquipment())   == true)  { removeItem(); return true; } }
	                case SCANER_EQUIPMENT_ID:    { if (_slot->insertItem(getScanerEquipment())    == true)  { removeItem(); return true; } }
			case GRAPPLE_EQUIPMENT_ID:   { if (_slot->insertItem(getGrappleEquipment())   == true)  { removeItem(); return true; } }
		
			case ROCKET_MODULE_ID:       { if (_slot->insertItem(getRocketModule())    == true)  { removeItem(); return true; } }	 
        		case LAZER_MODULE_ID:        { if (_slot->insertItem(getLazerModule())     == true)  { removeItem(); return true; } }	 
    	      		case RADAR_MODULE_ID:        { if (_slot->insertItem(getRadarModule())     == true)  { removeItem(); return true; } } 
    	       		case DRIVE_MODULE_ID:        { if (_slot->insertItem(getDriveModule())     == true)  { removeItem(); return true; } } 
    			case BAK_MODULE_ID:          { if (_slot->insertItem(getBakModule())       == true)  { removeItem(); return true; } }
    	      		case ENERGIZER_MODULE_ID:    { if (_slot->insertItem(getEnergizerModule()) == true)  { removeItem(); return true; } }
       			case PROTECTOR_MODULE_ID:    { if (_slot->insertItem(getProtectorModule()) == true)  { removeItem(); return true; } }
        		case DROID_MODULE_ID:        { if (_slot->insertItem(getDroidModule())     == true)  { removeItem(); return true; } }
        		case FREEZER_MODULE_ID:      { if (_slot->insertItem(getFreezerModule())   == true)  { removeItem(); return true; } }	
    			case SCANER_MODULE_ID:       { if (_slot->insertItem(getScanerModule())    == true)  { removeItem(); return true; } }
   			case GRAPPLE_MODULE_ID:      { if (_slot->insertItem(getGrappleModule())   == true)  { removeItem(); return true; } }	
		}
	}

	if ( (is_EQUIPED == true) and (_slot->getEquipedStatus() == true) )
       	{          
       		if ( (item_type_id == MODULE_ID) and (_slot->getItemTypeId() == EQUIPMENT_ID) )
       		{
       			switch(item_subtype_id)
       			{
       				case ROCKET_MODULE_ID:       { if (_slot->getRocketEquipment()->insertModule(rocket_module)       == true)  { removeItem(); return true; } }  
        			case LAZER_MODULE_ID:        { if (_slot->getLazerEquipment()->insertModule(lazer_module)         == true)  { removeItem(); return true; } }   
    	      			case RADAR_MODULE_ID:        { if (_slot->getRadarEquipment()->insertModule(radar_module)         == true)  { removeItem(); return true; } }  
    	       			case DRIVE_MODULE_ID:        { if (_slot->getDriveEquipment()->insertModule(drive_module)         == true)  { removeItem(); return true; } }  
    				case BAK_MODULE_ID:          { if (_slot->getBakEquipment()->insertModule(bak_module)             == true)  { removeItem(); return true; } }  
    	      			case ENERGIZER_MODULE_ID:    { if (_slot->getEnergizerEquipment()->insertModule(energizer_module) == true)  { removeItem(); return true; } }  
       				case PROTECTOR_MODULE_ID:    { if (_slot->getProtectorEquipment()->insertModule(protector_module) == true)  { removeItem(); return true; } }  
        			case DROID_MODULE_ID:        { if (_slot->getDroidEquipment()->insertModule(droid_module)         == true)  { removeItem(); return true; } }  
        			case FREEZER_MODULE_ID:      { if (_slot->getFreezerEquipment()->insertModule(freezer_module)     == true)  { removeItem(); return true; } }  
    				case SCANER_MODULE_ID:       { if (_slot->getScanerEquipment()->insertModule(scaner_module)       == true)  { removeItem(); return true; } }  
   				case GRAPPLE_MODULE_ID:      { if (_slot->getGrappleEquipment()->insertModule(grapple_module)     == true)  { removeItem(); return true; } }  
      			}
       		}
       		
       		if ( (item_type_id == EQUIPMENT_ID) and (_slot->getItemTypeId() == MODULE_ID) )
       		{
       			switch(_slot->getItemSubTypeId())
       			{
       				case ROCKET_MODULE_ID:       { if (rocket_equipment->insertModule(_slot->getRocketModule())       == true)  { _slot->removeItem(); return true; } }  
        			case LAZER_MODULE_ID:        { if (lazer_equipment->insertModule(_slot->getLazerModule())         == true)  { _slot->removeItem(); return true; } }   
    	      			case RADAR_MODULE_ID:        { if (radar_equipment->insertModule(_slot->getRadarModule())         == true)  { _slot->removeItem(); return true; } }  
    	       			case DRIVE_MODULE_ID:        { if (drive_equipment->insertModule(_slot->getDriveModule())         == true)  { _slot->removeItem(); return true; } }  
    				case BAK_MODULE_ID:          { if (bak_equipment->insertModule(_slot->getBakModule())             == true)  { _slot->removeItem(); return true; } }  
    	      			case ENERGIZER_MODULE_ID:    { if (energizer_equipment->insertModule(_slot->getEnergizerModule()) == true)  { _slot->removeItem(); return true; } }  
       				case PROTECTOR_MODULE_ID:    { if (protector_equipment->insertModule(_slot->getProtectorModule()) == true)  { _slot->removeItem(); return true; } }  
        			case DROID_MODULE_ID:        { if (droid_equipment->insertModule(_slot->getDroidModule())         == true)  { _slot->removeItem(); return true; } }  
        			case FREEZER_MODULE_ID:      { if (freezer_equipment->insertModule(_slot->getFreezerModule())     == true)  { _slot->removeItem(); return true; } }  
    				case SCANER_MODULE_ID:       { if (scaner_equipment->insertModule(_slot->getScanerModule())       == true)  { _slot->removeItem(); return true; } }  
   				case GRAPPLE_MODULE_ID:      { if (grapple_equipment->insertModule(_slot->getGrappleModule())     == true)  { _slot->removeItem(); return true; } }  
      			}
       		}
       		
       		if ( (item_type_id == EQUIPMENT_ID) and (_slot->getItemTypeId() == EQUIPMENT_ID) )
		{
			        
                    		//LazerEquipment* _buf = lazer_equipment;
				//removeItem();
                		//if (insertEquipment(_slot->getLazerEquipment()) == true)
                		//{
                			//_slot->removeItem();
                			//_slot->insertEquipment(_buf);                			
                		//}
                		//else
                		//{
                			//insertEquipment(_buf);
                		//}
                    		 
		}       
	}               
	
	// artifacts
	// bomb 
}
