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

#include <types/IdType.hpp>
#include <types/TechLevelTypes.hpp>
#include <types/RaceTypes.hpp>

#include <item/ItemCommonData.hpp>


class ItemSlot; 

namespace item {

struct UnresolvedDataBaseItem
{
    std::string textureOb_path;
    id_type item_slot_id;
};

class Base : public ::Base
{
public:
    Base();
    virtual ~Base();

    virtual void putChildrenToGarbage() const {}

    void setParentSubTypeId(type::ENTITY parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
    void setItemCommonData(const ItemCommonData& data_item)
    {
        setId(data_item.id);

        m_data_item = data_item;
        m_deterioration = data_item.deterioration;
        setCondition(data_item.condition_max);
    }
    void setItemSlot(ItemSlot* item_slot)  { m_item_slot = item_slot; }
    void setCondition(int condition) { m_condition = condition; }

    ItemSlot* itemSlot() const { return m_item_slot; }

    virtual int radius() const { return 0; }
    virtual int damage() const { return 0; }

    int mass()          const { return m_data_item.mass; }
    int condition()     const { return m_condition; }
    int price()         const { return m_price; }
    int basePrice()     const { return m_data_item.price; }
    int deterioration() const { return m_data_item.deterioration; }

    int modulesNum() const { return m_data_item.modules_num; }
    int descriptorType() const { return m_data_item.descriptor_type; }

    type::TECH tech() const { return m_data_item.tech; }

    type::ENTITY parentSubTypeId() const { return m_parent_subtype_id; }
    type::RACE race() const { return m_race_id; }

    bool isDamaged()    const { return (m_condition <= 0); }
    bool isLocked()     const { return (m_locked_turns > 0); }
    int isFunctioning() const { return ( !isDamaged() && !isLocked() ); }

    void useNormalDeterioration();
    void useOverloadDeterioration();

    void doBreak();
    void deteriorationEvent();
    void doLock(int lock = 1);
    void doUnlock();
    bool doRepair();

    virtual void updateProperties() {}
    virtual void updateInStatic() { updateLock(); }

    //        void UpdateInfo();

    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);
    //        void RenderKorpus(const jeti::Renderer&, const ceti::Box2D&);
    //        void RenderInfo(const jeti::Renderer&, const glm::vec2&);

protected:
    type::RACE m_race_id = type::RACE::NONE_ID;

    int m_locked_turns = 0;
    int m_condition = 0;
    int m_price = 0;
    int m_deterioration = 0;

    type::ENTITY m_parent_subtype_id = type::ENTITY::NONE_ID;

    ItemCommonData m_data_item;
    UnresolvedDataBaseItem m_data_unresolved_BaseItem;
    //        InfoTable info;

    void updateLock();

    virtual void AddCommonInfo()=0;
    virtual void addUniqueInfo()=0;

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    ItemSlot* m_item_slot = nullptr;
};

} // namespace item
