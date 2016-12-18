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

#include <ceti/type/IdType.hpp>
#include <types/StatusTypes.hpp>

#include <slots/BaseSlot.hpp>

class Turrel; 
namespace item {
class Base;
}
class SpaceObject;

namespace item {
namespace equipment {
class Rocket;
class Lazer;
class Radar;
class Bak;
#ifdef USE_EXTRA_EQUIPMENT
class FreezerEquipment;
class EnergizerEquipment; 
#endif
class Protector;
class Droid;
class Scaner;
class Drive;
class Grapple;
} // namespace equipment
} // namespace item

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
#endif

class Bomb; 
class GoodsPack; 

//namespace ceti {
//class Box2D;
//}

//namespace jeti {
//class Renderer;
//}

struct UnresolvedDataItemSlot
{
    UnresolvedDataItemSlot()
    {}
    
    int_t target_id = NONE;
    int_t subtarget_id = NONE;
};

class ItemSlot : public BaseSlot
{   
public:
    ItemSlot(int_t id, type::entity subtype_id);
    virtual ~ItemSlot();

    virtual void putChildrenToGarbage() const;

    void setTarget(SpaceObject* target, ItemSlot* subtarget = nullptr);
    void setTurrel(Turrel* turrel) { m_turrel = turrel; }

    SpaceObject* target() const { return m_target; }
    ItemSlot* subtarget() const { return m_subtarget; }

    int hitProbability() const { return m_hitProbability; }

    Turrel* turrel() const { return m_turrel; }

    item::Base* item() const { return m_item; }
    bool isEmpty() const { return !m_item; }

    item::equipment::Rocket*    rocketEquipment()    const { return reinterpret_cast<item::equipment::Rocket*>(m_item); }
    item::equipment::Lazer*     lazerEquipment()     const { return reinterpret_cast<item::equipment::Lazer*>(m_item); }
    item::equipment::Radar*     radarEquipment()     const { return reinterpret_cast<item::equipment::Radar*>(m_item); }
    item::equipment::Drive*     driveEquipment()     const { return reinterpret_cast<item::equipment::Drive*>(m_item); }
    item::equipment::Bak*       bakEquipment()       const { return reinterpret_cast<item::equipment::Bak*>(m_item); }
#ifdef USE_EXTRA_EQUIPMENT
    item::equipment::EnergizerEquipment* energizerEquipment() const { return reinterpret_cast<item::equipment::EnergizerEquipment*>(m_item); }
    item::equipment::FreezerEquipment*   freezerEquipment()   const { return reinterpret_cast<item::equipment::FreezerEquipment*>(m_item); }
#endif
    item::equipment::Protector* protectorEquipment() const { return reinterpret_cast<item::equipment::Protector*>(m_item); }
    item::equipment::Droid*     droidEquipment()     const { return reinterpret_cast<item::equipment::Droid*>(m_item); }
    item::equipment::Scaner*    scanerEquipment()    const { return reinterpret_cast<item::equipment::Scaner*>(m_item); }
    item::equipment::Grapple*   grappleEquipment()   const { return reinterpret_cast<item::equipment::Grapple*>(m_item); }

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

    bool insert(item::Base*);
    void removeItem();

    STATUS validateTarget();
    void resetTarget();
    bool checkAmmo() const;
    void fireEvent(float, bool);

    void updateVehiclePropetries() const;

    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
    //        virtual void RenderItem(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
    //        void RenderMark(const jeti::Renderer&, const ceti::Box2D&, jeti::control::TextureOb*) const;
    //        void RenderTargetMark(const jeti::Renderer&, const ceti::Box2D&, jeti::control::TextureOb*, jeti::control::TextureOb*) const;

    item::Base* takeItem();

    bool swapItem(ItemSlot*);

    void updateRange(jeti::control::TextureOb*);
    void drawRange(const glm::vec2&);

    bool checkSubTarget(ItemSlot*) const;
    STATUS checkTarget(SpaceObject*) const;
    STATUS checkTargetPure(SpaceObject*) const;

    void selectEvent();
    void deselectEvent();

    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

    int itemRadius() const;
    int itemDamage() const;

private:
    Turrel* m_turrel = nullptr;          // only for weapons slot

    item::Base* m_item = nullptr;

    SpaceObject* m_target = nullptr;
    ItemSlot* m_subtarget = nullptr;

    int m_hitProbability = 0;

    bool checkItemInsertion(item::Base*) const;

    bool isTargetAlive(SpaceObject*) const;
    bool isTargetInSpace(SpaceObject*) const;
    bool isTargetInSameStarSystem(SpaceObject*) const;
    bool checkDistanceToTarget(SpaceObject*) const;

    UnresolvedDataItemSlot m_unresolved_ItemSlot;
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

    void log(const std::string&) const;
}; 
