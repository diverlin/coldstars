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


GrappleModule :: GrappleModule(int strength_add, int radius_add, int speed_add, int maxNumItem_add)
{
       this->strength_add   = strength_add;
       this->radius_add     = radius_add;
       this->speed_add      = speed_add;
       this->maxNumItem_add = maxNumItem_add;
}

GrappleModule :: ~GrappleModule() /* virtual */
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


GrappleModule* getNewGrappleModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int strength_add   = getRandInt(GRAPPLE_MODULE_STRENGTH_MIN, GRAPPLE_MODULE_STRENGTH_MAX);
    	int radius_add     = getRandInt(GRAPPLE_MODULE_RADIUS_MIN, GRAPPLE_MODULE_RADIUS_MAX);
    	int speed_add      = getRandInt(GRAPPLE_MODULE_SPEED_MIN, GRAPPLE_MODULE_SPEED_MAX);
    	int maxNumItem_add = getRandInt(GRAPPLE_MODULE_MAXNUMITEM_MIN, GRAPPLE_MODULE_MAXNUMITEM_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE;
        data_id.subtype_id = MODULE::GRAPPLE;  
        
    	GrappleModule* grapple_module = new GrappleModule(strength_add, radius_add, speed_add, maxNumItem_add);    	
    	grapple_module->setTextureOb(texOb);
        grapple_module->setIdData(data_id);
        
        return grapple_module;
}







