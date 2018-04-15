#include "main.hpp"

namespace sandbox {

void
StarSystemView::refresh() {
    for(ShipView* view: m_ships) {
        delete view;
    }
    m_ships.clear();

    auto ships = m_model->ships();
    for(int id: ships) {
        ShipModel* model = ENTITIES->getShip(id);
        ShipView* ship = new ShipView(model);
        m_ships.push_back(ship);
    }
}

} // namespace sandbox

int main()
{
    using namespace sandbox;

    ENTITIES = new Enteties;

    StarSystemModel* ss_model = reg(new StarSystemModel(/*id=*/1));
    StarSystem* ss_control = new StarSystem(ss_model);
    StarSystemView* ss_view = new StarSystemView(ss_model);

    for(int i=2; i<5; ++i) {
        ShipModel* model = reg(new ShipModel(/*id=*/i));
        ss_control->add(model, 10*i);
    }
//    descr::Ship* descr = new descr::Ship(/*id=*/1, /*prop=*/100);

    for(int i=0; i<2; ++i) {
        ss_control->update();
        ss_view->draw();
    }

    return 0;
}


