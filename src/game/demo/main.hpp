#pragma once

#include <iostream>
#include <vector>
#include <cassert>


namespace sandbox {

namespace descr {

class Ship {
public:
    Ship(int id, int prop):m_id(id), m_prop(prop) {}

    int id() const { return m_id; }
    int prop() const { return m_prop; }
private:
    int m_id = 0;
    int m_prop = 0;
};

} // namespace descr

namespace model {

class Base {
public:
    Base(int id):m_id(id) {}

    int id() const { return m_id; }

private:
    int m_id = 0;

};

class Ship : public Base {
public:
    Ship(int id):Base(id) {}

    int pos() const { return m_pos; }

    void setPos(int pos) { m_pos = pos; }
private:
    int m_pos = 0;
};

class StarSystem : public Base {
public:
    StarSystem(int id):Base(id) {}
    void addShip(int id) { m_ships.push_back(id); }

    const std::vector<int>& ships() const { return m_ships; }

private:
    std::vector<int> m_ships;
};

} // namespace model

namespace control {

class Ship {
public:
    Ship(model::Ship* model):m_model(model) {}

    void update() {
        std::cout<<"update ship: id="<<m_model->id()<<std::endl;
        m_model->setPos( m_model->pos() + 1 );
    }
private:
    model::Ship* m_model = nullptr;
};

class StarSystem {
public:
    StarSystem(model::StarSystem* model):m_model(model) {}

    void add(model::Ship* model, int pos) {
        model->setPos(pos);
        auto control = new control::Ship(model);
        m_model->addShip(model->id());
        m_ships.push_back(control);
    }

    void update() {
        std::cout<<"update ss: id="<<m_model->id()<<std::endl;
        for(control::Ship* ship: m_ships) {
            ship->update();
        }
    }

private:
    model::StarSystem* m_model = nullptr;

    std::vector<control::Ship*> m_ships;
};

} // namespace control

namespace view {

class Ship {
public:
    Ship(model::Ship* model):m_model(model) {}

    void draw() {
        std::cout<<"draw ship: id="<<m_model->id()<<" pos="<<m_model->pos()<<std::endl;
    }

private:
    model::Ship* m_model = nullptr;
};

class StarSystem {
public:
    StarSystem(model::StarSystem* model):m_model(model) {}

    void refresh();

    void draw() {
        refresh();
        std::cout<<"draw ss: id="<<m_model->id()<<std::endl;
        for(view::Ship* ship: m_ships) {
            ship->draw();
        }
    }

private:
    model::StarSystem* m_model = nullptr;

    std::vector<view::Ship*> m_ships;
};

} // namespace view


class Enteties {
public:
    void add(model::Ship* ship) { m_ships.push_back(ship); }
    void add(model::StarSystem* starsystem) { m_starsystems.push_back(starsystem); }
    model::Ship* getShip(int id) {
        for(model::Ship* ship: m_ships) {
            if (ship->id() == id) {
                return ship;
            }
        }

        assert(false);
        return nullptr;
    }
    model::StarSystem* getStarSystem(int id) {
        for(model::StarSystem* starsystem: m_starsystems) {
            if (starsystem->id() == id) {
                return starsystem;
            }
        }

        assert(false);
        return nullptr;
    }

    std::vector<model::StarSystem*> starsytems() const { return m_starsystems; }
    std::vector<model::Ship*> ships() const { return m_ships; }

private:
    std::vector<model::StarSystem*> m_starsystems;
    std::vector<model::Ship*> m_ships;
};

Enteties* ENTITIES = nullptr;

template<typename T>
T* reg(T* model) {
    assert(model);
    ENTITIES->add(model);
    return model;
}

} // namespace sandbox
