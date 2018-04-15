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

class MaterialDescr : public BaseDescr
{
public:
    MaterialDescr() = default;
    ~MaterialDescr() = default;

    void setTexturePath(const std::string& path) { m_texturePath = path; }
    void setNormalmapPath(const std::string& path) { m_normalmapPath = path; }
    void setAlpha(bool alpha) { m_alpha = alpha; }
    void setCol(int col) { m_col = col; }
    void setRow(int row) { m_row = row; }
    void setFps(float fps) { m_fps = fps; }
    void setAutoRotated(bool auto_rotated) { m_autoRotated = auto_rotated; }
    void setBrightThreshold(float brightThreshold) { m_brightThreshold = brightThreshold; }

    const std::string& texturePath() const { return m_texturePath; }
    const std::string& normalmapPath() const { return m_normalmapPath; }
    bool useAlpha() const { return m_alpha; }
    bool animated() const { return (m_col !=1 || m_row != 1); }
    bool autoRotated() const { return m_autoRotated; }
    float brightThreshold() const { return m_brightThreshold; }
    int col() const { return m_col; }
    int row() const { return m_row; }
    float fps() const { return m_fps; }

private:
    std::string m_texturePath = "";
    std::string m_normalmapPath = "";
    bool m_alpha = true;
    int m_col = 1;
    int m_row = 1;
    float m_fps = 1.0f;
    bool m_autoRotated = false;
    float m_brightThreshold = 1.0f;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseDescr>(*this);
        ar & m_texturePath;
        ar & m_normalmapPath;
        ar & m_alpha;
        ar & m_col;
        ar & m_row;
        ar & m_fps;
        ar & m_autoRotated;
        ar & m_brightThreshold;
    }
};

} // namespace ceti
