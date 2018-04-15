#pragma once

#include <iostream>
#include <vector>
#include <cassert>


namespace sandbox {

class ShipDescr {
public:
    ShipDescr(int id, int prop):m_id(id), m_prop(prop) {}

    int id() const { return m_id; }
    int prop() const { return m_prop; }
private:
    int m_id = 0;
    int m_prop = 0;
};

class BaseModel {
public:
    BaseModel(int id):m_id(id) {}

    int id() const { return m_id; }

private:
    int m_id = 0;
};

class ShipModel : public BaseModel {
public:
    ShipModel(int id):BaseModel(id) {}

    int pos() const { return m_pos; }

    void setPos(int pos) { m_pos = pos; }
private:
    int m_pos = 0;
};

class StarSystemModel : public BaseModel {
public:
    StarSystemModel(int id):BaseModel(id) {}
    void addShip(int id) { m_ships.push_back(id); }

    const std::vector<int>& ships() const { return m_ships; }

private:
    std::vector<int> m_ships;
};

class Ship {
public:
    Ship(ShipModel* model):m_model(model) {}

    void update() {
        std::cout<<"update ship: id="<<m_model->id()<<std::endl;
        m_model->setPos( m_model->pos() + 1 );
    }
private:
    ShipModel* m_model = nullptr;
};

class StarSystem {
public:
    StarSystem(StarSystemModel* model):m_model(model) {}

    void add(ShipModel* model, int pos) {
        model->setPos(pos);
        auto control = new Ship(model);
        m_model->addShip(model->id());
        m_ships.push_back(control);
    }

    void update() {
        std::cout<<"update ss: id="<<m_model->id()<<std::endl;
        for(Ship* ship: m_ships) {
            ship->update();
        }
    }

private:
    StarSystemModel* m_model = nullptr;

    std::vector<Ship*> m_ships;
};


class ShipView {
public:
    ShipView(ShipModel* model):m_model(model) {}

    void draw() {
        std::cout<<"draw ship: id="<<m_model->id()<<" pos="<<m_model->pos()<<std::endl;
    }

private:
    ShipModel* m_model = nullptr;
};

class StarSystemView {
public:
    StarSystemView(StarSystemModel* model):m_model(model) {}

    void refresh();

    void draw() {
        refresh();
        std::cout<<"draw ss: id="<<m_model->id()<<std::endl;
        for(ShipView* ship: m_ships) {
            ship->draw();
        }
    }

private:
    StarSystemModel* m_model = nullptr;

    std::vector<ShipView*> m_ships;
};

class Enteties {
public:
    void add(ShipModel* ship) { m_ships.push_back(ship); }
    void add(StarSystemModel* starsystem) { m_starsystems.push_back(starsystem); }
    ShipModel* getShip(int id) {
        for(ShipModel* ship: m_ships) {
            if (ship->id() == id) {
                return ship;
            }
        }

        assert(false);
        return nullptr;
    }
    StarSystemModel* getStarSystem(int id) {
        for(StarSystemModel* starsystem: m_starsystems) {
            if (starsystem->id() == id) {
                return starsystem;
            }
        }

        assert(false);
        return nullptr;
    }

    std::vector<StarSystemModel*> starsytems() const { return m_starsystems; }
    std::vector<ShipModel*> ships() const { return m_ships; }

private:
    std::vector<StarSystemModel*> m_starsystems;
    std::vector<ShipModel*> m_ships;
};

Enteties* ENTITIES = nullptr;

template<typename T>
T* reg(T* model) {
    assert(model);
    ENTITIES->add(model);
    return model;
}

} // namespace sandbox
