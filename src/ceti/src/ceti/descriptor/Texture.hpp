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

#include "Base.hpp"

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

#include <string>

namespace ceti {
namespace descriptor {

class Association {
public:
    Association():
        m_race(0)
      , m_type(0)
    {}

    Association(int race, int type = 0):
        m_race(race)
      , m_type(type)
    {}

private:
    int m_race = 0;
    int m_type = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_race;
        ar & m_type;
    }
};

class Animation {
public:
    Animation():
        m_col(1)
      , m_row(1)
      , m_fps(1.0f)
    {}

    Animation(int col, int row, float fps):
        m_col(col)
      , m_row(row)
      , m_fps(fps)
    {}

    bool animated() const { return (m_col !=1 || m_row != 1); }

    int col() const { return m_col; }
    int row() const { return m_row; }
    float fps() const { return m_fps; }

private:
    int m_col = 1;
    int m_row = 1;
    float m_fps = 1.0f;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_col;
        ar & m_row;
        ar & m_fps;
    }
};

class Material : public Base
{
public:
    Material(int type,
            const std::string& path,
            bool alpha = true);

    Material(const std::string& data);
    ~Material();

    std::string data() const;

    bool operator==(const Material& rhs) const;

    const std::string& path() const { return m_path; }


    void setAnimation(const Animation& animation) { m_animation = animation; }
    void setAssociation(const Association& association) { m_association = association; }

private:
    std::string m_path = "";
    bool m_alpha = true;
    Animation m_animation;
    Association m_association;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_path;
        ar & m_alpha;
        ar & m_animation;
        ar & m_association;
    }
};

} // namespace descriptor
} // namespace ceti
