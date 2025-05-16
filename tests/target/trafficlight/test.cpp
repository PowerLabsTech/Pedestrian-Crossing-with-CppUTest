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