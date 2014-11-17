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

#pragma once

#include <jeti/BaseDrawable.hpp>

class BaseVehicleDrawable : public jeti::BaseDrawable
{   
    public:
        BaseVehicleDrawable(jeti::TextureOb*, jeti::Mesh*);
        virtual ~BaseVehicleDrawable() override;

        void CreateDriveComplexTextureDependedStuff();
        void CreateProtectionComplexTextureDependedStuff(); 

        virtual void UpdateInSpace(int, bool) = 0;        

        void UpdateSpecialEffect();
            
//        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
//        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
        void RenderInfo(const glm::vec2&, int, int);
                    
        void RenderRadarRange();
        void RenderGrappleRange();
        
    protected:    
        virtual void UpdateInfo() = 0;
        
        void RenderGrabTrail(const jeti::Renderer&) const;
        void RenderKorpus(const jeti::Renderer&);
        void RenderTurrels() const;
        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;
};

