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

#include <client/session/imachine.hpp>
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

class Client : public core::IMachine {
public:
    Client(int id, bool graphic = false);
    ~Client() override final;

    ClientSession* session() const { return m_session; }

    Player* player() const;

    void connect();

    bool sessionIsRunning() const; // why both?
    bool isRunning() const; // why both?

    void requestCreatePlayerNpc();
    void requestCreatePlayerVehicle();

    void update() override final;
    int telegramsNum() const override final;

protected:
    jeti::Camera* _camera() const;
    jeti::Render* _render() const;
    jeti::Screen* _screen() const;
    view::StarSystem* _view() const;
    gui::UserInputInSpace* _inputs() const;

private:
    bool m_isConnected = false;
    bool m_wait_npc = false;
    bool m_wait_vehicle = false;
    bool m_graphic = false;
    ClientSession* m_session = nullptr;

    std::shared_ptr<TelegramHandler> m_telegramHandler;
};

} // namespace client
