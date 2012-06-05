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


#ifndef BASELAND_H
#define BASELAND_H

struct UnresolvedDataUniqueBaseLand
{
	std::vector<int> npc_vec ;
	std::vector<int> vehicle_vec;
	std::vector<int> npc_launching_vec;
	std::vector<int> npc_docking_vec;
};

class BaseLand : public Base
{
        public:
                BaseLand();
                virtual ~BaseLand();

		void SetOwner(Base* owner)  { this->owner = owner; } 
		
		Base* GetOwner() const { return owner; };
		virtual bool GetPermissionToLand() const = 0;
		                
                virtual bool Add(Vehicle*) = 0;
                //virtual bool Remove(Vehicle*) = 0;
                
                virtual void Ai() = 0;  
		  
        protected:
                Base* owner;
             
                UnresolvedDataUniqueBaseLand data_unresolved_BaseLand;
                void SaveDataUniqueBaseLand(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueBaseLand(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseLand();
};

#endif
