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

#include <core/type/StatusType.hpp>
#include <core/slot/BaseSlot.hpp>
#include <core/item/equipment/Weapon.hpp>

#include <ceti/type/IdType.hpp>

class Turrel; 

namespace control {
class Item;

namespace item {
class Radar;
class Rocket;
class Lazer;
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
} // namespace item

} // naemspace control

namespace control {
class SpaceObject;
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


//namespace descriptor {

//class ItemSlot : public BaseSlot
//{
//public:
//    ItemSlot() = default;
//    ~ItemSlot() = default;
//    ItemSlot(const std::string& data);
//    std::string data() const;

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & boost::serialization::base_object<BaseSlot>(*this);
//    }
//};

//} // namespace descriptor


//namespace model {

//class ItemSlot : public BaseSlot
//{
//public:
//    ItemSlot() = default;
//    ~ItemSlot() = default;
//    ItemSlot(const std::string& data);
//    std::string data() const;

//    ItemSlot(int_t id, entity::type subtype_id);

//    void setTarget(int_t target) { m_target = target; }
//    void setSubtargetTarget(int_t subtarget) { m_subtarget = subtarget; }

//    int_t item() const { return m_item; }
//    int_t target() const { return m_target; }
//    int_t subtarget() const { return m_subtarget; }

//private:
//    int_t m_item = NONE;
//    int_t m_target = NONE;
//    int_t m_subtarget = NONE;

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & boost::serialization::base_object<BaseSlot>(*this);
//        ar & m_item;
//        ar & m_target;
//        ar & m_subtarget;
//    }
//};

//} // namespace model

namespace slot {

class ItemSlot : public Base
{
public:
    ItemSlot(entity::Type subtype_id);
    virtual ~ItemSlot();

    void setOffset(int offset) { m_offset = offset; }
    void setType(entity::Type type) { m_type = type; }
    void setSubType(entity::Type subtype) { m_subtype = subtype; }

    int offset() const { return m_offset; }
    entity::Type type() const { return m_type; }
    entity::Type subtype() const { return m_subtype; }

    virtual void putChildrenToGarbage() const;

    void setTarget(control::SpaceObject* target, slot::ItemSlot* subtarget = nullptr);
    void setTurrel(Turrel* turrel) { m_turrel = turrel; }

    control::SpaceObject* target() const { return m_target; }
    slot::ItemSlot* subtarget() const { return m_subtarget; }

    int hitProbability() const { return m_hitProbability; }

    Turrel* turrel() const { return m_turrel; }

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

    control::Item* takeItem();

    bool swapItem(slot::ItemSlot*);

//    void updateRange(jeti::control::Material*);
    void drawRange(const glm::vec2&);

    bool checkSubTarget(slot::ItemSlot*) const;
    STATUS checkTarget(control::SpaceObject*) const;
    STATUS checkTargetPure(control::SpaceObject*) const;

    void selectEvent();
    void deselectEvent();

    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

    int itemRadius() const;
    int itemDamage() const;

//    model::ItemSlot* model() const { return m_model_itemslot; }

private:
//    model::ItemSlot* m_model_itemslot = nullptr;

    Turrel* m_turrel = nullptr;          // only for weapons slot

    control::Item* m_item = nullptr;

    control::SpaceObject* m_target = nullptr;
    slot::ItemSlot* m_subtarget = nullptr;

    int m_hitProbability = 0;

    bool checkItemInsertion(control::Item*) const;

    bool isTargetAlive(control::SpaceObject*) const;
    bool isTargetInSpace(control::SpaceObject*) const;
    bool isTargetInSameStarSystem(control::SpaceObject*) const;
    bool checkDistanceToTarget(control::SpaceObject*) const;

    void log(const std::string&) const;

    int m_offset = NONE;
    entity::Type m_type = entity::Type::NONE;
    entity::Type m_subtype = entity::Type::NONE;
};

} // namespace slot

