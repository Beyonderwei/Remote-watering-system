#include <string.h>
#include "simplelink.h"

// driverlib includes
#include "hw_types.h"

// common interface includes
#include "uart_if.h"
#include "common.h"
#include "pinmux.h"

/*--http include--*/
#include "http.h"

/*--wlan--*/
#include "wlan.h"

/*--pump--*/
#include "pump.h"

/*--sys--*/
#include "sys.h"

/*--flowerStatus--*/
#include "flower_status.h"

/*--dataHandler--*/
#include "flowerdata.h"


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
    initFlowerDataStruct();

    /*-----------------------------------网页配置测试路由器信息 Start----------------------------*/
    //当STA模式时直接连接已经配置好的路由器
    // ①. Read Device Mode Configuration
    ReadDeviceConfiguration();
    printf("ReadDeviceConfiguration \r\n");

    // ②. Connect to Network
    lRetVal = ConnectToNetwork();
    printf("ConnectToNetwork \r\n");
    /*------------------------------------网页配置测试路由器信息 End-----------------------------*/

    /*--@TODO 将下面过程通过定时器触发--*/
    while (1)
    {
        /*-------------------连接服务器：Start-----------------------*/
        start:

        lRetVal = ConnectToHTTPServer(&httpClient);
        if (lRetVal < 0)
        {
            printf("connect error !!!\n");
            goto start;
            //LOOP_FOREVER();
        }
        /*---------------------连接服务器：End-----------------------*/

        updateBulkFromServer(httpClient);    //从服务器获取浇水量

        flowerStatusUpdate();    //读取传感器 更新花卉状态数据

        WaterTheFlowers();  //执行浇水命令，执行后将所有的bulk 置为0

        updateStatusToServer(httpClient);   //上传花卉状态数据到服务器

        HTTPCli_disconnect(&httpClient);    //关闭连接

        UtilsDelay(80000000);

    }

}

