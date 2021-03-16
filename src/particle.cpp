//
// Created by student on 3/16/21.
//
#include "particle.h"

namespace idealgas {

  Particle::Particle(glm::vec2 position, glm::vec2 velocity) {
    position_ = position;
    velocity_ = velocity;
  }

  glm::vec2 Particle::GetPosition() const {
    return position_;
  }

  glm::vec2 Particle::GetVelocity() const {
    return velocity_;
  }

  void Particle::SetPosition(glm::vec2 position) {
    position_ = position;
  }

  void Particle::SetVelocity(glm::vec2 velocity) {
    velocity_ = velocity;
  }
}