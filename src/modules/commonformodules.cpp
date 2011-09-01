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


#include "commonformodules.h"


CommonForModules :: CommonForModules()
{}

void CommonForModules :: CommonForModules_init(int _subtype_id, TextureOb* _pTo_texOb)
{
     	pTo_texOb = _pTo_texOb;

     	if (pTo_texOb->is_animated == false)
        	pToFunc_render = &CommonForModules::_renderFrame;
     	else
        	pToFunc_render = &CommonForModules::_renderFrames;

     	w = pTo_texOb->w;
     	h = pTo_texOb->h;
          
     	id = g_ENTITY_ID_GENERATOR.returnNextId(); 
          
     	type_id = MODULE_ID;
     	subtype_id = _subtype_id;
          
     	mass = 1;
}


CommonForModules :: ~CommonForModules ()
{}


int CommonForModules :: getId()      const { return id; }
int CommonForModules :: getType()    const { return type_id; }
int CommonForModules :: getSubType() const { return subtype_id; }
    		
TextureOb* CommonForModules  :: getTexOb() const { return pTo_texOb; }
      		

void CommonForModules :: render(Rect slot_rect)
{
     (this->*pToFunc_render)(slot_rect);
}


void CommonForModules :: _renderFrame(Rect slot_rect)
{
     drawTexturedRect(pTo_texOb->texture, slot_rect, -1);   
}

void CommonForModules :: _renderFrames(Rect slot_rect)
{
    int i = pTo_texOb->updateAnimationFrame(); 
    glBindTexture(GL_TEXTURE_2D, pTo_texOb->texture);
    drawRect(slot_rect, -1.0, pTo_texOb->texCoord_bottomLeft_x_list[i], pTo_texOb->texCoord_bottomLeft_y_list[i], pTo_texOb->texCoord_bottomRight_x_list[i], pTo_texOb->texCoord_bottomRight_y_list[i], pTo_texOb->texCoord_topLeft_x_list[i], pTo_texOb->texCoord_topLeft_y_list[i], pTo_texOb->texCoord_topRight_x_list[i], pTo_texOb->texCoord_topRight_y_list[i]);
}


void CommonForModules :: renderInfo(Rect slot_rect)
{  
     drawInfoIn2Column(&info.title_list, &info.value_list, slot_rect.center_x, slot_rect.center_y, 0, 0);
}


