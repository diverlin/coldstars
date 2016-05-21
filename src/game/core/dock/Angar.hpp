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

#ifndef ANGAR_H
#define ANGAR_H

#include "Room.hpp"
class ItemSlot;
class VehicleSlot; 
class Vehicle;
class Npc;
namespace item {
class Base;
} // namespace item

class RocketEquipment;

class Angar : public Room
{
        public: 
                Angar(int id);
                ~Angar();
                
                virtual void putChildrenToGarbage() const;
                
                void AddVehicleSlot(VehicleSlot*);
                void AddItemSlot(ItemSlot*);
                
                void UpdateInStatic() const;
                
                bool AddVehicle(Vehicle*);
                
                bool RepairItem(Npc*, item::Base*) const;
                bool ChargeRocketEquipment(Npc*, RocketEquipment*) const;
                                
                bool RepairVehicle(Vehicle*) const; 
                bool TankUpVehicle(Vehicle*) const; 
                
                int GetFreeVehicleSlotTotalNum() const;
                
                int GetPriceFuel() const { return price_fuel; };
                             
                std::string GetDockVehicleStr() const;
                                                        
                void Save(boost::property_tree::ptree&) const;
        void Load(const boost::property_tree::ptree&);
        void Resolve();
        
        private:               
                std::vector<VehicleSlot*> vehicle_total_slot_vec;
                std::vector<VehicleSlot*> vehicle_military_slot_vec;
                std::vector<VehicleSlot*> vehicle_visitors_slot_vec;

                std::vector<ItemSlot*> item_slot_vec;
                                                                                
                int price_fuel;
                
                void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
        friend class GuiAngar;
};

#endif 
