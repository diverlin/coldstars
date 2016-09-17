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


#include "PlanetoidDrawable.hpp"
#include <jeti/Render.hpp>

#include <ceti/Logger.hpp> 
//#include <ceti/StringUtils.hpp>

PlanetoidDrawable::PlanetoidDrawable()
{}

PlanetoidDrawable::PlanetoidDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
    :
      BaseDrawable(texture, mesh)
{}

/* virtual override */
PlanetoidDrawable::~PlanetoidDrawable()
{
//    #if CREATEDESTROY_LOG_ENABLED == 1
//    Logger::Instance().Log("___::~PlanetoidDrawable("+std::to_string(id())+")");
//    #endif
}

/* virtual override final */
void PlanetoidDrawable::__renderStuffWhenFocusedInSpace(const jeti::Renderer& render)
{
    //m_Orbit.DrawPath(render);
}

