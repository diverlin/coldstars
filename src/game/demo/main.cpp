#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/world/starsystem.hpp>

#include <core/session/Sessions.hpp>
#include <core/resource/Data.hpp>

#include <client/view/StarSystem.hpp>
#include <client/session/client.hpp>
#include <client/session/ClientSession.hpp>


int main()
{
    int session_id = 1;
    bool use_graphics = true;
    ClientSession* session = new ClientSession(session_id, use_graphics);
    core::Sessions::get().add(session);
    core::Sessions::get().activate(session_id);

    bool save = true;
    session->init(save);

    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();

    starsystem->add(ship);

    view::StarSystemViewer* viewer = session->view();
    //view::StarSystemViewer* view = new view::StarSystemViewer;
    assert(viewer);

    while(viewer->isOpened()) {
        viewer->update();
        viewer->draw(starsystem);
    }

    return 0;
}


