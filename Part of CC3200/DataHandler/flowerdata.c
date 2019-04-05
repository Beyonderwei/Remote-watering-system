/*
 * flowerdata.c
 *
 *  Created on: 2019��4��1��
 *      Author: Beyon
 */

#include "flowerdata.h"

char g_buff[200] = { 0 };

/*--���軨��״̬����--*/
FLOWER_DATA flower1;
FLOWER_DATA flower2;
FLOWER_DATA flower3;
FLOWER_DATA flower4;

/**
 * Function to update flower's bulk
 * ע:����get��������������ÿһ�����ܵĽ�ˮ������ṹ��
 *  \param  moniter_id  ���˿ڵ�id 1~4
 *          bulk  ��monitor_id ��Ӧ�Ľ�ˮ��
 *  \return none
 */
static void updateBulk(int monitor_id, int bulk)
{
    switch (monitor_id)
    {
    case 1:
        flower1.bulk = bulk;
        break;
    case 2:
        flower2.bulk = bulk;
        break;
    case 3:
        flower3.bulk = bulk;
        break;
    case 4:
        flower4.bulk = bulk;
        break;
    default:
        break;  //����ʧ��
    }
}

/**
 * Function to get flower's bulk
 *  \param  moniter_id  ���˿ڵ��ַ���ָ��
 *          httpClient  ����HTTP����ʱ�Ľṹ��
 *  \return �û��Ľ�ˮ��
 */
void updateBulkFromServer(HTTPCli_Struct httpClient)
{
    long lRetVal = -1;

    UART_PRINT("\n\r");
    UART_PRINT("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient);  //ԭ��Ϊ&httpClient
    if (lRetVal < 0)
    {
        UART_PRINT("HTTP Post Get failed.\n\r");
    }
    UART_PRINT("HTTP Get End:\n\r");
    UART_PRINT("\n\r");
    /*--���ݵõ���json���ݽ��н��� Start--*/

    printf("g_buff:%s\n", g_buff);

    //printf("size:%d\n",strlen(g_buff));

    /*--����json--*/
    {
        cJSON *root = NULL, *arr = NULL, *json = NULL, *ret = NULL; //��������cJSON�ṹ��ָ��
        int size = 0, cnt = 0;    //���ڴ洢�����С
        int monitor_id, bulk;

        root = cJSON_Parse(g_buff);    //��cJSON�ַ���ת��ΪcJSON�ṹ��ָ��
        arr = cJSON_GetObjectItem(root, "flowers"); //��root�ṹ���в���"flowers" �õ� json ����
        size = cJSON_GetArraySize(arr);    //��ʱsizeֵΪ4
        for (cnt = 0; cnt < size; cnt++)
        {
            json = cJSON_GetArrayItem(arr, cnt);    //��ȡ�����cnt����Ա
            ret = cJSON_GetObjectItem(json, "monitor_id"); //��josn�ṹ���в���"monitor_id"
            monitor_id = ret->valueint;   //�õ�monitor_id

            ret = cJSON_GetObjectItem(json, "SUM(bulk)");   //��josn�ṹ���в���"bulk"
            bulk = ret->valueint;     //�õ���ˮ��

            /*--����monitor_id ȥ���� bulk--*/
            updateBulk(monitor_id, bulk);
        }
        cJSON_Delete(root); //�ͷ�cJSON�ṹ��  ע�⣬һ��Ҫ�ͷţ���Ȼpostʱ����˲�������

    }

    // HTTPCli_disconnect(&httpClient);  //���滹Ҫpost���ݣ����Բ��ܹأ�Ҫ��post�й�
    memset(g_buff, 0, strlen(g_buff));
    UtilsDelay(400000);  //@TODO
}

char *outData;
char flowerStatusData[200] = { 0 }; //���鳤��Ӧ���� strlen �õ����ַ������ȼ�һ   ���ֵ�����ϴ��������������Դ�ӡ�õ�
/**
 * Function to post flower status
 * ע�⣺����֮ǰҪ�����ˮ����������ʪ�ȹ���ǿ�����ݡ�
 *  \param  httpClient  ����HTTP����ʱ�Ľṹ��
 *  \return none
 */
static void postFlowerStatus(HTTPCli_Struct httpClient, FLOWER_DATA flower_data)
{
    long lRetVal = -1;
    //����һ��cJSON�ṹ��ָ�벢����ռ䣬Ȼ��ֵ��root
    cJSON *root = cJSON_CreateObject();

    //��root�ṹ���д���һ����Ϊ"key",ֵΪ" value" �ļ�ֵ�ԡ�
    cJSON_AddNumberToObject(root, "monitorID", flower_data.monitor_id);
    cJSON_AddNumberToObject(root, "co2", flower_data.co2);
    cJSON_AddNumberToObject(root, "temperature", flower_data.temperature);
    cJSON_AddNumberToObject(root, "humidity", flower_data.humidity);
    cJSON_AddNumberToObject(root, "light", flower_data.light);

    /*--�õ��޸�ʽ��ʽ��json�ַ�����������޻س��Ϳո����ļ�ֵ��--*/
    outData = cJSON_PrintUnformatted(root);
    {
        int lenth = 0;
        lenth = strlen(outData);
        printf("outData:%d\n", lenth);
    }
    strncpy(flowerStatusData, outData, strlen(outData));

    UART_PRINT("\n\r");
    UART_PRINT("HTTP Post Begin:\n\r");
    lRetVal = HTTPPostMethod(&httpClient);
    if (lRetVal < 0)
    {
        UART_PRINT("HTTP Post failed.\n\r");
    }
    UART_PRINT("HTTP Post End:\n\r");
    //printf("%s\n", g_buff);

    /*--�ͷ�  ����ڴ�--*/
    free(outData);  //�ͷ�malloc����Ŀռ�
    cJSON_Delete(root);  //�ͷ�cJSON�ṹ��ָ��

    memset(flowerStatusData, 0, strlen(flowerStatusData));

    UtilsDelay(400000);
}

/**
 * Function to update flower's status
 * ע:���»���״̬���ݵ�������
 *  \param  httpClient  ����HTTP����ʱ�Ľṹ��
 *  \return none
 */
void updateStatusToServer(HTTPCli_Struct httpClient)
{
    postFlowerStatus(httpClient, flower1);
    postFlowerStatus(httpClient, flower2);
    postFlowerStatus(httpClient, flower3);
    postFlowerStatus(httpClient, flower4);
}

/**
 * Function to Initlize flower's status
 * ע:��ʼ���ṹ��
 *  \param  none
 *  \return none
 */
void initFlowerDataStruct(void)
{
    flower1.monitor_id = 1;
    flower1.bulk = 0.01;
    flower1.co2 = 0.01;
    flower1.light = 0.01;
    flower1.temperature = 0.01;

    flower2.monitor_id = 2;
    flower2.bulk = 0.01;
    flower2.co2 = 0.01;
    flower2.light = 0.01;
    flower2.temperature = 0.01;

    flower3.monitor_id = 3;
    flower3.bulk = 0.01;
    flower3.co2 = 0.01;
    flower3.light = 0.01;
    flower3.temperature = 0.01;

    flower4.monitor_id = 4;
    flower4.bulk = 0.01;
    flower4.co2 = 0.01;
    flower4.light = 0.01;
    flower4.temperature = 0.01;
}
