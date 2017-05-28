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
#include <jeti/animations/BaseAnimationRotation.hpp>

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


//void BaseDrawable::RenderCollisionRadius(const Renderer& render) const
//{
////    TextureOb* texOb_collision_radius =  GuiTextureObCollector::Instance().radar_range;
////    glm::vec3 zero;
////    glm::mat4 Mm = getModelMatrix(m_Orientation->center(), glm::vec3(2*m_Orientation->collisionRadius()), zero);
////    render.DrawQuad(*texOb_collision_radius, Mm);
//}

//void BaseView::_renderAxis(const Renderer& render) const
//{
//    glm::mat4 Mm = getModelMatrix(m_orientation->position(), glm::vec3(2*m_orientation->collisionRadius()), glm::vec3(0.0f));    // angle
//    render.DrawAxis(Mm, /*width*/4);
//    //render.DrawVector(GetDir(), center(), size().x, /*width*/6);
//    render.DrawVector(m_Orientation->direction(), Mm, /*width*/6);
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

void BaseView::update()
{
    __updateModelMatrix();
}

void BaseView::draw(const jeti::Renderer& render) const
{
    render.drawMesh(_mesh(), _material(), _modelMatrix());
}

void BaseView::drawAxis(const jeti::Renderer& render) const
{
    render.drawAxis(_modelMatrix());
}

void BaseView::__updateModelMatrix()
{
    assert(m_mesh);
    assert(m_orientation);

    bool debug = true;

    if (debug) {
        auto pos = m_orientation->position();
        pos.z = -500.0;
        m_matrixTranslate = glm::translate(pos/*m_orientation->position()*/);
        m_matrixScale     = glm::scale(m_orientation->size());

        //meti::quatBetweenVectors(m_quatDirection, meti::OX/*m_mesh->originDirection()*/, meti::OX/*m_orientation->direction()*/);

        if (m_animationRotation) {
            m_animationRotation->update(m_quatAnimation, m_mesh->originDirection());
            m_matrixRotate = glm::toMat4(m_quatDirection * m_quatAnimation);
        } else {
            //m_matrixRotate = glm::toMat4(m_quatDirection);
            //zzz += 0.01f;
            zzz = 180/(2*3.14);
            m_matrixRotate = glm::rotate(glm::mat4(1.0f), zzz, glm::vec3(0.0, 1.0, 0.0));
            std::cout<<zzz*180/3.14<<std::endl;
        }

        m_matrixModel = m_matrixTranslate * m_matrixScale * m_matrixRotate;
    } else {
        m_matrixTranslate = glm::translate(m_orientation->position());
        m_matrixScale     = glm::scale(m_orientation->size());

        meti::quatBetweenVectors(m_quatDirection, m_mesh->originDirection(), m_orientation->direction());

        if (m_animationRotation) {
            m_animationRotation->update(m_quatAnimation, m_mesh->originDirection());
            m_matrixRotate = glm::toMat4(m_quatDirection * m_quatAnimation);
        } else {
            m_matrixRotate = glm::toMat4(m_quatDirection);
        }

        m_matrixModel = m_matrixTranslate * m_matrixScale * m_matrixRotate;
    }
}

} // namespace view

} // namespace jeti
