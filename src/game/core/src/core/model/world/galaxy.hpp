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

#include <core/model/Base.hpp>

#include <meti/VectorUtils.hpp>

#include <ceti/Pack.hpp>

#include <boost/serialization/vector.hpp>

namespace core {
class GalaxyDescr;
} // namespace core


namespace core {

class GalaxyModel : public BaseModel {

public:
    GalaxyModel(int_t, int_t);
    GalaxyModel(const std::string& data);
    ~GalaxyModel() override = default;
    std::string data() const override final;

    void addStarSystem(int_t starsystem) { m_starsystems.add(starsystem); }
    const ceti::pack<int_t>& starsystems() const { return m_starsystems; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = BaseModel::info();
        result.add("starsystems", m_starsystems);
        return result;
    }

private:
    ceti::pack<int_t> m_starsystems;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<core::BaseModel>(*this);
        ar & m_starsystems;
    }
};

} // namespace core
