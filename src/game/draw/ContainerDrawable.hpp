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

class ContainerDrawable : public jeti::BaseDrawable
{
    public:                  
        ContainerDrawable(jeti::TextureOb*, jeti::Mesh*);
        virtual ~ContainerDrawable() final override;
        
        //virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
        void Render(const jeti::Renderer&);
        
    private:
        //virtual void UpdateInfo() override final;
};

