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


#include "grappleModule.h"


GrappleModule :: GrappleModule(TextureOb* _pTo_texOb, int _strength_add, int _radius_add, int _speed_add, int _maxNumItem_add)
{
       CommonForModules_init(GRAPPLE_ID, _pTo_texOb);

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
		

void GrappleModule :: updateInfo()
{
	info.clear();

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
    	info.addNameStr("mass:");         info.addValueStr(int2str(mass));
}


GrappleModule* grappleModuleGenerator()
{
    	TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int _strength_add   = randIntInRange(GRAPPLE_MODULE_STRENGTH_MIN, GRAPPLE_MODULE_STRENGTH_MAX);
    	int _radius_add     = randIntInRange(GRAPPLE_MODULE_RADIUS_MIN, GRAPPLE_MODULE_RADIUS_MAX);
    	int _speed_add      = randIntInRange(GRAPPLE_MODULE_SPEED_MIN, GRAPPLE_MODULE_SPEED_MAX);
    	int _maxNumItem_add = randIntInRange(GRAPPLE_MODULE_MAXNUMITEM_MIN, GRAPPLE_MODULE_MAXNUMITEM_MAX);
    	
    	GrappleModule* pTo_grapple_module = new GrappleModule(pTo_texOb, _strength_add, _radius_add, _speed_add, _maxNumItem_add);
    	return pTo_grapple_module;
}







