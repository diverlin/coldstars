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

#include <core/spaceobject/Planetoid.hpp>

#include <type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace core {

class PlanetModel : public PlanetoidModel {

public:
    PlanetModel(int_t, int_t);
    PlanetModel(const std::string& data);
    ~PlanetModel() override = default;
    std::string data() const override final;

    void setPopulation(int_t population)  { m_population = population; }
    void setLand(int_t land)  { m_land = land; }

    int_t population() const { return m_population; }
    int_t land() const { return m_land; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = PlanetoidModel::info();
        result.add("Planet");
        result.add("land", m_land);
        result.add("population", m_population);
        return result;
    }

private:
    int_t m_land = NONE;
    int_t m_population = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<PlanetoidModel>(*this);
        ar & m_land;
        ar & m_population;
    }
};

} // namespace core

