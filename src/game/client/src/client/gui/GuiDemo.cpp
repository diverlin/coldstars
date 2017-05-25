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

#include "GuiDemo.hpp"

#include <client/gui/info/table.hpp>
#include <client/gui/info/starsystem.hpp>

#include <jeti/SFMLWrapper.hpp>

namespace gui {

Demo::Demo(jeti::SFMLWrapper* wrapper)
    :
      m_window(wrapper->window())
{
    m_window.setActive();

    sfg::Window::Ptr window = sfg::Window::Create(/*sfg::Window::Style::BACKGROUND*/);
    window->SetTitle( "StarSystem" );

    auto red_scale = sfg::Scale::Create( 0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL );
    auto green_scale = sfg::Scale::Create( 0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL );
    auto blue_scale = sfg::Scale::Create( 0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL );
    auto angle_scale = sfg::Scale::Create( 0.f, 360.f, 1.f, sfg::Scale::Orientation::HORIZONTAL );
    auto auto_check = sfg::CheckButton::Create( "Auto" );

    auto table = sfg::Table::Create();
    table->SetRowSpacings( 5.f );
    table->SetColumnSpacings( 5.f );

    table->Attach( sfg::Label::Create( "Change the color of the rect using the scales below." ), sf::Rect<sf::Uint32>( 0, 0, 3, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    table->Attach( sfg::Label::Create( "Red:" ), sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    table->Attach( red_scale, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
    table->Attach( sfg::Label::Create( "Green:" ), sf::Rect<sf::Uint32>( 0, 2, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    table->Attach( green_scale, sf::Rect<sf::Uint32>( 1, 2, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
    table->Attach( sfg::Label::Create( "Blue:" ), sf::Rect<sf::Uint32>( 0, 3, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    table->Attach( blue_scale, sf::Rect<sf::Uint32>( 1, 3, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
    table->Attach( sfg::Label::Create( "Angle:" ), sf::Rect<sf::Uint32>( 0, 4, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
    table->Attach( angle_scale, sf::Rect<sf::Uint32>( 1, 4, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
    table->Attach( auto_check, sf::Rect<sf::Uint32>( 2, 4, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );

    m_infoStarSystem = new info::StarSystem;

    auto container = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

//    container->Pack( table );
//    container->Pack( m_info );
    container->Pack( m_infoStarSystem->mainWidget() );

    window->Add( container );

    m_desktop.Add( window );

    m_desktop.SetProperties(
        "Window {"
        "   BackgroundColor: #293546CC;"
        "}"
        "Label#value {"
        "   Color: #66ff33FF;"
        "}"
                );
}

Demo::~Demo() {
}

void
Demo::update(const std::vector<sf::Event>& events) {
//    sf::Event event;
//    while(m_window.pollEvent(event)) {
//        m_desktop.HandleEvent( event );
//    }

    for (const sf::Event& event: events) {
        m_desktop.HandleEvent( event );
    }
}

void Demo::draw() {
    auto delta = m_clock.restart().asSeconds();
    m_desktop.Update( delta );

    // SFGUI rendering.
    m_gui.Display( m_window );
}

} // namespace gui
