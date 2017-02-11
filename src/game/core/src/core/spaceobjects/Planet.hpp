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

#include "Planetoid.hpp"

#include <type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Land;
class Vehicle;

namespace model {

class Planet : public Planetoid {

public:
    Planet();
    ~Planet() = default;
    Planet(const std::string& data);
    std::string data() const;

    void setPopulation(int_t population)  { m_population = population; }
    void setLand(int_t land)  { m_land = land; }

    int_t population() const { return m_population; }
    int_t land() const { return m_land; }

private:
    int_t m_land = NONE;
    int_t m_population = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Planetoid>(*this);
        ar & m_land;
        ar & m_population;
    }
};

} // namespace model


namespace control {

class Planet : public Planetoid
{
public:
    Planet(model::Planet*);
    virtual ~Planet();

    void BindLand(Land*);

    [[warning("check const")]]
    Land* land();

    [[warning("check const")]]
//    void addVehicle(Vehicle*);

    void updateInSpace(int, bool);
    void updateInSpaceInStatic();

    model::Planet* model() const { return m_model_planet; }

private:
    model::Planet* m_model_planet = nullptr;
    Land* m_land = nullptr;

    [[deprecated("ugly, remove")]]
    virtual void putChildrenToGarbage() const override final;

    //        virtual void UpdateInfo() override final;

    void _postDeathUniqueEvent(bool);
};

} // namespace control




//class Planet : public Planetoid
//{
//public:
//    Planet(int);
//    virtual ~Planet();

//    void BindLand(Land*);
//    void SetPopulation(unsigned long int population)  { m_population = population; }

//    unsigned long int GetPopulation() const { return m_population; }
//    Land* const GetLand() const { return m_land; }

//    void AddVehicle(Vehicle*) const;

//    void UpdateInSpace(int, bool);
//    void UpdateInSpaceInStatic();

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    Land* m_land;

//    unsigned long int m_population;

//    virtual void putChildrenToGarbage() const override final;

//    //        virtual void UpdateInfo() override final;

//    void _postDeathUniqueEvent(bool);

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};






