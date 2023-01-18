/*
 * AppInfo.h
 *
 *  Created on: May 5, 2021
 *      Author: kendor
 */

#ifndef APPINFO_H_
#define APPINFO_H_

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define APP_VER_STR		"0.0.0"	// should be equal

/* Do not modify sizes! */
char APP_INFO_ID[32] __attribute__ ((section(".app_info"))) = "ID=DOOR_ECU_XMC4500";
char APP_INFO_VERSION[8] __attribute__ ((section(".app_info"))) = "Version=";
char APP_INFO_VER[24] __attribute__ ((section(".app_info"))) = APP_VER_STR;
char APP_INFO_DEVELOPER[64] __attribute__ ((section(".app_info"))) = "Developers=Smirnov D.A.; Karbovskiy D.A.";
char APP_INFO_PUBLISHER[64] __attribute__ ((section(".app_info"))) = "Publisher=PKDS";
char APP_INFO_LICENSE[64] __attribute__ ((section(".app_info"))) = "License=";
char APP_INFO_CONTACTS[128] __attribute__ ((section(".app_info"))) = "Contacts=";
char APP_INFO_HARDWARE[128] __attribute__ ((section(".app_info"))) = "HardWare=";
char APP_INFO_DESCRIPTION[256] __attribute__ ((section(".app_info"))) = "Description=";
char APP_INFO_EXTRA_PARAM[256] __attribute__ ((section(".app_info"))) = "Extra=";

#pragma GCC pop_options

#endif /* APPINFO_H_ */
