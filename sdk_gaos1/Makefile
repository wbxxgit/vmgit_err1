###################################################
##    Makefile
##    Created by GOSPELL
##    2018.06.01
###################################################

PRJ_PATH            = $(shell pwd)
#OSTYPE=PLA_QX

###################################################
######//change here for device select##########
#GAOSILIB_CHOSE=GSLIB_1002
GAOSILIB_CHOSE=GSLIB_1102

CFLAGS += -D MMACRO_FLASHCTEI
#CFLAGS += -D MMACRO_NOFLASH_T1_NT
###################################################

#CFLAGS += -D MMACRO_NOFLASH_T1_NT
#CFLAGS += -D MMACRO_FLASHCTEI
#MMACRO_NOFLASH_T2_YT
#MMACRO_NOFLASH_T1_NT
#MMACRO_NOFLASH_T0_EX
#MMACRO_NOFLASH_T3_E1102_DEDICATED

#MMACRO_NOFLASH_T3_E1102


CROSS_COMPILE       = arm-gk720x-linux-uclibcgnueabi-
CC                  = $(CROSS_COMPILE)gcc
CPLUSPLUS           = $(CROSS_COMPILE)g++
#platform sel

#CC		    =gcc
STRIP               = $(CROSS_COMPILE)strip


DYNAMIC_LIBS_FLAGS  = -Wl,-Bdynamic  
DYNAMIC_LIBS        = -lpthread -lm -lrt -ldl
STATIC_LIBS_FLAGS   = -Wl,-Bstatic 
STATIC_LIBS         = -lGokemain -lcurl -lmbedtls -lUpgrade -lmbedx509 -liniparser -linterface -lsystools -lmediabuf -lvideo -lgvapplatform -lthirdparty -lmbedcrypto -lrecord -llog -lQrcode -lzbar -lNtp -lMotor -lvision -lncnn -limage -losd -lAudio -laac -ladi -limage_goke -lbroadcasdiscover -lSchedule -lstdc++\
-lcommon -lcos -lthirdparty -lssl -lcrypto -lmbedtls -lmbedcrypto -lmbedx509

#STATIC_LIBS         = -lGokemain -lcurl -liniparser -linterface -lsystools -lmediabuf -lvideo -lgvapplatform  -lrecord -llog -lQrcode -lzbar -lNtp -lMotor #-lvision -lncnn -limage -losd -lAudio -laac -ladi -limage_goke -lbroadcasdiscover -lSchedule -lstdc++\
#-lcommon -lcos -lthirdparty -lssl -lcrypto -lmbedtls -lmbedcrypto -lmbedx509   
#LDFLAGS		        = -O0 -Wall -g3 -rdynamic -Wall -ggdb -Werror 
LDFLAGS		        = -O0 -Wall -g3 -rdynamic -ggdb -D_GNU_SOURCE -ffunction-sections -fdata-sections -D_COS_OS=_COS_LINUX
TARGET              = GS_DEVICE_SDK


#LIBS                := -L$(PRJ_PATH)/lib
#INC_FLAGS           := -I$(PRJ_PATH)/include

ifeq ($(GAOSILIB_CHOSE), GSLIB_1002)
	LIBS                := -L$(PRJ_PATH)/ef1002/lib
	INC_FLAGS           := -I$(PRJ_PATH)/ef1002/include
else
	LIBS                := -L$(PRJ_PATH)/ef1102/lib
	INC_FLAGS           := -I$(PRJ_PATH)/ef1102/include
	CFLAGS += -D MMACRO_NOFLASH_T3_E1102
endif


#LIBS                += -L$(PRJ_PATH)/zj_sdk/lib
#LIBS                += -L$(PRJ_PATH)/zj_sdk/lib/static
#INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/include

ifeq ($(OSTYPE), PLA_QX)
	LIBS                += -L$(PRJ_PATH)/zj_sdk/lib_qx/lib
	LIBS                += -L$(PRJ_PATH)/zj_sdk/lib_qx/lib/static
	INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/lib_qx/include

else
	LIBS                += -L$(PRJ_PATH)/zj_sdk/lib_zj/lib
	LIBS                += -L$(PRJ_PATH)/zj_sdk/lib_zj/lib/static
	INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/lib_zj/include
	CFLAGS += -D MACRO_ZJ
endif



INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/incsup
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/src/forZJcb/include
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/src/ZJ_relate/include
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/src/funReg
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/device/include
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/src/third/include
INC_FLAGS           += -I$(PRJ_PATH)/zj_sdk/src/sysAuxiliary/include

SOURCE              := $(PRJ_PATH)/test/sdk_main.c
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/src/forZJcb/src/*.c)
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/src/ZJ_relate/src/*.c)
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/src/funReg/*.c)
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/device/src/*.c)
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/src/third/src/*.c)
SOURCE              += $(wildcard $(PRJ_PATH)/zj_sdk/src/sysAuxiliary/src/*.c)


$(PRJ_PATH)/bin/$(TARGET) : $(SOURCE)
	@echo "\033[32m Compiling $(TARGET)... \033[0m" 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(INC_FLAGS) $(LIBS) $(STATIC_LIBS_FLAGS) $(STATIC_LIBS) $(DYNAMIC_LIBS_FLAGS) $(DYNAMIC_LIBS) -static-libstdc++
	@$(STRIP) $@
	@echo "\033[32m Compiling $(TARGET) successfully! \033[0m" 

.PHONY : clean
clean:
	@rm -rf $(PRJ_PATH)/bin/$(TARGET)
	@echo "\033[31m rm $(TARGET) successfully! \033[0m" 
    
