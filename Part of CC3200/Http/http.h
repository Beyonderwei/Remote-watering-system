/*
 * http.h
 *
 *  Created on: 2019年3月31日
 *      Author: Beyon
 */

#ifndef HTTP_HTTP_H_
#define HTTP_HTTP_H_

// HTTP Client lib
#include <http/client/httpcli.h>
#include <http/client/common.h>

// common interface includes
#include "uart_if.h"
#include "common.h"

// JSON Parser
#include "jsmn.h"

#define APPLICATION_VERSION "1.1.1"
#define APP_NAME            "HTTP Client"

#define POST_REQUEST_URI    "/cc3200Post"         //请求方式  即发送什么样的请求
/*--Post过去的数据--*/
#define POST_DATA       "{\n\"name\":\"xyz\",\n\"address\":\n{\n\"plot#\":12,\n\"street\":\"abc\",\n\"city\":\"ijk\"\n},\n\"age\":30\n}"

#define DELETE_REQUEST_URI  "/delete"

#define PUT_REQUEST_URI     "/put"
#define PUT_DATA            "PUT request."

#define GET_REQUEST_URI     "/cc3200Query"      //请求方式 即发送什么样的请求  请求参数为monitor_id

/*--HOST_NAME HTTP服务器的IP地址或者域名--*/
#define HOST_NAME           "192.168.1.102" //"<host name>" //先在内网测试
/*--HTTP服务器的默认端口是80，这种情况下端口号可以省略。如果使用了别的端口，必须指明，例如tomcat的默认端口是8080 http://localhost:8080/--*/
#define HOST_PORT           8080

#define PROXY_IP            <proxy_ip>
#define PROXY_PORT          <proxy_port>

#define READ_SIZE           1450
#define MAX_BUFF_SIZE       300     //1460

// Application specific status/error codes
typedef enum
{
    /* Choosing this number to avoid overlap with host-driver's error codes */
    DEVICE_NOT_IN_STATION_MODE = -0x7D0,
    DEVICE_START_FAILED = DEVICE_NOT_IN_STATION_MODE - 1,
    INVALID_HEX_STRING = DEVICE_START_FAILED - 1,
    TCP_RECV_ERROR = INVALID_HEX_STRING - 1,
    TCP_SEND_ERROR = TCP_RECV_ERROR - 1,
    FILE_NOT_FOUND_ERROR = TCP_SEND_ERROR - 1,
    INVALID_SERVER_RESPONSE = FILE_NOT_FOUND_ERROR - 1,
    FORMAT_NOT_SUPPORTED = INVALID_SERVER_RESPONSE - 1,
    FILE_OPEN_FAILED = FORMAT_NOT_SUPPORTED - 1,
    FILE_WRITE_ERROR = FILE_OPEN_FAILED - 1,
    INVALID_FILE = FILE_WRITE_ERROR - 1,
    SERVER_CONNECTION_FAILED = INVALID_FILE - 1,
    GET_HOST_IP_FAILED = SERVER_CONNECTION_FAILED - 1,

    STATUS_CODE_MAX = -0xBB8
} e_AppStatusCodes;

int FlushHTTPResponse(HTTPCli_Handle httpClient);
int ParseJSONData(char *ptr);
int readResponse(HTTPCli_Handle httpClient);
int HTTPPostMethod(HTTPCli_Handle httpClient);
int HTTPDeleteMethod(HTTPCli_Handle httpClient);
int HTTPPutMethod(HTTPCli_Handle httpClient);
int HTTPGetMethod(HTTPCli_Handle httpClient);
int ConnectToHTTPServer(HTTPCli_Handle httpClient);

#endif /* HTTP_HTTP_H_ */
