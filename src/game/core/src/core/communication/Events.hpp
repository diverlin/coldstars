#pragma once

#include <ceti/type/IdType.hpp>

#include <glm/glm.hpp>

namespace core {
namespace event {

/** TRANSITION */
void addStarSystemToGalaxy(int_t object, int_t parent, const glm::vec3& position);
void addNpcToShip(int_t object, int_t parent);

// items
void mountItem(int_t object, int_t parent);
void loadItem(int_t object, int_t parent);
/** */

/** CREATE */
void createGalaxy(int_t descriptor, int_t object);
void createStarSystem(int_t descriptor, int_t object);
void createNpc(int_t descriptor, int_t object);

// spaceobjects
void createStar(int_t descriptor, int_t object);
void createPlanet(int_t descriptor, int_t object);
void createAsteroid(int_t descriptor, int_t object);
void createShip(int_t descriptor, int_t object);
void createBomb(int_t descriptor, int_t object);
void createGoods(int_t descriptor, int_t object);
void createContainer(int_t descriptor, int_t object, int_t item);

void createBullet(int_t owner, int_t weapon, int_t target_id);


// items
void createBak(int_t descriptor, int_t object);
void createDrive(int_t descriptor, int_t object);
void createDroid(int_t descriptor, int_t object);
void createGrapple(int_t descriptor, int_t object);
void createProtector(int_t descriptor, int_t object);
void createScaner(int_t descriptor, int_t object);
void createRadar(int_t descriptor, int_t object);
void createLazer(int_t descriptor, int_t object);
void createRocket(int_t descriptor, int_t object);
/** */

void addStarToStarSystem(int_t object, int_t parent);
void addPlanetToStarSystem(int_t object, int_t parent);
void addAsteroidToStarSystem(int_t object, int_t parent);

void addShipToStarSystem(int_t object, int_t parent, const glm::vec3& position);
void addContainerToStarSystem(int_t object, int_t parent, const glm::vec3& position, const glm::vec3& impulse);

// hit
void hitSpaceObject(int_t object_id, int damage);
void explode(int_t object, const glm::vec3& center, int damage, int radius);

// GARBAGE
void garbageSpaceObject(int_t object_id);

// REMOVE
void removeSpaceObjectFromStarSystem(int_t object_id, int_t parent);

/** DOCK */
void dockShip(int_t object, int_t destination);
void launchShip(int_t object, int_t destination);

/** JUMP */
void jumpIn(int_t object);
void jumpOut(int_t object, int_t destination);
/** DROP/TAKE */
void dropItem(int_t object, int_t target);
void takeContainer(int_t object, int_t target);

void shoot(int_t object, int_t item);


// MOVE
void moveVehicle(int_t, const glm::vec3&);

// GAME STATES
void endTurn();

// shoot
void targetSpaceObject(int_t, int_t);

} // namespace event
} // namespace core
