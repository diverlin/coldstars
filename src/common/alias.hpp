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


typedef std::vector<int> VEC_int_type; 
typedef std::vector<float> VEC_float_type;
typedef std::vector<std::string> VEC_string_type;

typedef std::vector<int*> VEC_pInt_type; 
typedef std::vector<float*> VEC_pFloat_type;
typedef std::vector<std::string*> VEC_pString_type;


class Ship;      typedef std::vector<Ship*> VEC_pShip_type;
class Star;      typedef std::vector<Star*> VEC_pStar_type; 
class Planet;    typedef std::vector<Planet*> VEC_pPlanet_type; 
class Mineral;   typedef std::vector<Mineral*> VEC_pMineral_type;
class Container; typedef std::vector<Container*> VEC_pContainer_type;
class Asteroid;  typedef std::vector<Asteroid*> VEC_pAsteroid_type; 
class Npc;       typedef std::vector<Npc*> VEC_pNpc_type; 
class RocketBullet;      typedef std::vector<RocketBullet*> VEC_pRocketBullet_type; 
class LazerTraceEffect;  typedef std::vector<LazerTraceEffect*> VEC_pLazerTrace_type; 
class StarSystem;typedef std::vector<StarSystem*> VEC_pStarSystem_type; 

class ParticleForDamageEffect; typedef std::vector<ParticleForDamageEffect*> VEC_pParticleForDamageEffect_type; 
class DamageEffect;      typedef std::vector<DamageEffect*> VEC_pDamageEffect_type; 
class ParticleForExplosionEffect; typedef std::vector<ParticleForExplosionEffect*> VEC_pParticleForExplosionEffect_type; 
class ExplosionEffect;   typedef std::vector<ExplosionEffect*> VEC_pExplosionEffect_type; 

class Mineral;   typedef std::vector<Mineral*> VEC_pMineral_type;
class Asteroid;  typedef std::vector<Asteroid*> VEC_pAsteroid_type; 

//class Kosmoport;

typedef std::vector<int> VEC_int_type; 

class ItemSlot;         typedef std::vector<ItemSlot*> VEC_pItemSlot_type;
		        typedef std::vector<ItemSlot> VEC_ItemSlot_type;

class Turrel;           typedef std::vector<Turrel*> VEC_pTurrel_type; 
class LazerTraceEffect; typedef std::vector<LazerTraceEffect*> VEC_pLazerTrace_type; 

class Store;




//class RocketEquipment;
//class LazerEquipment;
//class RadarEquipment;
//class DriveEquipment;
//class BakEquipment;
//class EnergizerEquipment;
//class ProtectorEquipment;
//class DroidEquipment;
//class FreezerEquipment;
//class ScanerEquipment;
//class GrappleEquipment;

class RocketModule;    typedef std::vector<RocketModule*>    VEC_pRocketModule_type;
class LazerModule;     typedef std::vector<LazerModule*>     VEC_pLazerModule_type;
class RadarModule;     typedef std::vector<RadarModule*>     VEC_pRadarModule_type;
class DriveModule;     typedef std::vector<DriveModule*>     VEC_pDriveModule_type;
class BakModule;       typedef std::vector<BakModule*>       VEC_pBakModule_type;
class EnergizerModule; typedef std::vector<EnergizerModule*> VEC_pEnergizerModule_type;
class ProtectorModule; typedef std::vector<ProtectorModule*> VEC_pProtectorModule_type;
class DroidModule;     typedef std::vector<DroidModule*>     VEC_pDroidModule_type;
class FreezerModule;   typedef std::vector<FreezerModule*>   VEC_pFreezerModule_type;
class ScanerModule;    typedef std::vector<ScanerModule*>    VEC_pScanerModule_type;
class GrappleModule;   typedef std::vector<GrappleModule*>   VEC_pGrappleModule_type;





class LandingArea; typedef std::vector<LandingArea*> VEC_pLandingArea_type; 
