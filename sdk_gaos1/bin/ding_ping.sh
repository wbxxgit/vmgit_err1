#!/bin/sh

echo "tf card upgrade start"

UpgradeFile1="/opt/httpServer/lighttpd/htdocs/sd/upgrade/GS_DEVICE_SDK"
if [ -e "$UpgradeFile1" ];then
if [ -f "$UpgradeFile1" ];then
echo "rm GS_DEVICE_SDK"
rm /mnt/app/GS_DEVICE_SDK.tar.bz2 
rm /mnt/app/GS_DEVICE_SDK 
fi

cp /opt/httpServer/lighttpd/htdocs/sd/upgrade/GS_DEVICE_SDK /mnt/app/

echo "tf card upgrade finish"

/mnt/app/GS_DEVICE_SDK &

else
	if [ -e "/mnt/app/GS_DEVICE_SDK" ];then
			
		echo "exist file and run"
		/mnt/app/GS_DEVICE_SDK &
	else
	
		echo "file not exist,exit sdsh!"
	fi
fi
