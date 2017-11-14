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

#include <ceti/type/IdType.hpp>
#include <ceti/Orientation.hpp>
#include <ceti/rect.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ceti {

namespace control {
class Orientation;
} // namespace control

namespace model {
class Base;
} // namespace model

namespace descriptor {
class BaseView;
} // namespace model

} // namespace ceti

namespace jeti {

class Mesh;

namespace control {
class Material;
} // namespace control

namespace animation {
class BaseRotation;
} // namespace animation

class Render;

class Base
{
    static int_t counter;
public:
    Base();
    Base(Mesh*, control::Material*);
    virtual ~Base();

    int_t id() const { return m_id; }

    const glm::vec3& position() const { return _orientation()->position(); }
    const glm::vec3& direction() const { return _orientation()->direction(); }
    const glm::vec3& size() const { return _orientation()->size(); }

    void setPosition(const glm::vec3& position) { _orientation()->setPosition(position); }
    void setPosition(float x, float y, float z) { _orientation()->setPosition(x,y,z); }
    void setDirection(const glm::vec3& direction) { _orientation()->setDirection(direction); }
    void setDirection(float x, float y, float z) { _orientation()->setDirection(x,y,z); }
    void setSize(const glm::vec3& size) { _orientation()->setSize(size); }
    void setSize(float x, float y, float z) { _orientation()->setSize(x,y,z); }
    void setScale(float scale) { _orientation()->setScale(scale); }

//    void validateResources() const;
    void setAnimationRotation(animation::BaseRotation* animation_rotation) { m_animationRotation = animation_rotation; }
    void setColor(const glm::vec4& color) { m_color = color; }
    void setMaterial(control::Material* material) { m_material = material; }
    void setMesh(Mesh* mesh);

    virtual void update();
    virtual void draw(const jeti::Render& render) const;

    void drawCollisionRadius(const jeti::Render& render) const;
    void drawAxis(const jeti::Render& render) const;

    const glm::mat4& modelMatrix() const { return m_matrixModel; }
    const glm::mat4& matrixRotate() const { return m_matrixRotate; }
    const glm::mat4& matrixScale() const { return m_matrixScale; }

    Mesh* mesh_DEBUG() const { return m_mesh; }

protected:
    void _genId();
    void _genOrientation();
    void _setOrientation(ceti::control::Orientation* control) { assert(control); m_orientation = control; }
    void _setParent(Base* parent) { assert(parent); m_parent = parent; }

    ceti::control::Orientation* _orientation() const { return m_orientation; }
    const glm::mat4& _collisionModelMatrix() const { return m_matrixCollisionModel; }

    //void _setTransparency(float alpha)  { m_color.a = alpha; }

    bool _updateFadeInEffect(); // depr, move to animation program
    bool _updateFadeOutEffect(); // depr, move to animation program

    const control::Material& _material() const { return *m_material; }
    const Mesh& _mesh() const { return *m_mesh; }

    Base* _parent() const { return m_parent; }

    bool _hasMaterial() const { return (m_material != nullptr); }

    const glm::vec4& _color() const { return m_color; }
    glm::vec4& _color() { return m_color; }

    //    const glm::vec3& _center() const;
//    const glm::vec3& _size() const;

    void _updateModelMatrix();

private:
    int_t m_id = 0;
    bool m_clear_orientation = false;
    Base* m_parent = nullptr;

    glm::vec4 m_color;
    meti::vec3 m_position;

    control::Material* m_material = nullptr;
    Mesh* m_mesh = nullptr;
    ceti::control::Orientation* m_orientation = nullptr;

    animation::BaseRotation* m_animationRotation = nullptr;

    glm::mat4 m_matrixTranslate;
    glm::mat4 m_matrixRotate;
    glm::mat4 m_matrixScale;

    glm::mat4 m_matrixModel;

    glm::mat4 m_matrixCollisionScale;
    glm::mat4 m_matrixCollisionModel;

    glm::quat m_quatDirection;
    glm::quat m_quatAnimation;

    virtual void __renderStuffWhenFocusedInSpace(const Render&) {}

    void __updateCollisionModelMatrix();

    void __adjustSizeFromMaterial();
};

} // namespace jeti

