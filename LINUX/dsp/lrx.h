/*
*****************************************Copyright (c)*********************************************
**
**
**									 �����������������޹�˾
**                             Guangzhou Lrsun Electronic Co.,Ltd.
**
**                                    http://www.lrsun.net
**
**
**
**	�ļ���	��LRX.h
**	
**	����Ա	���¼ҳ�
**
**	�ա���  ��2009��5��9��
**
**	�ļ������������ͺŵ�Ԥ����ͷ�ļ�����ͬ�Ĳ�����Ӧ��ͬ�ͺŵĴ�������
**			  
**
***************************************************************************************************
*/
#ifndef _LRX_H
#define _LRX_H

#include "MyType.h"


/**
 * The brief description.
 * The detail description.
 */
typedef	struct CTRL_DSP_t
{
	uint8_t  	type;						///< ֡��ʼ
	uint8_t		Addr;
	uint8_t		rw;
	uint8_t   	Length[2];
	uint8_t		DBuf[0];					///< �������ݻ�����ָ��
} CTRL_DSP_t;

#define DATA_HEAD_SIZE (sizeof(struct CTRL_DSP_t))

#define FRAME_HEAD   "info of device&"
#define FRAME_HEAD_SIZE (sizeof("info of device&")-1)

/**
 * The brief description.
 * The detail description.
 */
typedef struct volstr
{
	fp32 Gain;
	int8_t Pol;
	int8_t Mute;
	int8_t Reserved1;
	int8_t Reserved2;
} VOL_STR;

/**
*   ����
*/
typedef struct volOp
{
	VOL_STR vol;
	uint8_t Ch;			/**<���ͨ������Ch*/
	int8_t Reserved1;
	int8_t Reserved2;
	int8_t Reserved3;
} VOL_OP;


/**
 * The brief description.
 * The detail description.
 */
typedef struct eqstr
{
	fp32  Q;
	fp32  Gain;
	uint16_t Fc;
	int8_t Type;
	uint8_t en;///en=1����EQ��En=0��bypassEQ
} EQ_STR;

// ����
typedef struct EQOP
{
	EQ_STR peq;			/**<peq PEQ�ṹ��ָ��*/
	uint8_t Ch;			/**<���ͨ������Ch*/
	uint8_t no;			/**<ÿ��ͨ��Eq������no*/
	uint8_t reserved1;  ///< �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
}EQOP_STR;				/**<PEQ�����ṹ��*/

//
typedef struct tonestr
{
	int32_t Fc1;
	int32_t Fc2;
	fp32  Gain;
	fp32  Q;
	uint8_t en;
	uint8_t reserved1;  ///< �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
} TONE_STR;

/**
 * The brief description.
 * The detail description.
 */
typedef struct dlystr
{
	fp32  Dly;
	uint8_t en;
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
} DLY_STR;

// �ӳ�
typedef struct Outdlystr
{
	DLY_STR delay;
	uint8 Ch;     /**<���ͨ��������Ch={0,1}*/
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
}Outdly;             /**<���ͨ����ʱ�ṹ��*/

typedef struct hlpfstr
{
	uint16_t Fc;
	int8_t  Type;
	uint8_t en;
} HLPF_STR;

// �ߵ�ͨ
typedef struct CHLpf
{
	HLPF_STR xpf;
	uint8 Ch;      /**<���ͨ��������Ch={0,1,2,3,4,5}*/
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
}CHanHLPF_STR;    /**<��ͨ����ͨ�ṹ��*/


typedef struct bpfstr
{
	uint16_t Fp;
	uint16_t Fs;
	int8_t  Type;
	uint8_t en;
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
} BPF_STR;

typedef struct bpfstrOp
{
	uint16_t Fp;
	uint16_t Fs;
	int8_t  Type;
	uint8_t en;
	uint8_t Ch;  // �����ֽڶ���1
	uint8_t reserved1;  // �����ֽڶ���2
} BPF_OP;


/**
 * The detail description.
 */
typedef struct drcstr
{
	//  float T1;
	float T2;
	//  float O1;
	//  float O2;
	//  float k0;
	//  float k1;
	float k2;
	float Attack;
	float Release;
	uint8_t en;
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
} DRC_STR;

//ѹ��
typedef struct LimiterOP
{
	DRC_STR limiter;
	uint8 Ch;
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
}LimiterOP_STR;



typedef struct mixstr
{
	float fVal;     ///mixer
	uint8_t Start;  ///in
	uint8_t End;    ///out
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
} MIX_STR;


typedef struct Mix4Ch
{
	float mix;
	uint8_t in;
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
} Mix4Ch_STR;

/**
 *  3D
 */
typedef struct Music3DOp
{
	DLY_STR delay;//��ʱ
	//Mix4Ch_STR *Mix4ChNo;//3Dmusic ģ���еĻ���ģ������������ˣ���ɾ��
	float mix[4];//���һ��·��ϵ��,����
	uint8 en;
	uint8_t Ch;//ͨ������Ch={0,1}
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
} Music3DOp_STR;



/**
 * �������� 
 *  LinType: 
 *<�������>0x10:�������,0x11:�����,0x12:�����  
 *< 2��������>0x20:�������,0x21:�ߵ������,0x22 :�е������ 
 *<3���������>0x30:���е���һ��·�����
 */

#if 0
typedef struct SCTOP
{
	HLPF_STR hpf;
	DRC_STR AGChp;

	BPF_STR  bpf;
	DRC_STR AGCbp;

	HLPF_STR lpf;
	DRC_STR AGClp;

	float VolDepth;
	float mix[3];//���һ��·��ϵ��,����
	uint8_t en;//ʹ�ܣ�en=1,en=0�ر�
	uint8_t Ch;//ͨ������Ch={0,1}
	uint8_t Type;//���е͵����ͣ�Type ��0--SCTHP,1--SCTBP,2--SCTLP
	uint8_t LinType;  // �����ʽ<0>�������<1>2��������<2>3���������
}SCTOP_STR;
#else
typedef struct SCTOP
{
	HLPF_STR hpf;
	DRC_STR AGChp;

	BPF_STR  bpf;
	DRC_STR AGCbp;

	HLPF_STR lpf;
	DRC_STR AGClp;

	float hVolDepth;
    float bVolDepth;
    float lVolDepth;
	float mix[4];//���һ��·��ϵ��,����
	uint8_t en;//ʹ�ܣ�en=1,en=0�ر�
	uint8_t Ch;//ͨ������Ch={0,1}
}SCTOP_STR;

#endif

// ��Դѡ��
typedef struct AnaOrDigSource
{
	float mixer;    /// 0-3  <1>
	uint8 en;     /**<en ģ��ͨ·ʹ�ܣ���Aen=1����ģ����Դ��Ч��Aen=0��������Դ��Ч��Aen={0,1}*/
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
	uint8_t reserved3;  // �����ֽڶ���3
}AnaOrDigSrc_STR;

//�ź�Դ
typedef struct SourceSig
{
	VOL_STR gain;    /**<VOL_STR* gain �����ź�Դ���������ƣ�*/
	float mixer;      /**<·�ɱ�������ͬ��ϵ��*/
	uint8 en;         /**<en �����ź�ʹ�ܣ�Aen=1ʱ��ʹ�ܣ�Aen=0ʱ����ֹ*/
	uint8 SourceType;  /**<SourceType �ź�����ѡ��SourceType={0,1,2}*/
	uint8_t reserved1;  // �����ֽڶ���1
	uint8_t reserved2;  // �����ֽڶ���2
}SourceSignal_STR;    /**<���¼ӵĲ����ź�Դ�ṹ��*/



//�ߵ�ͨ����ͨ���˲�������[Type] ��Ԥ����
#define	BW_06		0x00
#define	BW_12		0x02
#define	BW_18		0x05
#define	BW_24		0x07
#define	BW_36		0x0a
#define	BW_48		0x0d
#define	BL_06		0x01
#define	BL_12		0x03
#define	BL_18		0x06
#define	BL_24		0x08
#define	BL_36		0x0b
#define	BL_48		0x0e	
#define	LK_12		0x04
#define	LK_24		0x09
#define	LK_36		0x0c
#define	LK_48		0x0f



/**
 * The brief description.
 * The detail description.
 */
/*����*/
#define CMD_RESET					0X20		/*����*/
#define CMD_CONNECT					0X21		/*��λ���鿴�Ƿ��·�ɶϿ�����*/
#define	CMD_DSP_INFO				0x22		/*dsp ������Ϣ*/
#define CMD_SAVE					0X23		/*����*/

/*#define CMD_SYS_ON					0X24
#define CMD_DOWNLOADPRESET			0X25
#define CMD_DYNA					0X26
#define CMD_OTHER					0X27
#define CMD_DEVCONNECT				0X28
#define CMD_FS						0X29
#define CMD_LOCK					0X2A
*/


/*����*/
#define FUNC_VOLUME				0X00		/*����*/
#define FUNC_DELAY				0X01		/*�ӳ�*/
#define FUNC_HPF				0X02		/*��ͨ*/
//#define FUNC_LPF				0X03		/*��ͨ*/
#define FUNC_LIMIT				0X04		/*ѹ��*/
#define FUNC_PEQ				0X05		/*����*/
//#define FUNC_MIXERS				0X06		/*·��*/
//#define FUNC_MIX4CH				0X07        /*·��4��1*/
#define FUNC_MUSIC3DOP          0x08        /*3D*/
#define FUNC_SCTOP              0X09        /*��������*/
//#define FUNC_BPF                0X0A        /*��ͨ����*/
//#define FUNC_TONE               0X0B        /*����*/
#define SIGNALSOURCE            0X0c        /*�ź�Դ*/

#define FUNC_NGC                0x0d        /**/



/**
 * The brief description.
 * The detail description.
 */
enum{
	CHAIN0,
	CHAIN1
};



/**
 * The brief description.
 * The detail description.
 */
typedef struct Crossbar
{
    uint8_t in;
    uint8_t out;
    uint8_t rd;
    fp32    mix;
}Crossbar_STR;


typedef struct  
{
    VOL_OP    vol[3];                   //VOL_STR  vol;               //8
    EQOP_STR   achEQ[48];       //16 * 48    
    EQOP_STR   bchEQ[2][7];     //16 * 14
    Outdly   outDly[6];         //12 * 6
    LimiterOP_STR  limit[6];    //24 * 6    
    Music3DOp_STR  m3D[2];      //28 * 2
    SCTOP_STR    sct[2];        //104 * 2
    CHanHLPF_STR  hpf[6];       //8 * 6
    CHanHLPF_STR  lpf;       //8 * 2
    BPF_OP        bpf;
    AnaOrDigSrc_STR   ad;       //8
    Crossbar_STR    crossbar1[2][6];  //8      ���������·��
    float   outVol[6];
    char version[8];
} STR_DSP;

STR_DSP dspInfo;







#endif //G_VARIABLE_H__
