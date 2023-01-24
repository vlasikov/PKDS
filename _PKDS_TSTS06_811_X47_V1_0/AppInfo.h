/*
 * AppInfo.h
 *
 *  Created on: Apr 20, 2021
 *      Author: D. A. Karbovskiy
 */

#ifndef APPINFO_H_
#define APPINFO_H_


#pragma GCC push_options
#pragma GCC optimize ("O0")

#define APP_VER_STR		"1.0.0"

/* Do not modify sizes! */
char APP_INFO_ID[32] __attribute__ ((section(".app_info"))) = "ID=DOOR_ECU_XMC4700"; // This ID must be equal to the production software ID
char APP_INFO_VERSION[8] __attribute__ ((section(".app_info"))) = "Version=";
char APP_INFO_VER[24] __attribute__ ((section(".app_info"))) = APP_VER_STR;
char APP_INFO_DEVELOPER[64] __attribute__ ((section(".app_info"))) = "Developers=Smirnov D.A.";
char APP_INFO_PUBLISHER[64] __attribute__ ((section(".app_info"))) = "Publisher=PKDS";
char APP_INFO_LICENSE[64] __attribute__ ((section(".app_info"))) = "License=";
char APP_INFO_CONTACTS[128] __attribute__ ((section(".app_info"))) = "Contacts=info@pk-ds.org";
char APP_INFO_HARDWARE[128] __attribute__ ((section(".app_info"))) = "HardWare=PKDS.EPCU01.01.004";
char APP_INFO_DESCRIPTION[256] __attribute__ ((section(".app_info"))) = "Description=PKDS.TST.SW.100;";
char APP_INFO_EXTRA_PARAM[256] __attribute__ ((section(".app_info"))) = "Extra=";

#pragma GCC pop_options


#endif /* APPINFO_H_ */
