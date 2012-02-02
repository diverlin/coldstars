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

// Create the main window
bool g_USE_MODERN_HW = true;
				const bool g_DEBUG = false;            // debug 
				const bool g_AUTOTURN_ENABLE = false;  // debug
const int g_GAMESPEED = 1;

const int g_VIEW_WIDTH = 1024;
const int g_VIEW_HEIGHT = g_VIEW_WIDTH*600/800;
const int g_BPP = 32;
const int g_FPS_LIMIT = 60;
const bool g_VERT_SYNC = true;

// scrolling
//int g_SCROLL_COORD_X = 0;
//int g_SCROLL_COORD_Y = 0;

int g_SCROLL_VELOCITY_MAX = 20;
int g_SCROLL_VELOCITY_STEP = 1;

unsigned int g_MOUSE_POS_X;
unsigned int g_MOUSE_POS_Y;

bool g_MOUSE_LEFT_BUTTON;  
bool g_MOUSE_RIGHT_BUTTON; 

//int g_TIMER;
int TURN_TIME = 150;  //turn time, depends on game fps
int TURN_COUNT = 0; 
        
sf::RenderWindow g_APP(sf::VideoMode(g_VIEW_WIDTH, g_VIEW_HEIGHT, g_BPP), "cold star V0.0.4.29 (SFML/C++)");
sf::Font g_FONT;

sf::Clock g_CLOCK;
sf::Event g_EVENT;

ObjMeshInstance* g_SPHERE_MESH; 
ObjMeshInstance* g_DEFORMED_SPHERE_MESH;

//ModelOBJ            g_MODEL;

GLuint g_BLACK2ALPHA_PROGRAM;
GLuint g_SHOCKWAVE_PROGRAM;
GLuint g_VOLUMETRICLIGHT_PROGRAM;
GLuint g_LIGHT_PROGRAM;
GLuint g_BLUR_PROGRAM;
GLuint g_EXTRACT_BRIGHT_PROGRAM;
GLuint g_COMBINE_PROGRAM;
GLuint g_MULTITEX_PROGRAM;

FBO* g_FBO0;
FBO* g_FBO1;
FBO* g_FBO2;
FBO* g_FBO3;

BloomEffect* g_BLOOM;

Galaxy* g_GALAXY;

Player* pPLAYER;    

/* GUI */
GuiShip* g_GUI_SHIP;   
GuiSpace* g_GUI_SPACE;  
GuiKosmoport* g_GUI_KOSMOPORT;
GuiMap* g_GUI_MAP;
KeyEvents* g_KEYEVENTS;

Fps* g_FPS;
GameTimer* g_TIMER;

SimpleIdGenerator   g_STARSYSTEM_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_CONTAINER_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_ASTEROID_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_STAR_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_PLANET_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_MINERAL_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_BOMB_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_BLACKHOLE_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_EQUIPMENT_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_MODULE_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_SHIP_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_PLAYER_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_NPC_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_SPACESTATION_ID_GENERATOR  = SimpleIdGenerator();
SimpleIdGenerator   g_SATELLITE_ID_GENERATOR  = SimpleIdGenerator();

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

