#ifndef UTILITY_H
#define UTILITY_H

#include "wizchip_conf.h"

#define LED_PIN 25

static wiz_NetInfo g_net_info =
{
    .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
    .ip = {192, 168, 88, 100},                   // IP address
    .sn = {255, 255, 255, 0},                    // Subnet Mask
    .gw = {192, 168, 88, 1},                     // Gateway
    .dns = {8, 8, 8, 8},                         // DNS server
    .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};

#define SOCK_BUF_LENGTH (1024 * 2)
static uint8_t socketBuffer[SOCK_BUF_LENGTH];

void led_setup();
void led(int state);
void led_error();

void tcp_setup();
int32_t tcp_handler(uint8_t sn, uint16_t port);

#endif