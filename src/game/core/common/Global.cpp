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

#include "Global.hpp"
#include <ai/God.hpp>
#include <managers/EntityManager.hpp>
#include <communication/MessageManager.hpp>
#include <common/Config.hpp>
#include <common/TurnTimer.hpp>
#include <common/GameDate.hpp>
#include <common/IdGenerator.hpp>
#include <descriptors/RaceDescriptors.hpp>

#include <builder/dock/KosmoportBuilder.hpp>
#include <builder/dock/NatureLandBuilder.hpp>
#include <builder/dock/AngarBuilder.hpp>
#include <builder/dock/StoreBuilder.hpp>
#include <builder/dock/ShopBuilder.hpp>
#include <builder/dock/GovermentBuilder.hpp>

#include <builder/items/artefacts/GravityArtefactBuilder.hpp>
#include <builder/items/artefacts/ProtectorArtefactBuilder.hpp>

#include <builder/items/equipment/BakEquipmentBuilder.hpp>
#include <builder/items/equipment/DriveEquipmentBuilder.hpp>
#include <builder/items/equipment/DroidEquipmentBuilder.hpp>
#include <builder/items/equipment/EnergizerEquipmentBuilder.hpp>
#include <builder/items/equipment/FreezerEquipmentBuilder.hpp>
#include <builder/items/equipment/GrappleEquipmentBuilder.hpp>
#include <builder/items/equipment/ProtectorEquipmentBuilder.hpp>
#include <builder/items/equipment/RadarEquipmentBuilder.hpp>
#include <builder/items/equipment/ScanerEquipmentBuilder.hpp>
#include <builder/items/equipment/RocketEquipmentBuilder.hpp>
#include <builder/items/equipment/LazerEquipmentBuilder.hpp>

#include <builder/items/modules/BakModuleBuilder.hpp>
#include <builder/items/modules/DriveModuleBuilder.hpp>
#include <builder/items/modules/DroidModuleBuilder.hpp>
#include <builder/items/modules/GrappleModuleBuilder.hpp>
#include <builder/items/modules/ProtectorModuleBuilder.hpp>
#include <builder/items/modules/RadarModuleBuilder.hpp>
#include <builder/items/modules/ScanerModuleBuilder.hpp>
#include <builder/items/modules/RocketModuleBuilder.hpp>
#include <builder/items/modules/LazerModuleBuilder.hpp>

#include <builder/items/other/BombBuilder.hpp>

#include <builder/pilots/NpcBuilder.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/slots/VehicleSlotBuilder.hpp>

#include <builder/spaceobjects/AsteroidBuilder.hpp>
#include <builder/spaceobjects/BlackHoleBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>
#include <builder/spaceobjects/PlanetBuilder.hpp>
#include <builder/spaceobjects/StarBuilder.hpp>
#include <builder/spaceobjects/RocketBulletBuilder.hpp>
#include <builder/spaceobjects/SatelliteBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/spaceobjects/SpaceStationBuilder.hpp>

#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>

global& global::get()
{
    static global instance;
    return instance;
}

global::global()
    :
      m_idGenerator(new IdGenerator)
    , m_textureIdGenerator(new IdGenerator)
    , m_god(new God)
    , m_entityManager(new EntityManager)
    , m_messageManager(new MessageManager)
    , m_config(new Config)
    , m_turnTimer(new TurnTimer)
    , m_gameDate(new GameDate)
    , m_raceDescriptors(new RaceDescriptors)

    , m_kosmoportBuilder(new KosmoportBuilder)
    , m_natureLandBuilder(new NatureLandBuilder)
    , m_angarBuilder(new AngarBuilder)
    , m_storeBuilder(new StoreBuilder)
    , m_shopBuilder(new ShopBuilder)
    , m_govermentBuilder(new GovermentBuilder)

    , m_gravityArtefactBuilder(new GravityArtefactBuilder)
    , m_protectorArtefactBuilder(new ProtectorArtefactBuilder)

    , m_bakEquipmentBuilder(new BakEquipmentBuilder)
    , m_driveEquipmentBuilder(new DriveEquipmentBuilder)
    , m_droidEquipmentBuilder(new DroidEquipmentBuilder)
    , m_energizerEquipmentBuilder(new EnergizerEquipmentBuilder)
    , m_freezerEquipmentBuilder(new FreezerEquipmentBuilder)
    , m_grappleEquipmentBuilder(new GrappleEquipmentBuilder)
    , m_protectorEquipmentBuilder(new ProtectorEquipmentBuilder)
    , m_radarEquipmentBuilder(new RadarEquipmentBuilder)
    , m_scanerEquipmentBuilder(new ScanerEquipmentBuilder)
    , m_rocketEquipmentBuilder(new RocketEquipmentBuilder)
    , m_lazerEquipmentBuilder(new LazerEquipmentBuilder)

    , m_bakModuleBuilder(new BakModuleBuilder)
    , m_driveModuleBuilder(new DriveModuleBuilder)
    , m_droidModuleBuilder(new DroidModuleBuilder)
//    , m_energizerModuleBuilder(new EnergizerModuleBuilder)
//    , m_freezerModuleBuilder(new FreezerModuleBuilder)
    , m_grappleModuleBuilder(new GrappleModuleBuilder)
    , m_protectorModuleBuilder(new ProtectorModuleBuilder)
    , m_radarModuleBuilder(new RadarModuleBuilder)
    , m_scanerModuleBuilder(new ScanerModuleBuilder)
    , m_rocketModuleBuilder(new RocketModuleBuilder)
    , m_lazerModuleBuilder(new LazerModuleBuilder)
    , m_bombBuilder(new BombBuilder)
    , m_npcBuilder(new NpcBuilder)
//    , m_itemSlotBuilder(new ItemSlotBuilder)
//    , m_vehicleSlotBuilder(new VehicleSlotBuilder)
    , m_asteroidBuilder(new AsteroidBuilder)
    , m_blackHoleBuilder(new BlackHoleBuilder)
    , m_containerBuilder(new ContainerBuilder)
    , m_planetBuilder(new PlanetBuilder)
    , m_starBuilder(new StarBuilder)
    , m_rocketBulletBuilder(new RocketBulletBuilder)
    , m_satelliteBuilder(new SatelliteBuilder)
    , m_shipBuilder(new ShipBuilder)
    , m_spaceStationBuilder(new SpaceStationBuilder)
    , m_galaxyBuilder(new GalaxyBuilder)
    , m_sectorBuilder(new SectorBuilder)
    , m_starsystemBuilder(new StarSystemBuilder)
{}

global::~global()
{
    delete m_god;
    delete m_entityManager;
    delete m_config;
    delete m_turnTimer;
    delete m_gameDate;
    delete m_raceDescriptors;

    delete m_kosmoportBuilder;
    delete m_natureLandBuilder;
    delete m_angarBuilder;
    delete m_storeBuilder;
    delete m_shopBuilder;
    delete m_govermentBuilder;

    delete m_gravityArtefactBuilder;
    delete m_protectorArtefactBuilder;

    delete m_bakEquipmentBuilder;
    delete m_driveEquipmentBuilder;
    delete m_droidEquipmentBuilder;
    delete m_energizerEquipmentBuilder;
    delete m_freezerEquipmentBuilder;
    delete m_grappleEquipmentBuilder;
    delete m_protectorEquipmentBuilder;
    delete m_radarEquipmentBuilder;
    delete m_scanerEquipmentBuilder;
    delete m_rocketEquipmentBuilder;
    delete m_lazerEquipmentBuilder;

    delete m_bakModuleBuilder;
    delete m_driveModuleBuilder;
    delete m_droidModuleBuilder;
    //    delete m_energizerModuleBuilder;
    //    delete m_freezerModuleBuilder;
    delete m_grappleModuleBuilder;
    delete m_protectorModuleBuilder;
    delete m_radarModuleBuilder;
    delete m_scanerModuleBuilder;
    delete m_rocketModuleBuilder;
    delete m_lazerModuleBuilder;
    delete m_bombBuilder;

    delete m_npcBuilder;
//    delete m_itemSlotBuilder;
//    delete m_vehicleSlotBuilder;

    delete m_asteroidBuilder;
    delete m_blackHoleBuilder;
    delete m_containerBuilder;
    delete m_planetBuilder;
    delete m_starBuilder;
    delete m_rocketBulletBuilder;
    delete m_satelliteBuilder;
    delete m_shipBuilder;
    delete m_spaceStationBuilder;

    delete m_galaxyBuilder;
    delete m_sectorBuilder;
    delete m_starsystemBuilder;
}
