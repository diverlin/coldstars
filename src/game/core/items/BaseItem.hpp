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


class ItemSlot; 
namespace ceti {
class Box2D;
}

struct ItemCommonData 
{
    ItemCommonData()
    {}

    TYPE::TECHLEVEL tech_level = TYPE::TECHLEVEL::NONE_ID;
    unsigned int modules_num_max = 0;
    unsigned int condition_max = 0;
    unsigned int deterioration_normal = 0;
    float deterioration_overload_rate = 0.0f;
    unsigned int mass = 0;
};

struct UnresolvedDataBaseItem
{
    std::string textureOb_path;
    IDTYPE item_slot_id;
};

class BaseItem : public ceti::Orientation, public Base
{
    public:
        BaseItem();
        virtual ~BaseItem();
        
        virtual void putChildrenToGarbage() const {}
        
        void setParentSubTypeId(TYPE::ENTITY parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
        void setItemCommonData(const ItemCommonData& data_item) { m_data_item = data_item; m_deterioration = data_item.deterioration_normal; }
        void setItemSlot(ItemSlot* item_slot)  { m_item_slot = item_slot; }
        void setCondition(int condition) { m_condition = condition; }
        
        ItemSlot* itemSlot() const { return m_item_slot; }
                                    
        unsigned int mass()          const { return m_data_item.mass; }
        unsigned int condition()     const { return m_condition; }
        int price()                  const { return m_price; }
        TYPE::ENTITY parentSubTypeId() const { return m_parent_subtype_id; }
        
        bool isDamaged()    const { return (m_condition < 0); }
        bool isLocked()     const { return (m_locked_turns > 0); }
        int isFunctioning() const { return ( !isDamaged() && !isLocked() ); }
        
        void useNormalDeterioration();
        void useOverloadDeterioration();
        
        void damageEvent();
        void deteriorationEvent();
        void lockEvent(int);
        bool repairEvent();
        
        virtual void updateProperties() {}
        virtual void updateInStatic() { updateLock(); }
        
//        void UpdateInfo();
        
//        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);
//        void RenderKorpus(const jeti::Renderer&, const ceti::Box2D&);
//        void RenderInfo(const jeti::Renderer&, const glm::vec2&);

    protected:
        TYPE::RACE m_race_id = TYPE::RACE::NONE_ID;
        
        int m_locked_turns = 0;
        int m_condition = 0;
        int m_price = 0;
        
        int m_deterioration = 0;
        
        TYPE::ENTITY m_parent_subtype_id = TYPE::ENTITY::NONE_ID;
        
        ItemCommonData m_data_item;
        UnresolvedDataBaseItem m_data_unresolved_BaseItem;
//        InfoTable info;

        void updateLock();
        
        virtual void AddCommonInfo()=0;
        virtual void AddUniqueInfo()=0;   
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const; 
        void LoadData(const boost::property_tree::ptree&); 
        void ResolveData();

    private:
        ItemSlot* m_item_slot = nullptr;
};

