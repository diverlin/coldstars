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

class Land;
class Vehicle;


namespace model {

class Planet {
public:
    Land* land = nullptr;
    unsigned long int population = 0;
};

} // namespace model


namespace controller {

class Planet : public Planetoid
{
public:
    Planet(model::Planet*);
    virtual ~Planet();

    void BindLand(Land*);
    void SetPopulation(unsigned long int population)  { model()->population = population; }

    unsigned long int GetPopulation() const { return model()->population; }
    Land* const GetLand() const { return model()->land; }

    void AddVehicle(Vehicle*) const;

    void UpdateInSpace(int, bool);
    void UpdateInSpaceInStatic();

private:
    model::Planet* m_model_planet = nullptr;

    model::Planet* model() const { return m_model_planet; }

    [[deprecated("ugly, remove")]]
    virtual void putChildrenToGarbage() const override final;

    //        virtual void UpdateInfo() override final;

    void _postDeathUniqueEvent(bool);
};

} // namespace controller

class Planet : public Planetoid
{
public:
    Planet(int);
    virtual ~Planet();

    void BindLand(Land*);
    void SetPopulation(unsigned long int population)  { m_population = population; }

    unsigned long int GetPopulation() const { return m_population; }
    Land* const GetLand() const { return m_land; }

    void AddVehicle(Vehicle*) const;

    void UpdateInSpace(int, bool);
    void UpdateInSpaceInStatic();

    virtual void Save(boost::property_tree::ptree&) const override final;
    virtual void Load(const boost::property_tree::ptree&) override final;
    virtual void Resolve() override final;

private:
    Land* m_land;

    unsigned long int m_population;

    virtual void putChildrenToGarbage() const override final;

    //        virtual void UpdateInfo() override final;

    void _postDeathUniqueEvent(bool);

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};







