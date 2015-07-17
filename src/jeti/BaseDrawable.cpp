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


#include "BaseDrawable.hpp"
#include <Render.hpp>

#include <TextureOb.hpp>
#include <Mesh.hpp>
#include <animations/BaseAnimationRotation.hpp>

#include <ceti/Orientation.hpp>

#include <glm/gtx/transform.hpp>
#include <meti/QuaternionUtils.hpp>

#ifdef LOG_DRAW_ENABLED
#include "<common/Logger.hpp>
#endif

namespace jeti {

BaseDrawable::BaseDrawable(TextureOb* textureOb, Mesh* mesh)
    :
      m_TextureOb(textureOb),
      m_Mesh(mesh),
      m_AnimationRotation(nullptr)
{}

/* virtual */
BaseDrawable::~BaseDrawable() {
#if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Drawable("+std::to_string(id())+")");
#endif
    
    delete m_AnimationRotation;
}

const glm::vec3& BaseDrawable::center() const { return m_Orientation->center(); }
const glm::vec3& BaseDrawable::size() const { return m_Orientation->size(); }

void BaseDrawable::ValidateResources() const
{
    assert(m_TextureOb);
    if (!m_TextureOb->GetIsLoaded()) {
        m_TextureOb->Load();
    }
    // todo the same for mesh
}

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

//void BaseDrawable::RenderAxis(const Renderer& render) const
//{
//    glm::mat4 Mm = getModelMatrix(m_Orientation->center(), glm::vec3(2*m_Orientation->collisionRadius()), glm::vec3(0.0f));    // angle
//    render.DrawAxis(Mm, /*width*/4);
//    //render.DrawVector(GetDir(), center(), size().x, /*width*/6);
//    render.DrawVector(m_Orientation->direction(), Mm, /*width*/6);
//}

void BaseDrawable::UpdateRenderAnimation()
{
    if (m_AnimationRotation != nullptr) {
        //m_AnimationRotation->Update(GetAngle());
    }
}

bool BaseDrawable::UpdateFadeInEffect()
{
    if (m_Color.a > 0.01) {
        m_Color.a -= 0.02;
        return false;
    } else {
        m_Color.a = 0.0;
        return true;
    }
}

bool BaseDrawable::UpdateFadeOutEffect()
{
    if (m_Color.a < 1.0) {
        m_Color.a += 0.02;
        return false;
    } else {
        m_Color.a = 1.0;
        return true;
    }
}

const glm::mat4& BaseDrawable::actualModelMatrix()
{    
    meti::RotationBetweenVectors(m_QuatDirection, m_Mesh->GetOriginDirection(), m_Orientation->direction());
    if (m_AnimationRotation != nullptr) {
        m_AnimationRotation->Update(m_QuatAnimation, m_Mesh->GetOriginDirection());
    }
    
    m_MatrixTranslate = glm::translate(m_Orientation->center());
    m_MatrixRotate    = glm::toMat4(m_QuatDirection * m_QuatAnimation);
    m_MatrixScale     = glm::scale(m_Orientation->size());

    m_MatrixModel = m_MatrixTranslate * m_MatrixScale * m_MatrixRotate;
    
    return m_MatrixModel;
}

glm::mat4 getModelMatrix(const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle)
{
    glm::mat4 Tm = glm::translate(center);

    glm::quat Qx, Qy, Qz;

    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z);

    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);
    glm::mat4 Sm = glm::scale(size);

    glm::mat4 Mm = Tm * Rm * Sm;

    return Mm;
}

} // namespace jeti
