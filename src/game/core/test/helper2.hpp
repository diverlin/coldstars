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


namespace descriptor {
class Ship;

namespace item {
class Bak;
class Drive;
} // namespace item

} // namespace descriptor

namespace model {
class Ship;

namespace item {
class Bak;
class Drive;
} // namespace item

} // namespace model

namespace control {
class Ship;

namespace item {
class Bak;
class Drive;
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
    control::item::Drive* m_control = nullptr;
};

} // namespace item

} // namespace test

