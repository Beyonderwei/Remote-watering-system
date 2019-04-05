/*
 * flowerdata.c
 *
 *  Created on: 2019年4月1日
 *      Author: Beyon
 */

#include "flowerdata.h"

char g_buff[200] = { 0 };

/*--四盆花的状态数据--*/
FLOWER_DATA flower1;
FLOWER_DATA flower2;
FLOWER_DATA flower3;
FLOWER_DATA flower4;

/**
 * Function to update flower's bulk
 * 注:根据get到的数据来更新每一个花卉的浇水量到其结构体
 *  \param  moniter_id  监测端口的id 1~4
 *          bulk  与monitor_id 对应的浇水量
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
        break;  //更新失败
    }
}

/**
 * Function to get flower's bulk
 *  \param  moniter_id  监测端口的字符串指针
 *          httpClient  连接HTTP服务时的结构体
 *  \return 用户的浇水量
 */
void updateBulkFromServer(HTTPCli_Struct httpClient)
{
    long lRetVal = -1;

    UART_PRINT("\n\r");
    UART_PRINT("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient);  //原本为&httpClient
    if (lRetVal < 0)
    {
        UART_PRINT("HTTP Post Get failed.\n\r");
    }
    UART_PRINT("HTTP Get End:\n\r");
    UART_PRINT("\n\r");
    /*--根据得到的json数据进行解析 Start--*/

    printf("g_buff:%s\n", g_buff);

    //printf("size:%d\n",strlen(g_buff));

    /*--解析json--*/
    {
        cJSON *root = NULL, *arr = NULL, *json = NULL, *ret = NULL; //定义三个cJSON结构体指针
        int size = 0, cnt = 0;    //用于存储数组大小
        int monitor_id, bulk;

        root = cJSON_Parse(g_buff);    //将cJSON字符串转换为cJSON结构体指针
        arr = cJSON_GetObjectItem(root, "flowers"); //在root结构体中查找"flowers" 得到 json 数组
        size = cJSON_GetArraySize(arr);    //此时size值为4
        for (cnt = 0; cnt < size; cnt++)
        {
            json = cJSON_GetArrayItem(arr, cnt);    //获取数组第cnt个成员
            ret = cJSON_GetObjectItem(json, "monitor_id"); //在josn结构体中查找"monitor_id"
            monitor_id = ret->valueint;   //得到monitor_id

            ret = cJSON_GetObjectItem(json, "SUM(bulk)");   //在josn结构体中查找"bulk"
            bulk = ret->valueint;     //得到浇水量

            /*--根据monitor_id 去更新 bulk--*/
            updateBulk(monitor_id, bulk);
        }
        cJSON_Delete(root); //释放cJSON结构体  注意，一定要释放，不然post时会因此产生错误

    }

    // HTTPCli_disconnect(&httpClient);  //后面还要post数据，所以不能关，要到post中关
    memset(g_buff, 0, strlen(g_buff));
    UtilsDelay(400000);  //@TODO
}

char *outData;
char flowerStatusData[200] = { 0 }; //数组长度应该是 strlen 得到的字符串长度加一   这个值根据上传的数据量经调试打印得到
/**
 * Function to post flower status
 * 注意：在这之前要清除浇水量，并更新湿度光照强度数据。
 *  \param  httpClient  连接HTTP服务时的结构体
 *  \return none
 */
static void postFlowerStatus(HTTPCli_Struct httpClient, FLOWER_DATA flower_data)
{
    long lRetVal = -1;
    //创建一个cJSON结构体指针并分配空间，然后赋值给root
    cJSON *root = cJSON_CreateObject();

    //在root结构体中创建一个健为"key",值为" value" 的键值对。
    cJSON_AddNumberToObject(root, "monitorID", flower_data.monitor_id);
    cJSON_AddNumberToObject(root, "co2", flower_data.co2);
    cJSON_AddNumberToObject(root, "temperature", flower_data.temperature);
    cJSON_AddNumberToObject(root, "humidity", flower_data.humidity);
    cJSON_AddNumberToObject(root, "light", flower_data.light);

    /*--得到无格式形式的json字符串，即输出无回车和空格分离的键值对--*/
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

    /*--释放  相关内存--*/
    free(outData);  //释放malloc分配的空间
    cJSON_Delete(root);  //释放cJSON结构体指针

    memset(flowerStatusData, 0, strlen(flowerStatusData));

    UtilsDelay(400000);
}

/**
 * Function to update flower's status
 * 注:更新花卉状态数据到服务器
 *  \param  httpClient  连接HTTP服务时的结构体
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
 * 注:初始化结构体
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
