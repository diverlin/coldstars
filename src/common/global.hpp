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


bool g_USE_MODERN_HW = true;
bool g_DEBUG = false;            // debug 
bool g_AUTOTURN_ENABLE = false;  // debug
int  g_GAMESPEED = 1;


sf::RenderWindow g_APP(sf::VideoMode(SCREEN_WIDTH_MIN, SCREEN_HEIGHT_MIN, g_BPP), "cold star V0.0.4.51 (SFML/C++)");
sf::Font g_FONT;

sf::Clock g_CLOCK;

ObjMeshInstance* g_SPHERE_MESH; 
ObjMeshInstance* g_DEFORMED_SPHERE_MESH;


class Shaders;
Shaders g_SHADERS;


SimpleIdGenerator   g_ID_GENERATOR  = SimpleIdGenerator();

SimpleIdGenerator   g_TEXTURE_ID_GENERATOR = SimpleIdGenerator();
DetaliedIdGenerator g_TYPE_ID_GENERATOR    = DetaliedIdGenerator(); 

UniqueTextureCollector g_UNIQUE_TEXTURE_COLLECTOR;
TextureManager g_TEXTURE_MANAGER;


class MacroScenarioStarSystemLiberation; MacroScenarioStarSystemLiberation* g_MACROSCENARIO_STARSYSTEMLIBERATION;
class MacroScenarioStarSystemDefence;    MacroScenarioStarSystemDefence*    g_MACROSCENARIO_STARSYSTEMDEFENCE;
class MacroScenarioSelfSafety;           MacroScenarioSelfSafety*           g_MACROSCENARIO_SELFSAFETY;

class MicroScenarioDocking;              MicroScenarioDocking* g_MICROSCENARIO_DOCKING;
class MicroScenarioJump;                 MicroScenarioJump*    g_MICROSCENARIO_JUMP;
class MicroScenarioDestroy;              MicroScenarioDestroy* g_MICROSCENARIO_DESTROY;

class AiModelRanger;       AiModelRanger*      g_AIMODEL_RANGER;
class AiModelConqueror;    AiModelConqueror*   g_AIMODEL_CONQUEROR;

std::vector<int> SHIP_SUBTYPE_LIST;

std::vector<int> RACES_ALL_LIST;
std::vector<int> RACES_GOOD_LIST;
std::vector<int> RACES_EVIL_LIST;
std::vector<int> RACE4_ALLOWED_SUBTYPE_LIST;

