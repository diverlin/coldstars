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


#include "BaseView.hpp"
#include <jeti/Render.hpp>
#include <jeti/Material.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/animation/BaseRotation.hpp>

#include <meti/QuaternionUtils.hpp>

#include <ceti/Orientation.hpp>
#include <ceti/Logger.hpp>
#include <ceti/Base.hpp>

#include <glm/gtx/transform.hpp>

namespace jeti {

namespace  view {

//namespace {

//glm::mat4 getModelMatrix(const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle)
//{
//    glm::mat4 Tm = glm::translate(center);

//    glm::quat Qx, Qy, Qz;

//    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
//    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);
//    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z);

//    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);
//    glm::mat4 Sm = glm::scale(size);

//    glm::mat4 Mm = Tm * Rm * Sm;

//    return Mm;
//}

//} // namespace


BaseView::BaseView()
{}

BaseView::~BaseView() {
    delete m_animationRotation;
    m_animationRotation = nullptr;
}

void BaseView::setPosition(const glm::vec3& position)
{
    _orientation()->setPosition(position);
}

void BaseView::setSize(const glm::vec3& size)
{
    _orientation()->setSize(size);
}

void BaseView::setDirection(const glm::vec3& direction)
{
    _orientation()->setDirection(direction);
}

void
BaseView::setMesh(Mesh* mesh) {
    m_mesh = mesh;
    if (mesh->isFlat()) {
        __adjustSizeFromMaterial();
    }
}
//const glm::vec3& BaseView::_center() const { return m_orientation->position(); }
//const glm::vec3& BaseView::_size() const { return m_orientation->size(); }

//void BaseView::validateResources() const
//{
//    assert(m_material);
//    if (!m_material->isLoaded()) {
//        m_material->load();
//    }
//    assert(m_mesh);
//    // todo the same for mesh
//}

//void BaseDrawable::BindData2D(TextureOb* textureOb)
//{
//m_TextureOb = textureOb;
//setSize(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0);
//setCollisionRadius((textureOb->GetFrameWidth() + textureOb->GetFrameHeight()) / 4.0);
//} 

//void BaseView::__updateRenderAnimation()
//{
//    if (m_animationRotation) {
//        m_animationRotation->Update(GetAngle());
//    }
//}

bool BaseView::_updateFadeInEffect()
{
    if (m_color.a > 0.01f) {
        m_color.a -= 0.02;
        return false;
    } else {
        m_color.a = 0.0;
        return true;
    }
}

bool BaseView::_updateFadeOutEffect()
{
    if (m_color.a < 1.0f) {
        m_color.a += 0.02;
        return false;
    } else {
        m_color.a = 1.0;
        return true;
    }
}

void BaseView::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), _modelMatrix());
}

void BaseView::drawAxis(const jeti::Render& render) const
{
    render.drawAxis(_modelMatrix());
}

void BaseView::drawCollisionRadius(const jeti::Render& render) const
{
    render.drawCollisionRadius(_collisionModelMatrix());
}

void BaseView::_updateModelMatrix(const glm::vec3& parallax_offset)
{
    assert(m_mesh);
    assert(m_orientation);

    // prepare rotation matrix
    meti::quatBetweenVectors(m_quatDirection, m_mesh->originDirection(), m_orientation->direction());

    if (m_animationRotation) {
        m_animationRotation->update(m_quatAnimation);
        m_quatDirection *= m_quatAnimation;
    }

    m_matrixRotate = glm::toMat4(m_quatDirection);

    // prepeare scale matrix
    m_matrixScale = glm::scale(m_orientation->size());

    // prepare transition matrix
    if (m_parent) {
        m_pos = m_parent->_matrixRotate() * m_parent->_matrixScale() * glm::vec4(m_orientation->position() - parallax_offset, 1.0f); // parent rotation offset position
        m_pos += m_parent->_orientation()->position();
    } else {
        m_pos = m_orientation->position() - parallax_offset;
    }

    m_matrixTranslate = glm::translate(m_pos);

    // combine transformations
    m_matrixModel = m_matrixTranslate * m_matrixRotate * m_matrixScale;

    __updateCollisionModelMatrix();
}

void
BaseView::__updateCollisionModelMatrix()
{
    // prepeare scale matrix
    float r = m_orientation->collisionRadius();
    assert(r>0);
    m_matrixCollisionScale = glm::scale(glm::vec3(r, r, 1.0f));

    // combine transformations
    m_matrixCollisionModel = m_matrixTranslate * m_matrixCollisionScale;
}

void
BaseView::__adjustSizeFromMaterial()
{
    assert(m_material);
    assert(m_orientation);

    m_orientation->setSize(glm::vec3(m_material->frameWidth(), m_material->frameHeight(), 1.0));
}

} // namespace view

} // namespace jeti
