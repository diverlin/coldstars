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

VehicleSlot::VehicleSlot(int id)
{   
	data_id.id = id;
	data_id.type_id = ENTITY::VEHICLEPLATFORM_ID;
	data_id.subtype_id = NONE_ID;
	
    	textureOb = NULL;
    	
    	owner = NULL;
    	vehicle = NULL;
}
   
VehicleSlot::~VehicleSlot()
{}
      
void VehicleSlot::SetRect(float pos_x, float pos_y, int w, int h) 
{
	rect.Set(pos_x, pos_y, w, h);
}

void VehicleSlot::Insert(Vehicle* vehicle)
{
        this->vehicle = vehicle;
        
       	vehicle->GetPoints().SetCenter(rect.GetCenter());
        vehicle->GetPoints().SetAngle(0);
        vehicle->GetPoints().Update();
}

void VehicleSlot::Free()
{
        vehicle = NULL;
} 

void VehicleSlot::Render() const
{
     	drawTexturedRect(textureOb, rect, -1);
     	if (vehicle != NULL)
     	{
     	       	((Ship*)vehicle)->RenderAtPlanet();
	}
}


void VehicleSlot::RenderInfo() const
{
	vehicle->RenderInfo(rect.GetCenter().x, rect.GetCenter().y, 0, 0);
}


/*virtual*/
void VehicleSlot::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "item_slot." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueVehicleSlot(save_ptree, root);
}

/*virtual*/		
void VehicleSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueVehicleSlot(load_ptree);
}
	
/*virtual*/	
void VehicleSlot::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueVehicleSlot();
}


void VehicleSlot::SaveDataUniqueVehicleSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        //save_ptree.put(root+"unresolved.rect.BottomLeft.x", rect.GetBottomLeft().x);
        //save_ptree.put(root+"unresolved.rect.BottomLeft.y", rect.GetBottomLeft().y); 
        //save_ptree.put(root+"unresolved.rect.width", rect.GetWidth());
        //save_ptree.put(root+"unresolved.rect.height", rect.GetHeight()); 
        
        //if (owner_vehicle) save_ptree.put(root+"unresolved.owner_vehicle_id", owner_vehicle->GetId());
        //else               save_ptree.put(root+"unresolved.owner_vehicle_id", NONE_ID);

        //if (owner_container) save_ptree.put(root+"unresolved.owner_container_id", owner_container->GetId());
        //else             save_ptree.put(root+"unresolved.owner_container_id", NONE_ID);
        
        //if (owner_angar) save_ptree.put(root+"unresolved.owner_angar_id", owner_angar->GetId());
        //else             save_ptree.put(root+"unresolved.owner_angar_id", NONE_ID);
        
        //if (owner_store) save_ptree.put(root+"unresolved.owner_store_id", owner_store->GetId());
        //else             save_ptree.put(root+"unresolved.owner_store_id", NONE_ID);
}

void VehicleSlot::LoadDataUniqueVehicleSlot(const boost::property_tree::ptree& load_ptree)
{
        //unresolved_VehicleSlot.rect_blx = load_ptree.get<float>("unresolved.rect.BottomLeft.x");
        //unresolved_VehicleSlot.rect_bly = load_ptree.get<float>("unresolved.rect.BottomLeft.y");
        //unresolved_VehicleSlot.rect_w   = load_ptree.get<int>("unresolved.rect.width"); 
        //unresolved_VehicleSlot.rect_h   = load_ptree.get<int>("unresolved.rect.height"); 
     
        //unresolved_VehicleSlot.owner_vehicle_id = load_ptree.get<int>("unresolved.owner_vehicle_id"); 
        //unresolved_VehicleSlot.owner_container_id = load_ptree.get<int>("unresolved.owner_container_id"); 
        //unresolved_VehicleSlot.owner_angar_id   = load_ptree.get<int>("unresolved.owner_angar_id"); 
        //unresolved_VehicleSlot.owner_store_id   = load_ptree.get<int>("unresolved.owner_store_id"); 
}

void VehicleSlot::ResolveDataUniqueVehicleSlot()
{
        //Rect tmp_rect(unresolved_VehicleSlot.rect_blx, unresolved_VehicleSlot.rect_bly, unresolved_VehicleSlot.rect_w, unresolved_VehicleSlot.rect_h);
        //if (unresolved_VehicleSlot.owner_vehicle_id != NONE_ID)
        //{	//std::cout<<"slot id ="<<data_id.id<<" added to vehicle!!!!"<<std::endl;
                //((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_VehicleSlot.owner_vehicle_id))->AddSlot(this, tmp_rect);
	//}

	//if (unresolved_VehicleSlot.owner_container_id != NONE_ID)
        //{     	//std::cout<<"slot id ="<<data_id.id<<" added to store!!!!"<<std::endl;
                //((Container*)EntityManager::Instance().GetEntityById(unresolved_VehicleSlot.owner_container_id))->BindVehicleSlot(this);
	//}
	
        //if (unresolved_VehicleSlot.owner_angar_id != NONE_ID)
        //{
                ////((Angar*)EntityManager::Instance().GetEntityById(unresolved_VehicleSlot.owner_angar_id))->AddSlot(this, tmp_rect);
	//}
	
	//if (unresolved_VehicleSlot.owner_store_id != NONE_ID)
        //{     	//std::cout<<"slot id ="<<data_id.id<<" added to store!!!!"<<std::endl;
                //((Store*)EntityManager::Instance().GetEntityById(unresolved_VehicleSlot.owner_store_id))->AddSlot(this, tmp_rect);
	//}
}
