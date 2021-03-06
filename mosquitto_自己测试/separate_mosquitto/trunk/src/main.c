#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "tbtools/topsdk.h"
#include "common/json.h"
#include "log/zlog.h"
#include "mqtt/mqtt_broker.h"

char* url = "http://gw.api.taobao.com/router/rest";
char* appkey = "23383927";
char* appsecret = "50f85a16bd93572f2708a1e51b4a3303";
char* sessionKey = "6101729e1653a9cff668238cdbdfa86ef2d4513294ef5dd2896101966";

typedef struct stMessage
{
    char *rec_num;
    char *sms_param;
}STMESSAGE,*PSTMESSAGE;

#if 1
/*********************************************************
功能描述：阿里聚石塔短信验证码发送测试程序
输入参数：无
输出参数：无
返回值：0
修改日期：20160824
作者：Loya
*/
void testMessageSend(PSTMESSAGE ptr){
    pTopRequest pRequest = alloc_top_request();
    pTopResponse pResponse = NULL;
    pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
    set_api_name(pRequest,"alibaba.aliqin.ta.sms.num.send");
    add_param(pRequest,"extend","123456");
    add_param(pRequest,"sms_type","normal");
    add_param(pRequest,"sms_free_sign_name","浩思智慧");
    add_param(pRequest,"sms_param",ptr->sms_param);
    add_param(pRequest,"rec_num",ptr->rec_num);
    add_param(pRequest,"sms_template_code","SMS_12441119");
    add_param(pRequest,"extend_code","1234");
    add_param(pRequest,"extend_name","1234");
    pResponse = top_execute(pClient,pRequest,NULL);
    printf("ret code:%d\n",pResponse->code);
    if(pResponse->code == 0){
        pTopResponseIterator ite = init_response_iterator(pResponse);
        pResultItem pResultItem = alloc_result_item();
        while(parseNext(ite, pResultItem) == 0){
            printf("%s:%s\n",pResultItem->key,pResultItem->value);
        }
        destroy_response_iterator(ite);
        destroy_result_item(pResultItem);
    }
    destroy_top_request(pRequest);
    destroy_top_response(pResponse);
    destroy_taobao_client(pClient);
}

/*********************************************************
功能描述：获取阿里服务器时间测试函数
输入参数：无
输出参数：无
返回值：0
修改日期：20160824
作者：Loya
*/
void testHttps(){
    
    pTopRequest pRequest = alloc_top_request();
    pTopResponse pResponse = NULL;
    pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
    
    set_retry_times(3);
    set_retry_sleep_times(100);
    
    set_api_name(pRequest,"taobao.time.get");
    pResponse = top_execute(pClient,pRequest,NULL);
    
    printf("ret code:%d\n",pResponse->code);
    if(pResponse->code == 0){
        pTopResponseIterator ite = init_response_iterator(pResponse);
        pResultItem pResultItem = alloc_result_item();
        while(parseNext(ite, pResultItem) == 0){
            printf("%s:%s\n",pResultItem->key,pResultItem->value);
        }
        destroy_response_iterator(ite);
        destroy_result_item(pResultItem);
    }else{
         printf("Error Msg:%s\n",pResponse->msg);
         printf("Error Sub Msg:%s\n",pResponse->subMsg);
    }

    destroy_top_request(pRequest);
    destroy_top_response(pResponse);
    destroy_taobao_client(pClient);
}

/*********************************************************
功能描述：向设备发送数据
输入参数：无
输出参数：无
返回值：0
修改日期：20160824
作者：Loya
*/
void testTrans(char *res)
{
    pTopRequest pRequest = alloc_top_request();
    pTopResponse pResponse = NULL;
    pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
    set_api_name(pRequest,"yunos.yoc.router.action");
    add_param(pRequest,"action",res);
    pResponse = top_execute(pClient,pRequest,NULL);
    printf("ret code:%d\n",pResponse->code);
    if(pResponse->code == 0){
        pTopResponseIterator ite = init_response_iterator(pResponse);
        pResultItem pResultItem = alloc_result_item();
        while(parseNext(ite, pResultItem) == 0){
            printf("%s:%s\n",pResultItem->key,pResultItem->value);
        }
        destroy_response_iterator(ite);
        destroy_result_item(pResultItem);
    }
    destroy_top_request(pRequest);
    destroy_top_response(pResponse);
    destroy_taobao_client(pClient);
}
#endif
/*********************************************************
功能描述：程序入口主函数
输入参数：无
输出参数：无
返回值：0
修改日期：20160824
作者：Loya
*/
int main(){
    char randomNum[6];
    STMESSAGE sendMSG;
    char *cmdSend;
    char ID2[18];
    char name[20];
    char getName;
    char date[100];
/*
    sendMSG.rec_num = "18600260684";
    generatNum(randomNum, 6);
    printf("randomNum is %s\n",randomNum);

    cJSON *root;
    root = cJSON_CreateObject();  
    cJSON_AddItemToObject(root, "number", cJSON_CreateString(randomNum));
    sendMSG.sms_param = cJSON_Print(root);
    printf("%s\n",sendMSG.sms_param);
//  testMessageSend(&sendMSG);

    int rc;
	zlog_category_t *zc;

	rc = zlog_init("/mnt/hgfs/share/sdk-cloudStack/src/config/cslog.conf");
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	zlog_info(zc, "hello, cstack");

	zlog_fini();
*/
    printf("***************************************************\n");
    printf("            浩思智慧XGO产品测试程序\n");
    printf("                  海豚实验室\n");
    printf("***************************************************\n");
	int broker_argc = 1;
	char *broker_argv[1] = {"mosquitto"};

	broker(broker_argc,broker_argv);

#if 0
    printf("请输入17位设备id2...\n");
    gets(ID2);
LOOP1:
    printf("请选择事件...\n");
    printf("1 setcustomaction(语音事件)\n");
    printf("2 nodeDataEvent(数据事件)\n");
    printf("q EXIT(退出)\n");
    scanf("%s",&getName);
    getchar();
    switch(getName)
    {
        case('1'): strcpy(name, "setcustomaction"); break;
        case('2'): strcpy(name, "nodeDataEvent"); break;
        case('q'): return 0;
        default:printf("请输入正确的格式!\n");goto LOOP1;break;
    }
    printf("请输入下发的数据...\n");
    gets(date);

    cJSON *cmdJson;
    cJSON *sonCmdJson;
    char *sonCmdSend;
    cmdJson = cJSON_CreateObject();
    cJSON_AddItemToObject(cmdJson, "id2", cJSON_CreateString(ID2));
    cJSON_AddItemToObject(cmdJson, "service_id", cJSON_CreateString("HAOSI_23383927_new"));
    cJSON_AddItemToObject(cmdJson, "type", cJSON_CreateString("action"));
    cJSON_AddItemToObject(cmdJson, "name", cJSON_CreateString(name));
    sonCmdJson = cJSON_CreateObject();
    cJSON_AddItemToObject(sonCmdJson, "value", cJSON_CreateString(date));

    cJSON_AddItemToObject(cmdJson, "args", sonCmdJson);
    cmdSend = cJSON_Print(cmdJson);
    printf("%s\n",cmdSend);
    testHttps();
/*    testMessageSend(&sendMSG);*/
    testTrans(cmdSend);
    goto LOOP1;
#endif
    return 0;
}

