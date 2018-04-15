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

#include <boost/serialization/vector.hpp>


namespace core {

class SectorModel : public BaseModel
{
public:
    SectorModel(int_t, int_t);
    ~SectorModel() = default;
    SectorModel(const std::string& data);
    std::string data() const;

    bool operator==(const SectorModel& rhs) const;
    bool operator!=(const SectorModel& rhs) const;

    void setGalaxy(int_t galaxy)  { m_galaxy = galaxy; }
    void setPosition(const meti::vec3& center) { m_position = center; }

    int_t galaxy() const  { return m_galaxy; }
    const meti::vec3& position() const  { return m_position; }

    void add(int_t starsystem) { m_starsystems.push_back(starsystem); }

private:
    int_t m_galaxy = NONE;
    meti::vec3 m_position; // do we need this?

    std::vector<int_t> m_starsystems;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseModel>(*this);
        ar & m_galaxy;
        ar & m_position;
        ar & m_starsystems;
    }
};

} // namespace core
