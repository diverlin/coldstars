
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

# pragma once

#include <core/session/BaseSession.hpp>


namespace view {
class StarSystemViewer;
} // namespace view

namespace client {
class Player;
} // namespace client

class ClientSession : public core::BaseSession {
public:
    ClientSession(int, bool use_graphic = true);
    ~ClientSession() override final;

    void init(bool) override final;

    client::Player* player() const { return m_player; }
    view::StarSystemViewer* view() const { assert(m_view); return m_view; }

private:
    bool m_useGraphic = true;
    bool m_initialized = false;

    view::StarSystemViewer* m_view = nullptr;
    client::Player* m_player = nullptr;
};



