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

#include <core/item/BaseItem.hpp>

#ifdef USE_MODULES
#include <core/item/modules/BaseModule.hpp>
#endif

namespace control {
namespace item {

class Equipment : public control::item::Base
{
public:
    Equipment();
    virtual ~Equipment();

    virtual void putChildrenToGarbage() const;

#ifdef USE_MODULES
    bool InsertModule(BaseModule*);
#endif
    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);

protected:
#ifdef USE_MODULES
    std::vector<BaseModule*> modules_vec;
#endif

    virtual void AddCommonInfo();

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace item
} // namespace control
