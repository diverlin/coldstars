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


#include "src/resources/textureOb.hpp"
#include "src/resources/textureManager.hpp"
#include "src/resources/resources.hpp"
#include "src/resources/init.hpp"

#include "src/common/rect.hpp"

#include "src/gui/UserInput.hpp"

#include "src/items/others/Bomb.hpp"
#include "src/spaceobjects/Container.hpp"
#include "src/items/others/GoodsPack.hpp"


#include "src/spaceobjects/BlackHole.hpp"

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

#include "src/effects/ShockWaveEffect.hpp"

#include "src/effects/BaseBackGroundEffect.hpp"
#include "src/effects/DistantNebulaEffect.hpp"
#include "src/effects/DistantStarEffect.hpp"


#include "src/effects/Shield.hpp"  


#include "src/effects/lazerTrace.hpp"


#include "src/spaceobjects/Turrel.hpp"

#include "src/spaceobjects/BaseSlot.hpp"
#include "src/docking/VehicleSlot.hpp"
#include "src/spaceobjects/ItemSlot.hpp"
#include "src/spaceobjects/DriveComplex.hpp"
#include "src/spaceobjects/WeaponComplex.hpp"
#include "src/spaceobjects/ProtectionComplex.hpp"

#include "src/spaceobjects/RocketBullet.hpp"
#include "src/spaceobjects/SpaceStation.hpp"
#include "src/spaceobjects/Satellite.hpp"
#include "src/spaceobjects/Ship.hpp"

#include "src/pilots/Player.hpp"





//   
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
#include "src/world/starsystem.hpp"    
#include "src/effects/lazerTrace.hpp"

#include "src/world/galaxy.hpp"
#include "src/gui/GuiMap.hpp"

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
 

#include "src/spaceobjects/SpaceStation.cpp" 
#include "src/spaceobjects/Satellite.cpp" 
#include "src/items/others/Bomb.cpp" 
#include "src/spaceobjects/BlackHole.cpp"

#include "src/docking/VehicleSlot.cpp"
#include "src/docking/Room.cpp"
#include "src/docking/Angar.cpp"
#include "src/docking/Store.cpp"
#include "src/docking/Shop.cpp"
#include "src/docking/Goverment.cpp"
#include "src/docking/BaseLand.cpp"
#include "src/docking/Kosmoport.cpp"

#include "src/docking/NatureLand.cpp"

#include "src/gui/BaseGui.cpp"
#include "src/gui/BaseButton.cpp"
#include "src/gui/ButtonTrigger.cpp"
#include "src/gui/ButtonSingle.cpp"
#include "src/gui/GuiRadar.cpp"
#include "src/gui/GuiSpace.cpp"
#include "src/gui/GuiAngar.cpp"
#include "src/gui/GuiKosmoport.cpp"
#include "src/gui/GuiStore.cpp"
#include "src/gui/GuiManager.cpp"
#include "src/gui/GuiVehicle.cpp"
#include "src/gui/GuiVehicle2.cpp"
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

#include "src/spaceobjects/Ship.cpp"
#include "src/spaceobjects/DriveComplex.cpp"
#include "src/spaceobjects/Turrel.cpp"


#include "src/effects/BaseBackGroundEffect.cpp"
#include "src/effects/DistantNebulaEffect.cpp"
#include "src/effects/DistantStarEffect.cpp"

#include "src/effects/lazerTrace.cpp"
#include "src/effects/Shield.cpp"
#include "src/spaceobjects/RocketBullet.cpp"

#include "src/pilots/Player.cpp"
//

#include "src/pilots/Observation.cpp" 

#include "src/render/Render.cpp"

#include "src/effects/ShockWaveEffect.cpp"

#include "src/text/textstuff.cpp"


#include "src/common/TurnTimer.cpp"
#include "src/common/GameDate.cpp"

#include "src/builder/items/other/BombBuilder.cpp"

////////////////////////////////////////////
