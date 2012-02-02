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
class VehicleCommon;    
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

#include "src/gui/fps.hpp"

#include "src/common/myVector.hpp"
#include "src/common/myStr.hpp"
#include "src/resources/objLoader.hpp"

#include "src/common/gameStruct.hpp"
#include "src/common/rand.hpp"
#include "src/common/id.hpp"
#include "src/common/points.hpp"
#include "src/common/common.hpp"

#include "src/render/pathVisual.hpp"

#include "src/text/textstuff.hpp"

#include "src/resources/textureOb.hpp"
#include "src/resources/textureManager.hpp"
#include "src/resources/resources.hpp"
#include "src/resources/init.hpp"

#include "src/common/rect.hpp"

#include "src/gui/keyEvents.hpp"

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

#include "src/spaceobjects/baseSpaceObject.hpp" 
#include "src/spaceobjects/commonForSpaceItems.hpp" 
#include "src/spaceobjects/commonForPlanet.hpp" 
#include "src/spaceobjects/asteroid.hpp"
#include "src/spaceobjects/mineral.hpp"
#include "src/vehicle/bomb.hpp"
#include "src/spaceobjects/container.hpp"
#include "src/spaceobjects/goodsPack.hpp"
#include "src/spaceobjects/blackHole.hpp"

class Planet;
class StarSystem;
class Star;
#include "src/obj/targetObject.hpp" 


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
#include "src/player/player.hpp"

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

#include "src/vehicle/rocketBullet.hpp"
#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/star.hpp"  
#include "src/spaceobjects/planet.hpp"

#include "src/vehicle/turrel.hpp"

#include "src/vehicle/itemSlot.hpp"
#include "src/vehicle/navigator.hpp"
#include "src/vehicle/weaponComplex.hpp"
#include "src/vehicle/vehicleCommon.hpp"
#include "src/vehicle/spaceStation.hpp"
#include "src/vehicle/satellite.hpp"
#include "src/vehicle/ship.hpp"


#include "src/skill/skill.hpp"
#include "src/obj/questGenerator.hpp" 
class StateMachine;

class MicroScenarioBase;
class MacroScenarioBase;

class AiModelBase;
#include "src/pilots/npc.hpp"           


//
#include "src/pilots/scenarios/microScenarioBase.hpp" 
#include "src/pilots/scenarios/macroScenarioBase.hpp" 

#include "src/pilots/scenarios/microScenarioDestroy.hpp" 
#include "src/pilots/scenarios/microScenarioGrab.hpp" 
#include "src/pilots/scenarios/microScenarioJump.hpp" 
#include "src/pilots/scenarios/microScenarioDocking.hpp"

#include "src/pilots/scenarios/stateMachine.hpp"

#include "src/pilots/scenarios/macroScenarioSelfSafety.hpp"
#include "src/pilots/scenarios/macroScenarioStarSystemLiberation.hpp"
#include "src/pilots/scenarios/macroScenarioStarSystemDefence.hpp"

#include "src/pilots/aiModel/aiModelBase.hpp"
#include "src/pilots/aiModel/aiModelRanger.hpp"
#include "src/pilots/aiModel/aiModelConqueror.hpp"

//   
#include "src/pilots/observation.hpp" 

#include "src/gui/button.hpp"
#include "src/gui/guiSpace.hpp"
#include "src/gui/guiKosmoport.hpp"
#include "src/gui/guiShip.hpp"
#include "src/world/garbage.hpp"  
#include "src/world/starsystem.hpp"    
#include "src/effects/lazerTrace.hpp"

#include "src/vehicle/turrel.hpp"
#include "src/world/galaxy.hpp"
#include "src/gui/guiMap.hpp"


#include "src/common/gameTimer.hpp"













#include "src/render/pathVisual.cpp"
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
#include "src/spaceobjects/baseSpaceObject.cpp" 
#include "src/spaceobjects/commonForSpaceItems.cpp" 
#include "src/spaceobjects/commonForPlanet.cpp"
#include "src/spaceobjects/asteroid.cpp"   
#include "src/spaceobjects/mineral.cpp" 
#include "src/vehicle/spaceStation.cpp" 
#include "src/vehicle/satellite.cpp" 
#include "src/vehicle/bomb.cpp" 
#include "src/spaceobjects/blackHole.cpp"

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
#include "src/gui/guiSpace.cpp"
#include "src/gui/guiKosmoport.cpp"
#include "src/gui/guiShip.cpp"
#include "src/gui/guiMap.cpp"
#include "src/gui/cursor.cpp"   

#include "src/gui/keyEvents.cpp"

#include "src/resources/textureOb.cpp"
#include "src/resources/textureManager.cpp"
#include "src/resources/resources.cpp"
#include "src/resources/init.cpp"

#include "src/common/rect.cpp"
#include "src/common/points.cpp"

#include "src/vehicle/itemSlot.cpp"

#include "src/vehicle/weaponComplex.cpp"
#include "src/vehicle/vehicleCommon.cpp"
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
#include "src/vehicle/rocketBullet.cpp"

#include "src/player/player.cpp"
#include "src/skill/skill.cpp"

#include "src/obj/targetObject.cpp"  
#include "src/obj/questGenerator.cpp" 
#include "src/pilots/npc.cpp"
//
#include "src/pilots/scenarios/microScenarioBase.cpp" 
#include "src/pilots/scenarios/macroScenarioBase.cpp" 

#include "src/pilots/scenarios/microScenarioDestroy.cpp" 
#include "src/pilots/scenarios/microScenarioGrab.cpp" 
#include "src/pilots/scenarios/microScenarioJump.cpp" 
#include "src/pilots/scenarios/microScenarioDocking.cpp"

#include "src/pilots/scenarios/stateMachine.cpp"

#include "src/pilots/scenarios/macroScenarioSelfSafety.cpp"
#include "src/pilots/scenarios/macroScenarioStarSystemLiberation.cpp"
#include "src/pilots/scenarios/macroScenarioStarSystemDefence.cpp"

#include "src/pilots/aiModel/aiModelBase.cpp"
#include "src/pilots/aiModel/aiModelRanger.cpp"
#include "src/pilots/aiModel/aiModelConqueror.cpp"
//
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

#include "src/gui/fps.cpp"
#include "src/common/gameTimer.cpp"

////////////////////////////////////////////
