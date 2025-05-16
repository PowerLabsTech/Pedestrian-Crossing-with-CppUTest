#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    sleep_ms(10000);
    printf("Running CppUTest...\n");

    const char* fav[] = {"trafficlight_test", "-c", "-v", "-g", "TrafficLightGroup"}; 
    int fac = sizeof(fav) / sizeof(fav[0]);
    return CommandLineTestRunner::RunAllTests(fac, fav);
}