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


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <common/Base.hpp>
#include <gui/Cursor.hpp>
#include <pilots/Show.hpp>
#include <render/Render.hpp>

class TurnTimer;

class StarSystem;
class Star;
class Planet;
class BlackHole;
class Asteroid;
class Vehicle;
class Npc;
class SpaceStation;
class Satellite;
class Ship;
class Container; 
class RocketBullet; 

class LazerTraceEffect;
class ShockWaveEffect;
class BaseParticleSystem;
class VerticalFlowText;


struct UnresolvedDataPlayer
{
    int npc_id;
    int starsystem_id;
    glm::vec2 screen_pos;
};


class Player : public Base
{
    public:
        Player(int);
        ~Player();

        virtual void PutChildsToGarbage() const {};
        
        Show& GetShow() { return show; };
                              
        Npc* GetNpc() const { return npc; }
        Cursor& GetCursor() { return cursor; }
        
        void BindNpc(Npc*);
        
        void ClearVisibleEntities();
        
        void AddIfVisible(Star*);
        void AddIfVisible(Planet*);
        void AddIfVisible(Asteroid*);             
        void AddIfVisible(Container*);         
        void AddIfVisible(RocketBullet*);  
        void AddIfVisible(BlackHole*);  
        void AddIfVisible(Vehicle*); 
        
        void AddIfVisible(ShockWaveEffect*);  
        void AddIfVisible(LazerTraceEffect*);  
        void AddIfVisible(BaseParticleSystem*); 
        void AddIfVisible(VerticalFlowText*); 
          
        bool IsAbleToGetFullControlOnScanedVehicle(bool force_full_control = false) const;
          
        void RunSession(const TurnTimer&); 
        
        void ForceStateMachineReset() const;
                
        void UpdatePostTransaction();        
        void UpdatePostTransactionEvent(TurnTimer&);
                                                
        void Save(boost::property_tree::ptree&) const;        
        void Load(const boost::property_tree::ptree&);
        void Resolve();
                 
    private:
        Npc* npc;
        
        Cursor cursor;
        
        Show show;  
        StarSystem* starsystem;
        
        // VISIBLE ENTITY LIST
        std::vector<Star*>         visible_STAR_vec;
        std::vector<Planet*>       visible_PLANET_vec;
        std::vector<Asteroid*>     visible_ASTEROID_vec;
        std::vector<Container*>    visible_CONTAINER_vec;
        std::vector<RocketBullet*> visible_ROCKET_vec;
        std::vector<BlackHole*>    visible_BLACKHOLE_vec;         
        std::vector<Ship*>         visible_SHIP_vec;
        std::vector<Satellite*>    visible_SATELLITE_vec;
        std::vector<SpaceStation*> visible_SPACESTATION_vec;
                    
        //effects
        std::vector<ShockWaveEffect*>    visible_effect_SHOCKWAVE_vec;
        std::vector<LazerTraceEffect*>   visible_effect_LAZERTRACE_vec;
        std::vector<BaseParticleSystem*> visible_effect_PARTICLESYSTEM_vec;          
        std::vector<VerticalFlowText*>   visible_text_DAMAGE_vec;
        //  
    
        void RenderInSpace(StarSystem*, bool, bool, bool); 
            void RenderInSpace_NEW(Renderer&, StarSystem*);
            void RenderCollisionRadius(const Renderer&) const;
            void RenderAxis(const Renderer&) const;
                                    
        void SessionInSpace(StarSystem*, const TurnTimer&);
        void SessionInKosmoport();
        void SessionInNatureLand();
                    
        bool MouseInteractionWithSpaceObjectsInSpace(const MouseData&);
        bool MouseInteractionWithRockets(const MouseData&);
        bool MouseInteractionWithContainers(const MouseData&);
        bool MouseInteractionWithSatellites(const MouseData&);
        bool MouseInteractionWithAsteroids(const MouseData&);
        bool MouseInteractionWithShips(const MouseData&);
        bool MouseInteractionWithBlackHoles(const MouseData&);
        bool MouseInteractionWithSpaceStations(const MouseData&);
        bool MouseInteractionWithPlanets(const MouseData&);
        bool MouseInteractionWithStars(const MouseData&);
        void MouseNavigation(const MouseData&) const;

        UnresolvedDataPlayer data_unresolved_player;            
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();

    friend class UserInput;
};

bool isObjectOnScreen(const glm::vec3&, const glm::vec3&);
bool isObjectOnScreen(const glm::vec3&, float);
bool isPointOnScreen(const glm::vec2&);

bool isObjectWithinRadarRange(BaseParticleSystem*, Vehicle*);                                      
bool isObjectWithinRadarRange(ShockWaveEffect*, Vehicle*);
bool isObjectWithinRadarRange(LazerTraceEffect*, Vehicle*);
            
#endif 



        
