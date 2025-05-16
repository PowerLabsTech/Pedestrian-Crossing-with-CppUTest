//test.cpp

#include "CppUTest/TestHarness.h"
#include "traffic_light.h"

// Function overload to simulate button press
bool trafficLightButtonPressed(bool simulatePressed, traffic_light_state_t currentState)
{
    if (simulatePressed && currentState == GREEN)
    {
        return true;
    } else
    {
        return false;
    }
}

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

TEST(TrafficLightGroup, ButtonPressOnGreenToYellowThenRed)
{
    // Start the light at GREEN
    setTrafficLightState(GREEN);
    CHECK_EQUAL(GREEN, runTrafficLight());

    // Simulate the pedestrian button press during GREEN
    CHECK_TRUE(trafficLightButtonPressed(true, GREEN));

    // On the next run, we expect a transition to YELLOW
    startYellowTransition();
    CHECK_EQUAL(YELLOW, runTrafficLight());

    // Then the next run should bring it to RED
    completeYellowTransitionToRed(3000);
    CHECK_EQUAL(RED, runTrafficLight());
}