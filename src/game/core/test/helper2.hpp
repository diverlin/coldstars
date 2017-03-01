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

#include <vector>

namespace descriptor {
class Ship;

namespace item {
class Bak;
class Drive;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
class Scaner;
} // namespace item

} // namespace descriptor

namespace model {
class Ship;

namespace item {
class Bak;
class Drive;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
class Scaner;
} // namespace item

} // namespace model

namespace control {
class Ship;

namespace item {
class Bak;
class Drive;
class Droid;
class Grapple;
class Lazer;
class Protector;
class Radar;
class Rocket;
class Scaner;
} // namespace item

} // namespce control



namespace test {

class Ship {
public:
    Ship();
    ~Ship();

    descriptor::Ship* descriptor() const;
    model::Ship* model() const;
    control::Ship* control() const { return m_control; }

private:
    control::Ship* m_control = nullptr;
};

namespace item {

class Bak {
public:
    Bak();
    ~Bak();

    descriptor::item::Bak* descriptor() const;
    model::item::Bak* model() const;
    control::item::Bak* control() const { return m_control; }

private:
    Bak(const Bak&) = delete;
    control::item::Bak* m_control = nullptr;
};

class Drive {
public:
    Drive();
    ~Drive();

    descriptor::item::Drive* descriptor() const;
    model::item::Drive* model() const;
    control::item::Drive* control() const { return m_control; }

private:
    Drive(const Drive&) = delete;
    control::item::Drive* m_control = nullptr;
};

class Droid {
public:
    Droid();
    ~Droid();

    descriptor::item::Droid* descriptor() const;
    model::item::Droid* model() const;
    control::item::Droid* control() const { return m_control; }

private:
    Droid(const Droid&) = delete;
    control::item::Droid* m_control = nullptr;
};

class Grapple {
public:
    Grapple();
    ~Grapple();

    descriptor::item::Grapple* descriptor() const;
    model::item::Grapple* model() const;
    control::item::Grapple* control() const { return m_control; }

private:
    control::item::Grapple* m_control = nullptr;
};

class Lazer {
public:
    Lazer();
    ~Lazer();

    descriptor::item::Lazer* descriptor() const;
    model::item::Lazer* model() const;
    control::item::Lazer* control() const { return m_control; }

private:
    Lazer(const Lazer&) = delete;
    control::item::Lazer* m_control = nullptr;
};

class Protector {
public:
    Protector();
    ~Protector();

    descriptor::item::Protector* descriptor() const;
    model::item::Protector* model() const;
    control::item::Protector* control() const { return m_control; }

private:
    Protector(const Protector&) = delete;
    control::item::Protector* m_control = nullptr;
};

class Radar {
public:
    Radar();
    ~Radar();

    descriptor::item::Radar* descriptor() const;
    model::item::Radar* model() const;
    control::item::Radar* control() const { return m_control; }

private:
    Radar(const Radar&) = delete;
    control::item::Radar* m_control = nullptr;
};

class Rocket {
public:
    Rocket();
    ~Rocket();

    descriptor::item::Rocket* descriptor() const;
    model::item::Rocket* model() const;
    control::item::Rocket* control() const { return m_control; }

private:
    Rocket(const Rocket&) = delete;
    control::item::Rocket* m_control = nullptr;
};

class Scaner {
public:
    Scaner();
    ~Scaner();

    descriptor::item::Scaner* descriptor() const;
    model::item::Scaner* model() const;
    control::item::Scaner* control() const { return m_control; }

private:
    Scaner(const Scaner&) = delete;
    control::item::Scaner* m_control = nullptr;
};

} // namespace item


template<typename T>
class pVector : public std::vector<T> {
public:
    pVector() = default;
    ~pVector() {
        for(T e: *this) {
            delete e;
        }
        this->clear();
    }
};

} // namespace test

