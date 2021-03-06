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

#include <builder/pilots/PlayerBuilder.hpp>
#include <builder/pilots/NpcBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>

#include <pilots/Player.hpp>

#include <spaceobjects/Ship.hpp>

#include <common/IdGenerator.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>

#include <common/constants.hpp>

 
PlayerBuilder& PlayerBuilder::Instance()
{
    static PlayerBuilder instance;
    return instance;
}

PlayerBuilder::~PlayerBuilder()
{}

Player* PlayerBuilder::GetNewPlayerTemplate(INTLONGEST id) const
{
    Player* player = nullptr;
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        player = new Player(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
        
    EntityManager::Instance().RegisterEntity(player); 
    
    return player;       
} 
   
Player* PlayerBuilder::GetNewPlayer() const
{
    Player* player = GetNewPlayerTemplate();
    CreateNewInternals(player);
    
    return player;
}         

void PlayerBuilder::CreateNewInternals(Player* player) const
{    
    TYPE::RACE prace_id         = TYPE::RACE::R0_ID;
    TYPE::ENTITY psubtype_id    = TYPE::ENTITY::RANGER_ID;
    TYPE::ENTITY psubsubtype_id = TYPE::ENTITY::WARRIOR_ID;
    int size_id        = SIZE_4_ID;
    int weapons_num    = 6;
    TYPE::TECHLEVEL tech_level = TYPE::TECHLEVEL::L3_ID;
    
    Npc* npc = NpcBuilder::Instance().GetNewNpc(prace_id, psubtype_id, psubsubtype_id);
    Ship* ship = ShipBuilder::Instance().GetNewShip(prace_id, psubtype_id, size_id, weapons_num);
    
    ShipBuilder::Instance().EquipEquipment(ship, tech_level);   
    ShipBuilder::Instance().EquipModules(ship, tech_level); 
    //ShipBuilder::Instance().EquipArtefacts(ship, tech_level); 
    ShipBuilder::Instance().EquipBomb(ship, tech_level); 
    
    ship->BindOwnerNpc(npc);
    player->BindNpc(npc);
}

