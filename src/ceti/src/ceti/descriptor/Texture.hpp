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
    Association()
    {}

public:
    void setRace(const std::string& race) { m_race = race; }
    void setType(const std::string& type) { m_type = type; }
    void setSubtype(const std::string& subtype) { m_subtype = subtype; }
    void setName(const std::string& name) { m_name = name; }
    void setColor(const std::string& color) { m_color = color; }

private:
    std::string m_race = "";
    std::string m_type = "";
    std::string m_subtype = "";
    std::string m_name = "";
    std::string m_color = "";

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_race;
        ar & m_type;
        ar & m_subtype;
        ar & m_name;
        ar & m_color;
    }
};


class Material : public Base
{
public:
//    Material(int type,
//            const std::string& path,
//            bool alpha = true);

    Material(int_t type = -1);
    Material(const std::string& data);
    ~Material();

    std::string data() const;

    bool operator==(const Material& rhs) const;

    void setAssociation(const Association& association) { m_association = association; }
    void setPath(const std::string& path) { m_path = path; }
    void setAlpha(bool alpha) { m_alpha = alpha; }
    void setCol(int col) { m_col = col; }
    void setRow(int row) { m_row = row; }
    void setFps(float fps) { m_fps = fps; }
    void setAutoRotated(bool auto_rotated) { m_autoRotated = auto_rotated; }
    void setBrightThreshold(float brightThreshold) { m_brightThreshold = brightThreshold; }

    const std::string& path() const { return m_path; }

    bool animated() const { return (m_col !=1 || m_row != 1); }

    int col() const { return m_col; }
    int row() const { return m_row; }
    float fps() const { return m_fps; }

private:
    std::string m_path = "";
    bool m_alpha = true;
    int m_col = 1;
    int m_row = 1;
    float m_fps = 1.0f;
    bool m_autoRotated = false;
    float m_brightThreshold = 1.0f;
    Association m_association;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_path;
        ar & m_alpha;
        ar & m_col;
        ar & m_row;
        ar & m_fps;
        ar & m_autoRotated;
        ar & m_brightThreshold;
        ar & m_association;
    }
};

} // namespace descriptor
} // namespace ceti
