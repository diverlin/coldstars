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


#pragma once

#include <MyGl.hpp>

struct Shaders
{      
    GLuint screentexture = 0;
    GLuint basetexture = 0;
    GLuint texturewithperlin = 0;
    GLuint perlin = 0;
    GLuint basecolor = 0;
    GLuint black2alpha = 0;
    GLuint shockwave = 0;
    GLuint volumetriclight = 0;
    GLuint light = 0;
    GLuint light_normalmap = 0;
    GLuint blur = 0;
    GLuint extractbright = 0;
    GLuint combine = 0;
    GLuint multitexturing = 0;
    GLuint blank = 0;
    GLuint fogwarspark = 0;
    GLuint flash = 0;
    GLuint mask = 0;
    GLuint particle = 0;
    GLuint particle_blink = 0;
    GLuint star = 0;
    GLuint starfield = 0;
    GLuint flatlight = 0;
    GLuint defferedflatlight = 0;
};




