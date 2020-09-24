#ifndef _IPC_MEDIABUFF_H_
#define _IPC_MEDIABUFF_H_

#include "stream_manager.h"

typedef enum {
    IPC_FRAME_TYPE_I = 0,
    IPC_FRAME_TYPE_P = 1,
    IPC_FRAME_TYPE_A = 2,
    IPC_FRAME_TYPE_JPEG = 3,
} IPC_FRAME_TYPE;


typedef struct {
    unsigned int 	frame_size;    					/* frame size */
    unsigned int 	frame_no;      					/* frame number */
    unsigned int 	frame_type;   					/* frame type  IPC_FRAME_TYPE*/
    unsigned int 	sec;             				/*second of frame*/
    unsigned int 	pts;             				/*pts of frame*/
    unsigned int 	reserved;     					/* user defined */
}IPC_MEDIABUFF_FRAME_HEADER;

typedef struct tagHANDLE_MEDIA_BUFF_
{
	shm_stream_t * 	pUserWirteMain;
	shm_stream_t * 	pUserWirteSub;
}stMEDIA_HANDLE, * pstMEDIA_HANDLE;
extern stMEDIA_HANDLE g_stMediaHandle;


int IPC_MediaBuff_ReadFrame(void *pUserCtx, void **pFrame, int *pFrameLen, void *pFrameHead);
int IPC_MediaBuff_ReadIFrame(void *pUserCtx, void **pFrame, int *pFrameLen, void *pFrameHead);
int IPC_MediaBuff_WirteFrame(unsigned int nEncType, unsigned int nChn, void * pHead, unsigned char* data, int frame_size);

void * IPC_MediaBuff_AddRead(int nChn, int nSeq, char * strName);
int IPC_MediaBuff_DelRead(void * pUserCtx);
int IPC_MediaBuff_Sync(void * pUserCtx);

int IPC_MediaBuff_Init();
int IPC_MediaBuff_Exit();

#endif
