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


BaseLand::BaseLand()
{
	owner = NULL;
}

/* virtual */
BaseLand::~BaseLand()
{
	//delete NPC_vec/VEHICLE_vec;
}

void BaseLand::ManageLaunchingQueue()
{
         for (unsigned int i = 0; i<NPC_launching_vec.size(); i++)
         {
         	NPC_launching_vec[i]->GetVehicle()->LaunchingEvent();
         }
              
         NPC_launching_vec.clear();  
}

void BaseLand::AddToLaunchingQueue(Npc* npc)
{
         NPC_launching_vec.push_back(npc);
}



void BaseLand::SaveDataUniqueBaseLand(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	for (unsigned int i=0; i<NPC_vec.size(); i++)
	{
		save_ptree.put(root+"unresoved.npc_vec.id.", NPC_vec[i]->GetId());
	}

	for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
	{
		save_ptree.put(root+"unresoved.vehicle_vec.id.", VEHICLE_vec[i]->GetId());
	}

	for (unsigned int i=0; i<NPC_launching_vec.size(); i++)
	{
		save_ptree.put(root+"unresoved.npc_launching_vec.id.", NPC_launching_vec[i]->GetId());
	}

	for (unsigned int i=0; i<NPC_docking_vec.size(); i++)
	{
		save_ptree.put(root+"unresoved.npc_docking_vec.id.", NPC_docking_vec[i]->GetId());
	}
}

void BaseLand::LoadDataUniqueBaseLand(const boost::property_tree::ptree& load_ptree)
{
	boost::property_tree::ptree _load_ptree = load_ptree;
	if (load_ptree.get_child_optional("unresolved.npc_vec"))
	{ 
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _load_ptree.get_child("unresolved.npc_vec"))
		{
			data_unresolved_BaseLand.npc_vec.push_back(v.second.get<int>("id"));
		}
	}

	if (load_ptree.get_child_optional("unresolved.vehicle_vec"))
	{ 
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _load_ptree.get_child("unresolved.vehicle_vec"))
		{
			data_unresolved_BaseLand.vehicle_vec.push_back(v.second.get<int>("id"));
		}
	}

	if (load_ptree.get_child_optional("unresolved.npc_docking_vec"))
	{ 	
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _load_ptree.get_child("unresolved.npc_docking_vec"))
		{
			data_unresolved_BaseLand.npc_vec.push_back(v.second.get<int>("id"));
		}
	}

	if (load_ptree.get_child_optional("unresolved.npc_docking_vec"))
	{ 		
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _load_ptree.get_child("unresolved.npc_docking_vec"))
		{
			data_unresolved_BaseLand.npc_vec.push_back(v.second.get<int>("id"));
		}
	}
}

void BaseLand::ResolveDataUniqueBaseLand()
{
	//for (unsigned int i=0; i<data_unresolved_BaseLand.npc_vec.size(); i++)
	//{
		//NPC_vec.push_back((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_BaseLand.npc_vec[i]));
	//}
	//for (unsigned int i=0; i<data_unresolved_BaseLand.vehicle_vec.size(); i++)
	//{
		//VEHICLE_vec.push_back((Vehicle*)EntityManager::Instance().GetEntityById(data_unresolved_BaseLand.vehicle_vec[i]));
	//}
	//for (unsigned int i=0; i<data_unresolved_BaseLand.npc_docking_vec.size(); i++)
	//{
		//NPC_docking_vec.push_back((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_BaseLand.npc_docking_vec[i]));
	//}
	//for (unsigned int i=0; i<data_unresolved_BaseLand.npc_launching_vec.size(); i++)
	//{
		//NPC_launching_vec.push_back((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_BaseLand.npc_launching_vec[i]));
	//}
}
