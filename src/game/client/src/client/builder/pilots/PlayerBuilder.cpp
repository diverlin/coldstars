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

#include <client/builder/pilots/PlayerBuilder.hpp>
#include <builder/pilots/NpcBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>

#include <client/pilots/Player.hpp>

#include <spaceobjects/Ship.hpp>

#include <ceti/IdGenerator.hpp>
#include <ceti/Logger.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <common/constants.hpp>

 
PlayerBuilder& PlayerBuilder::Instance()
{
    static PlayerBuilder instance;
    return instance;
}

PlayerBuilder::~PlayerBuilder()
{}

Player* PlayerBuilder::GetNewPlayerTemplate(int_t id) const
{
    Player* player = nullptr;
    if (id == NONE) {
        //id = EntityIdGenerator::Instance().GetNextId();
    }

    try {
        player = new Player(id);
    }
    catch(std::bad_alloc) {
        //Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
        
    //global::get().entitiesManager().RegisterEntity(player);
    
    return player;       
} 
   
Player* PlayerBuilder::createNewPlayer() const
{
    Player* player = GetNewPlayerTemplate();
    CreateNewInternals(player);
    
    return player;
}         

void PlayerBuilder::CreateNewInternals(Player* player) const
{    
    race::type prace_id         = race::type::R0_ID;
    entity::type psubtype_id    = entity::type::RANGER_ID;
    entity::type psubsubtype_id = entity::type::WARRIOR_ID;
    int size_id        = SIZE_4_ID;
    int weapons_num    = 6;
    tech::type tech = tech::type::LEVEL3;
    
//    Npc* npc = NpcBuilder::Instance().GetNewNpc(prace_id, psubtype_id, psubsubtype_id);
//    Ship* ship = ShipBuilder::Instance().GetNewShip(prace_id, psubtype_id, size_id, weapons_num);
    
//    ShipBuilder::Instance().EquipEquipment(ship, tech_level);
//    ShipBuilder::Instance().EquipModules(ship, tech_level);
//    //ShipBuilder::Instance().EquipArtefacts(ship, tech_level);
//    ShipBuilder::Instance().EquipBomb(ship, tech_level);
    
//    ship->BindOwnerNpc(npc);
    //player->BindNpc(npc);
}

