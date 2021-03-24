#include "gas_container.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(size_t num_particles, size_t MaxInitialVelocity) {

  for (size_t i = 0; i < num_particles; i++) {
    size_t particle_size = rand() % 3;
    size_t radius;
    size_t mass;
    std::string color;
    if (particle_size == 0) {
      radius = kSmallRadius;
      mass = kSmallMass;
    } else if (particle_size == 1) {
      radius = kMediumRadius;
      mass = kMediumMass;
    } else {
      radius = kLargeRadius;
      mass = kLargeMass;
    }

    double x_pos =
        rand() % (kRightWall - kLeftWall - radius - radius)
        + (kLeftWall + radius);
    double y_pos =
        rand() % (kBottomWall - kTopWall - radius - radius)
        + (kTopWall + radius);
    vec2 position = vec2(x_pos, y_pos);
    double x_velocity = rand() % MaxInitialVelocity;
    double y_velocity = rand() % MaxInitialVelocity;
    vec2 velocity = vec2(x_velocity, y_velocity);
    Particle particle(position, velocity, mass, radius);
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  for (size_t i = 0; i < particles_.size(); i++) {
    if (particles_[i].GetMass() == 1) {
      ci::gl::color(ci::Color("orange"));
    } else if (particles_[i].GetMass() == 2) {
      ci::gl::color(ci::Color("blue"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    ci::gl::drawSolidCircle(particles_[i].GetPosition(), particles_[i].GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftBox, kBottomRightBox));
}

void GasContainer::AdvanceOneFrame() {

  for (size_t i = 0; i < particles_.size(); i++) {
    vec2 position = particles_[i].GetPosition();
    vec2 velocity = particles_[i].GetVelocity();
    size_t radius = particles_[i].GetRadius();

    // check left wall collision
    if (position[0] < kTopLeftBox[0] + radius && velocity[0] < 0) {
      particles_[i].SetVelocity(vec2(-velocity[0], velocity[1]));
    }

    // check right wall collision
    if (position[0] > kBottomRightBox[0] - radius && velocity[0] > 0) {
      particles_[i].SetVelocity(vec2(-velocity[0], velocity[1]));
    }

    // check Top wall collision
    if (position[1] < kTopLeftBox[1] + radius && velocity[1] < 0) {
      particles_[i].SetVelocity(vec2(velocity[0], -velocity[1]));
    }

    // check bottom wall collision
    if (position[1] > kBottomRightBox[1] - radius && velocity[1] > 0) {
      particles_[i].SetVelocity(vec2(velocity[0], -velocity[1]));
    }

    if (particles_.size() > 1) {
      for (size_t j = 0; j < particles_.size(); j++) {
        if (i != j) {
          if (std::abs(particles_[j].GetPosition()[0] - position[0]) < 20 &&
              std::abs(particles_[j].GetPosition()[1] - position[1]) < 20 &&
              glm::dot((position - particles_[j].GetPosition()),
                       (velocity - particles_[j].GetVelocity())) < 0) {
            glm::vec2 one_vel = velocity;
            glm::vec2 two_vel = particles_[j].GetVelocity();
            glm::vec2 one_pos = position;
            glm::vec2 two_pos = particles_[j].GetPosition();

            particles_[i].SetVelocity(
                ParticleCollision(one_pos, two_pos, one_vel, two_vel));
            particles_[j].SetVelocity(
                ParticleCollision(two_pos, one_pos, two_vel, one_vel));
          }
        }
      }
    }
    particles_[i].SetPosition(
        particles_[i].GetPosition() + particles_[i].GetVelocity());
  }
}

glm::vec2 GasContainer::ParticleCollision(
    glm::vec2 pos_one, glm::vec2 pos_two, glm::vec2 vel_one, glm::vec2 vel_two)
{
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
