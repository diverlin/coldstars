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

#include <common/Base.hpp>
#include <ceti/Orientation.hpp>

#include <ceti/type/IdType.hpp>
#include <types/TechLevelTypes.hpp>
#include <types/RaceTypes.hpp>

#include <item/ItemCommonData.hpp>

namespace descriptor {
class Item;
} // namespace descriptor

namespace model {
class Item;
} // namespace model

namespace control {
class ItemSlot; 
} // namespace control


namespace control {

class Item : public Base
{
public:
    Item() = default;
    virtual ~Item() = default;

    virtual void putChildrenToGarbage() const {}

//    void setParentSubTypeId(entity::type parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
//    void setItemCommonData(const ItemCommonData& data_item)
//    {
//        m_data = data_item;
//        m_deterioration = data_item.deterioration;
//        setCondition(data_item.condition_max);
//    }
    void setSlot(control::ItemSlot* slot)  { m_slot = slot; }
//    void setCondition(int condition) { m_condition = condition; }

    control::ItemSlot* slot() const { return m_slot; }

//    virtual int radius() const { return 0; }
//    virtual int damage() const { return 0; }

//    int mass()          const { return m_data.mass; }
//    int condition()     const { return m_condition; }
//    int price()         const { return m_price; }
//    int basePrice()     const { return m_data.price; }
//    int deterioration() const { return m_data.deterioration; }

//    [[deprecated("remove")]]
//    int modulesNum() const { return m_data.modules_num; }
//    int descriptorType() const { return m_data.descriptor_type; }

//    tech::type tech() const { return m_data.tech; }

//    entity::type parentSubtype() const { return m_parent_subtype_id; }
//    race::type race() const { return m_race_id; }

    bool isDamaged() const;
    bool isLocked() const;
    int isFunctioning() const;

    void useNormalDeterioration();
    void useOverloadDeterioration();

    void doBreak();
    void deteriorationEvent();
    void doLock(int lock = 1);
    void doUnlock();
    bool doRepair();

    virtual void updateProperties() {}
    virtual void updateInStatic() { _updateLock(); }

    //        void UpdateInfo();

    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);
    //        void RenderKorpus(const jeti::Renderer&, const ceti::Box2D&);
    //        void RenderInfo(const jeti::Renderer&, const glm::vec2&);

protected:
//    race::type m_race_id = race::type::NONE;

//    int m_locked_turns = 0;
//    int m_condition = 0;
//    int m_price = 0;
//    int m_deterioration = 0;

//    entity::type m_parent_subtype_id = entity::type::NONE;

//    ItemCommonData m_data;
//    UnresolvedDataBase m_data_unresolved_Base;
    //        InfoTable info;

    void _updateLock();

    virtual void AddCommonInfo()=0;
    virtual void addUniqueInfo()=0;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

public:
    model::Item* model() const { return m_model_item; }
    descriptor::Item* descriptor() const { return m_descriptor_item; }

private:
    model::Item* m_model_item = nullptr;
    descriptor::Item* m_descriptor_item = nullptr;

    control::ItemSlot* m_slot = nullptr;
};

} // namespace control
