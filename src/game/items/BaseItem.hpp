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

#ifndef BASEITEM_HPP
#define BASEITEM_HPP

#include <common/BaseDrawable.hpp>

#include <types/MyInt.hpp>
#include <types/TechLevelTypes.hpp>
#include <types/RaceTypes.hpp>

#include <text/InfoTable.hpp>

class ItemSlot; 
class Box2D;

struct ItemCommonData 
{
    ItemCommonData(): 
    tech_level(TYPE::TECHLEVEL::NONE_ID),
    modules_num_max(0),
    condition_max(0), 
    deterioration_normal(0),
    deterioration_overload_rate(0.0f),
    mass(0)
    {};

    TYPE::TECHLEVEL tech_level; 
    unsigned int modules_num_max; 
    unsigned int condition_max; 
    unsigned int deterioration_normal;
    float deterioration_overload_rate;
    unsigned int mass; 
};

struct UnresolvedDataUniqueBaseItem
{
    std::string textureOb_path;
    INTLONGEST item_slot_id;
};

class BaseItem : public BaseDrawable
{
    public:
        BaseItem();
        virtual ~BaseItem();
        
        virtual void PutChildsToGarbage() const {};
        
        void SetParentSubTypeId(TYPE::ENTITY parent_subtype_id) { this->parent_subtype_id = parent_subtype_id; };
        void SetItemCommonData(const ItemCommonData& data_item) { this->data_item = data_item; deterioration = data_item.deterioration_normal; };
        void SetItemSlot(ItemSlot* item_slot)  { this->item_slot = item_slot; };
        void SetCondition(int condition) { this->condition = condition; };
        
        ItemSlot* GetItemSlot() const { return item_slot; };
                                    
        unsigned int GetMass()          const { return data_item.mass; };
        unsigned int GetCondition()     const { return condition; };
        int GetPrice()                  const { return price; };
        TYPE::ENTITY GetParentSubTypeId() const { return parent_subtype_id; };
        
        bool GetDamaged()       const { return (condition < 0); };
        bool GetLocked()    const { return (locked_turns > 0); };
        int GetFunctioning()    const { return ( (condition > 0) and (locked_turns == 0) ); };
        
        void UseNormalDeterioration();
        void UseOverloadDeterioration();
        
        void DamageEvent();
        
        void DeteriorationEvent(); 
        void LockEvent(int); 
        
        bool RepairEvent();
        
        virtual void UpdateProperties() {};
        virtual void UpdateInStatic() { UpdateLock(); };
        
        void UpdateInfo();
        
        virtual void Render(const Box2D&, const Vec2<float>&, bool draw_text = true);
        void RenderKorpus(const Box2D&);
        void RenderInfo(const Vec2<float>&); 

    protected:
        TYPE::RACE race_id;
        
        int locked_turns;
        int condition;
        int price;
        
        int deterioration;
        
        TYPE::ENTITY parent_subtype_id;
        
        ItemCommonData data_item;
        
        ItemSlot* item_slot;
        
        InfoTable info;  
        
        UnresolvedDataUniqueBaseItem data_unresolved_BaseItem;
        
        void UpdateLock();
        
        virtual void AddCommonInfo()=0;
        virtual void AddUniqueInfo()=0;   
        
        void SaveDataUniqueBaseItem(boost::property_tree::ptree&, const std::string&) const; 
        void LoadDataUniqueBaseItem(const boost::property_tree::ptree&); 
        void ResolveDataUniqueBaseItem();                   
};

#endif
