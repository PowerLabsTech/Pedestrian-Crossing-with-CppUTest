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

TEST(TrafficLightGroup, ButtonPressOnYellowOrRed)
{
    // Start light at YELLOW
    setTrafficLightState(GREEN); // Following our flow, we can't jump from RED to YELLOW, hence we need to go to GREEN before YELLOW.
    setTrafficLightState(YELLOW);
    CHECK_EQUAL(YELLOW, runTrafficLight());

    // Simulate the pedestrian button press during YELLOW
    CHECK_FALSE(trafficLightButtonPressed(true, YELLOW));

    // Start light at RED
    setTrafficLightState(RED);
    CHECK_EQUAL(RED, runTrafficLight());

    // Simulate the pedestrian button press during RED
    CHECK_FALSE(trafficLightButtonPressed(true, RED));
}

TEST(TrafficLightGroup, NoDirectJumps)
{
    // 1. Direct jump from GREEN to RED should not occur.
    setTrafficLightState(GREEN);
    CHECK_EQUAL(GREEN, runTrafficLight()); // Confirm we are at GREEN.
    setTrafficLightState(RED);              // Attempt an illegal jump.
    // Expect that the system does not transition to RED.
    CHECK_EQUAL(GREEN, runTrafficLight());

    // 2. Direct jump from YELLOW to GREEN should not occur.
    setTrafficLightState(YELLOW);
    CHECK_EQUAL(YELLOW, runTrafficLight()); // Confirm we are at YELLOW.
    setTrafficLightState(GREEN);            // Attempt an illegal jump.
    // Expect that the system does not transition to GREEN.
    CHECK_EQUAL(YELLOW, runTrafficLight());

    // 3. Direct jump from RED to YELLOW should not occur.
    setTrafficLightState(RED);
    CHECK_EQUAL(RED, runTrafficLight()); // Confirm we start at RED.
    setTrafficLightState(YELLOW);         // Attempt an illegal jump.
    // Expect that the system does not transition to YELLOW.
    CHECK_EQUAL(RED, runTrafficLight());
}