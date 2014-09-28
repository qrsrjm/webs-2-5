/*
*****************************************Copyright (c)*********************************************
**
**
**									 广州立锐升电子有限公司
**                             Guangzhou Lrsun Electronic Co.,Ltd.
**
**                                    http://www.lrsun.net
**
**
**
**	文件名	：TAS3xxxDownload.h
**
**	程序员	：陈家承
**
**	日　期  ：2009年2月2日
**
**	文件描述：TAS3xxx固件下载操作
**
**
***************************************************************************************************
*/
//extern "C"{
#ifndef _TAS3xxxDownload_H 
#define _TAS3xxxDownload_H


#include "MyType.h"

#include <unistd.h> //sleep close
#include <stdlib.h> //exit
#include <stdio.h>



//}

/* Memory Type */
#define TAS3XXX_MICRO_PROG_MEM					0x0
#define TAS3XXX_MICRO_EX_DATA_MEM				0x1
#define TAS3XXX_DAP_PROG_MEM					0x2
#define TAS3XXX_DAP_COEFF_MEM					0x3
#define TAS3XXX_DAP_DATA_MEM					0x4


/* I2C Subaddress */

//--------------------------------------------------
// TAS3108 predefined registers
//--------------------------------------------------
#define TAS3XXX_CLKSAP_CONTROL					0x00
#define TAS3XXX_STATUS							0x02
#define TAS3XXX_MEMLOAD_CTRL					0x04
#define TAS3XXX_MEMLOAD_DATA					0x05
#define TAS3XXX_PEEKPOKE_ADDR					0x06
#define TAS3XXX_PEEKPOKE_DATA					0x07
#define TAS3XXX_VERSION							0x08

/* Return Type */
#define TAS3108_TERMINATION_BLOCK				0x1
#define TAS3108_NORMAL_HEADER					0x0

/* Status Type */
#define TAS3XXX_LOAD_SUCCEED					0x00
#define TAS3XXX_MICRO_PROGMEM_ERR				0x01
#define TAS3XXX_MICRO_EXMEM_ERR					0x02
#define TAS3XXX_DAP_PROGMEM_ERR					0x04
#define TAS3XXX_DAP_COEFFMEM_ERR				0x08
#define TAS3XXX_DAP_DATAMEM_ERR					0x10
#define TAS3XXX_INVALID_MEMSEL					0x20
#define TAS3XXX_END_HEADER_ERR					0xF0
#define TAS3XXX_NO_EEPROM						0xFF



extern void  DapHwInit();

extern uint8 DapPrgDownload(uint8 sla);

extern uint8 DapStatusCheck(uint8 tas3xxx_sla);

extern uint8 CheckMemloadCtrl(uint8 tas3108_sla, uint8 *src_header_ptr);

//extern uint8 *DataOfBlockDownload(uint8 tas3108_sla, uint8 *data_ptr, int32 num_of_block);
extern uint8 *DataOfBlockDownload(uint8 tas3108_sla, uint8 *data_ptr, int32 num_of_block);


#endif



