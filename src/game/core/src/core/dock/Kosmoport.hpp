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

#include <core/dock/Land.hpp>
#include <core/type/RaceType.hpp>

namespace control {

class Angar;
class Store;
class Shop;
class Goverment;

class Kosmoport : public Land
{
public:
    Kosmoport(int);
    virtual ~Kosmoport();

    Angar* angar() const { return m_angar; }
    Store* store() const { return m_store; }
    Shop* shop() const { return m_shop; }
    Goverment* goverment() const { return m_goverment; }

    void bindAngar(Angar* m_angar);
    void bindStore(Store* m_store);
    void bindShop(Shop* m_shop);
    void bindGoverment(Goverment* m_goverment);

    virtual bool GetPermissionToLand() const;

    virtual bool add(Vehicle*);
    virtual bool remove(Vehicle*);

    virtual void UpdateInStatic();

    virtual std::string GetDockVehicleStr() const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

private:
    race::Type m_race = race::Type::NONE;

    Angar* m_angar = nullptr;
    Store* m_store = nullptr;
    Shop* m_shop = nullptr;
    Goverment* m_goverment = nullptr;

    virtual void putChildrenToGarbage() const;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control

