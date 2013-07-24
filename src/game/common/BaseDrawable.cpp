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
#include "../resources/MeshCollector.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../common/constants.hpp"
#include "../common/rand.hpp"
#include "../common/common.hpp"
#include "../world/EntityManager.hpp"
#include "../render/Render.hpp"
#include "../common/Logger.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../animations/AnimationBase.hpp"


BaseDrawable::BaseDrawable():
mesh(nullptr), 
textureOb(nullptr), 
animation_program(nullptr),
ZYX(false)
{}

/* virtual */
BaseDrawable::~BaseDrawable()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseDrawable("+int2str(GetId())+")");
	#endif
	
	delete animation_program;
}

void BaseDrawable::BindData3D(Mesh* mesh, TextureOb* textureOb, const Vec3<float>& size)
{
	this->mesh = mesh;
	this->textureOb = textureOb; 
	SetSize(size);
	SetCollisionRadius((size.x + size.y) / 4.0);
}

void BaseDrawable::BindData2D(TextureOb* textureOb)
{
	this->textureOb = textureOb; 
	SetSize(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0);
	SetCollisionRadius((textureOb->GetFrameWidth() + textureOb->GetFrameHeight()) / 4.0);
} 


void BaseDrawable::RenderCollisionRadius() const
{
	TextureOb* texOb_collision_radius =  GuiTextureObCollector::Instance().radar_range;
	drawQuad(texOb_collision_radius, GetCenter(), Vec3<float>(2*GetCollisionRadius(), 2*GetCollisionRadius(), 2*GetCollisionRadius()));
}

void BaseDrawable::UpdateRenderAnimation()
{
	if (animation_program != nullptr)
	{
		animation_program->Update(GetAngle());
	}
}


void BaseDrawable::RenderMeshLight(const Vec2<float>& scroll_coords, const Color4<float>& color) const
{
	float ambient_factor = 0.25;
	
	glUseProgram(ShaderCollector::Instance().light);
	
	glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light, "iLightPos"), -scroll_coords.x, -scroll_coords.y, -200.0);
	glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light, "iEyePos"), -scroll_coords.x, -scroll_coords.y, -200.0);
	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "iDiffColor"), color.r, color.g, color.b, color.a);
	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "iAmbientColor"), ambient_factor*color.r, ambient_factor*color.g, ambient_factor*color.b, ambient_factor*color.a);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light, "iTexture_0"), 0);
	
	renderMesh(mesh, GetCenter(), GetSize(), GetAngle(), ZYX);
	
	glUseProgram(0);
	glActiveTexture(GL_TEXTURE0);
}
		
void BaseDrawable::RenderMeshLightNormalMap(const Vec2<float>& scroll_coords, const Color4<float>& color) const
{
	float ambient_factor = 0.25;
	
	glUseProgram(ShaderCollector::Instance().light_normalmap);
	
	glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_lightPos"), -scroll_coords.x, -scroll_coords.y, 0.0);
	glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_eyePos"), -scroll_coords.x, -scroll_coords.y, 0.0);
	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_diffColor"), color.r, color.g, color.b, color.a);
	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_ambientColor"), ambient_factor*color.r, ambient_factor*color.g, ambient_factor*color.b, ambient_factor*color.a);
			
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_texture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureOb->normalmap);
	glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_normalmap"), 1);
			
	renderMesh(mesh, GetCenter(), GetSize(), GetAngle(), ZYX);
	
	glUseProgram(0);
	glActiveTexture(GL_TEXTURE0);
}

void BaseDrawable::SaveDataUniqueBaseDrawable(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::SaveDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
	#endif
		
	if (mesh) save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", mesh->GetTypeId());
	else      save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", NONE_ID);
	
	if (textureOb) 	save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", "none");
}

void BaseDrawable::LoadDataUniqueBaseDrawable(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::LoadDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
	#endif

	data_unresolved_BaseDrawable.mesh_type_id = load_ptree.get<int>("data_unresolved_BaseDrawable.mesh_type_id");
	data_unresolved_BaseDrawable.textureOb_path = load_ptree.get<std::string>("data_unresolved_BaseDrawable.textureOb_path");
}

void BaseDrawable::ResolveDataUniqueBaseDrawable()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::ResolveDataUniqueBaseDrawable", SAVELOAD_LOG_DIP);
	#endif
	
	if (data_unresolved_BaseDrawable.mesh_type_id != NONE_ID)
	{
		mesh = MeshCollector::Instance().GetMeshByTypeId(data_unresolved_BaseDrawable.mesh_type_id); 
	}
	
	textureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseDrawable.textureOb_path);
}
