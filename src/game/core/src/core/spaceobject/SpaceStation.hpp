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

namespace descriptor {
class SpaceStation;
} // namespace descriptor

namespace model {
class SpaceStation;
} // namespace descriptor

#include <core/model/spaceobject/Vehicle.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/dock/Land.hpp>
   
   
namespace control {

class SpaceStation : public Vehicle
{
public:
    SpaceStation(model::SpaceStation*, descriptor::SpaceStation*);
    virtual ~SpaceStation();

    [[warning("incapsulate this shit")]]
    Land* const innerLand() const { return m_innerLand; }

    void bindLand(Land* land);

    virtual void UpdateInSpace(int, bool) override final;

    //        void RenderInSpace(const jeti::Renderer&, float);

    model::SpaceStation* model() const { return m_model_spacestation; }
    descriptor::SpaceStation* descriptor() const { return m_descriptor_spacestation; }

private:
    model::SpaceStation* m_model_spacestation = nullptr;
    descriptor::SpaceStation* m_descriptor_spacestation = nullptr;

    Land* m_innerLand = nullptr;

    //        void UpdateRenderStuff_2D();
    //        virtual void UpdateInfo() override final;

    virtual void putChildrenToGarbage() const override final;
};

} // namespace control



//class SpaceStation : public Vehicle
//{
//public:
//    SpaceStation(int);
//    virtual ~SpaceStation();

//    Land* const land() const { return m_Land; };

//    void bindLand(Land* land);

//    virtual void UpdateInSpace(int, bool) override final;

//    //        void RenderInSpace(const jeti::Renderer&, float);

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    Land* m_Land;

//    //        void UpdateRenderStuff_2D();
//    //        virtual void UpdateInfo() override final;

//    virtual void putChildrenToGarbage() const override final;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};




