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

#include "SaveLoadManager.hpp"
#include <boost/property_tree/info_parser.hpp>
#include "../pilots/Npc.hpp"

//template<typename T>
//T getValFromPropertyTree(const boost::property_tree::ptree& ptree, const std::string& str)
//{
	//std::cout<<str<<std::endl;
	//return  ptree.get<T>(str);
//}

SaveLoadManager& SaveLoadManager::Instance()
{
	static SaveLoadManager instance;
	return instance;
}

Player* SaveLoadManager::Update(Player* player)
{
	if (perform_save == true)
	{
		EntityManager::Instance().SaveEvent();
		perform_save = false;
	}

	if (perform_load == true)
	{
		EntityManager::Instance().Clear();
		EntityManager::Instance().LoadPass0();
		EntityManager::Instance().LoadPass1();
						
		player = (Player*)EntityManager::Instance().GetPlayer();
		perform_load = false;
		
		return player;
	}
	
	return NULL;
}

void SaveLoadManager::SaveFile(const std::string& filename, boost::property_tree::ptree& ptree) const
{		
	write_info(filename, ptree);
}

void SaveLoadManager::LoadFile(const std::string& filename, boost::property_tree::ptree& ptree) const
{
	read_info(filename, ptree);
}


