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


#ifndef RENDER_HPP
#define RENDER_HPP

#include <GL/glew.h>
#include "../resources/textureOb.hpp"
#include "../common/rect.hpp"
#include <common/Box2D.hpp>
class Mesh;

void initGl(int, int);
void resizeGl(int, int);

void clearScreen();
void resetRenderTransformation();

void camera(float x, float y, float z);
void setColor4f(const Color4<float>&);	
void setColor4f(float, float, float, float);

void enable_CULLFACE();
void disable_CULLFACE();

void enable_BLEND();
void disable_BLEND();

void enable_DEPTH();
void disable_DEPTH();

void enable_POINTSPRITE();
void disable_POINTSPRITE();

void drawQuad(TextureOb* texOb, 
		 const Vec3<float>& center,
		 const Vec3<float>& size, 
		 float angle=0);
         
void drawQuad(TextureOb* texOb,
		 const Vec2<float>& center, 
		 const Vec2<float>& size,
		 float angle);
		 	 
void drawQuad(TextureOb*, const Box2D&);
void drawQuadMasked(TextureOb*, const Box2D&, TextureOb*, float);
		 		 		 
void drawTexturedRect(TextureOb* texOb, const Rect& rect, float z_pos);   

void drawLine(TextureOb* texOb, 
              const Vec3<float>& start_pos, 
              float len, 
              float angle_inD, 
              int half_h);

void drawSimpleColoredTextWithBackground(const std::string&, 
			   int,
			   const Vec2<float>&, 
			   const Color4<int>&);
			   
void drawInfoIn2Column(
                const std::vector<std::string>& pnfo_title_list, 
                const std::vector<std::string>& info_value_list, 
                const Vec2<float>& pos);

void drawFullScreenQuad(int w, int h, float pos_z);


void drawFullScreenTexturedQuad(GLuint texture, int w, int h, float pos_z);


void drawFullScreenTexturedQuadBlurred(GLuint texture, int w, int h, float pos_z, GLuint program_blur);

void renderMesh(const Mesh* const mesh, const Vec3<float>& center, const Vec3<float>& size, const Vec3<float>& angle, bool ZYX);
void rotateZYX(const Vec3<float>&);
void rotateXYZ(const Vec3<float>&);

void drawParticleTextured(GLuint texture, const Vec2<float>& _center, float size, float pos_z);
void drawParticle(const Vec2<float>&, float, float r, float g, float b, float a);
void drawParticle(const Vec2<float>&, float, const Color4<float>&);
void drawParticle(const Vec2<float>&, float);

#endif 


