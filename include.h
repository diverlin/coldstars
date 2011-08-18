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

#include "GL/glew.h"   


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

#include "src/common/alias.hpp"

#include "src/resources/objLoader.h"
#include "src/resources/model_obj.cpp"

#include "src/common/global.h"
#include "src/common/constants.hpp"
#include "src/common/common.cpp"

#include "src/resources/texture.cpp"
#include "src/render/glsl.h"
#include "src/resources/resources.cpp"

class Angar;
class Shop;
class Goverment;
#include "src/kosmoport/kosmoport.h"
#include "src/land/land.h"

#include "src/pilots/player.h"
#include "src/render/init.h"

#include "src/common/rect.cpp"
#include "src/render/render.h"
#include "src/render/glsl.cpp"
#include "src/common/points.cpp"


#include "src/effects/background.cpp"
#include "src/effects/effects.cpp"

#include "src/world/starsystem.h"
#include "src/spaceobjects/commonForSpaceItems.cpp" 

#include "src/effects/shield.h"  
#include "src/equipment/commonforequipment.h"
class TurrelInstance;
class WeaponSlot;
#include "src/equipment/rocketEquipment.h"
#include "src/equipment/lazerEquipment.h"
#include "src/equipment/radarEquipment.h"
#include "src/equipment/driveEquipment.h"
#include "src/equipment/bakEquipment.h"
#include "src/equipment/energizerEquipment.h"
#include "src/equipment/protectorEquipment.h"
#include "src/equipment/droidEquipment.h"
#include "src/equipment/freezerEquipment.h"
#include "src/equipment/scanerEquipment.h"
#include "src/equipment/grappleEquipment.h"
#include "src/effects/turrel.h"
#include "src/slots/commonforslot.h"

#include "src/modules/commonformodules.h"
#include "src/modules/rocketModule.h"
#include "src/modules/lazerModule.h"
#include "src/modules/radarModule.h"
#include "src/modules/driveModule.h"
#include "src/modules/bakModule.h"
#include "src/modules/energizerModule.h"
#include "src/modules/protectorModule.h"
#include "src/modules/droidModule.h"
#include "src/modules/freezerModule.h"
#include "src/modules/scanerModule.h"
#include "src/modules/grappleModule.h"


#include "src/slots/otsecslot.h"
//#include "src/slots/driveslot.h"
//#include "src/slots/radarslot.h"
//#include "src/slots/bakslot.h"
//#include "src/slots/energizerslot.h"
//#include "src/slots/protectorslot.h"
//#include "src/slots/droidslot.h"
//#include "src/slots/freezerslot.h"
//#include "src/slots/scanerslot.h"
//#include "src/slots/grappleslot.h"
//#include "src/slots/gateslot.h"
#include "src/slots/weaponslot.h"
#include "src/vehicle/ship.h"
#include "src/spaceobjects/asteroid.h"
#include "src/spaceobjects/mineral.h"
#include "src/spaceobjects/container.h"


#include "src/slots/weaponslot.cpp"
#include "src/spaceobjects/container.cpp"    
#include "src/spaceobjects/star.cpp"  
#include "src/kosmoport/angar.h"
#include "src/pilots/skill.h"
#include "src/pilots/npc.h"              
#include "src/spaceobjects/planet.cpp"

#include "src/kosmoport/landingarea.h"
#include "src/kosmoport/angar.h"

#include "src/pilots/skill.cpp"
#include "src/pilots/npc.cpp"
#include "src/pilots/player.cpp"
#include "src/gui/cursor.cpp"                  
#include "src/spaceobjects/asteroid.cpp"   
#include "src/spaceobjects/mineral.cpp" 
#include "src/world/starsystem.cpp"    
#include "src/equipment/commonforequipment.cpp"
#include "src/equipment/rocketEquipment.cpp"
#include "src/equipment/lazerEquipment.cpp"
#include "src/equipment/radarEquipment.cpp"
#include "src/equipment/driveEquipment.cpp"
#include "src/equipment/bakEquipment.cpp"
#include "src/equipment/energizerEquipment.cpp"
#include "src/equipment/protectorEquipment.cpp"
#include "src/equipment/droidEquipment.cpp"
#include "src/equipment/freezerEquipment.cpp"
#include "src/equipment/scanerEquipment.cpp"
#include "src/equipment/grappleEquipment.cpp"
#include "src/effects/turrel.cpp"
#include "src/slots/commonforslot.cpp"
#include "src/slots/otsecslot.cpp"
//#include "src/slots/driveslot.cpp"
//#include "src/slots/radarslot.cpp"
//#include "src/slots/bakslot.cpp"
//#include "src/slots/energizerslot.cpp"
//#include "src/slots/protectorslot.cpp"
//#include "src/slots/droidslot.cpp"
//#include "src/slots/freezerslot.cpp"
//#include "src/slots/scanerslot.cpp"
//#include "src/slots/grappleslot.cpp"
//#include "src/slots/gateslot.cpp"
#include "src/kosmoport/store.h"


#include "src/modules/commonformodules.cpp"
#include "src/modules/rocketModule.cpp"
#include "src/modules/lazerModule.cpp"
#include "src/modules/radarModule.cpp"
#include "src/modules/driveModule.cpp"
#include "src/modules/bakModule.cpp"
#include "src/modules/energizerModule.cpp"
#include "src/modules/protectorModule.cpp"
#include "src/modules/droidModule.cpp"
#include "src/modules/freezerModule.cpp"
#include "src/modules/scanerModule.cpp"
#include "src/modules/grappleModule.cpp"


#include "src/vehicle/ship.cpp"
#include "src/world/world.cpp"
#include "src/effects/shield.cpp"
#include "src/kosmoport/landingarea.cpp"
#include "src/kosmoport/angar.cpp"
#include "src/kosmoport/store.cpp"
#include "src/kosmoport/shop.cpp"
#include "src/kosmoport/goverment.cpp"
#include "src/kosmoport/kosmoport.cpp"
#include "src/text/text.cpp"

#include "src/gui/button.cpp"
#include "src/gui/interfaceinspace.cpp"
#include "src/gui/interfaceinkosmoport.cpp"
#include "src/gui/shipInternal.cpp"

#include "src/land/land.cpp"
#include "src/keyevents/keyEventsInSpace.cpp"
////////////////////////////////////////////
