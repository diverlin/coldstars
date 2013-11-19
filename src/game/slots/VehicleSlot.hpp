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


#ifndef VEHICLESLOT_HPP
#define VEHICLESLOT_HPP

#include <boost/property_tree/ptree.hpp>
#include "../slots/BaseSlot.hpp"

class Vehicle;
class Rect; // to be removed


class VehicleSlot : public BaseSlot
{
    public:
        VehicleSlot(int, TYPE::ENTITY);
        ~VehicleSlot();    
        
        virtual void PutChildsToGarbage() const;
        
        Vehicle* GetVehicle() const { return vehicle; };
        void InsertVehicle(Vehicle*);
        void Release(); 
        void SwapVehicle(VehicleSlot*);
        
        void Render(const Rect&) const;
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Load();
        
    private:
        Vehicle* vehicle;
        
        void SaveDataUniqueVehicleSlot(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueVehicleSlot(const boost::property_tree::ptree&);
        void ResolveDataUniqueVehicleSlot();     
}; 

#endif
