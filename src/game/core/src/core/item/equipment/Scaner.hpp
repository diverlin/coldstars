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

namespace descriptor {
namespace item {
class Scaner;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Scaner;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Scaner : public Equipment
{
public:
    Scaner(model::item::Scaner*);
    virtual ~Scaner() = default;

    int scan() const { return m_scan; }

private:
    void setScanOrig(int scan_orig)  { m_scan_orig = scan_orig; }
    virtual void updateProperties();
    void countPrice();

protected:
    model::item::Scaner* model() const { return m_model_scaner; }
    descriptor::item::Scaner* descriptor() const { return m_descriptor_scaner; }

private:
    model::item::Scaner* m_model_scaner = nullptr;
    descriptor::item::Scaner* m_descriptor_scaner = nullptr;

    int m_scan_orig = 0;
    int m_scan_add = 0;
    int m_scan = 0;

    void virtual addUniqueInfo();

    std::string scanStr();
};

} // namespace item
} // namespace control
