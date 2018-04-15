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

#include <core/spaceobject/Vehicle.hpp>

namespace core {
class ShipDescr;
} // namespace core

namespace model {
class ShipModel;
} // namespace model

namespace core {
namespace control {

class Ship : public Vehicle
{
public:
    Ship(ShipDescr*, model::ShipModel*);
    ~Ship() override final;

    virtual void update(int time=1) override final;

    //        virtual void UpdateInfo() override final;

    //        void RenderInSpace(const jeti::Renderer&, float);
    //        void RenderAtPlanet(const jeti::Renderer&, const glm::vec3&);

    ShipDescr* descriptor() const { return m_descriptor_ship; }
    model::ShipModel* model() const { return m_model_ship; }

private:
    ShipDescr* m_descriptor_ship = nullptr;
    model::ShipModel* m_model_ship = nullptr;
};

} // namespace control
} // namespace core

//class Ship : public Vehicle
//{
//public:
//    Ship(int);
//    virtual ~Ship();

//    virtual void UpdateInSpace(int, bool) override final;

//    //        virtual void UpdateInfo() override final;

//    //        void RenderInSpace(const jeti::Renderer&, float);
//    //        void RenderAtPlanet(const jeti::Renderer&, const glm::vec3&);

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};


