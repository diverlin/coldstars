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


#include "Base.hpp"

#include <jeti/Render.hpp>
#include <jeti/Material.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/animation/BaseRotation.hpp>

#include <meti/QuaternionUtils.hpp>

#include <ceti/Orientation.hpp>
#include <ceti/Logger.hpp>
#include <ceti/Base.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace jeti {
namespace view {

int_t Base::counter=0;

Base::Base()
{
    _genId();
    //_genOrientation();
}

Base::Base(Mesh* mesh, control::Material* material)
    :
      m_mesh(mesh)
    , m_material(material)
{
    _genId();
    _genOrientation();
    __adjustSizeFromMaterial();
}

Base::~Base() {
    if (m_animationRotation) {
        delete m_animationRotation;
        m_animationRotation = nullptr;
    }

    if (m_clear_orientation) {
        delete m_orientation->model();
        delete m_orientation;
    }
}

void Base::_genId() {
    counter++;
    m_id = counter;
}

void Base::_genOrientation()
{
    assert(m_orientation==nullptr);
    m_clear_orientation = true;
    m_orientation = new ceti::control::Orientation(new ceti::OrientationModel);
}

void
Base::setMesh(Mesh* mesh) {
    m_mesh = mesh;
    if (mesh->isFlat()) {
        __adjustSizeFromMaterial();
    }
}

float Base::distanceTo(const glm::vec2& p) const {
    return m_orientation->distanceTo(p);
}

float Base::distanceTo(const glm::vec3& p) const {
    return m_orientation->distanceTo(p);
}

bool Base::isPointInsideCircle(const glm::vec2& p) const {
    return m_orientation->isPointInsideCircle(p);
}

bool Base::isPointInsideShape(const glm::vec3& p) const {
    return m_orientation->isPointInsideShape(p);
}

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

bool Base::_updateFadeInEffect()
{
    if (m_color.a > 0.01f) {
        m_color.a -= 0.02;
        return false;
    } else {
        m_color.a = 0.0;
        return true;
    }
}

bool Base::_updateFadeOutEffect()
{
    if (m_color.a < 1.0f) {
        m_color.a += 0.02;
        return false;
    } else {
        m_color.a = 1.0;
        return true;
    }
}

void Base::update()
{
    _updateModelMatrix();
}

void Base::update2()
{
    _updateModelMatrix2();
}

void Base::draw(const jeti::Render& render) const
{
    render.drawMesh(mesh(), material(), modelMatrix(), m_color);
}

void Base::drawAxis(const jeti::Render& render) const
{
    render.drawAxis(modelMatrix());
}

void Base::drawCollisionRadius(const jeti::Render& render) const
{
    render.drawDebugCircle(position(), collisionRadius());
}

void Base::_updateModelMatrix()
{
    assert(m_mesh);
    assert(m_orientation);

    // prepare rotation matrix
    if (m_mesh->isFlat()) {
        float angle = glm::orientedAngle(m_mesh->originDirection(), m_orientation->direction(), meti::OZ);
        m_matrixRotate = glm::rotate(angle, meti::OZ);
    } else {
        meti::quatBetweenVectors(m_quatDirection, m_mesh->originDirection(), m_orientation->direction());
        //meti::quatBetweenVectors(m_quatDirection, meti::OX, m_orientation->direction());

        if (m_animationRotation) {
            m_animationRotation->update(m_quatAnimation);
            m_quatDirection *= m_quatAnimation;
        }

        m_matrixRotate = glm::toMat4(m_quatDirection);
    }

    // prepeare scale matrix
    m_matrixScale = glm::scale(m_orientation->size());

    // prepare transition matrix
    if (m_parent) {
        m_position = m_parent->matrixRotate() * m_parent->matrixScale() * glm::vec4(m_orientation->position(), 1.0f); // parent rotation offset position
        m_position += m_parent->_orientation()->position();
    } else {
        m_position = _orientation()->position();
    }

    m_matrixTranslate = glm::translate(m_position);

    // combine transformations
    m_matrixModel = m_matrixTranslate * m_matrixRotate * m_matrixScale;
}

void Base::_updateModelMatrix2()
{
    assert(m_mesh);
    assert(m_orientation);

    if (std::fabs(angle) < 0.01f) {
        angle = meti::rand::gen_float(0, 2*3.14);
        d_angle = /*meti::rand::gen_sign()**/meti::rand::gen_float(0.001f, 0.003f)/1.0f;
    }
    angle += d_angle;

    // prepare rotation matrix
//    meti::quatBetweenVectors(m_quatDirection, m_mesh->originDirection(), m_orientation->direction());
    //meti::quatBetweenVectors(m_quatDirection, meti::OX, m_orientation->direction());

    m_matrixRotate = glm::rotate(angle, rotationAxis);
    glm::vec4 up_ = m_matrixRotate * glm::vec4(upOrigin.x, upOrigin.y, upOrigin.z, 1.0f);
    up = glm::vec3(up_.x, up_.y, up_.z);
//    if (m_animationRotation) {
//        m_animationRotation->update(m_quatAnimation);
//        m_quatDirection *= m_quatAnimation;
//    }

    //m_matrixRotate = glm::toMat4(m_quatDirection);

    // prepeare scale matrix
    m_matrixScale = glm::scale(m_orientation->size());

    // prepare transition matrix
//    if (m_parent) {
//        m_position = m_parent->matrixRotate() * m_parent->matrixScale() * glm::vec4(m_orientation->position(), 1.0f); // parent rotation offset position
//        m_position += m_parent->_orientation()->position();
//    } else {
        m_position = _orientation()->position();
//    }

    m_matrixTranslate = glm::translate(m_position);

    // combine transformations
    m_matrixModel = m_matrixTranslate * m_matrixRotate * m_matrixScale;
}

void
Base::__adjustSizeFromMaterial()
{
    assert(m_material);
    assert(m_orientation);

    m_orientation->setSize(glm::vec3(m_material->frameWidth(), m_material->frameHeight(), 1.0));
}

} // namespace view
} // namespace jeti
