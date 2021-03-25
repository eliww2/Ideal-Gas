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
  std::vector<float> small(6);
  std::vector<float> med(6);
  std::vector<float> large(6);
  for (size_t i = 0; i < particles_.size(); i++) {
    if (particles_[i].GetMass() == 1) {
      DrawHistogram(particles_[i], kTopLeftSmall, kBottomRightSmall, small);
      ci::gl::color(ci::Color("orange"));
      small.at(0)++;
    } else if (particles_[i].GetMass() == 2) {
      DrawHistogram(particles_[i], kTopLeftMed, kBottomRightMed, med);
      ci::gl::color(ci::Color("blue"));
      med.at(0)++;
    } else {
      DrawHistogram(particles_[i], kTopLeftLarge, kBottomRightLarge, large);
      ci::gl::color(ci::Color("red"));
      large.at(0)++;
    }
    ci::gl::drawSolidCircle(particles_[i].GetPosition(), particles_[i].GetRadius());
    DrawConstants();
  }

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
            float mass_one = particles_[i].GetMass();
            float mass_two = particles_[j].GetMass();

            particles_[i].SetVelocity(
                ParticleCollision(one_pos, two_pos, one_vel, two_vel, mass_one, mass_two));
            particles_[j].SetVelocity(
                ParticleCollision(two_pos, one_pos, two_vel, one_vel, mass_two, mass_one));
          }
        }
      }
    }
    particles_[i].SetPosition(
        particles_[i].GetPosition() + particles_[i].GetVelocity());
  }
}

glm::vec2 GasContainer::ParticleCollision(
    glm::vec2 pos_one, glm::vec2 pos_two,
    glm::vec2 vel_one, glm::vec2 vel_two,
    float mass_one, float mass_two)
{
  vec2 delta_pos =  pos_one - pos_two;
  vec2 delta_vel = vel_one - vel_two;

  float numerator_dot = glm::dot(delta_vel, delta_pos);
  float magnitude = pow(glm::length(delta_pos), 2);
  float scalar = numerator_dot / magnitude;
  float masses = (2 * mass_two) / (mass_one + mass_two);

  glm::vec2 rhs = scalar * delta_pos * masses;

  glm::vec2 updated_vel = vel_one - rhs;

  return updated_vel;
}

void GasContainer::DrawHistogram(Particle particle, vec2 top_left, vec2 bottom_right, std::vector<float>& count) const {
  ci::gl::color(ci::Color("green"));
  float velocity_x = particle.GetVelocity()[0] * particle.GetVelocity()[0];
  float velocity_y = particle.GetVelocity()[1] * particle.GetVelocity()[1];
  float final_velocity = sqrt(velocity_x + velocity_y);

  vec2 part_top_left;
  vec2 part_bottom_right;
  size_t left_start = (bottom_right[0] - top_left[0]) / 5;

  if (final_velocity < 1) {
    int counter = count.at(1);
    if ((counter % 2) == 0) {
      ci::gl::color(ci::Color("green"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    part_top_left = vec2(top_left[0], (bottom_right[1] - (20 * count.at(1))));
    part_bottom_right = vec2(top_left[0] + (left_start), (bottom_right[1]) - ((20 * count.at(1)) + 20));
    count.at(1)++;

  } else if (final_velocity < 2) {
    int counter = count.at(2);
    if ((counter % 2) == 0) {
      ci::gl::color(ci::Color("green"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    part_top_left = vec2(top_left[0] + left_start, (bottom_right[1] - (20 * count.at(2))));
    part_bottom_right = vec2(top_left[0] + (left_start * 2), (bottom_right[1]) - ((20 * count.at(2)) + 20));
    count.at(2)++;
  } else if (final_velocity < 3) {
    int counter = count.at(3);
    if ((counter % 2) == 0) {
      ci::gl::color(ci::Color("green"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    part_top_left = vec2(top_left[0] + (left_start * 2), (bottom_right[1] - (20 * count.at(3))));
    part_bottom_right = vec2(top_left[0] + (left_start * 3), (bottom_right[1]) - ((20 * count.at(3)) + 20));
    count.at(3)++;
  } else if (final_velocity < 4) {
    int counter = count.at(4);
    if ((counter % 2) == 0) {
      ci::gl::color(ci::Color("green"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    part_top_left = vec2(top_left[0] + (left_start * 3), (bottom_right[1] - (20 * count.at(4))));
    part_bottom_right = vec2(top_left[0] + (left_start * 4), (bottom_right[1]) - ((20 * count.at(4)) + 20));
    count.at(4)++;
  } else {
    int counter = count.at(5);
    if ((counter % 2) == 0) {
      ci::gl::color(ci::Color("green"));
    } else {
      ci::gl::color(ci::Color("red"));
    }
    part_top_left = vec2(top_left[0] + (left_start * 4), (bottom_right[1] - (20 * count.at(5))));
    part_bottom_right = vec2(top_left[0] + (left_start * 5), (bottom_right[1]) - ((20 * count.at(5)) + 20));
    count.at(5)++;
  }
  ci::gl::drawSolidRect(ci::Rectf(part_top_left, part_bottom_right));
}

void GasContainer::DrawConstants() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftBox, kBottomRightBox));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftSmall, kBottomRightSmall));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftMed, kBottomRightMed));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeftLarge, kBottomRightLarge));
  ci::gl::drawString("Speed", vec2(700, 810), ci::Color("white"), ci::Font("arial", 24));
  ci::gl::drawString("1<", vec2(640, 760), ci::Color("white"), ci::Font());
  ci::gl::drawString("1-2", vec2(685, 760), ci::Color("white"), ci::Font());
  ci::gl::drawString("2-3", vec2(730, 760), ci::Color("white"), ci::Font());
  ci::gl::drawString("3-4", vec2(775, 760), ci::Color("white"), ci::Font());
  ci::gl::drawString("4+", vec2(820, 760), ci::Color("white"), ci::Font());
  ci::gl::drawString("Big Particle", vec2(670, 550), ci::Color("white"), ci::Font("arial", 24));
  ci::gl::drawString("Medium Particle", vec2(650, 300), ci::Color("white"), ci::Font("arial", 24));
  ci::gl::drawString("Small Particle", vec2(670, 50), ci::Color("white"), ci::Font("arial", 24));
  ci::gl::drawString("One Block = 1 Particle", vec2(100, 700), ci::Color("white"), ci::Font("arial", 35));

}

}  // namespace idealgas
