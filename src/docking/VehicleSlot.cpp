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
	data_id.type_id = ENTITY::VEHICLESLOT_ID;
	data_id.subtype_id = NONE_ID;
	
    	vehicle = NULL;
}
   
VehicleSlot::~VehicleSlot()
{}
      


void VehicleSlot::InsertVehicle(Vehicle* vehicle)
{
        this->vehicle = vehicle;
        
        vehicle->SetPlaceTypeId(data_id.type_id);
        
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
	const std::string root = "vehicle_slot." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSlot(save_ptree, root);
	SaveDataUniqueVehicleSlot(save_ptree, root);
}

/*virtual*/		
void VehicleSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSlot(load_ptree);
	LoadDataUniqueVehicleSlot(load_ptree);
}
	
/*virtual*/	
void VehicleSlot::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseSlot();
	ResolveDataUniqueVehicleSlot();
}


void VehicleSlot::SaveDataUniqueVehicleSlot(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
}

void VehicleSlot::LoadDataUniqueVehicleSlot(const boost::property_tree::ptree& load_ptree)
{
}

void VehicleSlot::ResolveDataUniqueVehicleSlot()
{
        Rect tmp_rect(unresolved_BaseSlot.rect_blx, unresolved_BaseSlot.rect_bly, unresolved_BaseSlot.rect_w, unresolved_BaseSlot.rect_h);
        switch(unresolved_BaseSlot.owner_type_id)
        {
	       //case ENTITY::VEHICLE_ID: 	{	((Vehicle*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddSlot(this, tmp_rect); break; }
	       //case ENTITY::CONTAINER_ID:     	{	((Container*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->BindItemSlot(this); break; }
	       //case ENTITY::STORE_ID:         	{ 	((Store*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddSlot(this, tmp_rect); break; }
	       case ENTITY::ANGAR_ID:         	{ ((Angar*)EntityManager::Instance().GetEntityById(unresolved_BaseSlot.owner_id))->AddVehicleSlot(this, tmp_rect); break; }
	}
}
