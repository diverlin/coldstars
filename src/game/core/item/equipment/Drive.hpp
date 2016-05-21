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

namespace item {
namespace equipment {

class Drive : public Base
{
public:
    Drive(const id_type& id);
    virtual ~Drive();

    void SetSpeedOrig(int speed_orig) { m_speed_orig = speed_orig; };
    void SetHyperOrig(int hyper_orig) { m_hyper_orig = hyper_orig; };

    int speed() const { return m_speed; };
    int hyper() const { return m_hyper; };

    virtual void updateProperties();

    void CountPrice();

    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

private:
    int m_speed_orig = 0;
    int m_speed_add = 0;
    int m_speed = 0;

    int m_hyper_orig = 0;
    int m_hyper_add = 0;
    int m_hyper = 0;

    void virtual addUniqueInfo();
    std::string GetSpeedStr();
    std::string GetHyperStr();

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};

} // namespace equipment
} // namespace item
