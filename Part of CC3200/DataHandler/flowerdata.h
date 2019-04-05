/*
 * flowerdata.h
 *
 *  Created on: 2019年4月1日
 *      Author: Beyon
 */

#ifndef DATAHANDLER_FLOWERDATA_H_
#define DATAHANDLER_FLOWERDATA_H_

// SimpleLink includes
#include "simplelink.h"

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "utils.h"

// common interface includes
#include "uart_if.h"

/*--cJSON hub--*/
#include "cJSON.h"

/*--http--*/
#include "http.h"

typedef struct
{
    int monitor_id;     //监测端口字符串ID  需要为每个端口初始化
    float co2;    //体积比
    float temperature;  //温度
    float humidity;     //光强(单位LUX)
    int bulk;   //浇水量
    int light;  //光照强度
} FLOWER_DATA;
static void updateBulk(int monitor_id, int bulk);
static void postFlowerStatus(HTTPCli_Struct httpClient,
                             FLOWER_DATA flower_data);

void updateBulkFromServer(HTTPCli_Struct httpClient);
void updateStatusToServer(HTTPCli_Struct httpClient);
void initFlowerDataStruct(void);

#endif /* DATAHANDLER_FLOWERDATA_H_ */
