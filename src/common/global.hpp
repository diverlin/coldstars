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


#ifndef GLOBAL_H
#define GLOBAL_H

//#include "../resources/objLoader.hpp"
//#include "../common/id.hpp"
//#include "../resources/textureManager.hpp"
#include "../common/id.hpp"

sf::Clock g_CLOCK;

ObjMeshInstance* g_SPHERE_MESH; 
ObjMeshInstance* g_DEFORMED_SPHERE_MESH;


class ShadersPack; ShadersPack g_SHADERS_PACK;

SimpleIdGenerator   g_ID_GENERATOR  = SimpleIdGenerator();

SimpleIdGenerator   g_TEXTURE_ID_GENERATOR = SimpleIdGenerator();
DetaliedIdGenerator g_TYPE_ID_GENERATOR    = DetaliedIdGenerator(); 

GuiTextureObCollector g_GUI_TEXTUREOB_COLLECTOR;
TextureManager g_TEXTURE_MANAGER;

class AiModelRanger;       		 AiModelRanger*      AIMODEL_RANGER;
class AiModelConqueror;    		 AiModelConqueror*   AIMODEL_CONQUEROR;

std::vector<int> RACES_ALL_LIST;
std::vector<int> RACES_GOOD_LIST;
std::vector<int> RACES_EVIL_LIST;

std::vector<int> RACE0_ALLOWED_SUBTYPE_LIST;
std::vector<int> RACE1_ALLOWED_SUBTYPE_LIST;
std::vector<int> RACE2_ALLOWED_SUBTYPE_LIST;
std::vector<int> RACE3_ALLOWED_SUBTYPE_LIST; 
std::vector<int> RACE4_ALLOWED_SUBTYPE_LIST;
std::vector<int> RACE6_ALLOWED_SUBTYPE_LIST;
std::vector<int> RACE7_ALLOWED_SUBTYPE_LIST;



#endif 
