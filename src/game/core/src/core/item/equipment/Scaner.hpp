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

#include "Equipment.hpp"

namespace core {
class ScanerDescr;
} // namespace core

namespace core {
class ScanerModel;
} // namespace model

namespace core {
namespace control {

class Scaner : public Equipment
{
public:
    Scaner(ScanerDescr*, ScanerModel*);
    virtual ~Scaner() = default;

private:
    virtual void updateProperties();

public:
    ScanerModel* model() const { return m_model_scaner; }
    ScanerDescr* descriptor() const { return m_descriptor_scaner; }

private:
    ScanerModel* m_model_scaner = nullptr;
    ScanerDescr* m_descriptor_scaner = nullptr;

    int m_scan_add = 0;

    void virtual addUniqueInfo();

    std::string scanStr();
};

} // namespace control
} // namespace core
