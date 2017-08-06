
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
class BakBuilder;
//class DriveBuilder;
class DroidBuilder;
#ifdef USE_EXTRA_EQUIPMENT
class EnergizerBuilder;
class FreezerBuilder;
#endif
class ProtectorBuilder;
class RadarBuilder;
class ScanerBuilder;
class RocketBuilder;
class LazerBuilder;
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

class Rocket;
class Container;
class WormHole;

} // namespace builder

namespace descriptor {
class Manager;
} // namespace descriptor

namespace core {

class global
{
public:
    static global& get();

    God& god() { return *m_god; }
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

#ifdef USE_EXTRA_EQUIPMENT
    item::EnergizerBuilder& energizerBuilder() { return *m_energizerBuilder; }
    item::FreezerBuilder& freezerBuilder() { return *m_freezerBuilder; }
#endif // USE_EXTRA_EQUIPMENT

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

    //        ItemSlotBuilder& itemSlotBuilder() { return *m_itemSlotBuilder; }
    //        VehicleSlotBuilder& vehicleSlotBuilder() { return *m_vehicleSlotBuilder; }

    builder::WormHole& blackHoleBuilder() { return *m_blackHoleBuilder; }
    builder::Rocket& BulletBuilder() { return *m_BulletBuilder; }

private:
    global();
    global(const global&) = delete;
    ~global();
    global& operator=(const global&) = delete;

    God* m_god = nullptr;
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

#ifdef USE_EXTRA_EQUIPMENT
    item::EnergizerBuilder* m_energizerBuilder = nullptr;
    item::FreezerBuilder* m_freezerBuilder = nullptr;
#endif // USE_EXTRA_EQUIPMENT

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
    //        ItemSlotBuilder* m_itemSlotBuilder = nullptr;
    //        VehicleSlotBuilder* m_vehicleSlotBuilder = nullptr;

    builder::WormHole* m_blackHoleBuilder = nullptr;
    builder::Rocket* m_BulletBuilder = nullptr;
};

} // namespace core
