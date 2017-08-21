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

#include "GenericTable.hpp"

#include <cassert>

namespace {
const std::string title_id = "title";
const std::string value_id = "value";
} // namespace

namespace gui {
namespace info {

Table::Table(const std::map<std::string, std::string>& data)
{
    m_table = sfg::Table::Create();
    int col = 0;
    int row = 0;
    for (const auto& it: data) {
        sfg::Label::Ptr titleLabel = sfg::Label::Create(it.first);
        sfg::Label::Ptr valueLabel = sfg::Label::Create(it.second);

        titleLabel->SetId(title_id);
        valueLabel->SetId(value_id);

        m_widgets.insert(std::make_pair(it.first, valueLabel));
        m_table->Attach( titleLabel, sf::Rect<sf::Uint32>( col,   row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        m_table->Attach( valueLabel, sf::Rect<sf::Uint32>( col+1, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );

        row++;
    }

    m_table->SetColumnSpacings(10);
}

Table::~Table()
{

}

void Table::update(const std::map<std::string, std::string>& data)
{
    assert(data.size()==m_widgets.size());
    for (const auto& it_string: data) {
        if (const auto& it_widget = m_widgets.find(it_string.first) != m_widgets.end()) {
            //it_widget.SetText(it_string.second);
            m_widgets[it_string.first]->SetText(it_string.second);
        }
    }
}

} // naemspace info
} // namespace gui
