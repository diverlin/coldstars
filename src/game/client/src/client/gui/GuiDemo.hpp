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

#include <SFML/Window.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace jeti {
class SFMLWrapper;
} // namespace jeti

namespace gui {

namespace info {
class StarSystem;
class Camera;
class Renderer;
class Table;
} // namespace info

class Demo
{
public:
    Demo(jeti::SFMLWrapper*);
    ~Demo();

    sfg::Desktop* desktop() { return &m_desktop; }

    void update(const std::vector<sf::Event>&);
    void draw();

    info::StarSystem* infoStarSystem() const { return m_infoStarSystem; }
    info::Camera* infoCamera() const { return m_infoCamera; }
    info::Renderer* infoRender() const { return m_infoRender; }
    info::Table* modelTable() const { return m_modelTable; }
    info::Table* descriptorTable() const { return m_descriptorTable; }

    sfg::Window::Ptr windowObjectProperties() const { return m_windowObjectProperties; }

    void updateFps(int);
    void setMousePosScreenCoord(int, int);
    void setMousePosWorldCoord(int, int);

private:
    sf::Clock m_clock;
    sf::Window& m_window;
    sfg::Desktop m_desktop;
    sfg::SFGUI m_gui;

    sfg::Label::Ptr m_fpsLabel;
    sfg::Label::Ptr m_mousePosScLabel;
    sfg::Label::Ptr m_mousePosWcLabel;

    info::StarSystem* m_infoStarSystem = nullptr;
    info::Camera* m_infoCamera = nullptr;
    info::Renderer* m_infoRender = nullptr;

    sfg::Window::Ptr m_windowObjectProperties;
    info::Table* m_modelTable = nullptr;
    info::Table* m_descriptorTable = nullptr;
};

} // namespace gui
