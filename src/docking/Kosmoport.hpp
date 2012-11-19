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


#ifndef KOSMOPORT_H
#define KOSMOPORT_H

#include "../docking/BaseLand.hpp"

class Angar; 
class Store; 
class Shop; 
class Goverment; 

class Kosmoport : public BaseLand
{
        public:
                Kosmoport(int);
                virtual ~Kosmoport();
                
                void PutChildsToGarbage() const;

                Angar*     	GetAngar()    	const { return angar; };
                Store*    	GetStore()    	const { return store; };
                Shop*      	GetShop()      	const { return shop; };
                Goverment* 	GetGoverment() 	const { return goverment; }; 

                void BindAngar(Angar* angar);
                void BindStore(Store* store);
                void BindShop(Shop* shop);
                void BindGoverment(Goverment* goverment);
                                
                virtual bool GetPermissionToLand() const;
                                
                virtual bool AddVehicle(Vehicle*);
                //virtual bool RemoveVehicle(Vehicle*);
                
                virtual void UpdateInSpaceInStatic();
                
                virtual std::string GetDockVehicleStr() const;
                                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        private:
        	int race_id;
                
                Angar*     angar;
                Store*     store;
                Shop*      shop;
                Goverment* goverment; 
              
                void SaveDataUniqueKosmoport(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueKosmoport(const boost::property_tree::ptree&);
		void ResolveDataUniqueKosmoport();
};

#endif
