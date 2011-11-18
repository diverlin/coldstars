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


class Ship;      
class Npc;   
class Observation;
class StarSystem;
class ItemSlot;   
class Turrel;       

#include "src/common/global0.hpp" // used as work around

#include "GL/glew.h"   

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

#include "src/common/myVector.hpp"
#include "src/common/myStr.hpp"
#include "src/resources/objLoader.hpp"

#include "src/common/gameStruct.hpp"
#include "src/common/rand.hpp"
#include "src/common/id.hpp"
#include "src/common/points.hpp"
#include "src/common/common.hpp"

#include "src/text/textstuff.hpp"

#include "src/resources/textureOb.hpp"
#include "src/resources/textureManager.hpp"
#include "src/resources/resources.hpp"
#include "src/resources/init.hpp"

#include "src/common/rect.hpp"

#include "src/keyevents/keyEventsInSpace.hpp"

#include "src/modules/commonformodules.hpp"
#include "src/modules/rocketModule.hpp"
#include "src/modules/lazerModule.hpp"
#include "src/modules/radarModule.hpp"
#include "src/modules/driveModule.hpp"
#include "src/modules/bakModule.hpp"
#include "src/modules/energizerModule.hpp"
#include "src/modules/protectorModule.hpp"
#include "src/modules/droidModule.hpp"
#include "src/modules/freezerModule.hpp"
#include "src/modules/scanerModule.hpp"
#include "src/modules/grappleModule.hpp"

#include "src/spaceobjects/commonForSpaceItems.hpp" 
#include "src/spaceobjects/commonForPlanet.hpp" 
#include "src/spaceobjects/asteroid.hpp"
#include "src/spaceobjects/mineral.hpp"
#include "src/spaceobjects/container.hpp"
#include "src/spaceobjects/goodsPack.hpp"

class Planet;
class StarSystem;
class Star;
#include "src/pilots/targetObject.hpp" 


#include "src/equipment/commonforequipment.hpp"
#include "src/equipment/rocketEquipment.hpp"
#include "src/equipment/lazerEquipment.hpp"
#include "src/equipment/radarEquipment.hpp"
#include "src/equipment/driveEquipment.hpp"
#include "src/equipment/bakEquipment.hpp"
#include "src/equipment/energizerEquipment.hpp"
#include "src/equipment/protectorEquipment.hpp"
#include "src/equipment/droidEquipment.hpp"
#include "src/equipment/freezerEquipment.hpp"
#include "src/equipment/scanerEquipment.hpp"
#include "src/equipment/grappleEquipment.hpp"


#include "src/kosmoport/landingarea.hpp"
#include "src/kosmoport/angar.hpp"
#include "src/kosmoport/shop.hpp"
#include "src/kosmoport/goverment.hpp"
#include "src/kosmoport/store.hpp"
#include "src/kosmoport/kosmoport.hpp"
#include "src/land/land.hpp"

#include "src/gui/cursor.hpp"  
#include "src/pilots/player.hpp"

#include "src/render/render.hpp"
#include "src/render/glsl.hpp"
#include "src/render/fbo.hpp"
#include "src/render/bloom.hpp"
#include "src/effects/shockWave.hpp"


#include "src/effects/distantNebulaBg.hpp"
#include "src/effects/distantStarBg.hpp"
#include "src/effects/particlesystem/particle.hpp"
#include "src/effects/particlesystem/explosion.hpp"
#include "src/effects/particlesystem/trail.hpp"
#include "src/effects/particlesystem/damage.hpp"

#include "src/effects/shield.hpp"  

#include "src/spaceobjects/rocketBullet.hpp"
#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/star.hpp"  
#include "src/spaceobjects/planet.hpp"

#include "src/vehicle/turrel.hpp"

#include "src/vehicle/itemSlot.hpp"
#include "src/vehicle/navigator.hpp"
#include "src/vehicle/ship.hpp"

#include "src/pilots/skill.hpp"
#include "src/pilots/questObject.hpp"  
#include "src/pilots/questGenerator.hpp" 
#include "src/pilots/npc.hpp"              
#include "src/pilots/observation.hpp" 

#include "src/gui/button.hpp"
#include "src/gui/interfaceinspace.hpp"
#include "src/gui/shipInternal.hpp"
#include "src/world/garbage.hpp"  
#include "src/world/starsystem.hpp"    
#include "src/effects/lazerTrace.hpp"

#include "src/vehicle/turrel.hpp"
#include "src/world/galaxy.hpp"














#include "src/common/rand.cpp"
#include "src/common/gameStruct.cpp"
#include "src/common/id.cpp"
#include "src/common/global.cpp"
#include "src/common/constants.cpp"
#include "src/common/myVector.cpp"
#include "src/common/myStr.cpp"
#include "src/world/galaxy.cpp"
#include "src/world/garbage.cpp"  
#include "src/world/starsystem.cpp"  

#include "src/spaceobjects/container.cpp"    
#include "src/spaceobjects/goodsPack.cpp"   
#include "src/spaceobjects/star.cpp"  
#include "src/spaceobjects/planet.cpp"
#include "src/spaceobjects/commonForSpaceItems.cpp" 
#include "src/spaceobjects/commonForPlanet.cpp"
#include "src/spaceobjects/asteroid.cpp"   
#include "src/spaceobjects/mineral.cpp" 

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

#include "src/kosmoport/landingarea.cpp"
#include "src/kosmoport/angar.cpp"
#include "src/kosmoport/store.cpp"
#include "src/kosmoport/shop.cpp"
#include "src/kosmoport/goverment.cpp"
#include "src/kosmoport/kosmoport.cpp"

#include "src/land/land.cpp"

#include "src/gui/button.cpp"
#include "src/gui/interfaceinspace.cpp"
#include "src/gui/interfaceinkosmoport.cpp"
#include "src/gui/shipInternal.cpp"
#include "src/gui/cursor.cpp"   

#include "src/keyevents/keyEventsInSpace.cpp"

#include "src/resources/textureOb.cpp"
#include "src/resources/textureManager.cpp"
#include "src/resources/resources.cpp"
#include "src/resources/init.cpp"

#include "src/common/rect.cpp"
#include "src/common/points.cpp"

#include "src/vehicle/itemSlot.cpp"

#include "src/vehicle/ship.cpp"
#include "src/vehicle/navigator.cpp"
#include "src/vehicle/turrel.cpp"

#include "src/effects/distantNebulaBg.cpp"
#include "src/effects/distantStarBg.cpp"
#include "src/effects/particlesystem/particle.cpp"
#include "src/effects/particlesystem/explosion.cpp"
#include "src/effects/particlesystem/trail.cpp"
#include "src/effects/particlesystem/damage.cpp"
#include "src/effects/lazerTrace.cpp"
#include "src/effects/shield.cpp"
#include "src/spaceobjects/rocketBullet.cpp"

#include "src/pilots/player.cpp"
#include "src/pilots/skill.cpp"
#include "src/pilots/questObject.cpp"  
#include "src/pilots/targetObject.cpp"  
#include "src/pilots/questGenerator.cpp" 
#include "src/pilots/npc.cpp"
#include "src/pilots/observation.cpp" 

#include "src/common/common.cpp"
//#include "src/resources/model_obj.cpp"
#include "src/render/render.cpp"
//#include "src/render/camera.cpp"
#include "src/render/glsl.cpp"
#include "src/render/fbo.cpp"
#include "src/render/bloom.cpp"
#include "src/effects/shockWave.cpp"

#include "src/text/textstuff.cpp"
#include "src/gui/spaceMap.cpp"
////////////////////////////////////////////
