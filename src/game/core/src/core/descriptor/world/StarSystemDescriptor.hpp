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

#include <core/descriptor/Base.hpp>

#include <ceti/StringUtils.hpp>

#include <vector>
#include <boost/serialization/vector.hpp>


namespace ENTITY {
namespace STARSYSTEM {
const int JUMPRADIUS = 1200;

const int PLANET_NUM_MIN = 3;
const int PLANET_NUM_MAX = 5;

const int SHIP_INIT_MIN = 4;
const int SHIP_INIT_MAX = 7;
const int SHIPENEMY_INIT_MIN = 50;
const int SHIPENEMY_INIT_MAX = 100;

const int SPACESTATION_NUM_MIN = 1;
const int SPACESTATION_NUM_MAX = 3;

const int DISTANT_NEBULA_MIN = 6;
const int DISTANT_NEBULA_MAX = 8;

} // namespace STARSYSTEM
} // namespace ENTITY

//const int CONTAINER_NUM_MAX_DEFAULT = 400;

namespace core {

struct StarSystemDescr : public BaseDescr
{
public:
    StarSystemDescr();
    StarSystemDescr(const std::string&);
    ~StarSystemDescr() override = default;
    std::string data() const override final;

    void setStarsNum(int starsNum) { m_starsNum = starsNum; }
    void setPlanetsNum(int planetsNum) { m_planetsNum = planetsNum; }

    int starsNum() const { return m_starsNum; }
    int planetsNum() const { return m_planetsNum; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = BaseDescr::info();
        result.add("StarSystem");
        result.add("starsNum", m_starsNum);
        result.add("planetsNum", m_planetsNum);
        return result;
    }

private:
    int m_starsNum = 0;
    int m_planetsNum = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<BaseDescr>(*this);
        ar & m_starsNum;
        ar & m_planetsNum;
    }
}; 

} // namespace core





