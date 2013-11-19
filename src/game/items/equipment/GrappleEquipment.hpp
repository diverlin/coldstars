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


#ifndef GRAPPLEEQUIPMENT_HPP
#define GRAPPLEEQUIPMENT_HPP

class Renderer;
      
#include "BaseEquipment.hpp"
#include "../../spaceobjects/BaseSpaceEntity.hpp"


class GrappleEquipment : public BaseEquipment
{
    public:
        GrappleEquipment(int);   
        virtual ~GrappleEquipment();

        void SetStrengthOrig(int strength_orig)     { this->strength_orig   = strength_orig; }
        void SetRadiusOrig(int radius_orig)         { this->radius_orig     = radius_orig; }
        void SetSpeedOrig(int speed_orig)           { this->speed_orig      = speed_orig; }
                                
        int GetStrength()   const { return strength; };
        int GetRadius()     const { return radius; };
        int GetSpeed()      const { return speed; };
              
        bool CheckIfTargetAlreadyExistInQueue(BaseSpaceEntity* target) const;
        void AddTarget(BaseSpaceEntity*);
        void RemoveTarget(BaseSpaceEntity*);

        void RemoveAllTargets();
                                
        std::string GetTargetStr() const;

        void UpdateGrabScenarioProgram_inDynamic();
        void RenderGrabTrail(const Renderer&);
        
        virtual void UpdateProperties();  
        
        void CountPrice();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Load();
        
    private:
        int strength_orig;
        int strength_add;
        int strength;
        
        int radius_orig;
        int radius_add;
        int radius;
        
        int speed_orig;
        int speed_add;
        int speed; 
        
        int free_strength;
        
        std::vector<BaseSpaceEntity*> target_vec;
        
        void virtual AddUniqueInfo();
        std::string GetStrengthStr();
        std::string GetRadiusStr();
        std::string GetSpeedStr();
        
        void SaveDataUniqueGrappleEquipment(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueGrappleEquipment(const boost::property_tree::ptree&);
        void ResolveDataUniqueGrappleEquipment(); 
};

#endif 
