#ifndef __MYTYPE_H__
#define __MYTYPE_H__

/* �ض���������� */


typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;


typedef unsigned char  uint8;       /* 	�޷���8λ���ͱ���  		 */
typedef signed   char  int8;        /* 	�з���8λ���ͱ���  		 */
typedef unsigned short uint16;      /* 	�޷���16λ���ͱ��� 		 */
typedef signed   short int16;       /* 	�з���16λ���ͱ���	 	 */
typedef unsigned int   uint32;      /* 	�޷���32λ���ͱ��� 		 */
typedef signed   int   int32;       /* 	�з���32λ���ͱ��� 		 */
typedef float          fp32;        /*  �����ȸ�������32λ���ȣ� */
typedef double         fp64;        /*  ˫���ȸ�������64λ���ȣ� */



/* ϵͳʱ��ο� */
#define 	DLY_1US		13
#define 	DLY_10US	138
#define 	DLY_100US	1380
#define 	DLY_1MS		13800

#endif
