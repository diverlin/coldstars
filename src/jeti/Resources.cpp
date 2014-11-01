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

#include "Resources.hpp"
#include <ShaderLoader.hpp>
#include <Screen.hpp>

namespace jeti {

void loadShaders()
{
    Shaders shaders;
    shaders.base            = compileProgram(SHADERS_PATH+"base.vert",              SHADERS_PATH+"base.frag");
    shaders.black2alpha     = compileProgram(SHADERS_PATH+"black2alpha.vert",       SHADERS_PATH+"black2alpha.frag");
    shaders.shockwave       = compileProgram(SHADERS_PATH+"shockwave.vert",         SHADERS_PATH+"shockwave.frag");
    shaders.volumetriclight = compileProgram(SHADERS_PATH+"volumetricLight.vert",   SHADERS_PATH+"volumetricLight.frag");
    shaders.light           = compileProgram(SHADERS_PATH+"light.vert",             SHADERS_PATH+"light.frag");
    shaders.light_normalmap = compileProgram(SHADERS_PATH+"light_normalmap.vert",   SHADERS_PATH+"light_normalmap.frag");
    shaders.blur            = compileProgram(SHADERS_PATH+"blur.vert",              SHADERS_PATH+"blur.frag");
    shaders.extractbright   = compileProgram(SHADERS_PATH+"extractBright.vert",     SHADERS_PATH+"extractBright.frag");
    shaders.combine         = compileProgram(SHADERS_PATH+"combine.vert",           SHADERS_PATH+"combine.frag");
    shaders.multitexturing  = compileProgram(SHADERS_PATH+"multitex.vert",          SHADERS_PATH+"multitex.frag");
    shaders.blank           = compileProgram(SHADERS_PATH+"blank.vert",             SHADERS_PATH+"blank.frag");
    shaders.fogwarspark     = compileProgram(SHADERS_PATH+"fogwarspark.vert",       SHADERS_PATH+"fogwarspark.frag");   
    shaders.flash           = compileProgram(SHADERS_PATH+"flash.vert",             SHADERS_PATH+"flash.frag");
    shaders.mask            = compileProgram(SHADERS_PATH+"mask.vert",              SHADERS_PATH+"mask.frag");
    shaders.particle        = compileProgram(SHADERS_PATH+"particle.vert",          SHADERS_PATH+"particle.frag");
    shaders.starfield       = compileProgram(SHADERS_PATH+"starfield.vert",         SHADERS_PATH+"starfield.frag");
    
    Screen::Instance().GetRender().SetShaders(shaders);
}

}
