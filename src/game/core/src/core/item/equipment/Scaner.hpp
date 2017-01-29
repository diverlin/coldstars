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

class ScanerBuilder;

namespace item {
namespace equipment {

class Scaner : public control::item::equipment::Base
{
public:
    Scaner(int_t id);
    virtual ~Scaner();

    int scan() const { return m_scan; }

    [[deprecated("move out")]]
    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

private:
    void setScanOrig(int scan_orig)  { m_scan_orig = scan_orig; }
    virtual void updateProperties();
    void countPrice();

    friend ScanerBuilder;

private:
    int m_scan_orig = 0;
    int m_scan_add = 0;
    int m_scan = 0;

    void virtual addUniqueInfo();
    std::string str();

    [[deprecated("move out")]]
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};

} // namespace equipment
} // namespace item

