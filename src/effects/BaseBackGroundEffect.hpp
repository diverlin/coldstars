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


#ifndef BASEBACKGROUNDEFFECT_H
#define BASEBACKGROUNDEFFECT_H

class BaseBackGroundEffect
{
    	public:
	        BaseBackGroundEffect();
	        ~BaseBackGroundEffect();
	        
	        void SetTextureOb(TextureOb* textureOb) 	{ this->textureOb = textureOb; };
	        void SetCenter(vec3f center)		 	{ this->center = center; };	
	        void SetScale(float scale)			{ this->scale = scale; };     
	        void SetParallaxRate(float parallax_rate) 	{ this->parallax_rate = parallax_rate; };   
      		        	
        protected:
       		int id;

      		static int counter;
       		
       	       	TextureOb* textureOb;
       	       	std::string textureOb_path;
       	       	
        	vec3f center;

		float scale;
		float parallax_rate;
        	
     		void SaveDataUniqueBaseBackGroundEffect(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueBaseBackGroundEffect(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseBackGroundEffect();
    
};

int BaseBackGroundEffect::counter;

#endif 

