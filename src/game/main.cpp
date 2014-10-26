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

#include <iostream>
#include "resources/init.hpp"
#include "resources/MeshCollector.hpp"

#include "spaceobjects/Star.hpp"

#include "render/Screen.hpp"

#include "resources/TextureManager.hpp"
#include "resources/textureOb.hpp"

#include "gui/UserInputManagerInSpace.hpp"


void renderStar_NEW(Renderer& render, Star* star)
{
    int w = Screen::Instance().GetWidth();
    int h = Screen::Instance().GetHeight();
    glm::vec2 world_coord(Screen::Instance().GetBottomLeft());

    render.ClearColorAndDepthBuffers();

    // apply projection matrix
    render.SetOrthogonalProjection(w, h);

    // apply view matrix
    Camera& camera = Screen::Instance().GetCamera();
    camera.Update(w, h);
    render.ComposeViewMatrix(camera.GetViewMatrix());

    // render star to FBO0
    render.ActivateFbo(0, w, h);
    {
        render.DrawMeshMultiTextured(star->GetMesh(), star->GetTextureOb(), star->GetActualModelMatrix(), star->GetOffset());
    }
    render.DeactivateFbo(0);

    // apply BLOOM star (uses many internal FBO inside)
    render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), star->GetBrightThreshold());

    // apply VOLUMETRIC LIGHT to FBO1
    render.ActivateFbo(1, w, h);
    {
        render.DrawPostEffectVolumetricLight(world_coord, w, h);
    }
    render.DeactivateFbo(1);

    // compose final scene
    render.ClearColorAndDepthBuffers();
    render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w, h);
}


int main()
{   
    // init stuff (load, data, shaders and so on)
    Screen::Instance().InitRenderStuff();
    initGameStuff(); 

    // prepare renderer
    Renderer& renderer = Screen::Instance().GetRender();
    renderer.InitPostEffects();
    renderer.MakeShortCuts();
    renderer.SetMeshQuad(MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID));

    // create objects
    Star* star = GetNewStar();

    // GAME LOOP
    while (Screen::Instance().GetWindow().isOpen())
    {    
        // manage the user input
        UserInputManagerInSpace::Instance().UpdateInSpace(nullptr);
        Screen::Instance().UpdateInSpace();

        // render gl
        star->Update();
        renderStar_NEW(renderer, star);

        // send smfl draw command
        Screen::Instance().Draw();
    }

    return EXIT_SUCCESS;
}
