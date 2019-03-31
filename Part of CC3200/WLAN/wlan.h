/*
 * wlan.h
 *
 *  Created on: 2019年3月31日
 *      Author: Beyon
 */

#ifndef WLAN_WLAN_H_
#define WLAN_WLAN_H_
#include <stdio.h>

#include "simplelink.h"

// common interface includes
#include "uart_if.h"
#include "common.h"
#include "gpio_if.h"

// driverlib includes
#include "utils.h"

/*--smartconfig 用于网页配置--*/
#include "smartconfig.h"

/**
 * 直接连接wlan
 */
void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent);
void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent);
void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pHttpEvent,
                                  SlHttpServerResponse_t *pHttpResponse);
void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent);
void SimpleLinkSockEventHandler(SlSockEvent_t *pSock);
void InitializeAppVariables();

long ConfigureSimpleLinkToDefaultState();
long WlanConnect();


/**
 * 通过网页配置连接wlan
 */
int ConfigureMode(int iMode);
void ReadDeviceConfiguration();
long ConnectToNetwork();

#endif /* WLAN_WLAN_H_ */
