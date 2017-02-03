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
#include <ceti/IdGenerator.hpp>
#include <descriptors/RaceDescriptors.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <builder/dock/KosmoportBuilder.hpp>
#include <builder/dock/NatureLandBuilder.hpp>
#include <builder/dock/AngarBuilder.hpp>
#include <builder/dock/StoreBuilder.hpp>
#include <builder/dock/ShopBuilder.hpp>
#include <builder/dock/GovermentBuilder.hpp>

#include <builder/item/artefacts/GravityArtefactBuilder.hpp>
#include <builder/item/artefacts/ProtectorArtefactBuilder.hpp>

#include <builder/item/equipment/BakBuilder.hpp>
#include <builder/item/equipment/DriveBuilder.hpp>
#include <builder/item/equipment/DroidBuilder.hpp>
#ifdef USE_EXTRA_EQUIPMENT
#include <builder/item/equipment/EnergizerBuilder.hpp>
#include <builder/item/equipment/FreezerBuilder.hpp>
#endif
#include <builder/item/equipment/GrappleBuilder.hpp>
#include <builder/item/equipment/ProtectorBuilder.hpp>
#include <builder/item/equipment/RadarBuilder.hpp>
#include <builder/item/equipment/ScanerBuilder.hpp>
#include <builder/item/equipment/RocketBuilder.hpp>
#include <builder/item/equipment/LazerBuilder.hpp>

#ifdef USE_MODULES
#include <builder/item/modules/BakModuleBuilder.hpp>
#include <builder/item/modules/DriveModuleBuilder.hpp>
#include <builder/item/modules/DroidModuleBuilder.hpp>
#include <builder/item/modules/GrappleModuleBuilder.hpp>
#include <builder/item/modules/ProtectorModuleBuilder.hpp>
#include <builder/item/modules/RadarModuleBuilder.hpp>
#include <builder/item/modules/ScanerModuleBuilder.hpp>
#include <builder/item/modules/RocketModuleBuilder.hpp>
#include <builder/item/modules/LazerModuleBuilder.hpp>
#endif // USE_MODULES

#include <builder/item/other/BombBuilder.hpp>

#include <builder/pilots/NpcBuilder.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/slots/VehicleSlotBuilder.hpp>

#include <builder/spaceobjects/BlackHoleBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>
#include <builder/spaceobjects/RocketBulletBuilder.hpp>

namespace core {

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

    #ifdef USE_ARTEFACTS
    , m_gravityArtefactBuilder(new GravityArtefactBuilder)
    , m_protectorArtefactBuilder(new ProtectorArtefactBuilder)
    #endif // USE_ARTEFACTS

    , m_bakBuilder(new item::equipment::BakBuilder)
//    , m_driveBuilder(new item::equipment::DriveBuilder)
    , m_droidBuilder(new item::equipment::DroidBuilder)
    #ifdef USE_EXTRA_EQUIPMENT
    , m_energizerBuilder(new item::equipment::EnergizerBuilder)
    , m_freezerBuilder(new item::equipment::FreezerBuilder)
    #endif
    , m_grappleBuilder(new item::equipment::GrappleBuilder)
    , m_protectorBuilder(new item::equipment::ProtectorBuilder)
    , m_radarBuilder(new item::equipment::RadarBuilder)
    , m_scanerBuilder(new item::equipment::ScanerBuilder)
    , m_rocketBuilder(new item::equipment::RocketBuilder)
    , m_lazerBuilder(new item::equipment::LazerBuilder)

    #ifdef USE_MODULES
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
    #endif // USE_MODULES

    , m_bombBuilder(new BombBuilder)
    , m_npcBuilder(new NpcBuilder)
    , m_blackHoleBuilder(new builder::BlackHole)
    , m_containerBuilder(new builder::Container)
    , m_rocketBulletBuilder(new builder::Rocket)
    , m_descriptors(new descriptor::Manager)
{
}

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

#ifdef USE_ARTEFACTS
    delete m_gravityArtefactBuilder;
    delete m_protectorArtefactBuilder;
#endif // USE_ARTEFACTS

    delete m_bakBuilder;
//    delete m_driveBuilder;
    delete m_droidBuilder;
#ifdef USE_EXTRA_EQUIPMENT
    delete m_energizerBuilder;
    delete m_freezerBuilder;
#endif // USE_EXTRA_EQUIPMENT
    delete m_grappleBuilder;
    delete m_protectorBuilder;
    delete m_radarBuilder;
    delete m_scanerBuilder;
    delete m_rocketBuilder;
    delete m_lazerBuilder;

#ifdef USE_MODULES
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
#endif // USE_MODULES

    delete m_bombBuilder;

    delete m_npcBuilder;
    delete m_blackHoleBuilder;
    delete m_containerBuilder;
    delete m_rocketBulletBuilder;
}

} // namespace core
