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


#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "../effects/ShockWaveEffect.hpp"
#include "BasePlanet.hpp"

class BlackHole : public BasePlanet
{
    	public:  
        	BlackHole(int);
        	virtual ~BlackHole();

		void BindShockWaveEffect(ShockWaveEffect* shockwave) { this->shockwave = shockwave; };
		
		void SetCenter(const Vec3<float>&);
		
		ShockWaveEffect* GetShockWaveEffect() const { return shockwave; };
		
		void UpdateInSpace(int, bool);
        	
        	void Render_NEW(const Vec2<float>& scroll_coords);	
		void Render_OLD() const;
		
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
        	ShockWaveEffect* shockwave;
        	
         	void UpdateInfo();    
         	
         	void SaveDataUniqueBlackHole(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueBlackHole(const boost::property_tree::ptree&);
		void ResolveDataUniqueBlackHole();
};

#endif 

