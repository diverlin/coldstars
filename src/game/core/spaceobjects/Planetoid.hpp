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

#include <spaceobjects/SpaceObject.hpp>
#include <parts/orbit.hpp>
#include <descriptors/PlanetDescriptor.hpp>
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

    int_t descriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & descriptor;
    }
};

} // namespace model


namespace control {

class Planetoid : public SpaceObject
{
public:
    Planetoid(model::Planetoid* model);
    virtual ~Planetoid();

    void setPlanetDescriptor(int_t descriptor);

    Orbit& orbit() { return m_orbit; }   // !!!
    const Orbit& orbit() const { return m_orbit; }
    PlanetDescriptor* descriptor() const;

    void bindParent(const SpaceObject* const, int);

protected:
    virtual void putChildrenToGarbage() const {}

    virtual void _postDeathUniqueEvent(bool);
    void _updatePosition();

private:
    model::Planetoid* m_model_planetoid = nullptr;
    Orbit m_orbit;
    PlanetDescriptor* m_descriptor = nullptr;

    model::Planetoid* model() const { return m_model_planetoid; }

    void __createOrbit();
};

} // namespace control



class Planetoid : public SpaceObject 
{
public:
    Planetoid();
    virtual ~Planetoid();

    void setPlanetDescriptor(const PlanetDescriptor& planet_descriptor) { m_planetDescriptor = planet_descriptor; }

    Orbit& orbit() { return m_orbit; }   // !!!
    const Orbit& orbit() const { return m_orbit; }
    const PlanetDescriptor& planetDescriptor() const { return m_planetDescriptor; }

    void bindParent(const SpaceObject* const, int);

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;

protected:
    virtual void putChildrenToGarbage() const {}

    virtual void _postDeathUniqueEvent(bool);
    void _updatePosition();

    UnresolvedDataPlanetoid data_unresolved_Planetoid;
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    PlanetDescriptor m_planetDescriptor;
    Orbit m_orbit;

    void __createOrbit();
};

