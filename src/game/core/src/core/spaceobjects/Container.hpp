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

#include <core/spaceobjects/SpaceObject.hpp>

#include <ceti/type/IdType.hpp>

namespace control {
namespace item {
class Item;
} // namespace item
} // namespace control

namespace model {

class Container : public SpaceObject {

public:
    Container();
    ~Container() = default;
    Container(const std::string& data);
    std::string data() const;

    void setTargetPos(const glm::vec3& target_pos, float velocity)
    { m_targetPos = target_pos; m_velocity = velocity; }

private:
    int_t m_itemSlot = NONE;
    meti::vec3 m_targetPos;
    float m_velocity = 0.0f;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_itemSlot;
        ar & m_targetPos;
        ar & m_velocity;
    }
};

} // namespace model


namespace control {

class ItemSlot;

class Container : public SpaceObject
{
public:
    Container(model::Container*);
    virtual ~Container();

    void bindItemSlot(ItemSlot*);

    ItemSlot* const itemSlot() const { return m_itemSlot; }
    bool insertItem(control::item::Item*);

    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;

    virtual void _postDeathUniqueEvent(bool) override final;

    void updateInSpace(int, bool);

    void hit(int damage) override final;

    //        void Render(const jeti::Renderer&);

    model::Container* model() const { return m_model_container; }

private:
    model::Container* m_model_container = nullptr;
    ItemSlot* m_itemSlot = nullptr;

    //        virtual void UpdateInfo() override final;

    virtual void putChildrenToGarbage() const override final;
};

} // namespace control

//class Container : public SpaceObject
//{
//public:
//    Container(int_t id = NONE);
//    virtual ~Container();

//    void setTargetPos(const glm::vec3& target_pos, float velocity) { m_targetPos = target_pos; m_velocity = velocity; }
//    void bindItemSlot(ItemSlot*);

//    ItemSlot* const itemSlot() const { return m_itemSlot; }
//    bool insertItem(item::Base*);

//    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;

//    virtual void _postDeathUniqueEvent(bool) override final;

//    void updateInSpace(int, bool);

//    void hit(int damage) override final;

//    //        void Render(const jeti::Renderer&);

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    ItemSlot* m_itemSlot = nullptr;

//    glm::vec3 m_targetPos;
//    float m_velocity = 0.0f;

//    //        virtual void UpdateInfo() override final;

//    virtual void putChildrenToGarbage() const override final;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};


