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

class Mesh;
class TextureOb;
class AnimationBase;


struct UnresolvedDataUniqueBaseDrawable
{
    TYPE::MESH mesh_type_id;
    std::string textureOb_path;
};

class BaseDrawable : public Orientation
{
    public:      
        BaseDrawable();
        virtual ~BaseDrawable() override;

        void BindData3D(Mesh*, TextureOb*, const Vec3<float>&);
        void BindData2D(TextureOb*);    
        void SetRenderAnimation(AnimationBase* animation_program) { m_AnimationProgram = animation_program; }
        void SetTextureOb(TextureOb* textureOb) { m_TextureOb = textureOb; }
        void SetColor(const Color4<float>& color) { m_Color = color; }
                        
        bool Is3D() const                 { return (m_Mesh != nullptr); }
        //const Vec3<float>& GetBoundaryBox() const     { return m_Mesh->GetBoundaryBox(); }
        const Mesh* const GetMesh() const     { return m_Mesh; }
                
        void SetZYX(bool ZYX)                { m_ZYX = ZYX; }

           TextureOb* const GetTextureOb() const { return m_TextureOb; }
           bool GetZYX() const { return m_ZYX; }
        
        const Color4<float> GetColor() const { return m_Color; }
                                            
        void RenderCollisionRadius() const;
                
    protected:
        void SetTransparency(float alpha)  { m_Color.a = alpha; }
    
        void UpdateRenderAnimation();
                
        bool UpdateFadeInEffect(); // depr, move to animation program
        bool UpdateFadeOutEffect(); // depr, move to animation program
        
        void RenderMeshLight(const Vec2<float>&, const Color4<float>&) const;
        void RenderMeshLightNormalMap(const Vec2<float>&, const Color4<float>&) const;
        
        UnresolvedDataUniqueBaseDrawable data_unresolved_BaseDrawable;
        void SaveDataUniqueBaseDrawable(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueBaseDrawable(const boost::property_tree::ptree&);
        void ResolveDataUniqueBaseDrawable();

    private:
        bool m_ZYX;
                          
        Color4<float> m_Color;
        
        TextureOb* m_TextureOb;
        Mesh* m_Mesh; 
        
        AnimationBase* m_AnimationProgram;
                        
    friend class BaseVehicleBuilder;
};

#endif 
