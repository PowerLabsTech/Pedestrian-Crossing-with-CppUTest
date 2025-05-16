//test.cpp

#include "CppUTest/TestHarness.h"
#include "traffic_light.h"

// Create a test group
TEST_GROUP(TrafficLightGroup)
{
    void setup()
    {
        // Initialize before each test
    }
    
    void teardown()
    {
        // Deinitialize after each test
    }
};

TEST(TrafficLightGroup, InitialStateIsRed)
{
    CHECK_EQUAL(RED, runTrafficLight()); // This checks that the traffic light starts in RED.
}

TEST(TrafficLightGroup, CorrectLightTransitions)
{
    // The light should start in RED
    CHECK_EQUAL(RED, runTrafficLight());

    setTrafficLightState(GREEN); // Transition: RED should change to GREEN
    CHECK_EQUAL(GREEN, runTrafficLight());

    setTrafficLightState(YELLOW); // Transition: GREEN should change to YELLOW
    CHECK_EQUAL(YELLOW, runTrafficLight());

    setTrafficLightState(RED); // Transition: YELLOW should change to RED
    CHECK_EQUAL(RED, runTrafficLight());
}