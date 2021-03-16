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

  GasContainer(size_t num_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:

  int kDefaultRadius = 10;

  std::vector<Particle> particles_;

  vec2 kTopLeftBox = vec2(100, 100);
  vec2 kBottomRightBox = vec2(600, 600);

};

}  // namespace idealgas
