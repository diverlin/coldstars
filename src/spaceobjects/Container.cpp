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



Container::Container(int id)
{
	data_id.id         = id;
	data_id.type_id    = ENTITY::CONTAINER_ID;
        data_id.subtype_id = NONE_ID;
	
    	mass = 1;

	ItemSlotBuilder::Instance().CreateNewItemSlot();
	ItemSlotBuilder::Instance().CreateNewInternals(SLOT::CARGO_ID);
   	item_slot = ItemSlotBuilder::Instance().GetItemSlot();
    	
    	velocity = getRandInt(40, 42) / 100.0;
}

/* virtual */   
Container::~Container()
{
	delete item_slot;
}

void Container::UpdateInfo()  
{}        
       	
void Container::RenderInfoInSpace(vec2f scroll_coords)
{
	UpdateInfo();
     	item_slot->GetRect().setCenter(points.getCenter());
     	item_slot->RenderItemInfo(scroll_coords.x, scroll_coords.y);
}
 
/* virtual */    
void Container::PostDeathUniqueEvent(bool show_effect)
{
        if (item_slot->GetItem()->GetTypeId() == ENTITY::BOMB_ID)
        {
        	starsystem->BombExplosionEvent(this, show_effect);  
        }
        else
        {
        	if (show_effect == true)
        	{
        		createExplosion(starsystem, points.getCenter(), textureOb->size_id);  
        	}
        }
}

void Container::CalcCollisionrRadius()
{
        collision_radius = (textureOb->getFrameWidth() + textureOb->getFrameHeight())/4; 
        
        points.setWidthHeight(textureOb->getFrameWidth(), textureOb->getFrameHeight());  // needs for finding visible corners
}

void Container::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	UpdateRotation();
		
	if (time > 0)
	{
     		if (keep_moving == true)
     		{
        		keep_moving = get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, target_pos.x, target_pos.y, velocity, &d_pos.x, &d_pos.y);
        		points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
     		}  
     	}
}


void Container::SilentKill()
{
	data_life.is_alive      = false;  
	data_life.garbage_ready = true;  // ??? death(false);
}
   
       		
void Container::Render2D()
{ 
    	drawDynamic(textureOb, points.getCenter(), angle.z, points.getPosZ());
}




/*virtual*/
void Container::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void Container::LoadData(boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void Container::ResolveData()
{

}
