#include "gas_container.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(size_t num_particles) {
  for (size_t i = 0; i < num_particles; i++) {
    double xPos =
        rand() % (kRightWall - kLeftWall - kDefaultRadius - kDefaultRadius)
        + (kLeftWall + kDefaultRadius);
    double yPos =
        rand() % (kBottomWall - kTopWall - kDefaultRadius - kDefaultRadius)
        + (kTopWall + kDefaultRadius);
    vec2 position = vec2(xPos, yPos);
    double xVelocity = rand() % 3;
    double yVelocity = rand() % 3;
    vec2 velocity = vec2(xVelocity, yVelocity);
    Particle particle(position, velocity);
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("orange"));
  for (size_t i = 0; i < particles_.size(); i++) {
    ci::gl::drawSolidCircle(particles_[i].GetPosition(), kDefaultRadius);
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftBox, kBottomRightBox));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    // check left wall collision
    if (particles_[i].GetPosition()[0] < kTopLeftBox[0] + kDefaultRadius &&
        particles_[i].GetVelocity()[0] < 0) {
        vec2 velocity = particles_[i].GetVelocity();
        particles_[i].SetVelocity(vec2(-velocity[0], velocity[1]));
    }

    // check right wall collision
    if (particles_[i].GetPosition()[0] > kBottomRightBox[0] - kDefaultRadius &&
        particles_[i].GetVelocity()[0] > 0) {
      vec2 velocity = particles_[i].GetVelocity();
      particles_[i].SetVelocity(vec2(-velocity[0], velocity[1]));
    }

    if (particles_[i].GetPosition()[1] < kTopLeftBox[1] + kDefaultRadius &&
        particles_[i].GetVelocity()[1] < 0) {
      vec2 velocity = particles_[i].GetVelocity();
      particles_[i].SetVelocity(vec2(velocity[0], -velocity[1]));
    }

    if (particles_[i].GetPosition()[1] > kBottomRightBox[1] - kDefaultRadius &&
        particles_[i].GetVelocity()[1] > 0) {
      vec2 velocity = particles_[i].GetVelocity();
      particles_[i].SetVelocity(vec2(velocity[0], -velocity[1]));
    }

    for (size_t j = 0; j < particles_.size(); j++) {
      if (i != j) {
        if (std::abs (particles_[j].GetPosition()[0] - particles_[i].GetPosition()[0]) < 20
            && std::abs (particles_[j].GetPosition()[1] - particles_[i].GetPosition()[1]) < 20
            && glm::dot((particles_[i].GetPosition() - particles_[j].GetPosition()),
                        (particles_[i].GetVelocity() - particles_[j].GetVelocity())) < 0) {
          glm::vec2 one_vel = particles_[i].GetVelocity();
          glm::vec2 two_vel = particles_[j].GetVelocity();
          glm::vec2 one_pos = particles_[i].GetPosition();
          glm::vec2 two_pos = particles_[j].GetPosition();

          particles_[i].SetVelocity(ParticleCollision(one_pos, two_pos, one_vel, two_vel));
          particles_[j].SetVelocity(ParticleCollision(two_pos, one_pos, two_vel, one_vel));
        }
      }
    }
    particles_[i].SetPosition(particles_[i].GetPosition() + particles_[i].GetVelocity());
  }
}

glm::vec2 GasContainer::ParticleCollision(glm::vec2 pos_one, glm::vec2 pos_two, glm::vec2 vel_one,
                       glm::vec2 vel_two) {
  vec2 delta_pos =  pos_one - pos_two;
  vec2 delta_vel = vel_one - vel_two;

  float numerator_dot = glm::dot(delta_vel, delta_pos);
  float magnitude = pow(glm::length(delta_pos), 2);
  float scalar = numerator_dot / magnitude;

  glm::vec2 rhs = scalar * delta_pos;

  glm::vec2 updated_vel = vel_one - rhs;

  return updated_vel;
}

}  // namespace idealgas
