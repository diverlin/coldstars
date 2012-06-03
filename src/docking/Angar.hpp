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


class Angar : public Room
{
        public: 
                Angar(int id);
                ~Angar();
                
                void AddVehicleSlot(VehicleSlot*, const Rect&);
                void Ai() const;
                
                bool AddVehicle(Vehicle*);
                bool RemoveVehicle(Vehicle*);

                void MouseControl(Player*);

                void Render(Player*) const;
                void RenderItemInfo(Player*) const;

                int GetFreeVehicleSlotTotalNum() const;
                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        private:               
                std::vector<VehicleSlot*> vehicleslot_vec;

                void RenderInternals() const;
                
                void SaveDataUniqueAngar(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueAngar(const boost::property_tree::ptree&);
		void ResolveDataUniqueAngar();
};

#endif 
