
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

#pragma once

class IdGenerator;
class TextureIdGenerator;
class God;
class EntityManager;
class MessageManager;
class Config;
class TurnTimer;
class GameDate;
class RaceDescriptors;

// builders
class KosmoportBuilder;
class NatureLandBuilder;
class AngarBuilder;
class StoreBuilder;
class ShopBuilder;
class GovermentBuilder;

#ifdef USE_ARTEFACTS
class GravityArtefactBuilder;
class ProtectorArtefactBuilder;
#endif

namespace item {
namespace equipment {
class BakBuilder;
class DriveBuilder;
class DroidBuilder;
#ifdef USE_EXTRA_EQUIPMENT
class EnergizerBuilder;
class FreezerBuilder;
#endif
class GrappleBuilder;
class ProtectorBuilder;
class RadarBuilder;
class ScanerBuilder;
class RocketBuilder;
class LazerBuilder;
} // namespace equipment
} // namespace item

#ifdef USE_MODULES
class BakModuleBuilder;
class DriveModuleBuilder;
class DroidModuleBuilder;
//class EnergizerModuleBuilder;
//class FreezerModuleBuilder;
class GrappleModuleBuilder;
class ProtectorModuleBuilder;
class RadarModuleBuilder;
class ScanerModuleBuilder;
class RocketModuleBuilder;
class LazerModuleBuilder;
#endif

class BombBuilder;

class NpcBuilder;
//class ItemSlotBuilder;
//class VehicleSlotBuilder;

namespace builder {

class Asteroid;
class SatelliteBuilder;
class SpaceStationBuilder;
class RocketBulletBuilder;
class ContainerBuilder;
class BlackHoleBuilder;

} // namespace builder

//class PlanetBuilder;
//class StarBuilder;
class ShipBuilder;

class GalaxyBuilder;
class SectorBuilder;
class StarsystemBuilder;

namespace descriptor {
class Manager;
} // namespace descriptor

namespace core {

class global
{
public:
    static global& get();

    IdGenerator& idGenerator() { return *m_idGenerator; }
    IdGenerator& textureIdGenerator() { return *m_textureIdGenerator; }
    God& god() { return *m_god; }
    EntityManager& entityManager() { return *m_entityManager; }
    MessageManager& messageManager() { return *m_messageManager; }
    Config& config() { return *m_config; }
    TurnTimer& turnTimer() { return *m_turnTimer; }
    GameDate& gameDate() { return *m_gameDate; }
    RaceDescriptors& raceDescriptors() { return *m_raceDescriptors; }

    KosmoportBuilder& kosmoportBuilder() { return *m_kosmoportBuilder; }
    NatureLandBuilder& natureLandBuilder() { return *m_natureLandBuilder; }
    AngarBuilder& angarBuilder() { return *m_angarBuilder; }
    StoreBuilder& storeBuilder() { return *m_storeBuilder; }
    ShopBuilder& shopBuilder() { return *m_shopBuilder; }
    GovermentBuilder& govermentBuilder() { return *m_govermentBuilder; }

#ifdef USE_ARTEFACTS
    GravityArtefactBuilder& gravityArtefactBuilder() { return *m_gravityArtefactBuilder; }
    ProtectorArtefactBuilder& protectorArtefactBuilder() { return *m_protectorArtefactBuilder; }
#endif // USE_ARTEFACTS

    item::equipment::BakBuilder& bakBuilder() { return *m_bakBuilder; }
    item::equipment::DriveBuilder& driveBuilder() { return *m_driveBuilder; }
    item::equipment::DroidBuilder& droidBuilder() { return *m_droidBuilder; }
#ifdef USE_EXTRA_EQUIPMENT
    item::equipment::EnergizerBuilder& energizerBuilder() { return *m_energizerBuilder; }
    item::equipment::FreezerBuilder& freezerBuilder() { return *m_freezerBuilder; }
#endif // USE_EXTRA_EQUIPMENT
    item::equipment::GrappleBuilder& grappleBuilder() { return *m_grappleBuilder; }
    item::equipment::ProtectorBuilder& protectorBuilder() { return *m_protectorBuilder; }
    item::equipment::RadarBuilder& radarBuilder() { return *m_radarBuilder; }
    item::equipment::ScanerBuilder& scanerBuilder() { return *m_scanerBuilder; }
    item::equipment::RocketBuilder& rocketBuilder() { return *m_rocketBuilder; }
    item::equipment::LazerBuilder& lazerBuilder() { return *m_lazerBuilder; }

#ifdef USE_MODULES
    BakModuleBuilder& bakModuleBuilder() { return *m_bakModuleBuilder; }
    DriveModuleBuilder& driveModuleBuilder() { return *m_driveModuleBuilder; }
    DroidModuleBuilder& droidModuleBuilder() { return *m_droidModuleBuilder; }
    //EnergizerModuleBuilder& energizerModuleBuilder() { return *m_energizerModuleBuilder; }
    //FreezerModuleBuilder& freezerModuleBuilder() { return *m_freezerModuleBuilder; }
    GrappleModuleBuilder& grappleModuleBuilder() { return *m_grappleModuleBuilder; }
    ProtectorModuleBuilder& protectorModuleBuilder() { return *m_protectorModuleBuilder; }
    RadarModuleBuilder& radarModuleBuilder() { return *m_radarModuleBuilder; }
    ScanerModuleBuilder& scanerModuleBuilder() { return *m_scanerModuleBuilder; }
    RocketModuleBuilder& rocketModuleBuilder() { return *m_rocketModuleBuilder; }
    LazerModuleBuilder& lazerModuleBuilder() { return *m_lazerModuleBuilder; }
#endif // USE_MODULES

    BombBuilder& bombBuilder() { return *m_bombBuilder; }

    NpcBuilder& npcBuilder() { return *m_npcBuilder; }
    //        ItemSlotBuilder& itemSlotBuilder() { return *m_itemSlotBuilder; }
    //        VehicleSlotBuilder& vehicleSlotBuilder() { return *m_vehicleSlotBuilder; }

//    builder::Asteroid& asteroidBuilder() { return *m_asteroidBuilder; }
    builder::BlackHoleBuilder& blackHoleBuilder() { return *m_blackHoleBuilder; }
    builder::ContainerBuilder& containerBuilder() { return *m_containerBuilder; }
//    PlanetBuilder& planetBuilder() { return *m_planetBuilder; }
//    StarBuilder& starBuilder() { return *m_starBuilder; }
    builder::RocketBulletBuilder& rocketBulletBuilder() { return *m_rocketBulletBuilder; }
    builder::SatelliteBuilder& satelliteBuilder() { return *m_satelliteBuilder; }
    builder::SpaceStationBuilder& spaceStationBuilder() { return *m_spaceStationBuilder; }

    GalaxyBuilder& galaxyBuilder() { return *m_galaxyBuilder; }
    SectorBuilder& sectorBuilder() { return *m_sectorBuilder; }
    StarsystemBuilder& starsystemBuilder() { return *m_starsystemBuilder; }

    descriptor::Manager& descriptors() { return *m_descriptors; }

private:
    global();
    global(const global&) = delete;
    ~global();
    global& operator=(const global&) = delete;

    IdGenerator* m_idGenerator = nullptr;
    IdGenerator* m_textureIdGenerator = nullptr;
    God* m_god = nullptr;
    EntityManager* m_entityManager = nullptr;
    MessageManager* m_messageManager = nullptr;
    Config* m_config = nullptr;
    TurnTimer* m_turnTimer = nullptr;
    GameDate* m_gameDate = nullptr;
    RaceDescriptors* m_raceDescriptors = nullptr;

    KosmoportBuilder* m_kosmoportBuilder = nullptr;
    NatureLandBuilder* m_natureLandBuilder = nullptr;
    AngarBuilder* m_angarBuilder = nullptr;
    StoreBuilder* m_storeBuilder = nullptr;
    ShopBuilder* m_shopBuilder = nullptr;
    GovermentBuilder* m_govermentBuilder = nullptr;

#ifdef USE_ARTEFACTS
    GravityArtefactBuilder* m_gravityArtefactBuilder = nullptr;
    ProtectorArtefactBuilder* m_protectorArtefactBuilder = nullptr;
#endif // USE_ARTEFACTS

    item::equipment::BakBuilder* m_bakBuilder = nullptr;
    item::equipment::DriveBuilder* m_driveBuilder = nullptr;
    item::equipment::DroidBuilder* m_droidBuilder = nullptr;
#ifdef USE_EXTRA_EQUIPMENT
    item::equipment::EnergizerBuilder* m_energizerBuilder = nullptr;
    item::equipment::FreezerBuilder* m_freezerBuilder = nullptr;
#endif // USE_EXTRA_EQUIPMENT
    item::equipment::GrappleBuilder* m_grappleBuilder = nullptr;
    item::equipment::ProtectorBuilder* m_protectorBuilder = nullptr;
    item::equipment::RadarBuilder* m_radarBuilder = nullptr;
    item::equipment::ScanerBuilder* m_scanerBuilder = nullptr;
    item::equipment::RocketBuilder* m_rocketBuilder = nullptr;
    item::equipment::LazerBuilder* m_lazerBuilder = nullptr;

#ifdef USE_MODULES
    BakModuleBuilder* m_bakModuleBuilder = nullptr;
    DriveModuleBuilder* m_driveModuleBuilder = nullptr;
    DroidModuleBuilder* m_droidModuleBuilder = nullptr;
    //EnergizerModuleBuilder* m_energizerModuleBuilder = nullptr;
    //FreezerModuleBuilder* m_freezerModuleBuilder = nullptr;
    GrappleModuleBuilder* m_grappleModuleBuilder = nullptr;
    ProtectorModuleBuilder* m_protectorModuleBuilder = nullptr;
    RadarModuleBuilder* m_radarModuleBuilder = nullptr;
    ScanerModuleBuilder* m_scanerModuleBuilder = nullptr;
    RocketModuleBuilder* m_rocketModuleBuilder = nullptr;
    LazerModuleBuilder* m_lazerModuleBuilder = nullptr;
#endif // USE_MODULES

    BombBuilder* m_bombBuilder = nullptr;

    NpcBuilder* m_npcBuilder = nullptr;
    //        ItemSlotBuilder* m_itemSlotBuilder = nullptr;
    //        VehicleSlotBuilder* m_vehicleSlotBuilder = nullptr;

//    builder::Asteroid* m_asteroidBuilder = nullptr;
    builder::BlackHoleBuilder* m_blackHoleBuilder = nullptr;
    builder::ContainerBuilder* m_containerBuilder = nullptr;
//    PlanetBuilder* m_planetBuilder = nullptr;
//    StarBuilder* m_starBuilder = nullptr;
    builder::RocketBulletBuilder* m_rocketBulletBuilder = nullptr;
    builder::SatelliteBuilder* m_satelliteBuilder = nullptr;
    //ShipBuilder* m_shipBuilder = nullptr;
    builder::SpaceStationBuilder* m_spaceStationBuilder = nullptr;

    GalaxyBuilder* m_galaxyBuilder = nullptr;
    SectorBuilder* m_sectorBuilder = nullptr;
    StarsystemBuilder* m_starsystemBuilder = nullptr;

    descriptor::Manager* m_descriptors = nullptr;
};

} // namespace core
