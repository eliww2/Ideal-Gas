#include "gas_container.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(size_t num_particles) {
  for (size_t i = 0; i < num_particles; i++) {
    size_t xPos = rand() % 480 + 110;
    size_t yPos = rand() % 480 + 110;
    vec2 position = vec2(xPos, yPos);
    size_t xVelocity = rand() % 100;
    size_t yVelocity = rand() % 100;
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

}

}  // namespace idealgas
