/*
 * flowerdata.h
 *
 *  Created on: 2019��4��1��
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
    int monitor_id;     //���˿��ַ���ID  ��ҪΪÿ���˿ڳ�ʼ��
    float co2;    //�����
    float temperature;  //�¶�
    float humidity;     //��ǿ(��λLUX)
    int bulk;   //��ˮ��
    int light;  //����ǿ��
} FLOWER_DATA;
static void updateBulk(int monitor_id, int bulk);
static void postFlowerStatus(HTTPCli_Struct httpClient,
                             FLOWER_DATA flower_data);

void updateBulkFromServer(HTTPCli_Struct httpClient);
void updateStatusToServer(HTTPCli_Struct httpClient);
void initFlowerDataStruct(void);

#endif /* DATAHANDLER_FLOWERDATA_H_ */
