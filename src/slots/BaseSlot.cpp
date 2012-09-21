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

#include "BaseSlot.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"

BaseSlot::BaseSlot()
{
        equiped = false;
        selected = false;

        owner   = NULL; 

        textureOb  = NULL;
}

/* virtual */
BaseSlot::~BaseSlot()
{
	#ifdef CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseSlot(), id="+int2str(GetId()));
	#endif
}
                
/*virtual*/
void BaseSlot::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "item_slot." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSlot(save_ptree, root);
}

/*virtual*/		
void BaseSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSlot(load_ptree);
}
	
/*virtual*/	
void BaseSlot::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseSlot();
}

void BaseSlot::SaveDataUniqueBaseSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{       
        if (owner) 
        {
        	save_ptree.put(root+"unresolved.owner_type_id", owner->GetTypeId());        	
        	save_ptree.put(root+"unresolved.owner_id", owner->GetId());
        }
        else
        {
                save_ptree.put(root+"unresolved.owner_type_id", NONE_ID);
                save_ptree.put(root+"unresolved.owner_id", NONE_ID);	
	}

}

void BaseSlot::LoadDataUniqueBaseSlot(const boost::property_tree::ptree& load_ptree)
{   
        unresolved_BaseSlot.owner_type_id = load_ptree.get<int>("unresolved.owner_type_id"); 
        unresolved_BaseSlot.owner_id = load_ptree.get<int>("unresolved.owner_id"); 
}

void BaseSlot::ResolveDataUniqueBaseSlot()
{
        //Rect tmp_rect(unresolved_BaseSlot.rect_blx, unresolved_BaseSlot.rect_bly, unresolved_BaseSlot.rect_w, unresolved_BaseSlot.rect_h);
        //switch(unresolved_BaseSlot.owner_type_id)
        //{
	       //case ENTITY::VEHICLE_ID: 	{	((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddSlot(this, tmp_rect); break; }
	       //case ENTITY::CONTAINER_ID:     	{	((Container*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->BindBaseSlot(this); break; }
	       //case ENTITY::STORE_ID:         	{ 	((Store*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddSlot(this, tmp_rect); break; }
	       //case ENTITY::ANGAR_ID:         	{ 	}//((Store*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddSlot(this, tmp_rect); break; }
	//}
}
