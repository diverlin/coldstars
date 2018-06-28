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

#include <ceti/type/IdType.hpp>

#include <memory>

namespace jeti {
class Camera;
class Render;
class Screen;
} // namespace jeti

namespace view {
class StarSystem;
} // namespace view

namespace gui {
class UserInputInSpace;
} // namespace gui


class ClientSession;

namespace client {

class Player;
class TelegramHandler;

class Client {
public:
    Client(int id, bool graphic = false);
    ~Client();

    ClientSession* session() const { return m_session; }

//    void reply_create_player(int_t npc_id);

    bool sessionIsRunning() const; // why both?
    bool isRunning() const; // why both?

    void requestCreatePlayerNpc();
    void requestCreatePlayerVehicle();

    void update();

    Player* player() const;

private:
    bool m_graphic = false;
    int m_id = -1;
    ClientSession* m_session = nullptr;

    jeti::Camera* m_camera = nullptr;
    jeti::Render* m_render= nullptr;
    jeti::Screen* m_screen = nullptr;

    view::StarSystem* m_view = nullptr;
    gui::UserInputInSpace* m_inputs = nullptr;

    std::shared_ptr<TelegramHandler> m_telegramHandler;

    void __activate() const;
//    void __create_player();
};

} // namespace client
