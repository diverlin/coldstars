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


#ifndef BASEDRAWABLE_H
#define BASEDRAWABLE_H

#include "../common/Orientation.hpp"
class Mesh;
class TextureOb;
class AnimationBase;

struct UnresolvedDataUniqueBaseDrawable
{
	int mesh_type_id;
	std::string textureOb_path;
};

class BaseDrawable : public Orientation
{
	public:      
		BaseDrawable();
		virtual ~BaseDrawable();

		void BindData3D(Mesh*, TextureOb*, const Vec3<float>&);
		void BindData2D(TextureOb*);    
		void SetRenderAnimation(AnimationBase* animation_program) { this->animation_program = animation_program; }
		
		bool Is3D() const 				{ return (mesh != NULL); }
		const Vec3<float>& GetBoundaryBox() const 	{ return mesh->GetBoundaryBox(); }
		Mesh* GetMesh() const 				{ return mesh; }
                
		void SetZYX(bool ZYX)    			{ this->ZYX = ZYX; }

   		TextureOb* GetTextureOb() const { return textureOb; }
							
		void RenderCollisionRadius() const;
				
	protected:
		bool ZYX;

		TextureOb* textureOb;
		Mesh* mesh; 
		
		AnimationBase* animation_program;

		void UpdateRenderAnimation();
		void RenderMesh(const Vec2<float>&, const Color4<float>&) const;

		UnresolvedDataUniqueBaseDrawable data_unresolved_BaseDrawable;
		void SaveDataUniqueBaseDrawable(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseDrawable(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseDrawable();
				
	friend class BaseVehicleBuilder;
};

#endif 
