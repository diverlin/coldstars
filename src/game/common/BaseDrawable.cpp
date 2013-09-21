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


#include <common/BaseDrawable.hpp>

#include <resources/MeshCollector.hpp>
#include <resources/TextureManager.hpp>
#include <resources/GuiTextureObCollector.hpp>
#include <resources/ShaderCollector.hpp>

#include <common/constants.hpp>
#include <common/rand.hpp>
#include <common/common.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>

#include <render/Render.hpp>

#include <animations/AnimationBase.hpp>

#include <render/Mesh.hpp>


#include <glm/gtx/transform.hpp>


void QuatFromAngleAndAxis(glm::quat& quat, float angle, const glm::vec3& axis)
{
    // Here we calculate the sin( theta / 2) once for optimization
    float result = sin(angle/2.0);

    // Calculate the x, y and z of the quaternion
    quat.x = axis.x * result;
    quat.y = axis.y * result;
    quat.z = axis.z * result;

    // Calcualte the w value by cos( theta / 2 )
    quat.w = cos(angle/2.0);
    glm::normalize(quat); // ??
}

BaseDrawable::BaseDrawable()
:
m_ZYX(false),
m_TextureOb(nullptr), 
m_Mesh(nullptr), 
m_AnimationProgram(nullptr)
{}

/* virtual */
BaseDrawable::~BaseDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseDrawable("+int2str(GetId())+")");
    #endif
    
    delete m_AnimationProgram;
}

void BaseDrawable::BindData3D(Mesh* mesh, TextureOb* textureOb, const glm::vec3& size)
{
    m_Mesh = mesh;
    m_TextureOb = textureOb; 
    SetSize(size);
    SetCollisionRadius((size.x + size.y) / 4.0);
}

void BaseDrawable::BindData2D(TextureOb* textureOb)
{
    m_TextureOb = textureOb; 
    SetSize(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0);
    SetCollisionRadius((textureOb->GetFrameWidth() + textureOb->GetFrameHeight()) / 4.0);
} 


void BaseDrawable::RenderCollisionRadius(const Renderer& render) const
{
    TextureOb* texOb_collision_radius =  GuiTextureObCollector::Instance().radar_range;
    glm::vec3 zero;
    glm::mat4 Mm = getModelMatrix(GetCenter(), glm::vec3(2*GetCollisionRadius()), zero); 
    render.DrawQuad(texOb_collision_radius, Mm);
}

void BaseDrawable::RenderAxis(const Renderer& render) const
{
    glm::mat4 Mm = getModelMatrix(GetCenter(), glm::vec3(2*GetCollisionRadius()), GetAngle()); 
    render.DrawAxis(Mm);
}

void BaseDrawable::UpdateRenderAnimation()
{
    if (m_AnimationProgram != nullptr)
    {
        m_AnimationProgram->Update(GetAngle());
    }
}
          
bool BaseDrawable::UpdateFadeInEffect()
{
    if (m_Color.a > 0.01)
    {
        m_Color.a -= 0.02;
        return false;
    }
    else
    {
        m_Color.a = 0.0;
        return true;
    }
}

bool BaseDrawable::UpdateFadeOutEffect()
{
    if (m_Color.a < 1.0)
    {
        m_Color.a += 0.02;
        return false;
    }
    else
    {
        m_Color.a = 1.0;
        return true;
    }
}

const glm::mat4& BaseDrawable::GetActualModelMatrix()
{
    m_Tm = glm::translate(GetCenter());
      
    QuatFromAngleAndAxis(m_Qx, GetAngle().x, GetDir());
    //QuatFromAngleAndAxis(m_Qx, GetAngle().x, AXIS_X);
    //QuatFromAngleAndAxis(m_Qy, GetAngle().y, AXIS_Y);   
    QuatFromAngleAndAxis(m_Qz, GetAngle().z, AXIS_Z); 
       
    m_Rm = glm::toMat4(m_Qz*m_Qy*m_Qx);
    
    m_Sm = glm::scale(GetSize());
      
    m_Mm = m_Tm * m_Rm * m_Sm;
    
    return m_Mm;
}

void BaseDrawable::SaveDataUniqueBaseDrawable(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::SaveDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
    #endif
        
    if (m_Mesh) save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", (int)m_Mesh->GetTypeId());
    else        save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", (int)TYPE::MESH::NONE_ID);
    
    if (m_TextureOb)     save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", m_TextureOb->path);
    else                save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", "none");
}

void BaseDrawable::LoadDataUniqueBaseDrawable(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::LoadDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
    #endif

    data_unresolved_BaseDrawable.mesh_type_id = (TYPE::MESH)load_ptree.get<int>("data_unresolved_BaseDrawable.mesh_type_id");
    data_unresolved_BaseDrawable.textureOb_path = load_ptree.get<std::string>("data_unresolved_BaseDrawable.textureOb_path");
}

void BaseDrawable::ResolveDataUniqueBaseDrawable()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::ResolveDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
    #endif
    
    if (data_unresolved_BaseDrawable.mesh_type_id != TYPE::MESH::NONE_ID)
    {
        m_Mesh = MeshCollector::Instance().GetMeshByTypeId(data_unresolved_BaseDrawable.mesh_type_id); 
    }
    
    m_TextureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseDrawable.textureOb_path);
}


glm::mat4 getModelMatrix(const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle)
{
    glm::mat4 Tm = glm::translate(center);
     
    glm::quat Qx, Qy, Qz;
    
    QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);   
    QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z); 
       
    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);
    
    glm::mat4 Sm = glm::scale(size);
      
    glm::mat4 Mm = Tm * Rm * Sm;
    
    return Mm;
}
