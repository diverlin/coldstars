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


struct UnresolvedDataPlanetoid
{
    int orbit_it;
};

namespace model {

class Planetoid : public SpaceObject
{
public:
    Planetoid() = default;
    ~Planetoid() = default;
    Planetoid(const std::string& data);
    std::string data() const;

    //void setOrbitCenter(const meti::vec3& orbitCenter) { m_orbitCenter = orbitCenter; }
    void setOrbitPhi(float orbitPhi) { m_orbitPhi = orbitPhi; }
    void setRadiusA(int radiusA) { m_radiusA = radiusA; }
    void setRadiusB(int radiusB) { m_radiusB = radiusB; }
    void setSpeed(float speed) { m_speed = speed; }
    void setClockwise(bool clockwise) { m_clockwise = clockwise; }

    //const meti::vec3& orbitCenter() const { return m_orbitCenter; }
    float orbitPhi() const { return m_orbitPhi; }
    int radiusA() const { return m_radiusA; }
    int radiusB() const { return m_radiusB; }
    float speed() const { return m_speed; }
    bool clockwise() const { return m_clockwise; }

private:
    //meti::vec3 m_orbitCenter;
    float m_orbitPhi = 0.0f;
    int m_radiusA = 0;
    int m_radiusB = 0;
    float m_speed = 0.0f;
    bool m_clockwise = false;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        //ar & m_orbitCenter;
        ar & m_orbitPhi;
        ar & m_radiusA;
        ar & m_radiusB;
        ar & m_speed;
        ar & m_clockwise;
    }
};

} // namespace model


namespace control {

class Planetoid : public SpaceObject
{
public:
    Planetoid(model::Planetoid*, descriptor::Planetoid*);
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

    model::Planetoid* m_model_planetoid = nullptr;
    descriptor::Planetoid* m_descriptor_planetoid = nullptr;

    model::Planetoid* model() const { return m_model_planetoid; }
    descriptor::Planetoid* descriptor() const { return m_descriptor_planetoid; }

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

