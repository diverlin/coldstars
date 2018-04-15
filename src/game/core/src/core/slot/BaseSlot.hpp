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

//#include <core/Base.hpp>

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

namespace core {

namespace control {
class Vehicle;
class Base;
} // namespace control

class BaseSlot
{
public:
    BaseSlot() = default;
    virtual ~BaseSlot() = default;

    void setId(int id) { m_id = id; }
    void setOwner(control::Base* owner) { m_owner = owner; }
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setSelected(bool selected) { m_selected = selected; }
    void selectEvent() { m_selected = true; }
    void deselectEvent() { m_selected = false; }

    bool isSelected() const { return m_selected; }

    const glm::vec2& position() const { return m_position; }

    control::Vehicle* vehicleOwner() const;

    control::Base* owner() const { return m_owner; }

private:
    int m_id = 0;
    bool m_selected = false;

    control::Base* m_owner = nullptr;

    glm::vec2 m_position;
};

} // namespace core

//class BaseSlot : public ::control::Base
//{
//    public:
//        BaseSlot();
//        virtual ~BaseSlot();

////        void SetTextureOb(jeti::control::TextureOb* textureOb) { m_textureOb = textureOb; }
//        void setOwner(Base* owner) { m_owner = owner; }
//        void setPosition(const glm::vec2& position) { m_position = position; }
//        void selectEvent() { m_selected = true; }
//        void deselectEvent() { m_selected = false; }

//        bool isSelected() const { return m_selected; }

//        const glm::vec2& position() const { return m_position; }

//        Vehicle* vehicleOwner() const {
//            assert(m_owner);
//            assert(false);
////            Vehicle* vehicle = static_cast<Vehicle*>(m_owner);
////            assert(vehicle);
////            return vehicle;
//        }

//        Base* owner() const { return m_owner; }

//    protected:      // make private
//        bool m_selected;

//        jeti::control::Material* m_textureOb;

//        Base* m_owner;

//        glm::vec2 m_position;

//        UnresolvedDataBaseSlot unresolved_BaseSlot;
//        void SaveData(boost::property_tree::ptree&, const std::string&) const;
//        void LoadData(const boost::property_tree::ptree&);
//        void ResolveData();
//};

