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
	src/pilots/WeaponSelector.hpp
	src/spaceobjects/Vehicle.hpp
)


set (SOURCES
	src/gui/Slider.cpp
	src/common/Logger.cpp
	src/config/config.cpp
	src/common/SaveLoadManager.cpp
	src/pilots/WeaponSelector.cpp
	src/spaceobjects/Vehicle.cpp
	src/gui/GuiShop.cpp


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

	src/render/Glsl.cpp
	src/render/Fbo.cpp
	src/render/Bloom.cpp


	src/effects/particlesystem/Particle.cpp
	src/effects/particlesystem/BaseParticleSystem.cpp

	src/effects/particlesystem/DamageEffect.cpp
	src/effects/particlesystem/DriveEffect.cpp
	src/effects/particlesystem/ExplosionEffect.cpp

	src/builder/items/modules/DroidModuleBuilder.cpp
	src/builder/items/modules/RadarModuleBuilder.cpp

  	main.cpp
)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES} sfml-system sfml-graphics sfml-graphics sfml-window GL GLU GLEW)
target_link_libraries (${PROJECT})

ADD_CUSTOM_COMMAND(
  TARGET ${PROJECT}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ../install/${PROJECT}
  )
