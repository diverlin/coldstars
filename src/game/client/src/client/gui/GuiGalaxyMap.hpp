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

#include <client/gui/BaseGuiElement.hpp>
#include <client/gui/MouseData.hpp>

#include <jeti/PathVisual.hpp>

namespace model {
class Galaxy;
class Starsystem;
} // namespace model

namespace jeti {
class Render;
}

class GuiGalaxyMap : public BaseGuiElement
{
public:
    GuiGalaxyMap();
    ~GuiGalaxyMap();

    void BindGalaxy(model::Galaxy*);
    void UnbindGalaxy();

    model::Galaxy* GetGalaxy() const { return m_Galaxy; }

private:
    float m_ScaleParsecToScreenCoord;

    model::Galaxy* m_Galaxy;

//    jeti::PathView m_VisualHyperJumpRange;
//    jeti::PathView m_VisualHyperJumpPath;

    virtual void UpdateUnique(client::Player*) override final;
    virtual void RenderUnique(const jeti::Render&, client::Player*) const override final;

    glm::vec3 GetAbsoluteStarSystemPosition(const model::Starsystem&) const;
};

