#include "traffic_light.h"

static traffic_light_state_t currentState = RED;
static traffic_light_state_t nextState = currentState;
static bool buttonPressed = false;

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

/*
    A button press is valid only if <currentState> is GREEN
*/
bool trafficLightButtonPressed(void)
{
    buttonPressed = (gpio_get(BUTTON_PIN) == 1);
    if (buttonPressed && currentState == GREEN)
    {
        return true;
    } else
    {
        return false;
    }
}

/*
    Enable the YELLOW LED 
*/
void startYellowTransition(void)
{
    setTrafficLightState(YELLOW);
}

/*
    After duration <yellowToRedDuration>, enable the RED LED
*/
void completeYellowTransitionToRed(uint16_t yellowToRedDuration)
{
    sleep_ms(yellowToRedDuration);
    setTrafficLightState(RED);
}