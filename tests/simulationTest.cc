#include <catch2/catch.hpp>

#include <gas_container.h>

#include "particle.h"

using idealgas::GasContainer;

TEST_CASE("Wall collision test") {
  double x_pos = 100;
  double y_pos = 300;

  vec2 position = vec2(x_pos, y_pos);
  double x_velocity = -1;
  double y_velocity = 0;

  glm::vec2 expected(1, 0);

  vec2 velocity = vec2(x_velocity, y_velocity);
  idealgas::Particle particle(position, velocity);
  idealgas::GasContainer container(0, 2);

  container.AddParticle(particle);

  container.AdvanceOneFrame();
  REQUIRE(container)
  REQUIRE(expected[0] == particle.GetVelocity()[0]);
}


