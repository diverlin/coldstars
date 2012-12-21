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


#ifndef STAR_H
#define STAR_H

#include <boost/property_tree/ptree.hpp>

#include "../spaceobjects/BasePlanet.hpp"
#include "../resources/textureOb.hpp"

class Star : public BasePlanet
{
	public:
    		float texture_offset1, texture_offset2;    
   		
    		Star(int);
    		virtual ~Star();
                
		const Color4f& GetColor() const { return color; }
		int GetColorId()           const { return textureOb->color_id; }
		float GetBrightThreshold() const { return textureOb->brightThreshold; }
		float GetDColor() const { return d_color; }
				
		void Hit(int, bool) {};
		void InitiateSpark();

                void CalcColor();    		
    		void UpdateInSpace(int, bool);
    		
    		void Render_NEW() const;
    		void Render_OLD() const;
                
                void SaveData(boost::property_tree::ptree&) const;
                void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
                
        private:
        	Color4f color;
        	float d_color;
        	
        	bool spark_done;
        	bool spark_on;
        	
    		void UpdateInfo();
    		void PostDeathUniqueEvent(bool);

    		void SaveDataUniqueStar(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueStar(const boost::property_tree::ptree&);
		void ResolveDataUniqueStar();
}; 


#endif 
    

        


