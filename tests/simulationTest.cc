#include <catch2/catch.hpp>

#include <gas_container.h>

#include "particle.h"

using idealgas::GasContainer;

TEST_CASE("Wall collision test") {
  SECTION("Left Wall Collision Test") {
    double x_pos = 105;
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

    REQUIRE(expected[0] == particle.GetVelocity()[0]);
  }

  SECTION("Right Wall Collision Test") {
    double x_pos = 595;
    double y_pos = 300;

    vec2 position = vec2(x_pos, y_pos);
    double x_velocity = 1;
    double y_velocity = 0;

    glm::vec2 expected(-1, 0);

    vec2 velocity = vec2(x_velocity, y_velocity);
    idealgas::Particle particle(position, velocity);
    idealgas::GasContainer container(0, 2);

    container.AddParticle(particle);

    container.AdvanceOneFrame();

    REQUIRE(expected[0] == particle.GetVelocity()[0]);
  }

  SECTION("Bottom Wall Collision Test") {
    double x_pos = 300;
    double y_pos = 599;

    vec2 position = vec2(x_pos, y_pos);
    double x_velocity = 0;
    double y_velocity = 1;

    glm::vec2 expected(0, -1);

    vec2 velocity = vec2(x_velocity, y_velocity);
    idealgas::Particle particle(position, velocity);
    idealgas::GasContainer container(0, 2);

    container.AddParticle(particle);

    container.AdvanceOneFrame();

    REQUIRE(expected[1] == particle.GetVelocity()[1]);
  }

  SECTION("Top Wall Collision Test") {
    double x_pos = 300;
    double y_pos = 300;

    vec2 position = vec2(x_pos, y_pos);
    double x_velocity = 0;
    double y_velocity = -1;

    glm::vec2 expected(0, 1);

    vec2 velocity = vec2(x_velocity, y_velocity);
    idealgas::Particle particle(position, velocity);
    idealgas::GasContainer container(0, 2);

    container.AddParticle(particle);

    container.AdvanceOneFrame();

    REQUIRE(expected[1] == particle.GetVelocity()[1]);
  }
}

TEST_CASE("Velocity Updates Position") {
  SECTION("X Position is Updated") {
      double x_pos = 300;
      double y_pos = 300;

      vec2 position = vec2(x_pos, y_pos);
      double x_velocity = 1;
      double y_velocity = 0;

      glm::vec2 expected(301, 300);

      vec2 velocity = vec2(x_velocity, y_velocity);
      idealgas::Particle particle(position, velocity);
      idealgas::GasContainer container(0, 2);

      container.AddParticle(particle);

      container.AdvanceOneFrame();

      REQUIRE(expected[0] == particle.GetPosition()[0]);
  }

  SECTION("y Position is Updated") {
      double x_pos = 300;
      double y_pos = 300;

      vec2 position = vec2(x_pos, y_pos);
      double x_velocity = 0;
      double y_velocity = 0;

      glm::vec2 expected(300, 301);

      vec2 velocity = vec2(x_velocity, y_velocity);
      idealgas::Particle particle(position, velocity);
      idealgas::GasContainer container(0, 2);

      container.AddParticle(particle);

      container.AdvanceOneFrame();
      REQUIRE(expected[1] == particle.GetPosition()[1]);
  }
}

TEST_CASE("Particle Collision") {
  SECTION("Particle Collision X Velocity") {
    idealgas::GasContainer container(0,2);
    vec2 positionOne = vec2(300, 300);
    vec2 positionTwo = vec2(305, 300);
    vec2 velocityOne = vec2(1, 0);
    vec2 velocityTwo = vec2(-1, 0);
    idealgas::Particle particleOne(positionOne, velocityOne);
    idealgas::Particle particleTwo(positionTwo, velocityTwo);
    container.AddParticle(particleOne);
    container.AddParticle(particleTwo);
    container.AdvanceOneFrame();
    REQUIRE(-1 == particleOne.GetVelocity()[0]);
    REQUIRE(1 == particleTwo.GetVelocity()[0]);
  }

  SECTION("Particle Collision Y Velocity") {
    idealgas::GasContainer container(0,2);
    vec2 positionOne = vec2(300, 300);
    vec2 positionTwo = vec2(300, 305);
    vec2 velocityOne = vec2(0, 1);
    vec2 velocityTwo = vec2(0, -1);
    idealgas::Particle particleOne(positionOne, velocityOne);
    idealgas::Particle particleTwo(positionTwo, velocityTwo);
    container.AddParticle(particleOne);
    container.AddParticle(particleTwo);
    container.AdvanceOneFrame();
    REQUIRE(-1 == particleOne.GetVelocity()[1]);
    REQUIRE(1 == particleTwo.GetVelocity()[1]);
  }
}

TEST_CASE("Edge cases for particle") {
  SECTION("Particles not touching") {
    idealgas::GasContainer container(0,2);
    vec2 positionOne = vec2(300, 300);
    vec2 positionTwo = vec2(200, 200);
    vec2 velocityOne = vec2(0, 1);
    vec2 velocityTwo = vec2(0, 1);
    idealgas::Particle particleOne(positionOne, velocityOne);
    idealgas::Particle particleTwo(positionTwo, velocityTwo);
    container.AddParticle(particleOne);
    container.AddParticle(particleTwo);
    container.AdvanceOneFrame();
    REQUIRE(1 == particleOne.GetVelocity()[1]);
    REQUIRE(1 == particleTwo.GetVelocity()[1]);
  }
  SECTION("Particles touching moving in opposite direction") {
    idealgas::GasContainer container(0,2);
    vec2 positionOne = vec2(300, 300);
    vec2 positionTwo = vec2(301, 301);
    vec2 velocityOne = vec2(0, -1);
    vec2 velocityTwo = vec2(0, 1);
    idealgas::Particle particleOne(positionOne, velocityOne);
    idealgas::Particle particleTwo(positionTwo, velocityTwo);
    container.AddParticle(particleOne);
    container.AddParticle(particleTwo);
    container.AdvanceOneFrame();
    REQUIRE(-1 == particleOne.GetVelocity()[1]);
    REQUIRE(1 == particleTwo.GetVelocity()[1]);
  }

}


