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

//#include <client/text/InfoTable.hpp>

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

class Renderer;

namespace view {

class BaseView
{
public:
    BaseView();
    virtual ~BaseView();

//    void validateResources() const;
    void setAnimationRotation(animation::BaseRotation* animation_rotation) { m_animationRotation = animation_rotation; }
    void setColor(const glm::vec4& color) { m_color = color; }
    void setMaterial(control::Material* material) { m_material = material; }
    void bindMesh(Mesh* mesh);
    void setOrientationModel(ceti::model::Orientation* model) { m_orientation = model; }
    void setParent(BaseView* parent) { m_parent = parent; }

    //const glm::vec3& GetBoundaryBox() const     { return m_Mesh->GetBoundaryBox(); }

    [[warning("todo")]]
    virtual bool inRect(const ceti::Rect&) { return true; }
    //        void RenderCollisionRadius(const Renderer&) const;

    virtual void update();
    virtual void draw(const jeti::Renderer& render) const;

    void drawAxis(const jeti::Renderer& render) const;

protected:
    ceti::model::Orientation* _orientation() const { return m_orientation; }
    const glm::mat4& matrixRotate() const { return m_matrixRotate; }
    const glm::mat4& matrixScale() const { return m_matrixScale; }

    void _setTransparency(float alpha)  { m_color.a = alpha; }

    bool _updateFadeInEffect(); // depr, move to animation program
    bool _updateFadeOutEffect(); // depr, move to animation program

    const glm::mat4& _modelMatrix() const { return m_matrixModel; }

    const control::Material& _material() const { return *m_material; }
    const Mesh& _mesh() const     { return *m_mesh; }

    bool _hasMaterial() const { return (m_material != 0); }

    const glm::vec4& _color() const { return m_color; }
//    const glm::vec3& _center() const;
//    const glm::vec3& _size() const;

private:
    glm::vec4 m_color;
    meti::vec3 m_pos;

    control::Material* m_material = nullptr;
    Mesh* m_mesh = nullptr;
    ceti::model::Orientation* m_orientation = nullptr;
    BaseView* m_parent = nullptr;

    animation::BaseRotation* m_animationRotation = nullptr;

    glm::mat4 m_matrixModel;
    glm::mat4 m_matrixTranslate;
    glm::mat4 m_matrixRotate;
    glm::mat4 m_matrixScale;

    glm::quat m_quatDirection;
    glm::quat m_quatAnimation;

    virtual void __renderStuffWhenFocusedInSpace(const Renderer&) {}

    void __updateModelMatrix();
    void __adjustSizeFromMaterial();
};

} // namepsace view
} // namespace jeti

