/*
 * ds1631.h
 *
 *  Created on: 26.03.2023
 *      Author: manni4
 */

#ifndef DS1631_H_
#define DS1631_H_

//typedef struct
//{
//    unsigned char config;
//    unsigned short int temp;
//    unsigned short int tl;
//    unsigned short int th;
//}ds1631_regs;

void vl53l4cd_init(void);
void vl53l4cd_re_init(void);
unsigned short vl53l4cd_check_dialog(void);
int vl53l4cd_GetFirmwareSystemStatus(void);
void vl53l4cd_StartRanging(void);
void vl53l4cd_StopRanging(void);
int vl53l4cd_CheckForDataReady(void);
void vl53l4cd_ClearInterrupt(void);
int vl53l4cd_GetResult();



//void ds1631_init(void);
//int ds1631_check_addr(void);
//void ds1631_get_regs(ds1631_regs *r);
//void ds1631_start(void);
//void ds1631_stop(void);
//double ds1631_get_temp(void);
//void ds1631_write_borders(double dtl, double dth);
//void ds1631_reset(void);



#endif /* DS1631_H_ */
