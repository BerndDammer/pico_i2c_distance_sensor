/*
 * platform_adapt.h
 *
 *  Created on: 04.04.2023
 *      Author: manni4
 */

#ifndef PLATFORM_ADAPT_H_
#define PLATFORM_ADAPT_H_

void vl53l4cd_dialog( //
        int addr, //
        unsigned char *outBuffer, //
        int outLen, //
        unsigned char *inBuffer, //
        int inLen //
        );
void vl53l4cd_init(void);
void vl53l4cd_re_init(void);
unsigned short vl53l4cd_check_dialog(void);

#endif /* PLATFORM_ADAPT_H_ */
