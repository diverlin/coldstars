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

#include <core/spaceobject/SpaceObject.hpp>

#include <core/part/orbit.hpp>
#include <core/descriptor/spaceobject/Planet.hpp>
//#include <jeti/Render.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


namespace model {

class Planetoid : public SpaceObject
{
public:
    Planetoid() = default;
    ~Planetoid() = default;
    Planetoid(const std::string& data);
    std::string data() const;

    void setRadiusA(int radiusA) { m_radiusA = radiusA; }
    void setRadiusB(int radiusB) { m_radiusB = radiusB; }

    int radiusA() const { return m_radiusA; }
    int radiusB() const { return m_radiusB; }

    Info info() const override {
        Info result = SpaceObject::info();
        result.push_back(std::make_pair("model::Planetoid", ""));
        result.push_back(std::make_pair("radiusA", std::to_string(m_radiusA)));
        result.push_back(std::make_pair("radiusB", std::to_string(m_radiusB)));
        return result;
    }

private:
    int m_radiusA = 0;
    int m_radiusB = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_radiusA;
        ar & m_radiusB;
    }
};

} // namespace model


namespace control {

class Planetoid : public SpaceObject
{
public:
    Planetoid(descriptor::Planetoid*, model::Planetoid*);
    virtual ~Planetoid();

    void calibrateOrbit(float offset_radius = 0);

    Orbit& orbit() { return m_orbit; }   // !!!
    const Orbit& orbit() const { return m_orbit; }

    void initOrbit(int it=0);

protected:
    virtual void putChildrenToGarbage() const {}

    virtual void _postDeathUniqueEvent(bool);
    void _updatePosition();

private:
    Orbit m_orbit;

    descriptor::Planetoid* m_descriptor_planetoid = nullptr;
    model::Planetoid* m_model_planetoid = nullptr;

    descriptor::Planetoid* descriptor() const { return m_descriptor_planetoid; }
    model::Planetoid* model() const { return m_model_planetoid; }

    void __createOrbit();
};

} // namespace control



//class Planetoid : public SpaceObject
//{
//public:
//    Planetoid();
//    virtual ~Planetoid();

//    //void setPlanetDescriptor(const PlanetDescriptor& planet_descriptor) { m_planetDescriptor = planet_descriptor; }

//    Orbit& orbit() { return m_orbit; }   // !!!
//    const Orbit& orbit() const { return m_orbit; }
//    //const PlanetDescriptor& planetDescriptor() const { return m_planetDescriptor; }

//    void bindParent(const SpaceObject* const, int);

//    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;

//protected:
//    virtual void putChildrenToGarbage() const {}

//    virtual void _postDeathUniqueEvent(bool);
//    void _updatePosition();

//    UnresolvedDataPlanetoid data_unresolved_Planetoid;
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

//private:
//    descriptor::Planet m_planet_descriptor;
//    Orbit m_orbit;

//    void __createOrbit();
//};

