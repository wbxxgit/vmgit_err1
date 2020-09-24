#ifndef _ZJ_TYPE_H_
#define _ZJ_TYPE_H_
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZJ_EXPORTS
#define _ZJ_API  __declspec(dllexport)
#else
#define _ZJ_API
#endif

#define ZJ_HANDLE   void*


typedef enum enum_zj_os_type
{
    EN_ZJ_OS_TYPE_LINUX     = 1,
    EN_ZJ_OS_TYPE_IOS       = 2,
    EN_ZJ_OS_TYPE_ANDRIOD   = 3,
    EN_ZJ_OS_TYPE_ANDRIODTV = 4,
    EN_ZJ_OS_TYPE_WINDOWS   = 5,
    EN_ZJ_OS_TYPE_RTOS      = 6
}EN_ZJ_OS_TYPE;

/**
  * 设备初始化状态。分别为：初始化、配置加载、网络初始化、注册、登录、绑定、运行。
**********************************************/
typedef enum enum_ZJ_SERVER_STATUS
{
    EN_ZJ_SERVER_STATUS_INIT     = 0,
    EN_ZJ_SERVER_STATUS_GETADDR,
    EN_ZJ_SERVER_STATUS_CONNECT,        //网络连接完成
    EN_ZJ_SERVER_STATUS_REGIST,         //设备注册
    EN_ZJ_SERVER_STATUS_WAITBIND,       //设备等待绑定
    EN_ZJ_SERVER_STATUS_PROCESS,        //设备完成上线
    EN_ZJ_SERVER_STATUS_EXITGROUP       //设备解绑退组
}EN_ZJ_SERVER_STATUS;

/*
 * 设备内存富余级别
 */
typedef enum enum_ZJ_DEVICE_MEM_ABILITY
{
   EN_ZJ_DEVICE_MEM_ABILITY_RICH = 0, //内存余量可以存储3个以上完整GOP
   EN_ZJ_DEVICE_MEM_ABILITY_MID  = 1, //内存余量适中，可以存储1个以上完整GOP
   EN_ZJ_DEVICE_MEM_ABILITY_POOR = 2  //内存余量不足，只可以存在一个完整帧
}EN_ZJ_DEVICE_MEM_ABILITY;

typedef enum enum_ZJ_CFG_ITEM
{
    EN_ZJ_CFG_ITEM_ALL            = 0X00,
    EN_ZJ_CFG_ITEM_DEVICE         = 0X01,
    EN_ZJ_CFG_ITEM_CAMERA         = 0X02,
    EN_ZJ_CFG_ITEM_PTZ            = 0X04,
    EN_ZJ_CFG_ITEM_INIOT          = 0X08,
    EN_ZJ_CFG_ITEM_IOTHUB         = 0X10,
    EN_ZJ_CFG_ITEM_TIMEPOLICY     = 0X20,
    EN_ZJ_CFG_ITEM_ALARMPOLICY    = 0X40,
    EN_ZJ_CFG_ITEM_SYSTEM         = 0X80,
    EN_ZJ_CFG_ITEM_SERVERSET      = 0X100,
    EN_ZJ_CFG_ITEM_SCENEPOLICY    = 0X200,

    EN_ZJ_CFG_ITEM_GROUPINF       = 0x10000
}EN_ZJ_CFG_ITEM;

/*
 * 设备升级状态。
 */
typedef enum enum_ZJ_DEVICE_UPDATE_STATUS
{
    EN_ZJ_DEVICE_UPDATE_STATUS_NOUPDATE     = 0, //不需要升级
    EN_ZJ_DEVICE_UPDATE_STATUS_NEEDUPDATE   = 1, //有新版本需要升级
    EN_ZJ_DEVICE_UPDATE_STATUS_MUSTUPDATE   = 2  //强制升级，系统版本不兼容需要强制升级
}EN_ZJ_DEVICE_UPDATE_STATUS;

// 网络类型
typedef enum enum_ZJ_NETWORK_TYPE{
    EN_ZJ_NETWORK_TYPE_NONET                = 0x00,     // 无网络
    EN_ZJ_NETWORK_TYPE_WIRED                = 0x01,     // 有线连接
    EN_ZJ_NETWORK_TYPE_WIFI                 = 0x02,     // WIFI连接
    EN_ZJ_NETWORK_TYPE_AP                   = 0x04,     // AP连接
    EN_ZJ_NETWORK_TYPE_SIM                  = 0x08,     // 移动网络
}EN_ZJ_NETWORK_TYPE;

//定义WIFI列表元素
typedef struct stru_ZJ_WIFI_INFO{
    int     iSigStrength;       //信号强度
    int     iConnectFlag;       //是否当前连接 1.是；0.不是
    char    acWifiSSID[32];     //最长31字节WiFiSSID
    int     iSecurity;          //安全性，0：无，1.WEP，2.WPA-PSK，3.WPA-PSK/WPA2-PSK，4.WPA2-PSK，5.其他
}ST_ZJ_WIFI_INFO;

// 定义当前网络详情结构
typedef struct stru_ZJ_NETWORK_INFO{
	int             iNetType;
    int             iSignalType;            // 2: 2G 3: 3G 4: 4G 
	int             iSigStrength;
    unsigned char   aucNetmask[64];        //子网掩码				
    unsigned char   aucGateway[64];         //默认网关				
	unsigned char 	aucIPAddr[64];
	unsigned char 	aucMacAddr[64];
	unsigned char 	aucWIFISSID[32];
}ST_ZJ_NETWORK_INFO;

//WIFI连接状态
typedef enum enum_ZJ_NETWORK_ERR_STATUS{
	EN_ZJ_NETWORK_ERR_STATUS_PWDERR		= 0x01, //WIFI密码错误
 	EN_ZJ_NETWORK_ERR_STATUS_NOSIGNAL	= 0x02  //信号中断
}EN_ZJ_NETWORK_ERR_STATUS;


//支持OTA升级的模式
typedef enum enum_ZJ_OTA_ABILITY{
    EN_ZJ_OTA_ABILITY_SDCARD                = 0x01,     // SD卡升级，用户将升级包拷贝到SD卡，然后将SD卡插入设备完成升级；
    EN_ZJ_OTA_ABILITY_LOCALUPDATE           = 0x02,     // 本地升级，用户与设备连接在同一个局域网，完成升级；
    EN_ZJ_OTA_ABILITY_REMOTEUPDATE          = 0x04      // 远程升级，用户与设备不在同一个局域网，完成升级；设备需要更多的空间存放升级包；
}EN_ZJ_OTA_ABILITY;

// 支持WIFI配置模式
typedef enum enum_ZJ_SETWIFI_ABILITY{
    EN_ZJ_SETWIFI_ABILITY_AP                   = 0x01,  //支持AP配网
    EN_ZJ_SETWIFI_ABILITY_SOUND                = 0x02,  //支持声波配网
    EN_ZJ_SETWIFI_ABILITY_SMARTLINK            = 0x04,  //支持SMARTLINK配网
    EN_ZJ_SETWIFI_ABILITY_QRCODE               = 0x08,  //支持二维码配网
    EN_ZJ_SETWIFI_ABILITY_WIRED                = 0x10   //支持有线配网
}EN_ZJ_SETWIFI_ABILITY;

//设备休眠唤醒能力
typedef enum enum_ZJ_AWAKE_ABILITY{
    EN_ZJ_AWAKE_ABILITY_NOTSUPPORT          = 0x00, //不支持休眠
    EN_ZJ_AWAKE_ABILITY_LOCALAWAKE          = 0x01, //支持本地唤醒
    EN_ZJ_AWAKE_ABILITY_REMOTEAWAKE         = 0x02  //支持远程唤醒
}EN_ZJ_AWAKE_ABILITY;

//声音对讲支持能力
typedef enum enum_ZJ_VOICEPLAY_ABILITY{
    EN_ZJ_VOICEPLAY_ABILITY_NOSUPPORT   = 0x00, //不支持对讲
    EN_ZJ_VOICEPLAY_ABILITY_SIMPLEX     = 0x01, //单工
    EN_ZJ_VOICEPLAY_ABILITY_DUPLEX      = 0x02 //双工
}EN_ZJ_VOICEPLAY_ABILITY;

//摄像机PTZ支持能力
typedef enum enum_ZJ_CAMERA_PTZ_ABILITY{
    EN_ZJ_CAMERA_PTZ_ABILITY_P          = 0x01,  //支持P操作
    EN_ZJ_CAMERA_PTZ_ABILITY_T          = 0x02,  //支持T操作
    EN_ZJ_CAMERA_PTZ_ABILITY_Z          = 0x04   //支持Z操作
}EN_ZJ_CAMERA_PTZ_ABILITY;

//摄像机PTZ转动
typedef enum enum_ZJ_CAMERA_PTZ_CONTROL{
    EN_ZJ_CAMERA_PTZ_CONTROL_UP         = 1,
    EN_ZJ_CAMERA_PTZ_CONTROL_DOWN       = 2,
    EN_ZJ_CAMERA_PTZ_CONTROL_LEFT       = 3,
    EN_ZJ_CAMERA_PTZ_CONTROL_RIGHT      = 4,
}EN_ZJ_CAMERA_PTZ_CONTROL;

typedef struct str_ZJ_PRESET_POINT       		//PTZ ABS MOVE
{
	int    iX;			      	//预置位x轴坐标    （底层）
	int    iY;			      	//预置位y轴坐标    （底层）
}ST_ZJ_PRESET_POINT;

//巡航预置点定义
typedef struct stru_ZJ_CAMERA_CRUISE_PRESET{
    int         Idx;            //预置点序号
    int         iX;             //预置点位移X
    int         iY;             //预置点位移Y
    int         iDwellTime;     //停留时间 单位 s
    int         iSpeed;         //云台转速
}ST_ZJ_CAMERA_CRUISE_PRESET;

//摄像机分辨率支持能力集
typedef enum enum_ZJ_CAMERA_RESOLUTION_ABILITY{
    EN_ZJ_CARERA_RESOLUTION_ABILITY_360P        = 0x0001, //支持640*360分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_480P        = 0x0002, //支持640*480分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_720P        = 0x0004, //支持1280*720分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_960P        = 0x0008, //支持1280*960分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_1080P       = 0x0010, //支持1920*1080分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_1200P       = 0x0020, //支持1600*1200分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_300W        = 0x0040, //支持2048*1536分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_400W        = 0x0080, //支持2500*1600分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_500W        = 0x0100, //支持2560*1920分辨率
    EN_ZJ_CARERA_RESOLUTION_ABILITY_4K          = 0x0200, //支持3840*2160分辨率 800W像素
    EN_ZJ_CARERA_RESOLUTION_ABILITY_8K          = 0x0400, //支持7680*4320分辨率 3200W像素
}EN_ZJ_CARERA_RESOLUTION_ABILITY;

//摄像机编码码率定义
typedef enum enum_ZJ_CAMERA_BITRATE_TYPE{
    EN_ZJ_CAMERA_BITRATE_TYPE_96K       = 1,
    EN_ZJ_CAMERA_BITRATE_TYPE_128K      = 2,
    EN_ZJ_CAMERA_BITRATE_TYPE_196K      = 3,
    EN_ZJ_CAMERA_BITRATE_TYPE_256K      = 4,
    EN_ZJ_CAMERA_BITRATE_TYPE_384K      = 5,
    EN_ZJ_CAMERA_BITRATE_TYPE_512K      = 6,
    EN_ZJ_CAMERA_BITRATE_TYPE_768K      = 7,
    EN_ZJ_CAMERA_BITRATE_TYPE_1024K     = 8,
    EN_ZJ_CAMERA_BITRATE_TYPE_1536K     = 9,
    EN_ZJ_CAMERA_BITRATE_TYPE_2048K     = 10,
    EN_ZJ_CAMERA_BITRATE_TYPE_2560K     = 11,
    EN_ZJ_CAMERA_BITRATE_TYPE_3072K     = 12,
    EN_ZJ_CAMERA_BITRATE_TYPE_4096K     = 13
}EN_ZJ_CAMERA_BITRATE_TYPE;

//红外灯支持能力
typedef enum enum_ZJ_CAMERA_IRLED_ABILITY{
    EN_ZJ_CAMERA_IRLED_ABILITY_NOSUPPORT        = 0x00, //不支持红外灯
    EN_ZJ_CAMERA_IRLED_ABILITY_NOCONTROL        = 0x01, //不支持红外灯开关控制，只能通过感光器自动开关控制
    EN_ZJ_CAMERA_IRCUR_ABILITY_CANCONTROL       = 0x02, //支持红外灯命令开关控制
}EN_ZJ_CAMERA_IRLED_ABILITY;

//摄像机视频编码类型
typedef enum enum_ZJ_VIDEOENC_TYPE{
    EN_ZJ_VIDEOENC_TYPE_JPEG        = 0x01, //JPEG图片编码模式
    EN_ZJ_VIDEOENC_TYPE_H264        = 0x02, //H264编码类型
    EN_ZJ_VIDEOENC_TYPE_H265        = 0x04  //H265编码类型
}EN_ZJ_VIDEOENC_TYPE;

//音频编码类型
typedef enum enum_ZJ_AUDIOENC_TYPE{
    EN_ZJ_AUDIOENC_TYPE_PCM16       = 0x01,
    EN_ZJ_AUDIOENC_TYPE_G711A       = 0x02,
    EN_ZJ_AUDIOENC_TYPE_G711U       = 0x04,
    EN_ZJ_AUDIOENC_TYPE_AAC         = 0x08,
    EN_ZJ_AUDIOENC_TYPE_MP3         = 0x10
}EN_ZJ_AUDIOENC_TYPE;

typedef enum enum_ZJ_MEDIA_TYPE{
    EN_ZJ_MEDIA_VIDEO   = 0X01,
    EN_ZJ_MEDIA_AUDIO   = 0X02,
    EN_ZJ_MEDIA_AV      = 0X03
}EN_ZJ_STREAMER_TYPE;


//镜头类型
typedef enum enum_ZJ_CAMERA_LENS_TYPE{
    EN_ZJ_CAMERA_LENS_TYPE_NORMAL       = 0x00,
    EN_ZJ_CAMERA_LENS_TYPE_360          = 0x01,
    EN_ZJ_CAMERA_LENS_TYPE_720          = 0x02
}EN_ZJ_CAMERA_LENS_TYPE;

//视频编码参数
typedef struct stru_ZJ_VIDEO_PARAM{
    unsigned int uiResolution;    //分辨率，见分辨率定义
    unsigned int uiWidth;         //分辨率  回调设置可以忽略
    unsigned int uiHeight;        //分辨率  回调设置可以忽略
    unsigned int uiEncodeType;    //编码格式
    unsigned int uiSmartEncFlag;  //0.不支持Smart编码；1.支持Smart编码
    unsigned int uiQuality;       //编码质量
    unsigned int uiBitrate;       //码率，见码率定义
    unsigned int uiFramerate;     //帧率 
    unsigned int uiFrameInterval; //I帧间隔 50帧、100帧、200帧
    unsigned int uiRateType;      // 0 CBR 1 VBR 
}ST_ZJ_VIDEO_PARAM;

// 音频参数描述
typedef struct stru_ZJ_AUDIO_PARAM{
    unsigned int uiEncodeType;    //编码格式
    unsigned int uiSampleRate;    //采样率
    unsigned int uiChannel;       //声道数
    unsigned int uiDepth;         //深度
}ST_ZJ_AUDIO_PARAM;

//广角镜头圆心半径信息描述
typedef struct str_ZJ_VIDEO_CIRCLE
{
    unsigned int uiRadius;  //半径
    double doubleAngle;    //角度
    unsigned int uiCc1x;    //圆心坐标X
    unsigned int uiCc1Y;    //圆心坐标Y
    unsigned int uiCc2x;   // 720度双目
    unsigned int uiCc2Y;   // 720度双目
}ST_ZJ_VIDEO_CIRCLE;

// 扭曲度描述 
typedef struct str_ZJ_VIDEO_DISTORTION
{
    double fx;    // 镜头光轴与图像圆心的水平偏移
    double fy;    // 镜头光轴与图像圆心的垂直偏移
    double a;     // 桶形畸变校正参数
    double b;     // 枕形畸变校正参数
    double scale; // 图像缩放因子
}ST_ZJ_VIDEO_DISTORTION;

//视频编码帧类型
typedef enum enum_ZJ_VIDEO_FRAME_TYPE{
    EN_ZJ_VIDEO_FRAME_TYPE_UNKNOW       = 0, //未知帧类型，需要去检测
    EN_ZJ_VIDEO_FRAME_TYPE_I            = 1, //I帧
    EN_ZJ_VIDEO_FRAME_TYPE_P            = 2, //P帧
}EN_ZJ_VIDEO_FRAME_TYPE;


// 图片类型定义。普通图片，中等大小图片，小图，ICON图片；
typedef enum enum_ZJ_PICTURE_TYPE{
    EN_ZJ_PICTURE_NORMAL                = 0X01,   //码流同等尺寸
    EN_ZJ_PICTURE_MIDDLE                = 0X02,   //码流缩放一倍尺寸
    EN_ZJ_PICTURE_SMALL                 = 0X04,   //320*240尺寸
    EN_ZJ_PICTURE_ICON                  = 0X08    //64*48尺寸
}EN_ZJ_PICTURE_TYPE;


//  IR模式。自动模式，红外模式，全彩模式。
typedef enum enum_ZJ_IRMODE{
    EN_ZJ_IRMODE_AUTO               = 0,  //自动模式
    EN_ZJ_IRMODE_IR                 = 1,  //红外模式
    EN_ZJ_IRMODE_FULLCOLOR          = 2   //全彩模式
}EN_ZJ_IRMODE;

// 关键帧编码质量参数
typedef enum enum_ZJ_KEYFRAME_QUALITY{
    EN_ZJ_KEYFRAME_QUALITY_NORMAL = 1, // 标准质量
    EN_ZJ_KEYFRAME_QUALITY_LOW    = 2, // 低质量
}EN_ZJ_KEYFRAME_QUALITY;

//定义AIIoT类型，包括报警器、信号采集检测器、控制器；
typedef enum enum_ZJ_AIIOT_TYPE{
    EN_ZJ_AIIOT_TYPE_REMOTECTRLER               = 0,        //遥控器
    EN_ZJ_AIIOT_TYPE_DOORSWITCH                 = 1,        //门磁
    EN_ZJ_AIIOT_TYPE_SMOKETRANSDUCER            = 2,        //烟雾传感器
    EN_ZJ_AIIOT_TYPE_GASSENSOR                  = 3,        //燃气 探测 传感器
    EN_ZJ_AIIOT_TYPE_LIGHTSWITCH                = 4,        //电灯
    EN_ZJ_AIIOT_TYPE_CURTAIN                    = 5,        //窗帘
    EN_ZJ_AIIOT_TYPE_JACK                       = 6,        //插座
    EN_ZJ_AIIOT_TYPE_PIR                        = 7,        //人体 红外 
    EN_ZJ_AIIOT_TYPE_WATER                      = 8,        //水浸
    EN_ZJ_AIIOT_TYPE_ERG                        = 9,        //紧急
    EN_ZJ_AIIOT_TYPE_ALARMBEER                  = 10,       //警号
    
    EN_ZJ_AIIOT_TYPE_JCAKHVAC                   = 11,       //空调插座
    EN_ZJ_AIIOT_TYPE_MULTISWITCH                = 12,       //多路开关
    EN_ZJ_AIIOT_TYPE_SHUTTERMOTOR               = 13,       //卷帘 电动机
    EN_ZJ_AIIOT_TYPE_GLASSBROKENSENSOR          = 20,       //玻璃破碎 传感器
    EN_ZJ_AIIOT_TYPE_INFRAREDSENSOR             = 23,       //红外 对射 
    EN_ZJ_AIIOT_TYPE_BATTERYVALVE               = 24,       //电磁阀门
    EN_ZJ_AIIOT_TYPE_AIRFLOWSENSOR              = 25,       //气流传感器
    EN_ZJ_AIIOT_TYPE_MULTICTR                   = 32,       //多功能控制
    EN_ZJ_AIIOT_TYPE_INTELLOCK                  = 33,       //智能锁
    EN_ZJ_AIIOT_TYPE_DOORBELL                   = 34,       //门铃
	EN_ZJ_AIIOT_TYPE_COSENSOR                   = 40,       //一氧化碳探测器
    
	EN_ZJ_AIIOT_TYPE_MOTION                     = 1000,      //运动检测
	EN_ZJ_AIIOT_TYPE_INNER_DOORBELL             = 1001,      //内置 门铃
    EN_ZJ_AIIOT_TYPE_RECORD                     = 1002,      //录像 不需要注册IOT
    EN_ZJ_AIIOT_TYPE_INNER_PIR                  = 1003,      //内置人体红外探测器
    EN_ZJ_AIIOT_TYPE_VOICEALARMDETECT           = 1004,      //声音报警检测
    EN_ZJ_AIIOT_TYPE_SNAPSHORT                  = 1005,      //SnapShot截图  不需要注册IOT
    EN_ZJ_AIIOT_TYPE_PTZ                        = 1006,      //PTZ 不需要用注册IOT
    EN_ZJ_AIIOT_TYPE_INNER_LAMP                 = 1007,      //内置白光灯
    EN_ZJ_AIIOT_TYPE_INNER_STATELAMP            = 1008,      //内置状态指示灯
    EN_ZJ_AIIOT_TYPE_BUZZER                     = 1009,      //内置蜂鸣器
    EN_ZJ_AIIOT_TYPE_CLOUDRECORD                = 1010,      // 云端录像
    EN_ZJ_AIIOT_TYPE_CLOUDSNAP                  = 1011,      // 云端截图
    EN_ZJ_AIIOT_TYPE_CAMERA                     = 1012,      // 摄像机
    EN_ZJ_AIIOT_TYPE_EVENT                      = 1013,      // 事件记录
    EN_ZJ_AIIOT_TYPE_DNSET                      = 1014,      // 强制白天晚上,和自动
    EN_ZJ_AIIOT_TYPE_FORCEREMOVE                = 1015,       // 强拆
    EN_ZJ_AIIOT_TYPE_STAY                       = 1016        // 逗留
}EN_ZJ_AIIOT_TYPE;

//区分MOTION中不同的检测类型
typedef enum enum_zj_motion_event_type
{
    EN_ZJ_MOTION_EVENT_MOTION = 0X00,         //移动侦测事件类型
    EN_ZJ_MOTION_EVENT_HUMAN  = 0X01,         //人形侦测事件类型
    EN_ZJ_MOTION_EVENT_FACE   = 0X02          //人脸侦测事件类型
}EN_ZJ_MOTION_EVENT_TYPE;

typedef enum enum_ZJ_ROTATE_TYPE {
    EN_ZJ_ROTATE_TYPE_VERTICAL_UP      = 0x01,  //旋转180°
    EN_ZJ_ROTATE_TYPE_VERTICAL_DOWN    = 0x02,  //反向旋转180°
    EN_ZJ_ROTATE_TYPE_MIRROR_ENABLE    = 0x04,  //镜像翻转
    EN_ZJ_ROTATE_TYPE_MIRROR_DISABLE   = 0x08,  //取消镜像翻转
}EN_ZJ_ROTATE_TYPE;

typedef enum enum_ZJ_CTRLDEVICEID_TYPE{

    EN_ZJ_CTRLDID_NODE       = 0,
    EN_ZJ_CTRLDID_CLEAR      = 1,
    EN_ZJ_CTRLDID_QUERY      = 2,
    EN_ZJ_CTRLDID_EXITGROUP  = 3
}EN_ZJ_CTRLDEVICEID_TYPE;

//设置设备类型?1.摄像机；2.分体门铃；3.单体门铃；4.NVR
typedef enum enum_ZJ_DEV_TYPE
{
    EN_ZJ_DEV_TYPE_CAMERA                   = 0X01,     //摄像机
    EN_ZJ_DEV_TYPE_DOORBELL_SPLIT           = 0X02,     //分体门铃
    EN_ZJ_DEV_TYPE_DOORBELL_SINGLE          = 0X03,     //单体门铃
    EN_ZJ_DEV_TYPE_NVR                      = 0X04      //NVR
}EN_ZJ_DEV_TYPE;

typedef struct stru_ZJ_TRIGGER_INFO{
    unsigned int uiIotType;
    unsigned long long lluIotId;
    unsigned int uiEventId;
    unsigned int uiDuration;
    time_t       tCreateTime;
    void        *pstHandler;  // 保留
}ST_ZJ_TRIGGER_INFO;


// 人脸检测 的 人脸 抠图
typedef struct stru_ZJ_HUMANFACE_INFO
{
    unsigned  char *pjpgBuff;
    unsigned int uiJpgLen;
    double dPointX;  //  0 - 1  左上角 是 00 右下角 是11
    double dPointY;
    double dWidth;
    double dHeight;
    struct stru_ZJ_HUMANFACE_INFO *pstNext;
}ST_ZJ_HUMANFACE_INFO;

typedef int (*ZJ_PFUN_COLLECTLOGFILES)(unsigned char *pucPeerId,unsigned int iSessionId,unsigned char *pcDesInfo);


// 设备状态回调接口； 告诉设备当前状态；
typedef int (*ZJ_PFUN_DEVICE_STATUS)(EN_ZJ_SERVER_STATUS enDeviceStatus, int iErrCode);

// 重启摄像机回调接口； 告诉设备需要重新启动
typedef int (*ZJ_PFUN_DEV_REBOOT)();

// 设置时间时区回调接口， 告诉设备按参数设置时间时区；
typedef int (*ZJ_PFUN_DEVICE_SETTIMEZONE)(int iSyncFlag, int iZone, char* pcDatetime,char *pucDst);

// 时间时区信息获取回调接口，将设备时间时区信息通过该接口参数设置下去；
typedef int (*ZJ_PFUN_DEVICE_GETTIMEANDZONE)(int *piZone,unsigned char *pucTime,int *piSyncFlag);

// 设备恢复出厂设置回调接口，告诉设备需要将参数配置恢复出厂配置状态
typedef int (*ZJ_PFUN_DEVICE_RESTOREFACTORYSETTING)();

// 设置WIFI回调接口，告诉设备当前设置的WIFI模式，WIFI的参数（SSID, 密码，加密类型）；
typedef int (*ZJ_PFUN_DEVICE_SETWIFI)(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType);
// 获取WIFI列表回调接口，获取信号最强的，最多16个WIFI列表；
typedef int (*ZJ_PFUN_DEVICE_GETWIFI)(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount);
// 获取当前网络详情
typedef int (*ZJ_PFUN_DEVICE_GETNETINFO)(ST_ZJ_NETWORK_INFO* pstNetInfo);

typedef int (*ZJ_PFUN_DEVICE_RECVCUSTOMDATA)(const unsigned char* pucPeerID, unsigned char* pucData, int iLen);

// 设备进入休眠回调接口， 设备在该接口,收到等待秒数后，进入休眠状态，-1.为不可以进入休眠； 0.立刻进入休眠； > 0为等待对应的秒数后进入休眠；
typedef int (*ZJ_PFUN_STARTSLEEP)(int iWaitSecond);

// 音频编码开关回调， 音频开始编码/关闭编码 0. 结束； 1.开始
typedef int (*ZJ_PFUN_AUDIO_SWITCH)(int iState); 

// 视频编码开关回调， 该路视频开始编码/结束编码 0. 结束； 1.开始
typedef int (*ZJ_PFUN_VIDEO_SWITCH)(int iStreamID, int iState);

//流媒体需要一个I帧回调接口，告知设备当前流需要一个关键帧； EN_ZJ_KEYFRAME_QUALITY
typedef int (*ZJ_PFUN_VIDEO_NEEDIFRAME)(int iStreamID,unsigned int uiKeyQuality);

//红外灯开关回调接口，告诉设备红外灯切换模式 见：EN_ZJ_IRMODE
typedef int (*ZJ_PFUN_IRLED_SWITCH)(int iState);

//设置画面翻转回调接口， 告诉设备画面进行翻转，取值参考：EN_ZJ_ROTATE_TYPE
typedef int (*ZJ_PFUN_IMAGEINVERSION)(int iState);

//设置摄像机打开关闭回调接口，告诉设备关闭音频和视频； 0. 关闭； 1.打开
typedef int (*ZJ_PFUN_CAMERA_SWITCH)(int iState);

//设置抓取图片回调接口，告诉设备抓取一幅实时画面的图片, 获取对应尺寸的图片，并存入到传入的空间中。 If success, the return value is the jpeg buf length.
typedef int (*ZJ_PFUN_VIDEO_GETJPEG)(EN_ZJ_PICTURE_TYPE enPicType, unsigned char** ppucJpegBuf);

//摄像头PTZ回调接口，告诉设备进行PTZ操作;PTZ操作方法；速度，1~7；1最低；7最快；PTZStep：移动步长，一个步长为1度。360表示一直移动到头一圈
typedef int (*ZJ_PFUN_CAMERA_ONPTZ)(EN_ZJ_CAMERA_PTZ_CONTROL enPTZControl, int iSpeed, int iPTZStep);
//摄像头当前位置获取，获取X,Y点值；
typedef int (*ZJ_PFUN_CAMERA_PTZ_GETPOINT)(int* piX, int* piY);
//摄像机移动到预置点位置
typedef int (*ZJ_PFUN_CAMERA_PTZ_GOTOPOINT)(int iX, int iY);
//摄像机自动检测，当预置点位置因人为转动电机导致错乱时，需要重新设置，设置前需要先自检获得初始位置；
typedef int (*ZJ_PFUN_CAMERA_PTZ_AUTOCHECK)();

//摄像机巡航开始回调接口，告诉设备按定义的预置点巡航；
typedef int (*ZJ_PFUN_CAMERA_CRUISE_START)(int iPresetPointNum, ST_ZJ_CAMERA_CRUISE_PRESET* pstPresets);
//摄像机停止巡航
typedef int (*ZJ_PFUN_CAMERA_PTZ_STOP)();

//音频音量调节回调接口，告诉设备要将音量大小; 0~100。 0为静音；10为最大声音
typedef int (*ZJ_PFUN_AUDIO_VOLUMN_ADJUST)(int iSpeakerId,int iVolumn);

//本地录像状态回调接口，告诉设备本地录像是否进行。 0.未录像；1.录像
typedef int (*ZJ_PFUN_CAMERA_RECORD_STATUS)(int iStatus);

/* 摄像头OSD水印添加回调接口，告诉设备对当前码流增加水印 iPosition:1.左上；2.左下；3.右上；4.右下；0.默认
当 openfalg 是 0 的时候 , 忽略 iPosition 和 pcOSDName 两个参数
*/
typedef int (*ZJ_PFUN_CAMERA_OSDSETTING)(int iPosition, char* pcOSDName);
// osd 水印的 开关显示
typedef int (*ZJ_PFUN_CAMERA_CTRLOSDSHOWFLAG)(int iOpenFlag);


// 摄像头有逆向流传入回调接口，告诉设备有逆向媒体流传入； 1. Start; 0. Stop; iStreamType:EN_ZJ_STREAMER_TYPE
typedef int (*ZJ_PFUN_CAMERA_MEDIA_TOPLAY)(const char* pcPeerID, ZJ_HANDLE hPlayHandle, int iStreamType, int iStatus);

//SD卡格式化回调接口，通过该接口通知设备重构
typedef int (*ZJ_PFUN_CAMERA_FORMATSDCARD)();

//获取SD卡容量回调接口，通过该接口获取SD卡容量信息 单位 M
typedef int (*ZJ_PFUN_CAMERA_GETSDCARDSIZE)(unsigned int* piTotalSize, unsigned int* piFreeSize);

//SD卡自检测回调接口，通过该接口让SD卡进行检测修复，返回错误信息。 0 为无错误；
typedef int (*ZJ_PFUN_CAMERA_CHECKSDCARD)(int* piErrCode);

//AIiOT 设备开始工作回调接口， 通过该接口启动AIIOT设备信号采集；
typedef int (*ZJ_PFUN_AIIOT_START)(unsigned int uiAIIoTType, unsigned long long uiAIIoTID);

//AIiOT 设备停止工作回调接口， 通过该接口通知设备停止信号采集；
typedef int (*ZJ_PFUN_AIIOT_STOP)(unsigned int uiAIIoTType, unsigned long long lluAIIoTID);

/*************************************************************************************
查询AIiOT 设备当前事件或信号量回调接口， 通过该接口返回设备当前的信号量和事件, 
返回输入信号类型和对应的信号Json字串返回下来；输出值内部分配， sdk 只使用， 不释放
*************************************************************************************/
typedef int (*ZJ_PFUN_AIIOT_GETINPUT)(unsigned int uiAIIoTType, unsigned long long uiAIIoTID,unsigned char** ppSignalValue);

//向AIiOT 设备输出信号回调接口，通过该接口，将输出信号类型和对应的JSON描述字符串输出到AIiOT设备；CONTRL 函数
typedef int (*ZJ_PFUN_AIIOT_OUTPUT)(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue,ST_ZJ_TRIGGER_INFO* pstTriggerInf);

//向AIIoT设备设置属性回调接口，通过该接口，将新的属性值设置给AIIoT设备，让设备以设置的属性值进行工作；属性以一个JSON字符串传递；
typedef int (*ZJ_PFUN_AIIOT_SETPROP)(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pstProp); //yinkai changed type

//检测当前输入信号对应的事件类型回调接口，通过该接口，判定当前输入信号的事件类型，以返回值返回；
typedef int (*ZJ_PFUN_AIIOT_CHECKEVENT)(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue);

//设置设备名称
typedef int (*ZJ_PFUN_SET_DEVICE_NAME)(unsigned char *pucDeviceName);

//强拆设备触发报警开关
typedef int (*ZJ_PFUN_SET_DISMANTABLE_ALARM)(unsigned int uiOpenFlag);

//逗留报警开关
typedef int (*ZJ_PFUN_SET_STAY_ALARM)(unsigned int uiOpenFlag);

//设置摄像机宽动态开关
typedef int (*ZJ_PFUN_SET_WIDE_DYNAMIC_CAM)(unsigned int uiOpenFlag);

//配置变化 通知 
typedef int (*ZJ_PFUN_CFGITEM_CHANGE)(unsigned int uiCfgItem);


// 音频采集参数配置的回调接口,参数配置放在pstAudioParm里边；
typedef int (*ZJ_PFUN_SET_AUDIO_PARM)(ST_ZJ_AUDIO_PARAM *pstAudioParm);

//这是设置视频采集参数的回调函数
typedef int (*ZJ_PFUN_SET_VIDEO_PARM)(int iStreamID,ST_ZJ_VIDEO_PARAM *pstVideoParm);

//这是设置PTZ 参数的回调接口
typedef int (*ZJ_PFUN_SET_PTZ_PARM)(int iOpenFlag);

/****************************************************************
升级回调函数
***************************************************************/
// 设备版本状态回调接口，告诉设备当前版本升级状态
typedef int (*ZJ_PFUN_NEWVERSON_NOTICE)(unsigned char *pucNewVersion,unsigned int uiFileSize);

// 设备版本状态回调接口，告诉设备当前版本升级状态
typedef int (*ZJ_PFUN_NEWVERSON_DATADOWN)(unsigned char *pucPackage,unsigned int uiPacklen,unsigned int uiEndFlag);

// 停止下载文件
typedef int (*ZJ_PFUN_STOPUPGRADE)();

// 1 解签成功，通知固件覆盖镜像、 0 解签不成功，不覆盖
typedef int (*ZJ_PFUN_COVERIMAGE_NOTICE)(unsigned int uiCoverFlag);

/****************************************************************
***************************************************************/
//切换摄像头
typedef int (*ZJ_PFUN_SWITCH_LEN)(int iLenId);

/***************************************************************
自定义报警声音
***************************************************************/
//删除声音文件
typedef int (*ZJ_PFUN_DELSOUNDFILE)(unsigned char *pucSoundName);
//获取声音文件列表
typedef int (*ZJ_PFUN_GETSOUNDFILES)( unsigned int *piTotalSize, unsigned int *piFreeSize, unsigned char aucSoundList[32][64], unsigned int *uiSoundListCnt,unsigned int uiRingType);

/***************************************************************
人脸相关的信息
***************************************************************/
typedef struct ZJ_HUMANFACE_NODE
{
    unsigned char aucFaceId[64];        //人脸id
    unsigned char aucFaceLabelId[64];   //人脸标签id
    struct ZJ_HUMANFACE_NODE *pstNextNode;
}ZJ_HUMANFACE_NODE;

typedef struct ZJ_HUMANFACE_LABLE_NODE
{
    unsigned int  uiMaxFaceCnt;         //最大数量
    unsigned int  *pucFaceDes;          //人脸标签备注信息
    unsigned char aucFaceLabeName[64];  //人脸名称
    unsigned char aucFaceLabelId[64];   //人脸标签id
    struct ZJ_HUMANFACE_LABLE_NODE *pstNextNode;
}ZJ_HUMANFACE_LABLE_NODE;

//获取人脸库列表
typedef int (*ZJ_PFUN_GET_FACELABLELIST)(ZJ_HUMANFACE_LABLE_NODE **pstFaceLableHead);
// 获取人脸列表
typedef int (*ZJ_PFUN_GET_FACELIST)(ZJ_HUMANFACE_NODE **pstFaceHead);
// 修改人脸库信息
typedef int (*ZJ_PFUN_MODIFY_FACELABLEINF)(ZJ_HUMANFACE_LABLE_NODE *pstFaceLableInf);
// 更改人脸归属的人脸库
typedef int (*ZJ_PFUN_MODIFY_FACEINF)(ZJ_HUMANFACE_NODE *pstFaceHead);
// 创建人脸库
typedef int (*ZJ_PFUN_CREAT_FACELABLE)(unsigned char *pucInLableName,unsigned char *pucOutLableId);
// 向 人脸库中添加人脸
typedef int (*ZJ_PFUN_ADDFACETOLABLE)(unsigned char *pucLableId,unsigned char *pucFileName);

// 设置人脸图片缓存路径
_ZJ_API int ZJ_SetFaceFileCachePath(unsigned char *pucFaceCachePath);



#ifdef __cplusplus
}
#endif


#endif
