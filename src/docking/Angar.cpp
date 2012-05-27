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
		
	owner_kosmoport = NULL;
        textureOb_background = NULL;
}

Angar::~Angar()
{
	EntityManager::Instance().RemoveEntity(this);
}
                
int Angar::GetFreePlatformTotalNum() const
{
        int sum_free = 0;
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                //if (platform_vec[i]->GetVehicle() == NULL)
                {
                        sum_free++;
                }
        }
        return sum_free; 
}

bool Angar::AddVehicle(Vehicle* vehicle)
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                if (platform_vec[i]->GetVehicle() == NULL)
                {
                        platform_vec[i]->Insert(vehicle);
                        return true;
                }
        }
        
        return false;        
}


bool Angar::RemoveVehicle(Vehicle* vehicle)
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                if (platform_vec[i]->GetVehicle() != NULL)
                {
                        if (platform_vec[i]->GetVehicle() == vehicle)
                        {
                                platform_vec[i]->Free();
                                return true;
                        }
                }
        }
    
        return false;       
}



void Angar::MouseControl(Player* player)
{
        //bool lmb = player->GetCursor()->getMouseLeftButton(); 
        bool rmb = player->GetCursor()->GetMouseRightButton(); 

        for (unsigned int i = 0; i < platform_vec.size(); i++)
        { 
                float dist = distBetweenPoints(player->GetCursor()->GetMousePos().x, 
                                               player->GetScreen()->getHeight() - player->GetCursor()->GetMousePos().y, 
                                               platform_vec[i]->GetRect().GetCenter().x, 
                                               platform_vec[i]->GetRect().GetCenter().y);
        				
                if (dist < platform_vec[i]->GetRect().GetWidth()/2)
                {
                        if (rmb == true)
                        {
                                if (platform_vec[i]->GetVehicle() != NULL)
                                {
                                        player->GetNpc()->SetScanTarget(platform_vec[i]->GetVehicle());
                                }
                        }
                }
        }
}


void Angar::Render(Player* player) const
{
        clearScreen();
        resetRenderTransformation();
                        
        RenderBackground(player);
                
	enable_BLEND();
        
        RenderInternals();
        //RenderItemInfo();
        
}

void Angar::RenderBackground(Player* player) const
{
     	Rect screen_rect = Rect(0, 0, player->GetScreen()->getWidth(), player->GetScreen()->getHeight());
     	drawTexturedRect(textureOb_background, screen_rect, -2);  
}

void Angar::RenderInternals() const
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                platform_vec[i]->Render();
        }
}

void Angar::RenderItemInfo(Player* player) const
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        { 
		if (platform_vec[i]->GetVehicle() != NULL)
                {

                	float dist = distBetweenPoints(player->GetCursor()->GetMousePos().x, 
                        	                       player->GetScreen()->getHeight() - player->GetCursor()->GetMousePos().y, 
                                	               platform_vec[i]->GetRect().GetCenter().x, 
                                        	       platform_vec[i]->GetRect().GetCenter().y);
        				
                	if (dist < platform_vec[i]->GetRect().GetWidth()/2)
                	{
		                platform_vec[i]->RenderInfo();
                	}
                }
        }
}
            

void Angar::SaveDataUniqueAngar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	//save_ptree.put(root+"unresolved.angar_id",     angar->GetId());

}

void Angar::LoadDataUniqueAngar(const boost::property_tree::ptree& load_ptree)
{
	//data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");

}

void Angar::ResolveDataUniqueAngar()
{
	//angar     = (Angar*)EntityManager::Instance().GetEntityById(data_unresolved_Kosmoport.angar_id); 

}


void Angar::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "angar." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueAngar(save_ptree, root);
}

void Angar::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueAngar(load_ptree);
}

void Angar::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueAngar();
}

