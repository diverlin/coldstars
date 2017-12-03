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

#include <core/type/GuiType.hpp>
#include <ceti/Box2D.hpp>

#include <map>
#include <vector>

namespace client {
class Player;
} // namespace client

namespace jeti {
class AnimationEffect2D;

namespace model {
class Material;
} // namespace model

namespace control {
class Material;
} // namespace control

class Render;
} // namespace jeti

namespace gui {

class Base
{
public:
    Base(gui::Type id=gui::Type::NONE,
         gui::Type group=gui::Type::NONE,
         const std::string& _info="",
         jeti::model::Material* material=nullptr);
    virtual ~Base();

    bool isRoot() const { return (m_parent == nullptr); }
    void setParent(Base* parent) { m_parent = parent; }
    void setLabel(const std::string& label) { m_label = label; }
    void setMaterial(jeti::control::Material* material) { m_material = material; }
    void setCenter(const glm::vec2& center) { m_box.setCenterOrig(center); }
    void setSize(float w, float h) { m_box.setSize(w, h); }
    void setSize(const glm::vec2& size) { m_box.setSize(size); }
    void setScale(float scale) { m_box.setScale(scale); }

    gui::Type id() const { return m_id; }
    gui::Type group() const { return m_group; }

    const ceti::Box2D& box() const { return m_box; }
    ceti::Box2D& box() { return m_box; } // !!!

    const jeti::control::Material& material() const { return *m_material; }

    bool isLocked() const { return m_isLocked; }
    bool isPressed() const { return m_isPressed; }

    bool hasAnimation() const { return (m_animation != nullptr); }

    static Base* element(gui::Type);

    void updatePosition();
    Base* updateMouseInteraction(const glm::vec2&);

    void add(Base*, const glm::vec2&);

    void show() {
        m_isVisible = true;
        for(Base* child: m_children) {
            child->show();
        }
    }
    void hide() {
        m_isVisible = false;
        for(Base* child: m_children) {
            child->hide();
        }
    }

    virtual void onPressEventMBL(client::Player*) {}
    virtual void onPressEventMBR(client::Player*) {}
    virtual void resetState();

    virtual void update(client::Player*);
    virtual void render(const jeti::Render&, client::Player*) const;
    virtual void renderInfo(const jeti::Render&) const {}

protected:
    void _setGroup(gui::Type group) { m_group = group; }

    void _setBox(const ceti::Box2D& box) { m_box = box; }

    void _setIsPressed(bool pressed) { m_isPressed = pressed; }
    void _setIsLocked(bool locked) { m_isLocked = locked; }

    void _setAnimationProgram(jeti::AnimationEffect2D* animation_program) { m_animation = animation_program; }

    bool _hasTextureOb() const { return (m_material != nullptr); }

    const std::string& _info() const { return m_info; }
    const std::string& _label() const { return m_label; }

    bool _animationProgramActive() const { return (m_animation != nullptr); }
    void _deleteAnimationProgram();

    void _pressEventMBL_onGuiElement(gui::Type, int, client::Player*);
    void _resetStateEventOnGuiElement(gui::Type);

    virtual void _updateUnique(client::Player*);
    void _updateChildren(client::Player*);

    virtual void _renderUnique(const jeti::Render&, client::Player*) const;
    void _renderChildren(const jeti::Render&, client::Player*) const;

    std::vector<Base*>& _children() { return m_children; } // !!!

private:
    static std::map<gui::Type, Base*> m_elements;

    Base* m_parent = nullptr;

    std::vector<Base*> m_children;

    gui::Type m_id;
    gui::Type m_group;

    jeti::control::Material* m_material = nullptr;

    std::string m_info;
    std::string m_label;

    ceti::Box2D m_box;

    bool m_isLocked = false;
    bool m_isPressed = false;
    bool m_isVisible = false; // setting to false cause bug

    jeti::AnimationEffect2D* m_animation = nullptr;

    friend class Manager;
};

} // namespace gui
