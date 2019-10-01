#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/world/starsystem.hpp>

#include <core/session/Sessions.hpp>
#include <core/resource/Data.hpp>

#include <client/view/StarSystem.hpp>
#include <client/session/client.hpp>
#include <client/session/ClientSession.hpp>
#include <client/gui/UserInput.hpp>


int main()
{
    int session_id = 1;
    bool use_graphics = true;
    ClientSession* session = new ClientSession(session_id, use_graphics);
    core::Sessions::get().add(session);
    core::Sessions::get().activate(session_id);

    bool save = true;
    session->init(save);

    view::StarSystemViewer* viewer = session->view();
    assert(viewer);

    while(viewer->isOpened()) {
        viewer->update();
        viewer->draw();
//        viewer->drawDeffered();
        gui::UserInput::get().update();
        usleep(200);
    }

    return 0;
}


