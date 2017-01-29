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

#include "Land.hpp"

namespace item {
class Base;
} // namespace item


namespace control {
class ItemSlot;
} // namespace control

struct UnresolvedDataNatureLand {
    std::string textureOb_background_path;
};

class NatureLand : public Land
{
public:
    NatureLand(int);
    virtual ~NatureLand();

    virtual void putChildrenToGarbage() const;

    //void SetTextureObBackground(jeti::control::TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };

    //jeti::control::TextureOb* GetBackgroundTextureOb() const { return textureOb_background; };

    void AddItemSlot(control::ItemSlot*);

    bool AddItem(item::Base*);
    bool CanAcceptNewItem() const;

    virtual bool AddVehicle(Vehicle*);
    virtual bool RemoveVehicle(Vehicle*);

    virtual bool GetPermissionToLand() const;

    virtual void UpdateInStatic();

    virtual std::string GetDockVehicleStr() const;

    void Save(boost::property_tree::ptree&) const;
    void Load(const boost::property_tree::ptree&);
    void Resolve();

private:
    //jeti::control::TextureOb* textureOb_background;

    std::vector<Vehicle*> m_vehicles;
    std::vector<control::ItemSlot*> m_itemslots;

    UnresolvedDataNatureLand data_unresolved_NatureLand;
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

    friend class GuiNatureLand;
};


