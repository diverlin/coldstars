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

class Show {
public:
    bool background() const { return (m_stars || m_nebulas); }
    bool backgroundFbo() const { return m_star; }
    bool star() const { return m_star; }
    bool stars() const { return m_stars; }
    bool nebulas() const { return m_nebulas; }
    bool spaceobjects() const { return m_spaceobjects; }
    bool spaceobjects_meta() const { return (collisionRadius() || axis()); }
    bool collisionRadius() const { return (m_spaceobjects && m_collision_radius); }
    bool axis() const { return (m_spaceobjects && m_axis); }
    bool hud() const { return m_hud; }
    bool experimental() const { return m_experimental; }

    void setStar(bool star) { m_star = star; }
    void setStars(bool stars) { m_stars = stars; }
    void setNebulas(bool nebulas) { m_nebulas = nebulas; }
    void setSpaceobjects(bool spaceobjects) { m_spaceobjects = spaceobjects; }
    void setCollisionRadius(bool collision_radius) { m_collision_radius = collision_radius; }
    void setAxis(bool axis) { m_axis = axis; }
    void setHud(bool hud) { m_hud = hud; }
    void setExperimental(bool experimental) { m_experimental = experimental; }

private:
    bool m_star = false;
    bool m_stars = true;
    bool m_nebulas = false;
    bool m_spaceobjects = true;
    bool m_collision_radius = false;
    bool m_axis = false;
    bool m_hud = true;
    bool m_experimental = true;
};

