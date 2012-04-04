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
class Turrel;       

class Planet;
class Star;

class StateMachine;
class ScenarioBase;
class AiModelBase;

class Player;
class FBO;
class BloomEffect;

class Galaxy;

class GuiManager;
class GuiSpace;
class GuiKosmoport;
class GuiMap;

#include "src/common/myVector.hpp"
#include "src/common/gameStruct.hpp"
#include "src/common/constants.hpp"
#include "src/config/config.hpp"
#include "src/config/SaveManager.hpp"
#include "GL/glew.h"   

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

#include "src/common/gameTimer.hpp"


#include "src/common/myStr.hpp"

#include "src/render/screen.hpp"

#include "src/resources/objLoader.hpp"

//#include "src/common/gameStruct.hpp"
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

#include "src/gui/userInput.hpp"
#include "src/items/BaseItem.hpp"
#include "src/items/modules/moduleBase.hpp"
#include "src/items/modules/rocketModule.hpp"
#include "src/items/modules/lazerModule.hpp"
#include "src/items/modules/radarModule.hpp"
#include "src/items/modules/driveModule.hpp"
#include "src/items/modules/bakModule.hpp"
#include "src/items/modules/energizerModule.hpp"
#include "src/items/modules/protectorModule.hpp"
#include "src/items/modules/droidModule.hpp"
#include "src/items/modules/freezerModule.hpp"
#include "src/items/modules/scanerModule.hpp"
#include "src/items/modules/grappleModule.hpp"

#include "src/spaceobjects/BaseGameEntity.hpp"
#include "src/spaceobjects/spaceItemBase.hpp" 
#include "src/common/EntityManager.hpp"
#include "src/common/Message.hpp"
#include "src/common/MessageManager.hpp"

#include "src/spaceobjects/orbit.hpp" 
#include "src/spaceobjects/planetBase.hpp" 
#include "src/spaceobjects/asteroid.hpp"
#include "src/spaceobjects/mineral.hpp"
#include "src/items/others/bomb.hpp"
#include "src/spaceobjects/container.hpp"
#include "src/items/others/goodsPack.hpp"

#include "src/effects/particlesystem/particle.hpp"
#include "src/effects/particlesystem/baseParticleSystem.hpp"
#include "src/effects/particlesystem/blackHoleEffect.hpp"
#include "src/effects/particlesystem/explosion.hpp"
#include "src/effects/particlesystem/trail.hpp"
#include "src/effects/particlesystem/damage.hpp"

#include "src/spaceobjects/blackHole.hpp"

#include "src/items/equipment/equipmentBase.hpp"
#include "src/items/equipment/rocketEquipment.hpp"
#include "src/items/equipment/lazerEquipment.hpp"
#include "src/items/equipment/radarEquipment.hpp"
#include "src/items/equipment/driveEquipment.hpp"
#include "src/items/equipment/bakEquipment.hpp"
#include "src/items/equipment/energizerEquipment.hpp"
#include "src/items/equipment/protectorEquipment.hpp"
#include "src/items/equipment/droidEquipment.hpp"
#include "src/items/equipment/freezerEquipment.hpp"
#include "src/items/equipment/scanerEquipment.hpp"
#include "src/items/equipment/grappleEquipment.hpp"


#include "src/docking/platform.hpp"
#include "src/docking/angar.hpp"
#include "src/docking/shop.hpp"
#include "src/docking/goverment.hpp"
#include "src/docking/store.hpp"
#include "src/docking/landBase.hpp"
#include "src/docking/kosmoport.hpp"
#include "src/docking/land.hpp"

#include "src/gui/cursor.hpp"  

#include "src/render/render.hpp"
#include "src/render/glsl.hpp"
#include "src/render/fbo.hpp"
#include "src/render/bloom.hpp"
#include "src/effects/shockWave.hpp"


#include "src/effects/distantNebulaBg.hpp"
#include "src/effects/distantStarBg.hpp"


#include "src/effects/shield.hpp"  


#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/star.hpp"  
#include "src/spaceobjects/planet.hpp"

#include "src/spaceobjects/turrel.hpp"

#include "src/spaceobjects//ItemSlot.hpp"
#include "src/spaceobjects/driveComplex.hpp"
#include "src/spaceobjects/WeaponComplex.hpp"
#include "src/spaceobjects/ProtectionComplex.hpp"
#include "src/spaceobjects/Vehicle.hpp"
#include "src/spaceobjects/rocketBullet.hpp"
#include "src/spaceobjects/spaceStation.hpp"
#include "src/spaceobjects/satellite.hpp"
#include "src/spaceobjects/ship.hpp"
#include "src/builder/BaseVehicleBuilder.hpp"
#include "src/builder/VehicleBuilder.hpp"
#include "src/builder/StarSystemBuilder.hpp"
#include "src/builder/GalaxyBuilder.hpp"
#include "src/builder/PlayerBuilder.hpp"
#include "src/builder/NpcBuilder.hpp"

#include "src/pilots/player.hpp"

#include "src/skill/skill.hpp"
#include "src/pilots/npc.hpp"           

#include "src/pilots/scenarios/scenarioBase.hpp" 

#include "src/pilots/scenarios/microScenarioDestroy.hpp" 
#include "src/pilots/scenarios/microScenarioGrab.hpp" 
#include "src/pilots/scenarios/microScenarioJump.hpp" 
#include "src/pilots/scenarios/microScenarioDocking.hpp"

#include "src/pilots/scenarios/taskHolder.hpp"
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
#include "src/gui/guiVehicle.hpp"
#include "src/gui/guiSkill.hpp"
#include "src/gui/guiStore.hpp"
#include "src/gui/guiManager.hpp"

#include "src/world/garbageEffects.hpp"  
#include "src/world/garbageEntities.hpp"  
#include "src/world/starsystem.hpp"    
#include "src/effects/lazerTrace.hpp"

#include "src/world/galaxy.hpp"
#include "src/gui/guiMap.hpp"



#include "src/common/global.hpp"












#include "src/render/pathVisual.cpp"
#include "src/common/rand.cpp"
#include "src/common/gameStruct.cpp"
#include "src/common/id.cpp"

#include "src/common/myVector.cpp"
#include "src/common/myStr.cpp"
#include "src/world/galaxy.cpp"
#include "src/world/garbageEffects.cpp"  
#include "src/world/garbageEntities.cpp"  
#include "src/world/starsystem.cpp"  

#include "src/spaceobjects/container.cpp"    
#include "src/items/others/goodsPack.cpp"   
#include "src/spaceobjects/star.cpp"  
#include "src/spaceobjects/planet.cpp"
#include "src/spaceobjects/BaseGameEntity.cpp" 
#include "src/spaceobjects/spaceItemBase.cpp" 
#include "src/common/EntityManager.cpp"
#include "src/common/Message.cpp"
#include "src/common/MessageManager.cpp"

#include "src/spaceobjects/orbit.cpp"
#include "src/spaceobjects/planetBase.cpp"
#include "src/spaceobjects/asteroid.cpp"   
#include "src/spaceobjects/mineral.cpp" 
#include "src/spaceobjects/spaceStation.cpp" 
#include "src/spaceobjects/satellite.cpp" 
#include "src/items/others/bomb.cpp" 
#include "src/spaceobjects/blackHole.cpp"

#include "src/items/BaseItem.cpp"
#include "src/items/equipment/equipmentBase.cpp"
#include "src/items/equipment/rocketEquipment.cpp"
#include "src/items/equipment/lazerEquipment.cpp"
#include "src/items/equipment/radarEquipment.cpp"
#include "src/items/equipment/driveEquipment.cpp"
#include "src/items/equipment/bakEquipment.cpp"
#include "src/items/equipment/energizerEquipment.cpp"
#include "src/items/equipment/protectorEquipment.cpp"
#include "src/items/equipment/droidEquipment.cpp"
#include "src/items/equipment/freezerEquipment.cpp"
#include "src/items/equipment/scanerEquipment.cpp"
#include "src/items/equipment/grappleEquipment.cpp"

#include "src/items/modules/moduleBase.cpp"
#include "src/items/modules/rocketModule.cpp"
#include "src/items/modules/lazerModule.cpp"
#include "src/items/modules/radarModule.cpp"
#include "src/items/modules/driveModule.cpp"
#include "src/items/modules/bakModule.cpp"
#include "src/items/modules/energizerModule.cpp"
#include "src/items/modules/protectorModule.cpp"
#include "src/items/modules/droidModule.cpp"
#include "src/items/modules/freezerModule.cpp"
#include "src/items/modules/scanerModule.cpp"
#include "src/items/modules/grappleModule.cpp"

#include "src/docking/platform.cpp"
#include "src/docking/angar.cpp"
#include "src/docking/store.cpp"
#include "src/docking/shop.cpp"
#include "src/docking/goverment.cpp"
#include "src/docking/landBase.cpp"
#include "src/docking/kosmoport.cpp"

#include "src/docking/land.cpp"

#include "src/gui/button.cpp"
#include "src/gui/guiSpace.cpp"
#include "src/gui/guiKosmoport.cpp"
#include "src/gui/guiStore.cpp"
#include "src/gui/guiManager.cpp"
#include "src/gui/guiVehicle.cpp"
#include "src/builder/BaseVehicleBuilder.cpp"
#include "src/builder/VehicleBuilder.cpp"
#include "src/builder/StarSystemBuilder.cpp"
#include "src/builder/GalaxyBuilder.cpp"
#include "src/builder/PlayerBuilder.cpp"
#include "src/builder/NpcBuilder.cpp"
#include "src/gui/guiSkill.cpp"
#include "src/gui/guiMap.cpp"
#include "src/gui/cursor.cpp"   

#include "src/gui/userInput.cpp"

#include "src/resources/textureOb.cpp"
#include "src/resources/textureManager.cpp"
#include "src/resources/resources.cpp"
#include "src/resources/init.cpp"

#include "src/common/rect.cpp"
#include "src/common/points.cpp"

#include "src/spaceobjects/ItemSlot.cpp"

#include "src/spaceobjects/WeaponComplex.cpp"
#include "src/spaceobjects/ProtectionComplex.cpp"
#include "src/spaceobjects/Vehicle.cpp"
#include "src/spaceobjects/ship.cpp"
#include "src/spaceobjects/driveComplex.cpp"
#include "src/spaceobjects/turrel.cpp"

#include "src/effects/distantNebulaBg.cpp"
#include "src/effects/distantStarBg.cpp"
#include "src/effects/particlesystem/particle.cpp"
#include "src/effects/particlesystem/baseParticleSystem.cpp"
#include "src/effects/particlesystem/blackHoleEffect.cpp"
#include "src/effects/particlesystem/explosion.cpp"
#include "src/effects/particlesystem/trail.cpp"
#include "src/effects/particlesystem/damage.cpp"
#include "src/effects/lazerTrace.cpp"
#include "src/effects/shield.cpp"
#include "src/spaceobjects/rocketBullet.cpp"

#include "src/pilots/player.cpp"
#include "src/skill/skill.cpp"

#include "src/pilots/npc.cpp"
//
#include "src/pilots/scenarios/scenarioBase.cpp" 

#include "src/pilots/scenarios/microScenarioDestroy.cpp" 
#include "src/pilots/scenarios/microScenarioGrab.cpp" 
#include "src/pilots/scenarios/microScenarioJump.cpp" 
#include "src/pilots/scenarios/microScenarioDocking.cpp"

#include "src/pilots/scenarios/taskHolder.cpp"
#include "src/pilots/scenarios/stateMachine.cpp"

#include "src/pilots/scenarios/macroScenarioSelfSafety.cpp"
#include "src/pilots/scenarios/macroScenarioStarSystemLiberation.cpp"
#include "src/pilots/scenarios/macroScenarioStarSystemDefence.cpp"

#include "src/pilots/aiModel/aiModelBase.cpp"
#include "src/pilots/aiModel/aiModelRanger.cpp"
#include "src/pilots/aiModel/aiModelConqueror.cpp"

#include "src/pilots/observation.cpp" 

#include "src/common/common.cpp"

#include "src/render/render.cpp"

#include "src/render/glsl.cpp"
#include "src/render/fbo.cpp"
#include "src/render/bloom.cpp"
#include "src/effects/shockWave.cpp"

#include "src/text/textstuff.cpp"

#include "src/render/screen.cpp"
#include "src/common/gameTimer.cpp"
#include "src/config/SaveManager.cpp" 

////////////////////////////////////////////
