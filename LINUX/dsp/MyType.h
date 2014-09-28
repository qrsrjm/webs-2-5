#ifndef __MYTYPE_H__
#define __MYTYPE_H__

/* 重定义变量声明 */


typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;


typedef unsigned char  uint8;       /* 	无符号8位整型变量  		 */
typedef signed   char  int8;        /* 	有符号8位整型变量  		 */
typedef unsigned short uint16;      /* 	无符号16位整型变量 		 */
typedef signed   short int16;       /* 	有符号16位整型变量	 	 */
typedef unsigned int   uint32;      /* 	无符号32位整型变量 		 */
typedef signed   int   int32;       /* 	有符号32位整型变量 		 */
typedef float          fp32;        /*  单精度浮点数（32位长度） */
typedef double         fp64;        /*  双精度浮点数（64位长度） */



/* 系统时间参考 */
#define 	DLY_1US		13
#define 	DLY_10US	138
#define 	DLY_100US	1380
#define 	DLY_1MS		13800

#endif
