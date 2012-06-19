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


Angar::Angar(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::ANGAR_ID;
	data_id.subtype_id = NONE_ID;
}

Angar::~Angar()
{
	EntityManager::Instance().RemoveEntity(this);
}
       
void Angar::AddVehicleSlot(VehicleSlot* vehicle_slot, const Rect& rect) 
{ 
	vehicle_slot->SetRect(rect.GetBottomLeft().x, rect.GetBottomLeft().y, rect.GetWidth(), rect.GetHeight());
	vehicle_slot->SetOwner(this);
	vehicleslot_vec.push_back(vehicle_slot); 
};
                         
                         
void Angar::Ai() const
{
        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        {
                if (vehicleslot_vec[i]->GetVehicle() != NULL)
                {
                	if (vehicleslot_vec[i]->GetVehicle()->GetOwnerNpc() != NULL)
                	{
                        	vehicleslot_vec[i]->GetVehicle()->GetOwnerNpc()->ThinkCommon_inKosmoport_inStatic();
                	}
               	}
        }
}

                                                
int Angar::GetFreeVehicleSlotTotalNum() const
{
        int sum_free = 0;
        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        {
                if (vehicleslot_vec[i]->GetVehicle() == NULL)
                {
                        sum_free++;
                }
        }
        return sum_free; 
}

bool Angar::AddVehicle(Vehicle* vehicle)
{
        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        {
                if (vehicleslot_vec[i]->GetVehicle() == NULL)
                {
                        vehicleslot_vec[i]->InsertVehicle(vehicle);
                        return true;
                }
        }        
        return false;        
}


//bool Angar::RemoveVehicle(Vehicle* vehicle)
//{
        //for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        //{
                //if (vehicleslot_vec[i]->GetVehicle() != NULL)
                //{
                        //if (vehicleslot_vec[i]->GetVehicle() == vehicle)
                        //{
                                //vehicleslot_vec[i]->Release();
                                //return true;
                        //}
                //}
        //}
    
        //return false;       
//}



void Angar::MouseControl(Player* player)
{
        //bool lmb = player->GetCursor()->getMouseLeftButton(); 
        bool rmb = player->GetCursor()->GetMouseRightButton(); 

        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        { 
                float dist = distBetweenPoints(player->GetCursor()->GetMousePos().x, 
                                               player->GetScreen()->GetHeight() - player->GetCursor()->GetMousePos().y, 
                                               vehicleslot_vec[i]->GetRect().GetCenter().x, 
                                               vehicleslot_vec[i]->GetRect().GetCenter().y);
        				
                if (dist < vehicleslot_vec[i]->GetRect().GetWidth()/2)
                {
                        if (rmb == true)
                        {
                                if (vehicleslot_vec[i]->GetVehicle() != NULL)
                                {
                                        player->GetNpc()->SetScanTarget(vehicleslot_vec[i]->GetVehicle());
                                }
                        }
                }
        }
}


void Angar::Render(Player* player) const // move to GuiAngar
{
        clearScreen();
        resetRenderTransformation();
                    
        Rect screen_rect = Rect(0, 0, player->GetScreen()->GetWidth(), player->GetScreen()->GetHeight());    
        RenderBackground(screen_rect);
                
	enable_BLEND();
        
        RenderInternals();
        //RenderItemInfo();
        
}

void Angar::RenderInternals() const
{
        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        {
                vehicleslot_vec[i]->Render();
        }
}

void Angar::RenderItemInfo(Player* player) const
{
        for (unsigned int i = 0; i < vehicleslot_vec.size(); i++)
        { 
		if (vehicleslot_vec[i]->GetVehicle() != NULL)
                {

                	float dist = distBetweenPoints(player->GetCursor()->GetMousePos().x, 
                        	                       player->GetScreen()->GetHeight() - player->GetCursor()->GetMousePos().y, 
                                	               vehicleslot_vec[i]->GetRect().GetCenter().x, 
                                        	       vehicleslot_vec[i]->GetRect().GetCenter().y);
        				
                	if (dist < vehicleslot_vec[i]->GetRect().GetWidth()/2)
                	{
		                vehicleslot_vec[i]->RenderInfo();
                	}
                }
        }
}
            

void Angar::SaveDataUniqueAngar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Angar::LoadDataUniqueAngar(const boost::property_tree::ptree& load_ptree)
{}

void Angar::ResolveDataUniqueAngar()
{
	((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindAngar(this); 
}


void Angar::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "angar." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueRoom(save_ptree, root);
	SaveDataUniqueAngar(save_ptree, root);
}

void Angar::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueRoom(load_ptree);
	LoadDataUniqueAngar(load_ptree);
}

void Angar::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueRoom();
	ResolveDataUniqueAngar();
}

