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

ItemSlot :: ItemSlot(int _subtype_id, VehicleBase* _owner_vehicle, TextureOb* _texOb)
{
	/* 
        The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
        Depending on slot subtype there is the rule what items can be used with slot (for example 
        Lazer weapon item cannot be inserted to drive slot and so on).
	*/

        type_id    = SLOT_ID;
	subtype_id = _subtype_id;
        
        owner_vehicle  = _owner_vehicle; 

        texOb = _texOb;
     
        rect = Rect();         

        is_EQUIPED       = false;
        is_FLASHING      = false;

        turrel = NULL;                
        item   = NULL;
}

ItemSlot :: ~ItemSlot()
{
        delete item;
}

void ItemSlot :: setOwner(VehicleBase* owner_vehicle) {  this->owner_vehicle = owner_vehicle; }
void ItemSlot :: setFlashingStatus(bool new_status) { is_FLASHING = new_status; }
                
void ItemSlot :: setRect(int _pos_x, int _pos_y, int w, int h)
{
	rect.set(_pos_x, _pos_y, w, h);
}
                                
int ItemSlot :: getTypeId()          const { return type_id; }
int ItemSlot :: getSubTypeId()       const { return subtype_id; }
ItemBase* ItemSlot :: getItem()      const { return item; }

Turrel* ItemSlot :: getTurrel() const { return turrel; }
void ItemSlot :: bindTurrel( Turrel* turrel) { this->turrel = turrel; }
                                
bool ItemSlot :: getEquipedStatus() const  { return is_EQUIPED; }
bool ItemSlot :: getFlashingStatus() const { return is_FLASHING; }

                
Rect& ItemSlot :: getRect() { return rect; }

VehicleBase* ItemSlot :: getOwnerVehicle() const { return owner_vehicle; }
                                
RocketEquipment*    ItemSlot :: getRocketEquipment()    const { return (RocketEquipment*)item; }
LazerEquipment*     ItemSlot :: getLazerEquipment()     const { return (LazerEquipment*)item; }
RadarEquipment*     ItemSlot :: getRadarEquipment()     const { return (RadarEquipment*)item; }
DriveEquipment*     ItemSlot :: getDriveEquipment()     const { return (DriveEquipment*)item; }
BakEquipment*       ItemSlot :: getBakEquipment()       const { return (BakEquipment*)item; }
EnergizerEquipment* ItemSlot :: getEnergizerEquipment() const { return (EnergizerEquipment*)item; }
ProtectorEquipment* ItemSlot :: getProtectorEquipment() const { return (ProtectorEquipment*)item; }
DroidEquipment*     ItemSlot :: getDroidEquipment()     const { return (DroidEquipment*)item; }
FreezerEquipment*   ItemSlot :: getFreezerEquipment()   const { return (FreezerEquipment*)item; }
ScanerEquipment*    ItemSlot :: getScanerEquipment()    const { return (ScanerEquipment*)item; }
GrappleEquipment*   ItemSlot :: getGrappleEquipment()   const { return (GrappleEquipment*)item; }

RocketModule*       ItemSlot :: getRocketModule()       const { return (RocketModule*)item; }
LazerModule*        ItemSlot :: getLazerModule()        const { return (LazerModule*)item; }
RadarModule*        ItemSlot :: getRadarModule()        const { return (RadarModule*)item; }
DriveModule*        ItemSlot :: getDriveModule()        const { return (DriveModule*)item; }
BakModule*          ItemSlot :: getBakModule()          const { return (BakModule*)item; }
EnergizerModule*    ItemSlot :: getEnergizerModule()    const { return (EnergizerModule*)item; }
ProtectorModule*    ItemSlot :: getProtectorModule()    const { return (ProtectorModule*)item; }
DroidModule*        ItemSlot :: getDroidModule()        const { return (DroidModule*)item; }
FreezerModule*      ItemSlot :: getFreezerModule()      const { return (FreezerModule*)item; }
ScanerModule*       ItemSlot :: getScanerModule()       const { return (ScanerModule*)item; }
GrappleModule*      ItemSlot :: getGrappleModule()      const { return (GrappleModule*)item; }

Bomb* ItemSlot :: getBomb() const { return (Bomb*)item; }
//Artefact* ItemSlot :: getArtefact() const { return artefact; }
GoodsPack* ItemSlot :: getGoodsPack() const { return (GoodsPack*)item; }
//Vehicle* ItemSlot :: getVehicle()     const { return vehicle; }

bool ItemSlot :: insertItem(ItemBase* item)
{
	if (item != NULL)
	{
		if (subtype_id == CARGO_SLOT_ID) 
		{
                	this->item = item;
                	is_EQUIPED = true; 
                
			return true;
   		}
   	
		if (subtype_id == item->getFunctionalSlotSubTypeId())
		{
		        this->item = item;
                	is_EQUIPED = true; 
                
			item->bindSlot(this);
			item->updateOwnerAbilities();
		
			return true;
		}
	}

	return false;
}


bool ItemSlot :: extractContainer(Container* container)
{
	return this->SwapItemWith(container->getItemSlot());
}


void ItemSlot :: removeItem()
{
        ItemBase* tmp_item = item;
        
        item = NULL;
    	is_EQUIPED = false;  
        
    	if (subtype_id != CARGO_SLOT_ID) 
    	{ 
    		tmp_item->updateOwnerAbilities(); 
    	}                     
}


void ItemSlot :: render(GLuint flash_tex)
{
	drawTexturedRect(texOb, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
                
        renderEquipedItem();     
}

              
int ItemSlot :: getItemRadius() const
{       
        switch(item->getTypeId())
        {
                case EQUIPMENT_ID:
                {
                        switch (item->getSubTypeId())
                        {
                                case LAZER_EQUIPMENT_ID:   { return ((LazerEquipment*)item)->getRadius();  break; };
                                case ROCKET_EQUIPMENT_ID:  { return ((RocketEquipment*)item)->getRadius(); break; };
		
                                case GRAPPLE_EQUIPMENT_ID: { return ((GrappleEquipment*)item)->getRadius(); break; };
                                case RADAR_EQUIPMENT_ID:   { return ((RadarEquipment*)item)->getRadius();   break; };
                        }
                        
                        break;
                }
                
                case BOMB_ID:
                {
                        return ((Bomb*)item)->getRadius();   break; 
                }
        }
        
        return 0;
}


void ItemSlot :: renderEquipedItem()
{
        if (is_EQUIPED == true)
        {
                item->render(rect);
        }
}

void ItemSlot :: renderItemInfo(float offset_x, float offset_y)
{
        if (is_EQUIPED == true)
        {
                item->renderInfo(rect, offset_x, offset_y);
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
	Container* _container = getNewContainer();
	_container->getItemSlot()->SwapItemWith(this);
	
	// update mass

	owner_vehicle->getStarSystem()->addToSpace(_container, owner_vehicle->getPoints()->getCenter());	

	//printf("container was created in ss_id = %i, pos = %f, %f\n", _starsystem->getId(), _container->getPoints()->getCenter().x, _container->getPoints()->getCenter().y );
}




         

bool ItemSlot :: SwapItemWith(ItemSlot* _slot)
{
       	if ( (is_EQUIPED == false) and (_slot->getEquipedStatus() == true) )
       	{      
       		if (insertItem(_slot->getItem()) == true) 
       		{
       			_slot->removeItem(); 
       			
       			return true; 
       		}             
	}
	
	
	if ( (is_EQUIPED == true) and (_slot->getEquipedStatus() == false) )
       	{ 
		if (_slot->insertItem(getItem())     == true)
		{ 
			removeItem(); 
			
			return true; 			
		}                     				
	}

	if ( (is_EQUIPED == true) and (_slot->getEquipedStatus() == true) )
       	{          
       		if ( (item->getTypeId() == MODULE_ID) and (_slot->getItem()->getTypeId() == EQUIPMENT_ID) )
       		{
			if (((EquipmentBase*)_slot->getItem())->insertModule((ModuleBase*)item) == true)  
			{ 
				removeItem(); 
				
				return true;       		
        		}
       		}
       		
       		if ( (item->getTypeId() == EQUIPMENT_ID) and (_slot->getItem()->getTypeId() == MODULE_ID) )
       		{
			 if (((EquipmentBase*)item)->insertModule((ModuleBase*)_slot->getItem()) == true)  
			 { 
			 	_slot->removeItem(); 
			 	
			 	return true; 
			 }       		        		
       		}
	}               
	
	return false;
}

void ItemSlot :: updateRange(TextureOb* _texOb)
{
	float radius = this->getItemRadius();
	float da = 4.0f/RADIAN_TO_DEGREE_RATE;// - radius/1000.0f;
	
    	range_vec.clear();
      	for (float a = 0.0f; a <= 2*PI; a+=da)
      	{
      		range_vec.push_back( vec2f(radius * cos(a), radius * sin(a)) );
      	}
      	
	int step = 1;
	int size = 6;
        range_visual.fillData(_texOb->texture, &range_vec, step, size);
}

void ItemSlot :: drawRange()
{ 
    	range_visual.draw();
}


bool ItemSlot :: isTargetOk(SpaceObjectBase* _target) const
{
        if (_target->getAlive() == true)
        {
                if (isStarSystemOk(_target) == true)
                {
                        if (isDistanceOk(_target) == true)
                        {
                                return true;
                        }
                }
        }
        
        return false;
}


bool ItemSlot :: isStarSystemOk(SpaceObjectBase* _target) const
{
        if (_target->getStarSystem() == owner_vehicle->getStarSystem())
        {
                return true;
        }
        
        return false;
}                

bool ItemSlot :: isDistanceOk(SpaceObjectBase* _target) const
{
	if (_target->getTypeId() == STARSYSTEM_ID)
	{
		return true;
	}
	
        float dist = distBetweenPoints(getOwnerVehicle()->getPoints()->getCenter(), _target->getPoints()->getCenter());                                               
        if (dist < getItemRadius())
        {
                return true;
        }

       	return false;
}

