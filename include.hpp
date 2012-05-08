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

#include <iostream>
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

#include "src/Base.hpp"

#include "src/gui/UserInput.hpp"
#include "src/items/BaseItem.hpp"
#include "src/items/modules/BaseModule.hpp"
#include "src/items/modules/RocketModule.hpp"
#include "src/items/modules/LazerModule.hpp"
#include "src/items/modules/RadarModule.hpp"
#include "src/items/modules/DriveModule.hpp"
#include "src/items/modules/BakModule.hpp"
#include "src/items/modules/EnergizerModule.hpp"
#include "src/items/modules/ProtectorModule.hpp"
#include "src/items/modules/DroidModule.hpp"
#include "src/items/modules/FreezerModule.hpp"
#include "src/items/modules/ScanerModule.hpp"
#include "src/items/modules/GrappleModule.hpp"

#include "src/spaceobjects/BaseGameEntity.hpp"
#include "src/common/EntityManager.hpp"
#include "src/common/Message.hpp"
#include "src/common/MessageManager.hpp"

#include "src/spaceobjects/orbit.hpp" 
#include "src/spaceobjects/BasePlanet.hpp" 
#include "src/spaceobjects/asteroid.hpp"
#include "src/spaceobjects/Mineral.hpp"
#include "src/items/others/Bomb.hpp"
#include "src/spaceobjects/Container.hpp"
#include "src/items/others/GoodsPack.hpp"

#include "src/effects/particlesystem/particle.hpp"
#include "src/effects/particlesystem/baseParticleSystem.hpp"
#include "src/effects/particlesystem/blackHoleEffect.hpp"
#include "src/effects/particlesystem/explosion.hpp"
#include "src/effects/particlesystem/trail.hpp"
#include "src/effects/particlesystem/damage.hpp"

#include "src/spaceobjects/blackHole.hpp"

#include "src/items/equipment/BaseEquipment.hpp"
#include "src/items/equipment/RocketEquipment.hpp"
#include "src/items/equipment/LazerEquipment.hpp"
#include "src/items/equipment/RadarEquipment.hpp"
#include "src/items/equipment/DriveEquipment.hpp"
#include "src/items/equipment/BakEquipment.hpp"
#include "src/items/equipment/EnergizerEquipment.hpp"
#include "src/items/equipment/ProtectorEquipment.hpp"
#include "src/items/equipment/DroidEquipment.hpp"
#include "src/items/equipment/FreezerEquipment.hpp"
#include "src/items/equipment/ScanerEquipment.hpp"
#include "src/items/equipment/GrappleEquipment.hpp"


#include "src/docking/Platform.hpp"
#include "src/docking/Angar.hpp"
#include "src/docking/Shop.hpp"
#include "src/docking/Goverment.hpp"
#include "src/docking/Store.hpp"
#include "src/docking/BaseLand.hpp"
#include "src/docking/Kosmoport.hpp"
#include "src/docking/NatureLand.hpp"

#include "src/gui/cursor.hpp"  

#include "src/render/render.hpp"
#include "src/render/glsl.hpp"
#include "src/render/fbo.hpp"
#include "src/render/bloom.hpp"
#include "src/effects/shockWave.hpp"


#include "src/effects/distantNebulaBg.hpp"
#include "src/effects/distantStarBg.hpp"


#include "src/effects/Shield.hpp"  


#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/Star.hpp"  
#include "src/spaceobjects/Planet.hpp"

#include "src/spaceobjects/Turrel.hpp"

#include "src/spaceobjects//ItemSlot.hpp"
#include "src/spaceobjects/driveComplex.hpp"
#include "src/spaceobjects/WeaponComplex.hpp"
#include "src/spaceobjects/ProtectionComplex.hpp"
#include "src/spaceobjects/Vehicle.hpp"
#include "src/spaceobjects/rocketBullet.hpp"
#include "src/spaceobjects/SpaceStation.hpp"
#include "src/spaceobjects/satellite.hpp"
#include "src/spaceobjects/Ship.hpp"
#include "src/builder/ContainerBuilder.hpp"
#include "src/builder/items/equipment/BakEquipmentBuilder.hpp"
#include "src/builder/items/equipment/DriveEquipmentBuilder.hpp"
#include "src/builder/items/equipment/DroidEquipmentBuilder.hpp"
#include "src/builder/items/equipment/EnergizerEquipmentBuilder.hpp"
#include "src/builder/items/equipment/FreezerEquipmentBuilder.hpp"
#include "src/builder/items/equipment/GrappleEquipmentBuilder.hpp"
#include "src/builder/items/equipment/LazerEquipmentBuilder.hpp"
#include "src/builder/items/equipment/ProtectorEquipmentBuilder.hpp"
#include "src/builder/items/equipment/RadarEquipmentBuilder.hpp"
#include "src/builder/items/equipment/RocketEquipmentBuilder.hpp"
#include "src/builder/items/equipment/ScanerEquipmentBuilder.hpp"
///

#include "src/builder/BaseVehicleBuilder.hpp"
#include "src/builder/ShipBuilder.hpp"
#include "src/builder/ItemSlotBuilder.hpp"
#include "src/builder/VehicleBuilder.hpp"
#include "src/builder/StarSystemBuilder.hpp"
#include "src/builder/StarBuilder.hpp"
#include "src/builder/PlanetBuilder.hpp"
#include "src/builder/GalaxyBuilder.hpp"
#include "src/builder/PlayerBuilder.hpp"
#include "src/builder/NpcBuilder.hpp"
#include "src/builder/AngarBuilder.hpp"
#include "src/builder/ShopBuilder.hpp"
#include "src/builder/StoreBuilder.hpp"
#include "src/builder/GovermentBuilder.hpp"
#include "src/builder/KosmoportBuilder.hpp"


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

#include "src/spaceobjects/Container.cpp"    
#include "src/items/others/GoodsPack.cpp"   
#include "src/spaceobjects/Star.cpp"  
#include "src/spaceobjects/Planet.cpp"
#include "src/Base.cpp" 
#include "src/spaceobjects/BaseGameEntity.cpp" 
#include "src/common/EntityManager.cpp"
#include "src/common/Message.cpp"
#include "src/common/MessageManager.cpp"

#include "src/spaceobjects/orbit.cpp"
#include "src/spaceobjects/BasePlanet.cpp"
#include "src/spaceobjects/asteroid.cpp"   
#include "src/spaceobjects/Mineral.cpp" 
#include "src/spaceobjects/SpaceStation.cpp" 
#include "src/spaceobjects/satellite.cpp" 
#include "src/items/others/Bomb.cpp" 
#include "src/spaceobjects/blackHole.cpp"

#include "src/items/BaseItem.cpp"
#include "src/items/equipment/BaseEquipment.cpp"
#include "src/items/equipment/RocketEquipment.cpp"
#include "src/items/equipment/LazerEquipment.cpp"
#include "src/items/equipment/RadarEquipment.cpp"
#include "src/items/equipment/DriveEquipment.cpp"
#include "src/items/equipment/BakEquipment.cpp"
#include "src/items/equipment/EnergizerEquipment.cpp"
#include "src/items/equipment/ProtectorEquipment.cpp"
#include "src/items/equipment/DroidEquipment.cpp"
#include "src/items/equipment/FreezerEquipment.cpp"
#include "src/items/equipment/ScanerEquipment.cpp"
#include "src/items/equipment/GrappleEquipment.cpp"

#include "src/items/modules/BaseModule.cpp"
#include "src/items/modules/RocketModule.cpp"
#include "src/items/modules/LazerModule.cpp"
#include "src/items/modules/RadarModule.cpp"
#include "src/items/modules/DriveModule.cpp"
#include "src/items/modules/BakModule.cpp"
#include "src/items/modules/EnergizerModule.cpp"
#include "src/items/modules/ProtectorModule.cpp"
#include "src/items/modules/DroidModule.cpp"
#include "src/items/modules/FreezerModule.cpp"
#include "src/items/modules/ScanerModule.cpp"
#include "src/items/modules/GrappleModule.cpp"

#include "src/docking/Platform.cpp"
#include "src/docking/Angar.cpp"
#include "src/docking/Store.cpp"
#include "src/docking/Shop.cpp"
#include "src/docking/Goverment.cpp"
#include "src/docking/BaseLand.cpp"
#include "src/docking/Kosmoport.cpp"

#include "src/docking/NatureLand.cpp"

#include "src/gui/button.cpp"
#include "src/gui/guiSpace.cpp"
#include "src/gui/guiKosmoport.cpp"
#include "src/gui/guiStore.cpp"
#include "src/gui/guiManager.cpp"
#include "src/gui/guiVehicle.cpp"
#include "src/builder/ContainerBuilder.cpp"
#include "src/builder/BaseVehicleBuilder.cpp"
#include "src/builder/ShipBuilder.cpp"

#include "src/builder/ItemSlotBuilder.cpp"
#include "src/builder/AngarBuilder.cpp"
#include "src/builder/StoreBuilder.cpp"
#include "src/builder/VehicleBuilder.cpp"
#include "src/builder/StarSystemBuilder.cpp"
#include "src/builder/StarBuilder.cpp"
#include "src/builder/PlanetBuilder.cpp"
#include "src/builder/GalaxyBuilder.cpp"
#include "src/builder/PlayerBuilder.cpp"
#include "src/builder/NpcBuilder.cpp"
#include "src/builder/GovermentBuilder.cpp"
#include "src/builder/ShopBuilder.cpp"
#include "src/builder/KosmoportBuilder.cpp"

#include "src/gui/guiSkill.cpp"
#include "src/gui/guiMap.cpp"
#include "src/gui/cursor.cpp"   

#include "src/gui/UserInput.cpp"

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
#include "src/spaceobjects/Ship.cpp"
#include "src/spaceobjects/driveComplex.cpp"
#include "src/spaceobjects/Turrel.cpp"

#include "src/effects/distantNebulaBg.cpp"
#include "src/effects/distantStarBg.cpp"
#include "src/effects/particlesystem/particle.cpp"
#include "src/effects/particlesystem/baseParticleSystem.cpp"
#include "src/effects/particlesystem/blackHoleEffect.cpp"
#include "src/effects/particlesystem/explosion.cpp"
#include "src/effects/particlesystem/trail.cpp"
#include "src/effects/particlesystem/damage.cpp"
#include "src/effects/lazerTrace.cpp"
#include "src/effects/Shield.cpp"
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

#include "src/builder/items/equipment/BakEquipmentBuilder.cpp"
#include "src/builder/items/equipment/DriveEquipmentBuilder.cpp"
#include "src/builder/items/equipment/DroidEquipmentBuilder.cpp"
#include "src/builder/items/equipment/EnergizerEquipmentBuilder.cpp"
#include "src/builder/items/equipment/FreezerEquipmentBuilder.cpp"
#include "src/builder/items/equipment/GrappleEquipmentBuilder.cpp"
#include "src/builder/items/equipment/LazerEquipmentBuilder.cpp"
#include "src/builder/items/equipment/ProtectorEquipmentBuilder.cpp"
#include "src/builder/items/equipment/RadarEquipmentBuilder.cpp"
#include "src/builder/items/equipment/RocketEquipmentBuilder.cpp"
#include "src/builder/items/equipment/ScanerEquipmentBuilder.cpp"
////////////////////////////////////////////
