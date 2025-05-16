#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "pico/stdlib.h"
#include <stdio.h>

#define RED_LED_PIN 20
#define GREEN_LED_PIN 21
#define YELLOW_LED_PIN 22
#define BUTTON_PIN 5

typedef enum
{
    RED,
    GREEN,
    YELLOW
}traffic_light_state_t;

void setTrafficLightState(traffic_light_state_t state);
traffic_light_state_t runTrafficLight(void);
bool trafficLightButtonPressed(void);
void startYellowTransition(void);
void completeYellowTransitionToRed(uint16_t yellowToRedDuration);

#endif // TRAFFIC_LIGHT_H