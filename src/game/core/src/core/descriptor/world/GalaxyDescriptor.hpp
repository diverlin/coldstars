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

namespace core {

struct GalaxyDescr : public BaseDescr
{
public:
    GalaxyDescr();
    GalaxyDescr(const std::string&);
    ~GalaxyDescr() override = default;
    std::string data() const override final;

    bool isMinimal() const { return m_starsystemsNum == 2; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = BaseDescr::info();
        result.add("Galaxy");
        result.add("starsystemsNum", std::to_string(m_starsystemsNum));
        return result;
    }

    void setStarSystemsNum(int num) { m_starsystemsNum = num; }
    int starsystemsNum() const { return m_starsystemsNum; }

private:
    int m_starsystemsNum;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<BaseDescr>(*this);
        ar & m_starsystemsNum;
    }
}; 

} // namespace core







