#include "traffic_light.h"

static traffic_light_state_t currentState = RED;
static traffic_light_state_t nextState = currentState;
static bool buttonPressed = false;

/*
    The system will transition to <state> only if <state> is the expected next state as defined in the requirement (RED → GREEN → YELLOW → RED).
*/
void setTrafficLightState(traffic_light_state_t state)
{
    traffic_light_state_t previousState;
    switch(state)
    {
        case RED:
            previousState = YELLOW;
            break;
        case YELLOW:
            previousState = GREEN;
            break;
        case GREEN:
            previousState = RED;
            break;
    }
    if (currentState == previousState)
    {
        nextState = state;
        runTrafficLight();
    }
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

/*
    Ensures duration <redToGreenDuration> is inbetween specified limits
*/
uint16_t holdOnBeforeGreen(uint16_t redToGreenDuration)
{
    if (redToGreenDuration < MIN_LIMIT)
    {
        redToGreenDuration = MIN_LIMIT;
    } else if (redToGreenDuration > MAX_LIMIT)
    {
        redToGreenDuration = MAX_LIMIT;
    }
    return redToGreenDuration;
}