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
   * Constructs a particle with a position and velocity.
   * @param position
   * @param velocity
   */
  Particle(glm::vec2 position, glm::vec2 velocity);

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


 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}

#endif  // IDEAL_GAS_PARTICLE_H
