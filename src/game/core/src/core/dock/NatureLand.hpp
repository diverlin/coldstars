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

namespace core {
class NatureLandDescr;
} // namespace core

namespace model {
class NatureLandModel;
} // namespace model


namespace core {

class ItemSlot;

namespace control {

class Item;

class NatureLand : public Land
{
public:
    NatureLand(NatureLandDescr*, model::NatureLandModel*);
    virtual ~NatureLand();

    virtual void putChildrenToGarbage() const;

    //void SetTextureObBackground(jeti::control::TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };

    //jeti::control::TextureOb* GetBackgroundTextureOb() const { return textureOb_background; };

    void add(ItemSlot*);

    bool add(control::Item*);
    bool canAcceptNewItem() const;

    bool add(Vehicle*) override final;
    bool remove(Vehicle*) override final;
    int shipsNum() const override final { return m_vehicles.size(); }

    virtual bool isAllowedToLand() const;

    virtual void updateInStatic();

    virtual std::string vehiclesStr() const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

    NatureLandDescr* descriptor() const { return m_descriptor_natureland; }
    model::NatureLandModel* model() const { return m_model_natureland; }

    const std::vector<ItemSlot*>& itemSlots() const { return m_itemslots; }

private:
    NatureLandDescr* m_descriptor_natureland = nullptr;
    model::NatureLandModel* m_model_natureland = nullptr;

    //jeti::control::TextureOb* textureOb_background;

    std::vector<Vehicle*> m_vehicles;
    std::vector<ItemSlot*> m_itemslots;

//    UnresolvedDataNatureLand data_unresolved_NatureLand;
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control
} // namespace core
