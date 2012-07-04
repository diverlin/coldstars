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

class StateMachine;
class ScenarioBase;
class BaseAiModel;

class Player;
class FBO;
class BloomEffect;

class Galaxy;

class GuiManager;
class GuiSpace;
class GuiKosmoport;
class GuiMap;

class Kosmoport;
class WeaponSelector;


class ScenarioCollector;

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

#include "src/common/GameDate.hpp"
#include "src/common/TurnTimer.hpp"

#include "src/common/Logger.hpp"
#include "src/common/myStr.hpp"

//#include "src/render/Screen.hpp"

#include "src/resources/objLoader.hpp"

//#include "src/common/gameStruct.hpp"
#include "src/common/rand.hpp"
#include "src/common/id.hpp"
#include "src/common/points.hpp"
#include "src/common/common.hpp"

#include "src/render/PathVisual.hpp"

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
#include "src/spaceobjects/Asteroid.hpp"
#include "src/items/others/Bomb.hpp"
#include "src/spaceobjects/Container.hpp"
#include "src/items/others/GoodsPack.hpp"

#include "src/effects/particlesystem/particle.hpp"
#include "src/effects/particlesystem/baseParticleSystem.hpp"
#include "src/effects/particlesystem/blackHoleEffect.hpp"
#include "src/effects/particlesystem/explosion.hpp"
#include "src/effects/particlesystem/trail.hpp"
#include "src/effects/particlesystem/damage.hpp"

#include "src/spaceobjects/BlackHole.hpp"

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


#include "src/docking/Room.hpp"
#include "src/docking/Angar.hpp"
#include "src/docking/Shop.hpp"
#include "src/docking/Goverment.hpp"
#include "src/docking/Store.hpp"
#include "src/docking/BaseLand.hpp"
#include "src/docking/Kosmoport.hpp"
#include "src/docking/NatureLand.hpp"

#include "src/gui/Cursor.hpp"  

#include "src/render/Render.hpp"
#include "src/render/Glsl.hpp"
#include "src/render/Fbo.hpp"
#include "src/render/Bloom.hpp"
#include "src/effects/ShockWaveEffect.hpp"

#include "src/effects/BaseBackGroundEffect.hpp"
#include "src/effects/DistantNebulaEffect.hpp"
#include "src/effects/DistantStarEffect.hpp"


#include "src/effects/Shield.hpp"  


#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/Star.hpp"  
#include "src/spaceobjects/Planet.hpp"

#include "src/spaceobjects/Turrel.hpp"

#include "src/spaceobjects/BaseSlot.hpp"
#include "src/docking/VehicleSlot.hpp"
#include "src/spaceobjects/ItemSlot.hpp"
#include "src/spaceobjects/DriveComplex.hpp"
#include "src/spaceobjects/WeaponComplex.hpp"
#include "src/spaceobjects/ProtectionComplex.hpp"
#include "src/spaceobjects/Vehicle.hpp"
#include "src/spaceobjects/RocketBullet.hpp"
#include "src/spaceobjects/SpaceStation.hpp"
#include "src/spaceobjects/Satellite.hpp"
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

#include "src/builder/items/module/RadarModuleBuilder.hpp"

#include "src/builder/items/other/BombBuilder.hpp"
///

#include "src/builder/BaseVehicleBuilder.hpp"
#include "src/builder/ShipBuilder.hpp"
#include "src/builder/RocketBulletBuilder.hpp"
#include "src/builder/SpaceStationBuilder.hpp"
#include "src/builder/SatelliteBuilder.hpp"
#include "src/builder/ItemSlotBuilder.hpp"
#include "src/builder/VehicleSlotBuilder.hpp"
#include "src/builder/StarSystemBuilder.hpp"
#include "src/builder/StarBuilder.hpp"
#include "src/builder/AsteroidBuilder.hpp"
#include "src/builder/PlanetBuilder.hpp"
#include "src/builder/GalaxyBuilder.hpp"
#include "src/builder/PlayerBuilder.hpp"
#include "src/builder/NpcBuilder.hpp"
#include "src/builder/AngarBuilder.hpp"
#include "src/builder/ShopBuilder.hpp"
#include "src/builder/StoreBuilder.hpp"
#include "src/builder/GovermentBuilder.hpp"
#include "src/builder/KosmoportBuilder.hpp"


#include "src/pilots/Player.hpp"

#include "src/pilots/Skill.hpp"
#include "src/pilots/Npc.hpp"           

#include "src/ai/scenarios/BaseScenario.hpp" 

#include "src/ai/scenarios/micro/MicroScenarioDestroy.hpp" 
#include "src/ai/scenarios/micro/MicroScenarioGrab.hpp" 
#include "src/ai/scenarios/micro/MicroScenarioJump.hpp" 
#include "src/ai/scenarios/micro/MicroScenarioDocking.hpp"
#include "src/ai/scenarios/micro/MicroScenarioLaunching.hpp"

#include "src/ai/BaseTask.hpp"
#include "src/ai/MacroTask.hpp"
#include "src/ai/MicroTask.hpp"
#include "src/ai/MicroTaskManager.hpp"
#include "src/ai/MacroTaskManager.hpp"


#include "src/ai/StateMachine.hpp"
#include "src/ai/ScenarioCollector.hpp"


#include "src/ai/scenarios/macro/MacroScenarioSelfSafety.hpp"
#include "src/ai/scenarios/macro/MacroScenarioStarSystemLiberation.hpp"
#include "src/ai/scenarios/macro/MacroScenarioStarSystemDefence.hpp"

#include "src/ai/aiModel/BaseAiModel.hpp"
#include "src/ai/aiModel/AiModelRanger.hpp"
#include "src/ai/aiModel/AiModelConqueror.hpp"

//   
#include "src/pilots/Observation.hpp" 

#include "src/gui/Button.hpp"
#include "src/gui/GuiSpace.hpp"
#include "src/gui/GuiAngar.hpp"
#include "src/gui/GuiStore.hpp"
#include "src/gui/GuiKosmoport.hpp"
#include "src/gui/GuiVehicle.hpp"
#include "src/gui/GuiSkill.hpp"
#include "src/gui/GuiManager.hpp"

#include "src/world/garbageEffects.hpp"  
#include "src/world/GarbageEntities.hpp"  
#include "src/world/starsystem.hpp"    
#include "src/effects/lazerTrace.hpp"

#include "src/world/galaxy.hpp"
#include "src/gui/GuiMap.hpp"



#include "src/common/global.hpp"
#include "src/render/Screen.hpp"











#include "src/render/PathVisual.cpp"
#include "src/common/rand.cpp"
#include "src/common/gameStruct.cpp"
#include "src/common/id.cpp"

#include "src/common/myVector.cpp"
#include "src/common/myStr.cpp"
#include "src/world/galaxy.cpp"
#include "src/world/garbageEffects.cpp"  
#include "src/world/GarbageEntities.cpp"  
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
#include "src/spaceobjects/Asteroid.cpp"   
#include "src/spaceobjects/SpaceStation.cpp" 
#include "src/spaceobjects/Satellite.cpp" 
#include "src/items/others/Bomb.cpp" 
#include "src/spaceobjects/BlackHole.cpp"

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

#include "src/docking/VehicleSlot.cpp"
#include "src/docking/Room.cpp"
#include "src/docking/Angar.cpp"
#include "src/docking/Store.cpp"
#include "src/docking/Shop.cpp"
#include "src/docking/Goverment.cpp"
#include "src/docking/BaseLand.cpp"
#include "src/docking/Kosmoport.cpp"

#include "src/docking/NatureLand.cpp"

#include "src/gui/Button.cpp"
#include "src/gui/GuiSpace.cpp"
#include "src/gui/GuiAngar.cpp"
#include "src/gui/GuiKosmoport.cpp"
#include "src/gui/GuiStore.cpp"
#include "src/gui/GuiManager.cpp"
#include "src/gui/GuiVehicle.cpp"
#include "src/builder/ContainerBuilder.cpp"
#include "src/builder/BaseVehicleBuilder.cpp"
#include "src/builder/ShipBuilder.cpp"
#include "src/builder/RocketBulletBuilder.cpp"
#include "src/builder/SpaceStationBuilder.cpp"
#include "src/builder/SatelliteBuilder.cpp"

#include "src/builder/ItemSlotBuilder.cpp"
#include "src/builder/VehicleSlotBuilder.cpp"
#include "src/builder/AngarBuilder.cpp"
#include "src/builder/StoreBuilder.cpp"
#include "src/builder/StarSystemBuilder.cpp"
#include "src/builder/StarBuilder.cpp"
#include "src/builder/AsteroidBuilder.cpp"
#include "src/builder/PlanetBuilder.cpp"
#include "src/builder/GalaxyBuilder.cpp"
#include "src/builder/PlayerBuilder.cpp"
#include "src/builder/NpcBuilder.cpp"
#include "src/builder/GovermentBuilder.cpp"
#include "src/builder/ShopBuilder.cpp"
#include "src/builder/KosmoportBuilder.cpp"

#include "src/gui/GuiSkill.cpp"
#include "src/gui/GuiMap.cpp"
#include "src/gui/Cursor.cpp"   

#include "src/gui/UserInput.cpp"

#include "src/resources/textureOb.cpp"
#include "src/resources/textureManager.cpp"
#include "src/resources/resources.cpp"
#include "src/resources/init.cpp"

#include "src/common/rect.cpp"
#include "src/common/points.cpp"

#include "src/spaceobjects/BaseSlot.cpp"
#include "src/spaceobjects/ItemSlot.cpp"

#include "src/spaceobjects/WeaponComplex.cpp"
#include "src/spaceobjects/ProtectionComplex.cpp"
#include "src/spaceobjects/Vehicle.cpp"
#include "src/spaceobjects/Ship.cpp"
#include "src/spaceobjects/DriveComplex.cpp"
#include "src/spaceobjects/Turrel.cpp"


#include "src/effects/BaseBackGroundEffect.cpp"
#include "src/effects/DistantNebulaEffect.cpp"
#include "src/effects/DistantStarEffect.cpp"
#include "src/effects/particlesystem/particle.cpp"
#include "src/effects/particlesystem/baseParticleSystem.cpp"
#include "src/effects/particlesystem/blackHoleEffect.cpp"
#include "src/effects/particlesystem/explosion.cpp"
#include "src/effects/particlesystem/trail.cpp"
#include "src/effects/particlesystem/damage.cpp"
#include "src/effects/lazerTrace.cpp"
#include "src/effects/Shield.cpp"
#include "src/spaceobjects/RocketBullet.cpp"

#include "src/pilots/Player.cpp"
#include "src/pilots/Skill.cpp"

#include "src/pilots/Npc.cpp"
//
#include "src/ai/scenarios/BaseScenario.cpp" 

#include "src/ai/scenarios/micro/MicroScenarioDestroy.cpp" 
#include "src/ai/scenarios/micro/MicroScenarioGrab.cpp" 
#include "src/ai/scenarios/micro/MicroScenarioJump.cpp" 
#include "src/ai/scenarios/micro/MicroScenarioDocking.cpp"
#include "src/ai/scenarios/micro/MicroScenarioLaunching.cpp"

#include "src/ai/BaseTask.cpp"
#include "src/ai/MacroTask.cpp"
#include "src/ai/MicroTask.cpp"
#include "src/ai/MicroTaskManager.cpp"
#include "src/ai/MacroTaskManager.cpp"
#include "src/ai/StateMachine.cpp"
#include "src/ai/ScenarioCollector.cpp"

#include "src/ai/scenarios/macro/MacroScenarioSelfSafety.cpp"
#include "src/ai/scenarios/macro/MacroScenarioStarSystemLiberation.cpp"
#include "src/ai/scenarios/macro/MacroScenarioStarSystemDefence.cpp"

#include "src/ai/aiModel/BaseAiModel.cpp"
#include "src/ai/aiModel/AiModelRanger.cpp"
#include "src/ai/aiModel/AiModelConqueror.cpp"

#include "src/pilots/Observation.cpp" 

#include "src/common/common.cpp"

#include "src/render/Render.cpp"

#include "src/render/Glsl.cpp"
#include "src/render/Fbo.cpp"
#include "src/render/Bloom.cpp"
#include "src/effects/ShockWaveEffect.cpp"

#include "src/text/textstuff.cpp"

//#include "src/render/Screen.cpp"
#include "src/common/TurnTimer.cpp"
#include "src/common/GameDate.cpp"
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


#include "src/builder/items/module/RadarModuleBuilder.cpp"

#include "src/builder/items/other/BombBuilder.cpp"
#include "src/common/Logger.cpp"
#include "src/render/Screen.cpp"
////////////////////////////////////////////
