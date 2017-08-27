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
const std::string title_main_id = "title_main";
const std::string value_id = "value";
} // namespace

namespace gui {
namespace info {

Table::Table(const ceti::InfoTable& data)
{
    m_table = sfg::Table::Create();
    __create(data);
    m_table->SetColumnSpacings(10);
}

Table::~Table()
{
    __clear(); // is it needed?
}

void Table::reset()
{
    __clear();
}

void Table::__clear()
{
    for(auto widget: m_table->GetChildren()) {
        widget.reset();
    }
    m_table->RemoveAll();
}

void Table::__create(const ceti::InfoTable& data)
{
    unsigned int col = 0;
    unsigned int row = 0;
    for (const auto& it: data) {
        std::string title = it.first;
        std::string value = it.second;

        if (title == "id") {
            m_id = title;
        }
        if (title.find("::") != title.npos) {
            value = "----";
        }

        sfg::Label::Ptr titleLabel = sfg::Label::Create(title);
        sfg::Label::Ptr valueLabel = sfg::Label::Create(value);

        if (title.find("::") != title.npos) {
            titleLabel->SetId(title_main_id);
            valueLabel->SetId(title_main_id);
        } else {
            titleLabel->SetId(title_id);
            valueLabel->SetId(value_id);
        }

        m_table->Attach( titleLabel, sf::Rect<sf::Uint32>( col,   row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );
        m_table->Attach( valueLabel, sf::Rect<sf::Uint32>( col+1, row, 1, 1 ), sfg::Table::FILL, sfg::Table::FILL );

        row++;
    }
}

void Table::update(const ceti::InfoTable& data)
{
    std::string id;
    for (ceti::InfoTable::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::string title = it->first;
        if (title == "id") {
            id = it->second;
        }
    }

    if (id == m_id) {
        return;
    }
    __clear();
    __create(data);
}

} // naemspace info
} // namespace gui
