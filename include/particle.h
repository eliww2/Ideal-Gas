//
// Created by student on 3/16/21.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:

  Particle(glm::vec2 position, glm::vec2 velocity);

  void SetPosition(glm::vec2 position);
  void SetVelocity(glm::vec2 velocity);

  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity() const;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}

#endif  // IDEAL_GAS_PARTICLE_H
