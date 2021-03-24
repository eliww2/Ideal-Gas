//
// Created by student on 3/16/21.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:

  /**
   * Constructs a particle with a position, mass and velocity.
   * @param position
   * @param velocity
   * @param mass
   */
  Particle(glm::vec2 position, glm::vec2 velocity, size_t mass, size_t radius);

  /**
   * set position.
   * @param position
   */
  void SetPosition(glm::vec2 position);

  /**
   * set velocity.
   * @param velocity
   */
  void SetVelocity(glm::vec2 velocity);

  /**
   * get position.
   * @return
   */

  glm::vec2 GetPosition() const;

  /**
   * get position.
   * @return
   */
  glm::vec2 GetVelocity() const;

  size_t GetMass() const;

  size_t GetRadius() const;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  size_t mass_;
  size_t radius_;
};

}

#endif  // IDEAL_GAS_PARTICLE_H
