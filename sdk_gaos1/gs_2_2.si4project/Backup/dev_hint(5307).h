#ifndef DEV_HINT_H_
#define DEV_HINT_H_


#define DEVVOICE_QL_START       "/mnt/config/aac/qlink_start.g711a"
#define DEVVOICE_QL_SUCCEED     "/mnt/config/aac/qlink_success.g711a"
#define DEVVOICE_QL_FAIL        "/mnt/config/aac/qlink_failure.g711a"
#define DEVVOICE_QL_QROK1       "/mnt/config/aac/qrcode_ok1.aac"

int dev_hintSoundP(char *filePath);

#endif




