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
**	文件名	：LRX.h
**	
**	程序员	：陈家承
**
**	日　期  ：2009年5月9日
**
**	文件描述：机器型号的预定义头文件，不同的参数对应不同型号的处理器。
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
	uint8_t  	type;						///< 帧起始
	uint8_t		Addr;
	uint8_t		rw;
	uint8_t   	Length[2];
	uint8_t		DBuf[0];					///< 接收数据缓冲区指针
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
*   音量
*/
typedef struct volOp
{
	VOL_STR vol;
	uint8_t Ch;			/**<输出通道索引Ch*/
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
	uint8_t en;///en=1开启EQ，En=0，bypassEQ
} EQ_STR;

// 均衡
typedef struct EQOP
{
	EQ_STR peq;			/**<peq PEQ结构体指针*/
	uint8_t Ch;			/**<输出通道索引Ch*/
	uint8_t no;			/**<每个通道Eq的索引no*/
	uint8_t reserved1;  ///< 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
}EQOP_STR;				/**<PEQ操作结构体*/

//
typedef struct tonestr
{
	int32_t Fc1;
	int32_t Fc2;
	fp32  Gain;
	fp32  Q;
	uint8_t en;
	uint8_t reserved1;  ///< 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
} TONE_STR;

/**
 * The brief description.
 * The detail description.
 */
typedef struct dlystr
{
	fp32  Dly;
	uint8_t en;
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
} DLY_STR;

// 延迟
typedef struct Outdlystr
{
	DLY_STR delay;
	uint8 Ch;     /**<输出通道索引，Ch={0,1}*/
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
}Outdly;             /**<输出通道延时结构体*/

typedef struct hlpfstr
{
	uint16_t Fc;
	int8_t  Type;
	uint8_t en;
} HLPF_STR;

// 高低通
typedef struct CHLpf
{
	HLPF_STR xpf;
	uint8 Ch;      /**<输出通道索引，Ch={0,1,2,3,4,5}*/
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
}CHanHLPF_STR;    /**<主通道高通结构体*/


typedef struct bpfstr
{
	uint16_t Fp;
	uint16_t Fs;
	int8_t  Type;
	uint8_t en;
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
} BPF_STR;

typedef struct bpfstrOp
{
	uint16_t Fp;
	uint16_t Fs;
	int8_t  Type;
	uint8_t en;
	uint8_t Ch;  // 数据字节对齐1
	uint8_t reserved1;  // 数据字节对齐2
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
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
} DRC_STR;

//压限
typedef struct LimiterOP
{
	DRC_STR limiter;
	uint8 Ch;
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
}LimiterOP_STR;



typedef struct mixstr
{
	float fVal;     ///mixer
	uint8_t Start;  ///in
	uint8_t End;    ///out
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
} MIX_STR;


typedef struct Mix4Ch
{
	float mix;
	uint8_t in;
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
} Mix4Ch_STR;

/**
 *  3D
 */
typedef struct Music3DOp
{
	DLY_STR delay;//延时
	//Mix4Ch_STR *Mix4ChNo;//3Dmusic 模型中的混音模块操作；不用了，可删除
	float mix[4];//多进一出路由系数,最新
	uint8 en;
	uint8_t Ch;//通道索引Ch={0,1}
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
} Music3DOp_STR;



/**
 * 声音补偿 
 *  LinType: 
 *<单独输出>0x10:高音输出,0x11:中输出,0x12:低输出  
 *< 2个组合输出>0x20:高中输出,0x21:高低音输出,0x22 :中低音输出 
 *<3个混音输出>0x30:高中低音一起路由输出
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
	float mix[3];//多进一出路由系数,最新
	uint8_t en;//使能，en=1,en=0关闭
	uint8_t Ch;//通道索引Ch={0,1}
	uint8_t Type;//高中低的类型，Type ：0--SCTHP,1--SCTBP,2--SCTLP
	uint8_t LinType;  // 输出方式<0>单独输出<1>2个组合输出<2>3个混音输出
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
	float mix[4];//多进一出路由系数,最新
	uint8_t en;//使能，en=1,en=0关闭
	uint8_t Ch;//通道索引Ch={0,1}
}SCTOP_STR;

#endif

// 音源选择
typedef struct AnaOrDigSource
{
	float mixer;    /// 0-3  <1>
	uint8 en;     /**<en 模拟通路使能，若Aen=1，则模拟音源有效；Aen=0则数字音源有效，Aen={0,1}*/
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
	uint8_t reserved3;  // 数据字节对齐3
}AnaOrDigSrc_STR;

//信号源
typedef struct SourceSig
{
	VOL_STR gain;    /**<VOL_STR* gain 测试信号源的音量控制，*/
	float mixer;      /**<路由比例，相同的系数*/
	uint8 en;         /**<en 测试信号使能，Aen=1时，使能，Aen=0时，禁止*/
	uint8 SourceType;  /**<SourceType 信号类型选择，SourceType={0,1,2}*/
	uint8_t reserved1;  // 数据字节对齐1
	uint8_t reserved2;  // 数据字节对齐2
}SourceSignal_STR;    /**<最新加的测试信号源结构体*/



//高低通【带通】滤波器类型[Type] 的预定义
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
/*命令*/
#define CMD_RESET					0X20		/*重启*/
#define CMD_CONNECT					0X21		/*上位机查看是否和路由断开连接*/
#define	CMD_DSP_INFO				0x22		/*dsp 所有信息*/
#define CMD_SAVE					0X23		/*保存*/

/*#define CMD_SYS_ON					0X24
#define CMD_DOWNLOADPRESET			0X25
#define CMD_DYNA					0X26
#define CMD_OTHER					0X27
#define CMD_DEVCONNECT				0X28
#define CMD_FS						0X29
#define CMD_LOCK					0X2A
*/


/*功能*/
#define FUNC_VOLUME				0X00		/*音量*/
#define FUNC_DELAY				0X01		/*延迟*/
#define FUNC_HPF				0X02		/*高通*/
//#define FUNC_LPF				0X03		/*低通*/
#define FUNC_LIMIT				0X04		/*压限*/
#define FUNC_PEQ				0X05		/*均衡*/
//#define FUNC_MIXERS				0X06		/*路由*/
//#define FUNC_MIX4CH				0X07        /*路由4进1*/
#define FUNC_MUSIC3DOP          0x08        /*3D*/
#define FUNC_SCTOP              0X09        /*声音补偿*/
//#define FUNC_BPF                0X0A        /*带通中音*/
//#define FUNC_TONE               0X0B        /*音调*/
#define SIGNALSOURCE            0X0c        /*信号源*/

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
    Crossbar_STR    crossbar1[2][6];  //8      总输入输出路由
    float   outVol[6];
    char version[8];
} STR_DSP;



#define NAME_CNT   11
#define NAME_LEN   20

///机器信息
typedef struct MachineInformation
{
    char name[NAME_LEN];  //<启动存档名
    int sv;               //<软件版本  
    int hv;               //<硬件版本
    int SerialNumber;     //<序列号  
    int date;             //< 日期 
}MACINFO;

typedef struct Machine
{
    MACINFO macInfo;
    char archiveName[NAME_CNT][NAME_LEN];  //<存档名
    STR_DSP *readDspInfo;
}MACHINE;


#define MACINF_ADDR     0
#define NAME_ADDRX(x)   (sizeof(MACINFO) + sizeof(char)*NAME_LEN*(x))
#define DATA_ADDRX(x)   (sizeof(MACINFO) + sizeof(char)*NAME_CNT*NAME_LEN + sizeof(STR_DSP)*(x))


STR_DSP dspInfo;
STR_DSP *rDspInfo;

MACHINE machine;


#endif //G_VARIABLE_H__
