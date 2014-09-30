#ifndef DATA_TO_STRING____H____
#define DATA_TO_STRING____H____

#include "lrx.h"

void initDsp(STR_DSP *dspInfo);
void volToStr(VOL_OP *p, char *dest);
void achEQToStr(EQOP_STR  *achEQ, char *dest);
void bchEQToStr(EQOP_STR  p[][7], char *dest);
void outDlyToStr(Outdly *p, char *dest);
void limitToStr(LimiterOP_STR *p, char *dest);
void m3DToStr(Music3DOp_STR *p, char *dest);
void sctToStr(SCTOP_STR *p, char *dest);
void hpfToStr(CHanHLPF_STR *p, char *dest);
void lpfToStr(CHanHLPF_STR *p, char *dest);
void ADToStr(AnaOrDigSrc_STR *p, char *dest);
void crossbar1ToStr(Crossbar_STR ptr[][6], char *dest);
void outVolToStr(fp32 *p, char *dest);


#endif// DATA_TO_STRING____H____

