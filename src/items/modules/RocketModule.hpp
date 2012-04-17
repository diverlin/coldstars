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


#ifndef ROCKETMODULE_H
#define ROCKETMODULE_H


class RocketModule : public BaseModule
{
     	public:
       		RocketModule(int);
       		virtual ~RocketModule();

		void SetAmmoMaxAdd(int ammo_max_add) { this->ammo_max_add = ammo_max_add; };
		void SetDamageAdd(int damage_add)    { this->damage_add = damage_add; };
		void SetRadiusAdd(int radius_add)    { this->radius_add = radius_add; };
                
		int GetAmmoMaxAdd() const { return ammo_max_add; };
		int GetDamageAdd()  const { return damage_add; };
		int GetRadiusAdd()  const { return radius_add; };
		
		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
		virtual void ResolveData();
       		
       	private:
       		int ammo_max_add;
       		int damage_add;
       		int radius_add;
       		
       		void virtual AddUniqueInfo();
       		
       		void SaveDataUniqueRocketModule(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueRocketModule(const boost::property_tree::ptree&);
		void ResolveDataUniqueRocketModule(); 
};

RocketModule* GetNewRocketModule();


#endif
