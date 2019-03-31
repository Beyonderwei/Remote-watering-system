#include <string.h>

// SimpleLink includes
#include "simplelink.h"

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "utils.h"
#include "interrupt.h"

// common interface includes
#include "uart_if.h"
#include "common.h"
#include "pinmux.h"

/*--cJSON hub--*/
#include "cJSON.h"

/*--ADC include--*/
#include "humidity.h"

/*--http--*/
#include "http.h"

/*--wlan--*/
#include "wlan.h"

/*--pump--*/
#include "gpio.h"
#include "pump.h"

/*--sys--*/
#include "sys.h"

// Common interface includes
#include "gpio_if.h"


//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
/*--花卉状态数据 Start--*/

char *outData;
char flowerStatusData[63]={0};  //数组长度应该是 strlen 得到的字符串长度加一   这个值根据上传的数据量经调试打印得到

int monitor_id=1;
float co2=0.038;    //体积比
float temperature=23.0;
float humidity=300;     //LUX
int bulk;

/*--花卉状态数据 End--*/

unsigned char  g_buff[MAX_BUFF_SIZE+1];
long bytesReceived = 0; // variable to store the file size




int main()
{
    long lRetVal = -1;
    HTTPCli_Struct httpClient;


    //
    // Board Initialization
    //
    BoardInit();

    //
    // Configure the pinmux settings for the peripherals exercised
    //
    PinMuxConfig();

    /*-----------添加了 PIN_58 为了判断何时切换模式，IO 口初始化过程在 PinMuxConfig 函数中-----------*/
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_0,GPIO_PIN_0);        //拉高IO口  63
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_1,GPIO_PIN_1);        //拉高IO口  64
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_2,GPIO_PIN_2);        //拉高IO口  01
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_3,GPIO_PIN_3);        //拉高IO口  02

    //
    // 初始化 pump 的IO引脚
    //
    pump_init();

    //
    //初始化 ADC 功能
    //
    adcInit();

    //
    // Configuring UART
    //
    InitTerm();

    //
    //初始化应用的变量
    //
    InitializeAppVariables();

    //
    //连接到路由器，返回值非负表示连接成功，使用网页的配置方式后，不再需要这种固定方式的连接
    //
//    lRetVal = ConnectToAP();
//    if(lRetVal < 0)
//    {
//        LOOP_FOREVER();
//    }




#if 0
/*--------------------------------------网页配置测试路由器信息 Start----------------------------*/
    // ①. Read Device Mode Configuration
    ReadDeviceConfiguration();
    printf("ReadDeviceConfiguration \r\n");

    // ②. Connect to Network
    lRetVal = ConnectToNetwork();
    printf("ConnectToNetwork \r\n");

//    while(1)
//        {
//
//        }

/*------------------------------------网页配置测试路由器信息 End-----------------------------*/
//#endif

/*--------------湿度值获取 Start--------------*/
#if 0
    while(1)
    {
        float humidity_value=adcValueGet();
        printf("humidity = %f ;\n",humidity_value);
    }
#endif
/*--------------湿度值获取 End---------------*/




while(1)
{
    /*-------------------连接服务器：Start-----------------------*/
    start:

    lRetVal = ConnectToHTTPServer(&httpClient);
            if(lRetVal < 0)
            {
                printf("connect error !!!\n");
                goto start;
                //LOOP_FOREVER();
            }
    /*-------------------连接服务器：End-----------------------*/

    /*---------------------GET Start--------------------*/
                UART_PRINT("\n\r");
                UART_PRINT("HTTP Get Begin:\n\r");
                lRetVal = HTTPGetMethod(&httpClient);
                if(lRetVal < 0)
                {
                    UART_PRINT("HTTP Post Get failed.\n\r");
                }
                UART_PRINT("HTTP Get End:\n\r");
                UART_PRINT("\n\r");
                /*--根据得到的json数据进行解析 Start--*/

                printf("g_buff:%s\n",g_buff);

                //printf("size:%d\n",strlen(g_buff));


                /*--解析json--*/
                {
                cJSON *root;
                cJSON *ret;
                //char *str = "{\"key\":\"value\"}";// 花括号里面的(")前面必须加()，将其转换为转义字符，以免和c语言字符串冲突
                root = cJSON_Parse(g_buff);    //将cJSON字符串转换为cJSON结构体指针
                ret = cJSON_GetObjectItem(root, "bulk");    //在root结构体中查找"key"这个键(一个字符串),成功返回一个cJSON结构体，失败返回NULL。
                //printf("%d\n",ret -> valueint);    //打印出来的结果是value
                bulk=ret->valueint;  /*--根据得到的json数据进行解析End--*/
                cJSON_Delete(ret);    //释放cJSON结构体指针
                cJSON_Delete(root);    //释放cJSON结构体指针
                }

                printf("bulk : %d\n",bulk);

                switch(bulk)
                {
                    case 0:break;
                    case 50:break;
                    case 100:pump_open();MAP_UtilsDelay(20000000);pump_close();break;
                    case 150:break;
                    case 200:pump_open();MAP_UtilsDelay(400000000);pump_close();break;
                    default : break;
                }


                HTTPCli_disconnect(&httpClient);
                MAP_UtilsDelay(120000000);

/*---------------GET End------------------*/
//#if 0

    //经测试可用     post数据到服务器
    /*--根据测得的数据信息，post数据到服务器，从而更新花卉的状态数据--*/

            //创建一个cJSON结构体指针并分配空间，然后赋值给root
            cJSON *root = cJSON_CreateObject();

            //在root结构体中创建一个健为"key",值为" value" 的键值对。
            cJSON_AddNumberToObject(root,"monitorID",monitor_id);
            cJSON_AddNumberToObject(root,"co2",co2);
            cJSON_AddNumberToObject(root,"temperature",temperature);
            cJSON_AddNumberToObject(root,"humidity",humidity);

            /*--得到无格式形式的json字符串，即输出无回车和空格分离的键值对--*/
            outData = cJSON_PrintUnformatted(root);
            {
                int lenth=0;
                lenth=strlen(outData);
                printf("%d\n", lenth);
            }
            strncpy(flowerStatusData, outData, strlen(outData));

    UART_PRINT("\n\r");
    UART_PRINT("HTTP Post Begin:\n\r");
    lRetVal = HTTPPostMethod(&httpClient);
    if(lRetVal < 0)
    {
    	UART_PRINT("HTTP Post failed.\n\r");
    }
    UART_PRINT("HTTP Post End:\n\r");
    //printf("%s\n", g_buff);

    /*--释放  相关内存--*/
        free(outData);//释放malloc分配的空间
        cJSON_Delete(root);//释放cJSON结构体指针

        MAP_UtilsDelay(120000000);

        /*----------post测试结束，可以用-----------*/

//#endif

#if 0

    UART_PRINT("\n\r");
    UART_PRINT("HTTP Delete Begin:\n\r");
    lRetVal = HTTPDeleteMethod(&httpClient);

    if(lRetVal < 0)
    {
    	UART_PRINT("HTTP Delete failed.\n\r");
    }
    UART_PRINT("HTTP Delete End:\n\r");


    UART_PRINT("\n\r");
    UART_PRINT("HTTP Put Begin:\n\r");
    lRetVal = HTTPPutMethod(&httpClient);
    if(lRetVal < 0)
    {
    	UART_PRINT("HTTP Put failed.\n\r");
    }
    UART_PRINT("HTTP Put End:\n\r");




#endif

    }
#endif

}

