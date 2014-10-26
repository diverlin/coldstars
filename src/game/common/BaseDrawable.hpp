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


#ifndef BASEDRAWABLE_HPP
#define BASEDRAWABLE_HPP

#include <common/Orientation.hpp>
#include <types/MeshTypes.hpp>
#include <render/Render.hpp>

#include <glm/glm.hpp> // glm::vec
#include <glm/gtx/quaternion.hpp>

class Mesh;
class TextureOb;
class BaseAnimationRotation;

const glm::vec3 AXIS_X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 AXIS_Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 AXIS_Z = glm::vec3(0.0f, 0.0f, 1.0f);

struct UnresolvedDataBaseDrawable
{
    TYPE::MESH mesh_type_id;
    std::string textureOb_path;
};

class BaseDrawable : public Orientation
{
    public:      
        BaseDrawable();
        virtual ~BaseDrawable() override;

        void SetRenderData(Mesh*, TextureOb*, const glm::vec3&);
        void ValidateResources() const;
        void SetAnimationRotation(BaseAnimationRotation* animation_rotation) { m_AnimationRotation = animation_rotation; }
        void SetColor(const glm::vec4& color) { m_Color = color; }

        const glm::mat4& GetActualModelMatrix();
        const glm::mat4& GetModelMatrix() const { return m_MatrixModel; }
                        
        //const glm::vec3& GetBoundaryBox() const     { return m_Mesh->GetBoundaryBox(); }
        const Mesh& GetMesh() const     { return *m_Mesh; }

        const TextureOb& GetTextureOb() const { return *m_TextureOb; }
        bool HasTextureOb() const { return (m_TextureOb != 0); }
        
        const glm::vec4& GetColor() const { return m_Color; }
                                            
        void RenderCollisionRadius(const Renderer&) const;
        void RenderAxis(const Renderer&) const;
                
    protected:
        void SetTransparency(float alpha)  { m_Color.a = alpha; }
                
        bool UpdateFadeInEffect(); // depr, move to animation program
        bool UpdateFadeOutEffect(); // depr, move to animation program

    private:
        glm::vec4 m_Color;
        
        TextureOb* m_TextureOb;
        Mesh* m_Mesh; 
        
        BaseAnimationRotation* m_AnimationRotation;
        
        glm::mat4 m_MatrixModel;     
        glm::mat4 m_MatrixTranslate;
        glm::mat4 m_MatrixRotate;
        glm::mat4 m_MatrixScale;
 
        glm::quat m_QuatDirection;
        glm::quat m_QuatAnimation;        

        void UpdateRenderAnimation();
                                                        
    friend class BaseVehicleBuilder;
};

glm::mat4 getModelMatrix(const glm::vec3&, const glm::vec3&, const glm::vec3&);  // slow, mainly used for debug (draw collision radius, draw axis)

#endif 
