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


#include "grappleModule.hpp"


GrappleModule :: GrappleModule(TextureOb* _texOb, int _strength_add, int _radius_add, int _speed_add, int _maxNumItem_add)
{
       CommonForModules_init(GRAPPLE_MODULE_ID, _texOb);

       strength_add   = _strength_add;
       radius_add     = _radius_add;
       speed_add      = _speed_add;
       maxNumItem_add = _maxNumItem_add;
}

GrappleModule :: ~GrappleModule ()
{}


int GrappleModule :: getStrengthAdd()   const { return strength_add; }
int GrappleModule :: getRadiusAdd()     const { return radius_add; }
int GrappleModule :: getSpeedAdd()      const { return speed_add; }
int GrappleModule :: getMaxNumItemAdd() const { return maxNumItem_add; }
		

void GrappleModule :: addUniqueInfo()
{
    	info.addTitleStr("grapple module");
    	if (strength_add != 0)
    	{
    		info.addNameStr("strength_add:");    info.addValueStr( int2str(strength_add) );
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");      info.addValueStr( int2str(radius_add) );
    	} 
    	if (speed_add != 0)
    	{
    		info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
    	}
    	if (maxNumItem_add != 0)
    	{
    		info.addNameStr("maxNumItem_add:");  info.addValueStr( int2str(maxNumItem_add) ); 
    	}
}


GrappleModule* grappleModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int strength_add   = getRandInt(GRAPPLE_MODULE_STRENGTH_MIN, GRAPPLE_MODULE_STRENGTH_MAX);
    	int radius_add     = getRandInt(GRAPPLE_MODULE_RADIUS_MIN, GRAPPLE_MODULE_RADIUS_MAX);
    	int speed_add      = getRandInt(GRAPPLE_MODULE_SPEED_MIN, GRAPPLE_MODULE_SPEED_MAX);
    	int maxNumItem_add = getRandInt(GRAPPLE_MODULE_MAXNUMITEM_MIN, GRAPPLE_MODULE_MAXNUMITEM_MAX);
    	
    	GrappleModule* grapple_module = new GrappleModule(texOb, strength_add, radius_add, speed_add, maxNumItem_add);    	
    	return grapple_module;
}







