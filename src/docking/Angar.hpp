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


class Angar : public Base
{
        public: 
                Angar(int id);
                ~Angar();
                
                void SetOwnerKosmoport(Kosmoport* owner_kosmoport) { this->owner_kosmoport = owner_kosmoport; }
                void SetTextureObBackground(TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };
                void AddVehicleSlot(VehicleSlot* platform, const Rect&);
                
                Kosmoport* GetOwnerKosmoport() { return owner_kosmoport; }
                
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
        	Kosmoport* owner_kosmoport;
                TextureOb* textureOb_background;
                
                std::vector<VehicleSlot*> platform_vec;

                void RenderBackground(Player*) const;
                void RenderInternals() const;
                
                void SaveDataUniqueAngar(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueAngar(const boost::property_tree::ptree&);
		void ResolveDataUniqueAngar();
};

#endif 
