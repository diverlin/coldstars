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

#include <core/item/BaseItem.hpp>

#ifdef USE_MODULES
#include <core/item/modules/BaseModule.hpp>
#endif


namespace descriptor {
namespace item {

class BaseEquipment : public descriptor::item::Base
{
public:
    BaseEquipment() = default;
    ~BaseEquipment() = default;

    void setModules(int modules) { m_modules = modules; }

    int modules() const { return m_modules; }

protected:
    std::string info() const {
        std::string result = descriptor::item::Base::info();
        result += "descriptor::item::BaseEquipment:\n";
        result += std::string(" modules = ") + std::to_string(m_modules) + "\n";
        return result;
    }

private:
    int m_modules = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<descriptor::item::Base>(*this);
        ar & m_modules;
    }
};

} // namespace item
} // namespace descriptor



namespace model {
namespace item {

class BaseEquipment : public model::item::Base
{
public:
    BaseEquipment() = default;
    ~BaseEquipment() = default;

private:
    // ..

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<model::item::Base>(*this);
    }

};

} // namespace item
} // namespace model

namespace control {
namespace item {

class BaseEquipment : public control::item::Base
{
public:
    BaseEquipment();
    virtual ~BaseEquipment();

    virtual void putChildrenToGarbage() const;

#ifdef USE_MODULES
    bool InsertModule(BaseModule*);
#endif
    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);

protected:
#ifdef USE_MODULES
    std::vector<BaseModule*> modules_vec;
#endif

    virtual void AddCommonInfo();

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace item
} // namespace control

