#ifndef FORZB_CAMERAIOT_H_
#define FORZB_CAMERAIOT_H_

#include "zj_type.h"


int aiiot_dnset_start(unsigned int uiAIIoTType, unsigned long long uiAIIoTID);
int aiiot_dnset_stop(unsigned int uiAIIoTType, unsigned long long lluAIIoTID);
int aiiot_dnset_output(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue,ST_ZJ_TRIGGER_INFO* pstTriggerInf);

int aiiot_inner_start(unsigned int uiAIIoTType, unsigned long long uiAIIoTID);
int aiiot_inner_stop(unsigned int uiAIIoTType, unsigned long long lluAIIoTID);
int aiiot_inner_output(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue,ST_ZJ_TRIGGER_INFO* pstTriggerInf);



#endif




