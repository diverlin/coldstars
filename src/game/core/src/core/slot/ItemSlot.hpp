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

#include <core/slot/BaseSlot.hpp>
#include <core/slot/Weapon.hpp>

#include <core/type/StatusType.hpp>
#include <core/item/equipment/Weapon.hpp>

#include <ceti/type/IdType.hpp>

namespace control {

class SpaceObject;
class Item;

namespace item {
class Radar;
class Rocket;
class Lazer;
class Bak;
#ifdef USE_EXTRA_EQUIPMENT
class FreezerEquipment;
class EnergizerEquipment;
#endif // USE_EXTRA_EQUIPMENT
class Protector;
class Droid;
class Scaner;
class Drive;
class Grapple;
} // namespace item

} // naemspace control

namespace control {

} // namespace control

#ifdef USE_MODULES
class RocketModule;
class LazerModule;
class RadarModule; 
class BakModule; 
class EnergizerModule; 
class ProtectorModule; 
class DroidModule; 
class FreezerModule; 
class ScanerModule;
class DriveModule; 
class GrappleModule; 
#endif // USE_MODULES

class Bomb; 
class GoodsPack; 

namespace slot {

class Item : public Base, public Weapon
{
public:
    Item(entity::Type);
    virtual ~Item();

    void setType(entity::Type type) { m_type = type; }
    void setGroup(entity::Type group) { m_group = group; }
    void setPosition(int position) { m_position = position; }

    entity::Type type() const { return m_type; }
    //entity::Type group() const { return m_group; }
    int position() const { return m_position; }

//    virtual void putChildrenToGarbage() const;

    int hitProbability() const { return m_hitProbability; }

    control::item::Weapon* weapon() const { return static_cast<control::item::Weapon*>(m_item); }
    control::Item* item() const { return m_item; }
    bool isEmpty() const { return !m_item; }

    control::item::Rocket*    rocketEquipment()    const { return reinterpret_cast<control::item::Rocket*>(m_item); }
    control::item::Lazer*     lazerEquipment()     const { return reinterpret_cast<control::item::Lazer*>(m_item); }
    control::item::Radar*     radarEquipment()     const { return reinterpret_cast<control::item::Radar*>(m_item); }
    control::item::Drive*     driveEquipment()     const { return reinterpret_cast<control::item::Drive*>(m_item); }
    control::item::Bak*       bakEquipment()       const { return reinterpret_cast<control::item::Bak*>(m_item); }
#ifdef USE_EXTRA_EQUIPMENT
    control::item::EnergizerEquipment* energizerEquipment() const { return reinterpret_cast<control::item::EnergizerEquipment*>(m_item); }
    control::item::FreezerEquipment*   freezerEquipment()   const { return reinterpret_cast<control::item::FreezerEquipment*>(m_item); }
#endif
    control::item::Protector* protectorEquipment() const { return reinterpret_cast<control::item::Protector*>(m_item); }
    control::item::Droid*     droidEquipment()     const { return reinterpret_cast<control::item::Droid*>(m_item); }
    control::item::Scaner*    scanerEquipment()    const { return reinterpret_cast<control::item::Scaner*>(m_item); }
    control::item::Grapple*   grappleEquipment()   const { return reinterpret_cast<control::item::Grapple*>(m_item); }

#ifdef USE_MODULES
    RocketModule*       rocketModule()       const { return reinterpret_cast<RocketModule*>(m_item); }
    LazerModule*        lazerModule()        const { return reinterpret_cast<LazerModule*>(m_item); }
    RadarModule*        radarModule()        const { return reinterpret_cast<RadarModule*>(m_item); }
    DriveModule*        driveModule()        const { return reinterpret_cast<DriveModule*>(m_item); }
    BakModule*          bakModule()          const { return reinterpret_cast<BakModule*>(m_item); }
    EnergizerModule*    energizerModule()    const { return reinterpret_cast<EnergizerModule*>(m_item); }
    ProtectorModule*    protectorModule()    const { return reinterpret_cast<ProtectorModule*>(m_item); }
    DroidModule*        droidModule()        const { return reinterpret_cast<DroidModule*>(m_item); }
    FreezerModule*      freezerModule()      const { return reinterpret_cast<FreezerModule*>(m_item); }
    ScanerModule*       scanerModule()       const { return reinterpret_cast<ScanerModule*>(m_item); }
    GrappleModule*      grappleModule()      const { return reinterpret_cast<GrappleModule*>(m_item); }
#endif
    Bomb* bomb()           const { return reinterpret_cast<Bomb*>(m_item); }
    //Artefact* GetArtefact() const { return artefact; }
    GoodsPack* goodsPack() const { return reinterpret_cast<GoodsPack*>(m_item); }

    bool insert(control::Item*);
    control::Item* takeItem();
    void release();

    void updateVehiclePropetries() const;

    bool swapItem(slot::Item*);

    void selectEvent();
    void deselectEvent();

private:
    control::Item* m_item = nullptr;

    int m_hitProbability = 0;

    bool __checkItemInsertion(control::Item*) const;

    void log(const std::string&) const;

    int m_position = NONE;
    entity::Type m_type = entity::Type::NONE;
    entity::Type m_group = entity::Type::NONE;

    //    virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
    //    virtual void RenderItem(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
    //    void RenderMark(const jeti::Renderer&, const ceti::Box2D&, jeti::control::TextureOb*) const;
    //    void RenderTargetMark(const jeti::Renderer&, const ceti::Box2D&, jeti::control::TextureOb*, jeti::control::TextureOb*) const;

    //    void updateRange(jeti::control::Material*);
    //    void drawRange(const glm::vec2&);
};

} // namespace slot


