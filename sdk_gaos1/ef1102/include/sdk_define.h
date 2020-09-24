#ifndef _SDK_DEFINE_H_
#define _SDK_DEFINE_H_

#ifdef __cplusplus
extern "C"{
#endif

#define SDK_FAILUR -1
#define SDK_SUCESS  0

#define SDK_FALSE   0
#define SDK_TRUE    1


/*********** error code ********/
#define ERR_MAP            (SDK_SUCESS+ 1)
#define ERR_DEV            (ERR_MAP   + 1)
#define ERR_INI            (ERR_DEV   + 1)
#define ERR_AUDIOINIT      (ERR_INI   + 1)
#define ERR_VIDEOINIT      (ERR_AUDIOINIT + 1)
#define ERR_IMAGEINIT      (ERR_VIDEOINIT + 1)
#define ERR_RCSTART        (ERR_IMAGEINIT + 1)
#define ERR_BCASTINIT      (ERR_RCSTART   + 1)
#define ERR_NETWORK        (ERR_BCASTINIT + 1)
#define ERR_DISCOVER       (ERR_NETWORK   + 1)
#define ERR_AUDIO          (ERR_DISCOVER  + 1)
#define ERR_VIDEO          (ERR_AUDIO     + 1)
#define ERR_MOTION         (ERR_VIDEO     + 1)
#define ERR_OSD            (ERR_MOTION    + 1)
#define ERR_SYSPROC        (ERR_OSD       + 1)
#define ERR_BIPBUF        (ERR_SYSPROC       + 1)


#define ERR_STREAM         4
#define ERR_INVALID_PARAM  5
#define ERR_NULLPTR        6
#define ERR_NOINITSDK      7
#define ERR_NOTPERM        8
#define ERR_MULTINITSDK    9
#define ERR_NOTSUPPORT     10
#define ERR_INVALIDFILE    11
#define ERR_FILESIZE       12
#define ERR_GETSPS         13
#define ERR_READFILE       14
#define ERR_SD_BUSY        15
#define ERR_NO_SD          16
#define ERR_FILE_UPDATE    17
#define ERR_DEV_MODEL      18
#define ERR_SENSOR_TYPE    19
#define ERR_PWD_LENGTH     20

#if defined (__cplusplus)
}
#endif

#endif //_SDK_DEFINE_H_
