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

class Vehicle;   
class Ship;      
class Npc;   
class Observation;
class StarSystem;
class ItemSlot;   
class VehicleSlot;  
class Turrel;       

class Planet;
class Star;


class Player;
class FBO;
class BloomEffect;

class Galaxy;

class GuiManager;
class GuiSpace;
class GuiKosmoport;
class GuiMap;

class Kosmoport;


#include <iostream>
#include "src/common/myVector.hpp"
#include "src/common/gameStruct.hpp"
#include "src/common/constants.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>


#include "src/common/myStr.hpp"


#include "src/common/rect.hpp"

#include "src/gui/UserInput.hpp"

#include "src/gui/Cursor.hpp"  

#include "src/render/Render.hpp"

#include "src/effects/ShockWaveEffect.hpp"

#include "src/effects/BaseBackGroundEffect.hpp"
#include "src/effects/DistantNebulaEffect.hpp"
#include "src/effects/DistantStarEffect.hpp"


#include "src/effects/Shield.hpp"  


#include "src/effects/lazerTrace.hpp"

#include "src/pilots/Player.hpp"

#include "src/pilots/Observation.hpp" 

#include "src/gui/BaseGui.hpp"
#include "src/gui/BaseButton.hpp"
#include "src/gui/ButtonTrigger.hpp"
#include "src/gui/ButtonSingle.hpp"
#include "src/gui/GuiRadar.hpp"
#include "src/gui/GuiSpace.hpp"
#include "src/gui/GuiAngar.hpp"
#include "src/gui/GuiStore.hpp"
#include "src/gui/GuiKosmoport.hpp"
#include "src/gui/GuiVehicle.hpp"
#include "src/gui/GuiVehicle2.hpp"
#include "src/gui/GuiSkill.hpp"
#include "src/gui/GuiManager.hpp"

#include "src/world/garbageEffects.hpp"  
#include "src/world/GarbageEntities.hpp"  

#include "src/effects/lazerTrace.hpp"

#include "src/world/galaxy.hpp"
#include "src/gui/GuiMap.hpp"

#include "src/render/Screen.hpp"


//////////////////////////////////////
#include "src/gui/GuiManager.cpp"

