#include <stdio.h>
#include "pico/stdlib.h"
#include "utility.h"

#define INTERFACE_SOCKET 0
#define INTERFACE_PORT 5000

int main()
{
    stdio_init_all();
    led_setup();
    tcp_setup();

    while (true)
    {
        if (tcp_handler(INTERFACE_SOCKET, INTERFACE_PORT) < 0)
        {
            led_error();
        }
    }
}
