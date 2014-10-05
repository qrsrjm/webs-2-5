/**
 * @file         DSP.c
 * @brief        This is a brief description.
 * @details  This is the detail description.
 * @author       author
 * @date     2014.9.20
 * @version  A001
 * @par Copyright (c): 
 *       XXX公司
 * @par History:         
 *   version: author, date, desc\n
 */ 


//#include "I2C.h"
//#include "TAS3xxx.h"

//#include "ModulesAddr.h"
//#include "ModulesAddr_Ver2.0.h"

#include <unistd.h> //sleep close

#include "lrx.h"



/*********************************************************************************************************
** Function name:       DspMixerSet
** Descriptions:        路由控制,Crossbar_1模块
** input parameters:    in 输入通道 out 输出通道 mixer 比例值，线性比例；in和out一一对应，不能混音
in={0,1,2,3},out={0,1,2,3}
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet(uint8_t rd,uint32_t in, uint32_t out, float mixer);





/*********************************************************************************************************
** Function name:       DspMixerSet4Ch
** Descriptions:        路由控制
** input parameters:    in 输入通道 select Mix4Ch模块的索引  mixer 比例值

select 0-.Mix4Ch_11,1-.Mix4Ch_12,3D混音；2-.Mix4Ch_13,3-.Mix4Ch_14,3D开关；
4-.Mix4Ch_2,5-.Mix4Ch_10，SCT开关；6-.Mix4Ch_3，测试音源选择；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet4Ch(uint8_t rd, uint32_t select, float mixer[]);





/*********************************************************************************************************
** Function name:       DspGain
** Descriptions:        音量控制
** input parameters:    gain 音量结构体指针
**                    index =0.控制Volume_4，crossbar_3的输入端第一通道的音量，Ch =1.控制Volume_5，crossbar_3的输入端第二通道的音量，
**                    index =3.控制Volume_11，crossbar_3的输出端第一通道的音量，Ch =3.控制Volume_10，crossbar_3的输出端第二通道的音量
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
//int DspGain(VOL_STR *gain);

int DspGain(VOL_OP *gain);


/*********************************************************************************************************
** Function name:       DspOutDelay
** Descriptions:        输出通道延时控制
** input parameters:    Ch 输出通道 delay 延时结构体指针
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspOutDelay(Outdly *OutPutDly);






/*
***************************************************************************************************
**                                          DspLimiter()
**	功能描述：DRC动态范围控制。
**	参  数  ：Chn             音频通道选择
**		drc.T1,T2       起控电平
**            drc.k0,k1,k2    斜率
**            drc.O1,O2       电平偏移量
**            drc.Attack      起控时间
**            drc.Release       释放时间
**            drc.en          功能使能标志
**	返回值  ：无
***************************************************************************************************
*/

int DspLimiter(LimiterOP_STR *LimOP);




/*
***************************************************************************************************
**                                          Dsp3DMusicEn()
**	功能描述：音乐3D效果。
**	参  数  ：en
**	返回值  ：无
***************************************************************************************************
*/
int Dsp3DMusicEn(uint8 en, uint8_t Ch);


int Dsp3DMusicMix(float mixer[], uint8_t Ch );



/*********************************************************************************************************
** Function name:       Dsp3DMusicDelay
** Descriptions:        输出通道延时控制
** input parameters:    Ch 输出通道 delay 延时结构体指针
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int Dsp3DMusicDelay(DLY_STR delay, uint32_t Ch);


/*
***************************************************************************************************
**
**                                          DspMixer3DMusMultIn()
**
**
**	功能描述：3Dmusic中的路由选择多输入。
**
**	参  数  ：Ch  通道的索引 Ch={0,1}
**			LinType 连接3DMusic通道的类型，LinType=0时,3D关闭，直通开启
**			LinType=1时，延时、第一路、第二路，单个输出，LinType=2时，
**			延时和第一路、延时和第二路、第一路和第二路组合，两个一起输出，LinType=3时，延时、第一路、第二路一起输出
**			In  输出的通道类型，当LinType=1时，In=1，为延时输出，In=2，为第一路输出，In=3，为第二路输出；
**			当LinType=2时，In=1，为延时和第一路混音输出，In=2，为延时和第二路混音输出，In=3，为第一路和第二路混音输出，
**			当LinType=3时，In=1，为延时、第一路、第二路一起混音输出
**			mixer 为路由系数，暂定各路由系数都相同，以后需要再改 
**
**	返回值  ：无
**
**
***************************************************************************************************
*/
int DspMixer3DMusMultIn(uint8 Ch, uint8 LinType, uint8 In, float *mix);



/*
***************************************************************************************************
**                                          Dsp3DMusicOP()
**	功能描述：音乐3D效果。
**	参  数  ：en        Music3DOp_STR* Music3DOp1
**	返回值  ：无
***************************************************************************************************
*/
int Dsp3DMusicOP(Music3DOp_STR *Music3DOp1);



/*********************************************************************************************************
** Function name:       DspMixerSet4Ch_3DMusic
** Descriptions:        路由控制，Mix4Ch_11，Mix4Ch_12模块
** input parameters:    in Mix4Ch模块的输入端通道 select 主通道标号，select={0,1}；  mixer 比例值
**						in =0，mixer不等于0时直通开启，否则3D开启
select 0-.Mix4Ch_7,1-.Mix4Ch_9,；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet4Ch_3DMusic(uint32_t select, Mix4Ch_STR *Mix4ChNo);




/*
***************************************************************************************************
**                                         DspSctHp()
**	功能描述：椭圆逼近高通滤波器设置
**	参  数  ：hpf.Fc   	中心频率
**			  hpf.Type 	高通滤波器类型
**			  hpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspSctHp(uint8 Ch, HLPF_STR hpf);



/*********************************************************************************************************
** Function name:       DspSctBp
** Descriptions:        声音补偿中的中频段
** input parameters:    Bpf 低通结体指针，Ch 通道的索引
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspSctBp(uint8 Ch, BPF_STR bpf);



/*********************************************************************************************************
** Function name:       DspSctLp
** Descriptions:        声音补偿中的低频段
** input parameters:    hpf 低通结体指针，Ch 通道的索引
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspSctLp(uint8 Ch, HLPF_STR lpf);



/*
***************************************************************************************************
**                                          DspSCTVolDepth
**	功能描述：声音补偿中的深度。
**	参  数  ：Ch 通道数，Ch={0,1};SCTType  SCT的类型（HP，LP,BP）；VolDepth 深度
**	返回值  ：无
***************************************************************************************************
*/
int DspSCTVolDepth(uint8 Ch,uint8 SCTType,float VolDepth);



void DspSetSctDepth(uint8_t type, float VolDepth, uint8_t Ch);


/*
***************************************************************************************************
**                                          DspAGC()
**	功能描述：AGC动态范围控制。
**
**	参  数  ：SCT_ChCh             音频通道选择
**			  agc.T1,T2       起控电平
**            agc.k0,k1,k2    斜率
**            agc.O1,O2       电平偏移量
**            agc.Attack      起控时间
**            agc.Release       释放时间
**            agc.en          功能使能标志
**	返回值  ：无
***************************************************************************************************
*/
int DspAGC(uint8 SCT_Ch, DRC_STR AGC);



void DspSetSctAgc(uint8_t type, uint8_t en, fp32 T2, fp32 k2, fp32 attack, fp32 release, uint8_t Ch);


void DspSctEn(uint8_t en, uint8_t Ch);

//void DspSctEn(float mixer[], uint8_t Ch);
void DspSctMix(float mixer[], uint8_t Ch);


/*
***************************************************************************************************
**
**                                          DspSCTMixMulIn()
**
**
**	功能描述：声音补偿中的路由选择多输入。
**
**	参  数  ：Ch  通道的索引 Ch={0,1}
**			LinType 连接SCT通道的类型，LinType=1时，高、中、低音，单个输出，LinType=2时，
**			高中、高低、中低组合，两个一起混音输出，LinType=3时，高中低一起混音输出
**			In  输出的通道类型，当LinType=1时，In=0，为高音输出，In=1，为中输出，In=2，为低输出；
**			当LinType=2时，In=0，为高中输出，In=1，为高低音输出，In=2，为中低音输出，
**			当LinType=3时，In=0，为高中低音一起路由输出
**			mix 为路由系数， 
**
**	返回值  ：无
**
**
***************************************************************************************************
*/
int DspSCTMixMulIn(uint8 Ch, uint8 LinType, uint8 In, float *mix);




/*
***************************************************************************************************
**                                          DspSCTOP()
**	功能描述：声音补偿，SCT。
**	参  数  ：       SCTOP_STR* SCTOP1
**	返回值  ：无
***************************************************************************************************
*/
int DspSCTOP( SCTOP_STR *SCTOP1);






/*
***************************************************************************************************
**                                         DspACHBp_HP()
**	功能描述：椭圆逼近高通滤波器设置
**	参  数  ：hpf.Fc   	中心频率
**			  hpf.Type 	高通滤波器类型
**			  hpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**			  Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspACHBp_HP(CHanHLPF_STR *ChHP);


/*
***************************************************************************************************
**                                         DspACHBp_LP()
**	功能描述：椭圆逼近低通滤波器设置
**
**	参  数  ：hpf.Fc   	中心频率
**			  hpf.Type 	高通滤波器类型
**			  hpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**           Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspACHBp_LP(CHanHLPF_STR *ChLP);



/*********************************************************************************************************
** Function name:      
** Descriptions:        输出PEQ控制
** input parameters:    peq PEQ结构体指针，输出通道索引Ch，每个通道Eq的索引no
**						 Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

int DspACHPEQ(EQOP_STR *PEQOP);



/*********************************************************************************************************
** Function name:       DspBCHPEQ
** Descriptions:        输入PEQ控制
** input parameters:    peq PEQ结构体指针，输出通道索引Ch，每个通道Eq的索引no
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

int DspBCHPEQ(EQOP_STR *PEQOP);




/*********************************************************************************************************
** Function name:       DspAorDChanMixer()
** Descriptions:        模拟、数字通道路由控制，Crossbar_2模块
** input parameters:    Aen 模拟通道使能，当Aen=1时，模拟通道路由到此模块的输出端口，否则数字通路由输出端口
**						mixer 比例值
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspAorDChanMixer(AnaOrDigSrc_STR *AnaOrDig);



/**
* 读取输入电平
* This is a detail description.
* @outVal       输出读到的电平值 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
void VuDetect(uint8 *outVal);



/**
* 6 路输出音量设置
* This is a detail description.
* @in       输入音源【暂时不使用】
* @out     输出音源
* @gain,  输出音量 
* @par 修改日志
*      XXX于2014-9-28创建
*/
void volOutput(uint8_t in, uint8_t out, fp32 gain);


/**
* 测试信号源输出enable
* This is a detail description.
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspSignalSourceEnable();


/**
* 测试信号源输出cancel
* This is a detail description.
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspSignalSourceCancel();





/**
* 测试信号源输出选择
* This is a detail description.
* @in       输入音源
* @out     输出音源
* @total,  输出音源总数 
* @type   测试类型
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
int DspSigSourSelectOut(uint8_t in, uint8_t out, uint8_t total, uint8_t type);



/**
* 所有路由直通
* This is a detail description. 
* @par 标识符
*      保留                (测试中....)
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
void AllMixThrough();







/*********************************************************************************************************
** Function name:       DspDigChansMux()
** Descriptions:        模拟、数字通道路由控制，Mux_5,Mux_6模块
** input parameters:    uint8 DigChan    DigChan=1时，为第一路I2S通道，否则为第二路I2S通道
**						
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspDigChansMux(uint8 DigChan);







/*********************************************************************************************************
** Function name:       DspFunModInit
** Descriptions:        实现DSP各个功能模块的初始化，3D旁通，各个PEQ旁通，HP旁通，SCT旁通，音量模块
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspFunModInit(void);



void AllMixThrough();


void readAllHLpfEQ();

void testMUX();




void DapHwInit(void);




































