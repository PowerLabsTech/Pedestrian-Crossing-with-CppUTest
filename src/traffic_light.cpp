#include "traffic_light.h"

static traffic_light_state_t currentState = RED;
static traffic_light_state_t nextState = currentState;

void setTrafficLightState(traffic_light_state_t state)
{
    nextState = state;
    runTrafficLight();
}

/*
    The LEDs are set in correlation to <nextState>
*/
traffic_light_state_t runTrafficLight(void)
{
	switch (nextState)
    {
        case RED:
            currentState = RED;
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(YELLOW_LED_PIN, 0);
            break;
        case GREEN:
            currentState = GREEN;
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(YELLOW_LED_PIN, 0);
            break;
        case YELLOW:
            currentState = YELLOW;
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(YELLOW_LED_PIN, 1);
            break;
    }
    return currentState;
}

bool trafficLightButtonPressed(void)
{
    return false;
}