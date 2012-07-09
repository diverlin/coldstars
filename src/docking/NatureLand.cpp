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



NatureLand::NatureLand()
{}

/* virtual */
NatureLand::~NatureLand()
{}


//// ******* TRANSITION ******* 
/* virtual */
bool NatureLand::Add(Vehicle* vehicle)
{
        vehicle->SetPlaceTypeId(ENTITY::PLANET_ID);
        //VEHICLE_vec.push_back(vehicle);
        
        return true;
}

/* virtual */
bool NatureLand::Add(Npc* npc)
{
        //npc->SetPlaceTypeId(ENTITY::LAND_ID);        
        //NPC_vec.push_back(npc);

        //npc->SetLand(this);
 
        return true;
}

/*virtual */
bool NatureLand::Remove(Vehicle* vehicle)
{
        //bool is_removed = false;
        
        //for (unsigned int i = 0; i < VEHICLE_vec.size(); i++) 
        //{
                //if (VEHICLE_vec[i] == vehicle)
                //{
                        //VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
                        //is_removed = true;
                //}
        //}
        
        //return is_removed;
}

/* virtual */
bool NatureLand::Remove(Npc* npc)
{
        //bool is_removed = false;
    
        //for (unsigned int i = 0; i < NPC_vec.size(); i++)
        //{ 
                //if (NPC_vec[i] == npc)
                //{
                        //NPC_vec.erase(NPC_vec.begin() + i);
                        //is_removed = true;
                //}
        //}
        
        //return is_removed;
}

/* virtual */
bool NatureLand::GetPermissionToLand() const
{
       	return true;
}

/* virtual */
void NatureLand::Ai()
{
        //for (unsigned int i = 0; i < NPC_vec.size(); i++)
        //{
           	//NPC_vec[i]->ThinkCommon_inLand_inStatic();      
	//}
}  

/*virtual*/
void NatureLand::SaveData(boost::property_tree::ptree& save_ptree) const
{
	//const std::string root = "rocket."+int2str(data_id.id)+".";
}

/*virtual*/
void NatureLand::LoadData(const boost::property_tree::ptree& load_ptree)
{

}

/*virtual*/
void NatureLand::ResolveData()
{

}
