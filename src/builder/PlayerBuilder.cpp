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


PlayerBuilder& PlayerBuilder::Instance()
{
	static PlayerBuilder instance;
	return instance;
}

PlayerBuilder::~PlayerBuilder()
{}

void PlayerBuilder::CreateNewPlayer(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
	player = new Player(id);
	EntityManager::Instance().RegisterEntity(player);        
} 
        	
void PlayerBuilder::CreateNewInternals()
{    
	int prace_id    = RACE::R7_ID;
      	int psubtype_id = CLASS::WARRIOR_ID;
      	int size_id     = SIZE_5;
      	int weapons_num = 5;
        
        NpcBuilder::Instance().CreateNewNpc();
        NpcBuilder::Instance().CreateNewInternals(prace_id, psubtype_id);
        Npc* pnpc = NpcBuilder::Instance().GetNpc();
                   
        ShipBuilder::Instance().CreateNewShip();
        ShipBuilder::Instance().CreateNewInternals(prace_id, psubtype_id, size_id, weapons_num);
        Ship* pship = ShipBuilder::Instance().GetShip();
        	
	VehicleBuilder::Instance().Equip(pship);   // improove
        
        pnpc->BindVehicle(pship);
   	player->BindNpc(pnpc);
}

