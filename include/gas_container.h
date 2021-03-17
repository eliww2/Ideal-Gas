#pragma once

#include "cinder/gl/gl.h"
#include <vector>
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:

  /**
   * Takes in the preferred number of particals and the max initial volocity.
   * @param num_particles
   * @param max_velocity
   */
  GasContainer(size_t num_particles, size_t max_velocity);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Adds a particle to a container.
   * @param particle
   */
  void AddParticle(Particle& particle);

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Updates the velocity of the particles when they collide with each other.
   * @param pos_one
   * @param pos_two
   * @param vel_one
   * @param vel_two
   * @return
   */
  glm::vec2 ParticleCollision(glm::vec2 pos_one, glm::vec2 pos_two, glm::vec2 vel_one,
                         glm::vec2 vel_two);

 private:

  std::vector<Particle> particles_;

  size_t kDefaultRadius = 10;

  size_t kTopWall = 100;
  size_t kBottomWall = 600;

  size_t kLeftWall = 100;
  size_t kRightWall = 600;

  vec2 kTopLeftBox = vec2(kLeftWall, kTopWall);
  vec2 kBottomRightBox = vec2(kRightWall, kBottomWall);

};

}  // namespace idealgas
