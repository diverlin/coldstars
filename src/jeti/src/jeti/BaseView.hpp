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

//#include <text/InfoTable.hpp>
#include <ceti/type/IdType.hpp>
#include <ceti/Orientation.hpp>
#include <ceti/rect.hpp>
#include <ceti/descriptor/Collector.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ceti {

namespace control {
class Orientation;
} // namespace control

namespace model {
class BaseView;
} // namespace model

} // namespace ceti

namespace jeti {

class Mesh;

namespace control {
class TextureOb;
} // namespace control

class BaseAnimationRotation;
class Renderer;

namespace view {

class BaseView
{
    const glm::vec3 AXIS_X = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 AXIS_Y = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 AXIS_Z = glm::vec3(0.0f, 0.0f, 1.0f);

public:
    BaseView(ceti::model::BaseView*);
    virtual ~BaseView();

    void validateResources() const;
    void setAnimationRotation(BaseAnimationRotation* animation_rotation) { m_animationRotation = animation_rotation; }
    void setColor(const glm::vec4& color) { m_color = color; }
    void setMaterial(control::TextureOb* material) { m_material = material; }
    void setMesh(Mesh* mesh);

    const glm::mat4& actualModelMatrix();
    const glm::mat4& modelMatrix() const { return m_matrixModel; }

    //const glm::vec3& GetBoundaryBox() const     { return m_Mesh->GetBoundaryBox(); }
    const Mesh& mesh() const     { return *m_mesh; }

    const control::TextureOb& material() const { return *m_material; }
    bool hasMaterial() const { return (m_material != 0); }

    const glm::vec4& color() const { return m_color; }
    const glm::vec3& center() const;
    const glm::vec3& size() const;

    virtual bool inRect(const ceti::Rect&) { return true; }
    //        void RenderCollisionRadius(const Renderer&) const;
    //        void RenderAxis(const Renderer&) const;

    virtual void draw(const jeti::Renderer& render);

    void setOrientationModel(ceti::model::Orientation*);

protected:
    void _setTransparency(float alpha)  { m_color.a = alpha; }

    bool _updateFadeInEffect(); // depr, move to animation program
    bool _updateFadeOutEffect(); // depr, move to animation program

public:
    static ceti::Collector<control::TextureOb> s_materials;
    static ceti::Collector<Mesh> s_meshes;

private:
    ceti::model::BaseView* m_model_base = nullptr;
    ceti::model::BaseView* model() const { return m_model_base; }

    glm::vec4 m_color;

    control::TextureOb* m_material = nullptr;
    Mesh* m_mesh = nullptr;
    ceti::model::Orientation* m_orientation = nullptr;

    BaseAnimationRotation* m_animationRotation = nullptr;

    glm::mat4 m_matrixModel;
    glm::mat4 m_matrixTranslate;
    glm::mat4 m_matrixRotate;
    glm::mat4 m_matrixScale;

    glm::quat m_quatDirection;
    glm::quat m_quatAnimation;

    //void __updateRenderAnimation();

    //    protected:
    //        InfoTable m_Info;
    //        virtual void UpdateInfo() {};
    virtual void __renderStuffWhenFocusedInSpace(const Renderer&) {}
};

} // namepsace view

} // namespace jeti

