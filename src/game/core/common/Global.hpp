
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

class GravityArtefactBuilder;
class ProtectorArtefactBuilder;

class BakEquipmentBuilder;
class DriveEquipmentBuilder;
class DroidEquipmentBuilder;
class EnergizerEquipmentBuilder;
class FreezerEquipmentBuilder;
class GrappleEquipmentBuilder;
class ProtectorEquipmentBuilder;
class RadarEquipmentBuilder;
class ScanerEquipmentBuilder;
class RocketEquipmentBuilder;
class LazerEquipmentBuilder;

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

class BombBuilder;

class NpcBuilder;
//class ItemSlotBuilder;
//class VehicleSlotBuilder;

class AsteroidBuilder;
class BlackHoleBuilder;
class ContainerBuilder;
class PlanetBuilder;
class StarBuilder;
class RocketBulletBuilder;
class SatelliteBuilder;
class ShipBuilder;
class SpaceStationBuilder;

class GalaxyBuilder;
class SectorBuilder;
class StarSystemBuilder;

class global
{
    public:
        static global& get();

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

        GravityArtefactBuilder& gravityArtefactBuilder() { return *m_gravityArtefactBuilder; }
        ProtectorArtefactBuilder& protectorArtefactBuilder() { return *m_protectorArtefactBuilder; }

        BakEquipmentBuilder& bakEquipmentBuilder() { return *m_bakEquipmentBuilder; }
        DriveEquipmentBuilder& driveEquipmentBuilder() { return *m_driveEquipmentBuilder; }
        DroidEquipmentBuilder& droidEquipmentBuilder() { return *m_droidEquipmentBuilder; }
        EnergizerEquipmentBuilder& energizerEquipmentBuilder() { return *m_energizerEquipmentBuilder; }
        FreezerEquipmentBuilder& freezerEquipmentBuilder() { return *m_freezerEquipmentBuilder; }
        GrappleEquipmentBuilder& grappleEquipmentBuilder() { return *m_grappleEquipmentBuilder; }
        ProtectorEquipmentBuilder& protectorEquipmentBuilder() { return *m_protectorEquipmentBuilder; }
        RadarEquipmentBuilder& radarEquipmentBuilder() { return *m_radarEquipmentBuilder; }
        ScanerEquipmentBuilder& scanerEquipmentBuilder() { return *m_scanerEquipmentBuilder; }
        RocketEquipmentBuilder& rocketEquipmentBuilder() { return *m_rocketEquipmentBuilder; }
        LazerEquipmentBuilder& lazerEquipmentBuilder() { return *m_lazerEquipmentBuilder; }

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

        BombBuilder& bombBuilder() { return *m_bombBuilder; }

        NpcBuilder& npcBuilder() { return *m_npcBuilder; }
//        ItemSlotBuilder& itemSlotBuilder() { return *m_itemSlotBuilder; }
//        VehicleSlotBuilder& vehicleSlotBuilder() { return *m_vehicleSlotBuilder; }

        AsteroidBuilder& asteroidBuilder() { return *m_asteroidBuilder; }
        BlackHoleBuilder& blackHoleBuilder() { return *m_blackHoleBuilder; }
        ContainerBuilder& containerBuilder() { return *m_containerBuilder; }
        PlanetBuilder& planetBuilder() { return *m_planetBuilder; }
        StarBuilder& starBuilder() { return *m_starBuilder; }
        RocketBulletBuilder& rocketBulletBuilder() { return *m_rocketBulletBuilder; }
        SatelliteBuilder& satelliteBuilder() { return *m_satelliteBuilder; }
        ShipBuilder& shipBuilder() { return *m_shipBuilder; }
        SpaceStationBuilder& spaceStationBuilder() { return *m_spaceStationBuilder; }

        GalaxyBuilder& galaxyBuilder() { return *m_galaxyBuilder; }
        SectorBuilder& sectorBuilder() { return *m_sectorBuilder; }
        StarSystemBuilder& starSystemBuilder() { return *m_starsystemBuilder; }

    private:
        global();
        global(const global&) = delete;
        ~global();
        global& operator=(const global&) = delete;

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

        GravityArtefactBuilder* m_gravityArtefactBuilder = nullptr;
        ProtectorArtefactBuilder* m_protectorArtefactBuilder = nullptr;

        BakEquipmentBuilder* m_bakEquipmentBuilder = nullptr;
        DriveEquipmentBuilder* m_driveEquipmentBuilder = nullptr;
        DroidEquipmentBuilder* m_droidEquipmentBuilder = nullptr;
        EnergizerEquipmentBuilder* m_energizerEquipmentBuilder = nullptr;
        FreezerEquipmentBuilder* m_freezerEquipmentBuilder = nullptr;
        GrappleEquipmentBuilder* m_grappleEquipmentBuilder = nullptr;
        ProtectorEquipmentBuilder* m_protectorEquipmentBuilder = nullptr;
        RadarEquipmentBuilder* m_radarEquipmentBuilder = nullptr;
        ScanerEquipmentBuilder* m_scanerEquipmentBuilder = nullptr;
        RocketEquipmentBuilder* m_rocketEquipmentBuilder = nullptr;
        LazerEquipmentBuilder* m_lazerEquipmentBuilder = nullptr;

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

        BombBuilder* m_bombBuilder = nullptr;

        NpcBuilder* m_npcBuilder = nullptr;
//        ItemSlotBuilder* m_itemSlotBuilder = nullptr;
//        VehicleSlotBuilder* m_vehicleSlotBuilder = nullptr;

        AsteroidBuilder* m_asteroidBuilder = nullptr;
        BlackHoleBuilder* m_blackHoleBuilder = nullptr;
        ContainerBuilder* m_containerBuilder = nullptr;
        PlanetBuilder* m_planetBuilder = nullptr;
        StarBuilder* m_starBuilder = nullptr;
        RocketBulletBuilder* m_rocketBulletBuilder = nullptr;
        SatelliteBuilder* m_satelliteBuilder = nullptr;
        ShipBuilder* m_shipBuilder = nullptr;
        SpaceStationBuilder* m_spaceStationBuilder = nullptr;

        GalaxyBuilder* m_galaxyBuilder = nullptr;
        SectorBuilder* m_sectorBuilder = nullptr;
        StarSystemBuilder* m_starsystemBuilder = nullptr;
};
