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

namespace control {
class ItemSlot; 
} // namespace control


namespace descriptor {
namespace item {

class Base : public ::descriptor::Base, public ceti::descriptor::BaseView
{
public:
    Base() = default;
    ~Base() = default;

    void setRace(type::race race) { m_race = race; }
    void setTech(type::tech tech) { m_tech = tech; }
    void setCondition(int condition) { m_condition = condition; }
    void setDeterioration(int deterioration) { m_deterioration = deterioration; }
    void setMass(int mass) { m_mass = mass; }
    void setPrice(int price) { m_price = price; }

    type::race race() const { return m_race; }
    type::tech tech() const { return m_tech; }
    int condition() const { return m_condition; }
    int deterioration() const { return m_deterioration; }
    int mass() const { return m_mass; }
    int price() const { return m_price; }

private:
    type::race m_race = type::race::R0_ID;
    type::tech m_tech = type::tech::NONE;
    int m_condition = 0;
    int m_deterioration = 0;
    int m_mass = 0;
    int m_price = 0;

protected:
    std::string info() const {
        std::string result = "descriptor::item::Base:\n";
        result += std::string(" race = ") + to_string(m_race) + "\n";
        result += std::string(" tech = ") + to_string(m_tech) + "\n";
        result += std::string(" condition = ") + std::to_string(m_condition) + "\n";
        result += std::string(" deterioration = ") + std::to_string(m_deterioration) + "\n";
        result += std::string(" mass = ") + std::to_string(m_mass) + "\n";
        result += std::string(" price = ") + std::to_string(m_price) + "\n";
        result += ceti::descriptor::BaseView::info();
        result += ::descriptor::Base::info();
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::descriptor::Base>(*this);
        ar & boost::serialization::base_object<ceti::descriptor::BaseView>(*this);
        ar & m_race;
        ar & m_tech;
        ar & m_condition;
        ar & m_deterioration;
        ar & m_mass;
        ar & m_price;
    }
};

} // namespace item
} // namespace descriptor

namespace model {
namespace item {

class Base : public ::model::Base
{
public:
    Base() = default;
    ~Base() = default;

    void setParentSubTypeId(type::entity parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
    void setItemCommonData(const ItemCommonData& data_item)
    {
        m_data = data_item;
        m_deterioration = data_item.deterioration;
        setCondition(data_item.condition_max);
    }
    void setSlot(int_t slot)  { m_slot = slot; }
    void setCondition(int condition) { m_condition = condition; }

    int_t slot() const { return m_slot; }

    int mass()          const { return m_data.mass; }
    int condition()     const { return m_condition; }
    int price()         const { return m_price; }
    int basePrice()     const { return m_data.price; }
    int deterioration() const { return m_data.deterioration; }

    int modulesNum() const { return m_data.modules_num; }
    int descriptorType() const { return m_data.descriptor_type; }

    type::tech tech() const { return m_data.tech; }

    type::entity parentSubtype() const { return m_parent_subtype_id; }
    type::race race() const { return m_race_id; }

    int lockedTurns() const { return m_locked_turns; }

private:
    type::race m_race_id = type::race::NONE_ID;

    int m_locked_turns = 0;
    int m_condition = 0;
    int m_price = 0;
    int m_deterioration = 0;

    type::entity m_parent_subtype_id = type::entity::NONE_ID;

    ItemCommonData m_data;

    int_t m_slot = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::model::Base>(*this);
        // ..
    }
};

} // naemspace item
} // namespace model



namespace control {
namespace item {

class Base : public ::control::Base
{
public:
    Base();
    virtual ~Base();

    virtual void putChildrenToGarbage() const {}

    void setParentSubTypeId(type::entity parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
    void setItemCommonData(const ItemCommonData& data_item)
    {
        m_data = data_item;
        m_deterioration = data_item.deterioration;
        setCondition(data_item.condition_max);
    }
    void setSlot(control::ItemSlot* slot)  { m_slot = slot; }
    void setCondition(int condition) { m_condition = condition; }

    control::ItemSlot* slot() const { return m_slot; }

    virtual int radius() const { return 0; }
    virtual int damage() const { return 0; }

    int mass()          const { return m_data.mass; }
    int condition()     const { return m_condition; }
    int price()         const { return m_price; }
    int basePrice()     const { return m_data.price; }
    int deterioration() const { return m_data.deterioration; }

    int modulesNum() const { return m_data.modules_num; }
    int descriptorType() const { return m_data.descriptor_type; }

    type::tech tech() const { return m_data.tech; }

    type::entity parentSubtype() const { return m_parent_subtype_id; }
    type::race race() const { return m_race_id; }

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
    virtual void updateInStatic() { _updateLock(); }

    //        void UpdateInfo();

    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);
    //        void RenderKorpus(const jeti::Renderer&, const ceti::Box2D&);
    //        void RenderInfo(const jeti::Renderer&, const glm::vec2&);

protected:
    type::race m_race_id = type::race::NONE_ID;

    int m_locked_turns = 0;
    int m_condition = 0;
    int m_price = 0;
    int m_deterioration = 0;

    type::entity m_parent_subtype_id = type::entity::NONE_ID;

    ItemCommonData m_data;
//    UnresolvedDataBase m_data_unresolved_Base;
    //        InfoTable info;

    void _updateLock();

    virtual void AddCommonInfo()=0;
    virtual void addUniqueInfo()=0;

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    control::ItemSlot* m_slot = nullptr;
};

} // namespace item
} // namespace control
