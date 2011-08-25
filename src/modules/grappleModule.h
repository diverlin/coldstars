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


#ifndef GRAPPLEMODULE_H
#define GRAPPLEMODULE_H

class GrappleModule : public CommonForModules
{
    	public:     
      		GrappleModule(TextureOb* _pTo_texOb, int _strength_add, int _radius_add, int _speed_add, int _maxNumItem_add);
      		~GrappleModule();

		int getStrengthAdd()   const;
		int getRadiusAdd()     const;
		int getSpeedAdd()      const;
		int getMaxNumItemAdd() const;

      		void updateInfo();
      		
      	private: 
      	       	int strength_add;
       		int radius_add;
       		int speed_add;
       		int maxNumItem_add;
       		
      	      	// INFO 
      		std::string info_title_0;
      		std::string info_title_1;   std::string info_value_1;
      		std::string info_title_2;   std::string info_value_2; 
      		std::string info_title_3;   std::string info_value_3;
      		std::string info_title_4;   std::string info_value_4;
      		std::string info_title_5;   std::string info_value_5;
};


GrappleModule* grappleModuleGenerator();

#endif
