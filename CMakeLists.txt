cmake_minimum_required (VERSION 2.6)

set (PROJECT game)

project (${PROJECT})

#include_directories (share/)

set (LIBRARIES
  )
#foreach (LIBRARY ${LIBRARIES})
  #  add_subdirectory (share/${LIBRARY}/ bin/${LIBRARY})
  #endforeach()

add_definitions (-Wall -pedantic -std=c++0x -std=gnu++0x -pedantic-errors -Wextra -w -Waddress -Wc++0x-compat)

set (HEADERS
	include.hpp

	src/config/config.hpp	
	src/common/SaveLoadManager.hpp
	src/spaceobjects/Vehicle.hpp
)


set (SOURCES
	src/resources/textureOb.cpp
	src/resources/textureManager.cpp
	src/resources/resources.cpp
	src/resources/init.cpp

	src/gui/Slider.cpp
	src/common/Logger.cpp
	src/config/config.cpp
	src/common/SaveLoadManager.cpp
	src/spaceobjects/Vehicle.cpp
	src/gui/GuiShop.cpp

	src/common/common.cpp
	src/common/EntityManager.cpp
	src/common/Collision.cpp

	src/resources/MeshCollector.cpp
	src/resources/ShaderCollector.cpp
	src/resources/GlslLoader.cpp

	src/common/Base.cpp 
	src/spaceobjects/BaseGameEntity.cpp 

	src/ai/MacroTask.cpp
	src/ai/MicroTask.cpp

	src/ai/MicroTaskManager.cpp
	src/ai/MacroTaskManager.cpp

	src/ai/aiModel/AiModelCollector.cpp

	src/ai/aiModel/BaseAiModel.cpp
	src/ai/aiModel/AiModelRanger.cpp
	src/ai/aiModel/AiModelTrader.cpp
	src/ai/aiModel/AiModelConqueror.cpp

	src/ai/scenarios/ScenarioCollector.cpp

	src/ai/scenarios/macro/MacroScenarioSelfSafety.cpp
	src/ai/scenarios/macro/MacroScenarioStarSystemDefence.cpp
	src/ai/scenarios/macro/MacroScenarioStarSystemLiberation.cpp

	src/ai/scenarios/micro/MicroScenarioDestroy.cpp
	src/ai/scenarios/micro/MicroScenarioGrab.cpp
	src/ai/scenarios/micro/MicroScenarioJump.cpp
	src/ai/scenarios/micro/MicroScenarioDocking.cpp
	src/ai/scenarios/micro/MicroScenarioLaunching.cpp
	src/ai/scenarios/micro/MicroScenarioExploration.cpp

	src/ai/scenarios/macro/MacroScenarioGoodsTrading.cpp

	src/ai/StateMachine.cpp

	src/render/Screen.cpp

	src/render/Fbo.cpp
	src/render/Bloom.cpp


	src/spaceobjects/BasePlanet.cpp

	src/effects/particlesystem/Particle.cpp
	src/effects/particlesystem/BaseParticleSystem.cpp

	src/effects/particlesystem/DamageEffect.cpp
	src/effects/particlesystem/DriveEffect.cpp
	src/effects/particlesystem/ExplosionEffect.cpp

	src/builder/items/equipment/BakEquipmentBuilder.cpp
	src/builder/items/equipment/DriveEquipmentBuilder.cpp
	src/builder/items/equipment/DroidEquipmentBuilder.cpp
	src/builder/items/equipment/EnergizerEquipmentBuilder.cpp
	src/builder/items/equipment/FreezerEquipmentBuilder.cpp
	src/builder/items/equipment/GrappleEquipmentBuilder.cpp
	src/builder/items/equipment/LazerEquipmentBuilder.cpp
	src/builder/items/equipment/ProtectorEquipmentBuilder.cpp
	src/builder/items/equipment/RadarEquipmentBuilder.cpp
	src/builder/items/equipment/RocketEquipmentBuilder.cpp
	src/builder/items/equipment/ScanerEquipmentBuilder.cpp

	src/builder/items/modules/DroidModuleBuilder.cpp
	src/builder/items/modules/RadarModuleBuilder.cpp
	src/builder/items/modules/DriveModuleBuilder.cpp
	src/builder/items/modules/BakModuleBuilder.cpp
	src/builder/items/modules/GrappleModuleBuilder.cpp
	src/builder/items/modules/LazerModuleBuilder.cpp
	src/builder/items/modules/ProtectorModuleBuilder.cpp
	src/builder/items/modules/RocketModuleBuilder.cpp
	src/builder/items/modules/ScanerModuleBuilder.cpp

	src/builder/items/artefacts/GravityArtefactBuilder.cpp
	src/builder/items/artefacts/ProtectorArtefactBuilder.cpp

	src/builder/items/other/BombBuilder.cpp

	src/items/BaseItem.cpp
	src/items/equipment/BaseEquipment.cpp
	src/items/equipment/RocketEquipment.cpp
	src/items/equipment/LazerEquipment.cpp
	src/items/equipment/RadarEquipment.cpp
	src/items/equipment/DriveEquipment.cpp
	src/items/equipment/BakEquipment.cpp
	src/items/equipment/EnergizerEquipment.cpp
	src/items/equipment/ProtectorEquipment.cpp
	src/items/equipment/DroidEquipment.cpp
	src/items/equipment/FreezerEquipment.cpp
	src/items/equipment/ScanerEquipment.cpp
	src/items/equipment/GrappleEquipment.cpp

	src/items/modules/BaseModule.cpp
	src/items/modules/RocketModule.cpp
	src/items/modules/LazerModule.cpp
	src/items/modules/RadarModule.cpp
	src/items/modules/DriveModule.cpp
	src/items/modules/BakModule.cpp
	src/items/modules/EnergizerModule.cpp
	src/items/modules/ProtectorModule.cpp
	src/items/modules/DroidModule.cpp
	src/items/modules/FreezerModule.cpp
	src/items/modules/ScanerModule.cpp
	src/items/modules/GrappleModule.cpp

	src/items/artefacts/GravityArtefact.cpp
	src/items/artefacts/ProtectorArtefact.cpp

	src/resources/GuiTextureObCollector.cpp

	src/spaceobjects/Asteroid.cpp 
	src/spaceobjects/Planet.cpp
	src/spaceobjects/Star.cpp  
	src/spaceobjects/Ship.cpp
	src/spaceobjects/SpaceStation.cpp 
	src/spaceobjects/Satellite.cpp 

	src/builder/StarBuilder.cpp
	src/builder/PlanetBuilder.cpp
	src/builder/AsteroidBuilder.cpp
	src/builder/ContainerBuilder.cpp
	src/builder/BaseVehicleBuilder.cpp
	src/builder/ShipBuilder.cpp
	src/builder/RocketBulletBuilder.cpp
	src/builder/SpaceStationBuilder.cpp
	src/builder/SatelliteBuilder.cpp

	src/builder/ItemSlotBuilder.cpp
	src/builder/VehicleSlotBuilder.cpp
	src/builder/AngarBuilder.cpp
	src/builder/StoreBuilder.cpp
	src/builder/StarSystemBuilder.cpp

	src/builder/GalaxyBuilder.cpp
	src/builder/PlayerBuilder.cpp
	src/builder/NpcBuilder.cpp
	src/builder/GovermentBuilder.cpp
	src/builder/ShopBuilder.cpp
	src/builder/KosmoportBuilder.cpp

	src/pilots/Skill.cpp
	src/pilots/Npc.cpp           

	src/slots/BaseSlot.cpp
	src/slots/ItemSlot.cpp
	src/slots/VehicleSlot.cpp

	src/parts/orbit.cpp

	src/parts/WeaponComplex.cpp
	src/parts/ProtectionComplex.cpp
	src/parts/DriveComplex.cpp
	src/parts/Turrel.cpp

	src/docking/Room.cpp
	src/docking/Angar.cpp
	src/docking/Store.cpp
	src/docking/Shop.cpp
	src/docking/Goverment.cpp
	src/docking/BaseLand.cpp
	src/docking/Kosmoport.cpp
	src/docking/NatureLand.cpp

  	main.cpp
)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES} sfml-system sfml-graphics sfml-graphics sfml-window GL GLU GLEW boost_system boost_filesystem)
target_link_libraries (${PROJECT})

ADD_CUSTOM_COMMAND(
  TARGET ${PROJECT}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ../install/${PROJECT}
  )
