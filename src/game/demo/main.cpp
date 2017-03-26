#include "main.hpp"

namespace view {

void
StarSystem::refresh() {
    for(view::Ship* view: m_ships) {
        delete view;
    }
    m_ships.clear();

    auto ships = m_model->ships();
    for(int id: ships) {
        model::Ship* model = ENTITIES->getShip(id);
        view::Ship* ship = new view::Ship(model);
        m_ships.push_back(ship);
    }
}

}

int main()
{
    ENTITIES = new Enteties;

    model::StarSystem* ss_model = reg(new model::StarSystem(/*id=*/1));
    control::StarSystem* ss_control = new control::StarSystem(ss_model);
    view::StarSystem* ss_view = new view::StarSystem(ss_model);

    for(int i=2; i<5; ++i) {
        model::Ship* model = reg(new model::Ship(/*id=*/i));
        ss_control->add(model, 10*i);
    }
//    descr::Ship* descr = new descr::Ship(/*id=*/1, /*prop=*/100);

    for(int i=0; i<2; ++i) {
        ss_control->update();
        ss_view->draw();
    }

    return 0;
}
