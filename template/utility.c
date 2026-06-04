#include "utility.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "w5x00_spi.h"
#include "socket.h"

void led_setup()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led(int state)
{
    if (state) {
        gpio_put(LED_PIN, 1);
    } else {
        gpio_put(LED_PIN, 0);
    }
}

void led_error()
{
    while (1) 
    {
        led(1);
        sleep_ms(100);
        led(0);
        sleep_ms(100);
    }
}

void tcp_setup()
{
    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();
    wizchip_initialize();
    wizchip_check();

    network_initialize(g_net_info);
}

int32_t tcp_handler(uint8_t sn, uint16_t port)
{
    int32_t ret;
    uint16_t size = 0, sentsize=0;
    uint8_t destip[4];
    uint16_t destport;

    switch(getSn_SR(sn))
    {
        case SOCK_ESTABLISHED:
            if(getSn_IR(sn) & Sn_IR_CON)
            {
                getSn_DIPR(sn, destip);                                                                                 // Debug
			    destport = getSn_DPORT(sn);                                                                             // Debug
			    printf("Socket %d: Connected (%d.%d.%d.%d:%d)\r\n",sn, destip[0], destip[1], destip[2], destip[3], destport);   // Debug
                setSn_IR(sn,Sn_IR_CON);
            }
            if((size = getSn_RX_RSR(sn)) > 0) // Don't need to check SOCKERR_BUSY because it doesn't not occur.
            {
                if(size > SOCK_BUF_LENGTH) size = SOCK_BUF_LENGTH;
                ret = recv(sn, socketBuffer, size);
                if(ret <= 0) return ret;      // check SOCKERR_BUSY & SOCKERR_XXX. For showing the occurrence of SOCKERR_BUSY.
                size = (uint16_t)ret;

                // Can now use/parse the data in "socketBuffer" which has length of "size"
                
                // Example sending:
                //socketBuffer[0] = 0;
                //socketBuffer[1] = 1;
                //socketBuffer[2] = 2;
                //size = 3;
                //ret = send(sn, socketBuffer, size);
                //if(ret < 0)
                //{
                //    close(sn);
                //    return ret;
                //}
            }
            break;
        case SOCK_CLOSE_WAIT:
            if((ret = disconnect(sn)) != SOCK_OK) return ret;
            printf("Socket %d: Closed\r\n", sn);
            break;
        case SOCK_INIT:
            if((ret = listen(sn)) != SOCK_OK) return ret;
            printf("Socket %d: Listening\r\n", sn);
            break;
        case SOCK_CLOSED:
            if((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn) return ret;
            printf("Socket %d: Opened (TCP port %d)\r\n", sn, port);
            break;
        default:
            break;
    }
    return 1;
}