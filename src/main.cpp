#include "main.h"

int main(void)
{
    stdio_init_all();

    // Initialize pins
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_init(YELLOW_LED_PIN);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Set initial state    
    setTrafficLightState(RED);

    while(true)
    {
        if (trafficLightButtonPressed() == true)
        {
            startYellowTransition();
            completeYellowTransitionToRed(YELLOW_TO_RED_DURATION);
            sleep_ms(holdOnBeforeGreen(RED_TO_GREEN_DURATION));
        } else
        {
            setTrafficLightState(GREEN);
        }
    }
}