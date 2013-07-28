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

#include "Room.hpp"
#include "Kosmoport.hpp"
#include "../render/Render.hpp"
#include "../resources/TextureManager.hpp"
 
Room::Room()
{	
	owner_kosmoport = nullptr;
        textureOb_background = nullptr;
}

Room::~Room()
{}            

void Room::RenderBackground(const Rect& rect) const
{
     	drawTexturedRect(textureOb_background, rect, -2);  
}
           
void Room::SaveDataUniqueRoom(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"unresolved.textureOb_background_path", textureOb_background->path);
	save_ptree.put(root+"unresolved.owner_kosmoport_id", owner_kosmoport->GetId());
}

void Room::LoadDataUniqueRoom(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_Room.textureOb_background_path = load_ptree.get<std::string>("unresolved.textureOb_background_path");
	data_unresolved_Room.owner_kosmoport_id = load_ptree.get<int>("unresolved.owner_kosmoport_id");
}

void Room::ResolveDataUniqueRoom()
{
	textureOb_background = TextureManager::Instance().GetTextureObByPath(data_unresolved_Room.textureOb_background_path);
}

