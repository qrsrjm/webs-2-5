#include "dataToString.h"

#include <string.h>
#include <stdio.h>

void versionToStr(char *p, char *dest)
{
    strcpy(dest,p);
    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void outVolToStr(fp32 *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"outVol%f,",*p);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void crossbar1ToStr(Crossbar_STR ptr[][6], char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    Crossbar_STR *p = ptr;
    for(i=0;i<12;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"crossbar%d,%d,%f,",p->in,p->out,p->mix);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void ADToStr(AnaOrDigSrc_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"ad%d,%f,",p->en,p->mixer);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void hlpfToStr(HLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"pf%d,%d,%d,",p->Fc,p->Type,p->en);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void bpfToStr(BPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"bf%d,%d,%d,%d,",p->Fp,p->Fs,p->Type,p->en);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void agcToStr(DRC_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"agc%f,%f,%f,%f,%d,",p->T2,p->k2,p->Attack,p->Release,p->en);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void lpfToStr(CHanHLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<1;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"hpf%d,",p->Ch);
        hlpfToStr(&(p->xpf), tmp+strlen(tmp));
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void hpfToStr(CHanHLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"hpf%d,",p->Ch);
        hlpfToStr(&(p->xpf), tmp+strlen(tmp));
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void sctToStr(SCTOP_STR *p, char *dest)
{
    char tmp[512]={0};
    int len=0;
    int i;
    for(i=0;i<2;i++,p+=1) {
        memset(tmp,0,512);

        sprintf(tmp,"SCT%d,%d,",p->Ch,p->en);

        hlpfToStr(&(p->hpf), tmp+strlen(tmp));
        agcToStr(&(p->AGChp), tmp+strlen(tmp));

        bpfToStr(&(p->bpf), tmp+strlen(tmp));
        agcToStr(&(p->AGCbp), tmp+strlen(tmp));

        hlpfToStr(&(p->lpf), tmp+strlen(tmp));
        agcToStr(&(p->AGClp), tmp+strlen(tmp));

        sprintf(tmp+strlen(tmp),"vol%f,%f,%f,%f,%f,%f,%f,",p->hVolDepth,p->bVolDepth,p->lVolDepth,p->mix[0],p->mix[1],p->mix[2],p->mix[3]);

        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}



void m3DToStr(Music3DOp_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<2;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"3d%d,%f,%d,%f,%f,%f,%f,%d,",p->Ch,p->delay.Dly,p->delay.en,p->mix[0],p->mix[1],p->mix[2],p->mix[3],p->en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void limitToStr(LimiterOP_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"limit%d,%f,%f,%f,%f,%d,",p->Ch,p->limiter.T2,p->limiter.k2,p->limiter.Attack,p->limiter.Release,p->limiter.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

void outDlyToStr(Outdly *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"outDly%d,%f,%d,",p->Ch,p->delay.Dly,p->delay.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

void eqToStr(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<1;i++)        // 1¸ö
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    printf("%s,len=%d\n",dest,strlen(dest));
}

void achEQToStr(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    //for(i=0;i<48;i++,p+=1)   //48¸ö
    for(i=0;i<1;i++)        // 1¸ö
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    //printf("%s,len=%d\n",dest,strlen(dest));
}

void bchEQToStr(EQOP_STR  p[2][7], char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    int j;
    
    for(i=0;i<2;i++)
    {
        for(j=0;j<7;j++) {
            //printf("EQ%d,%d,%f,%f,%d,%d,%d,",p[i][j].Ch,p[i][j].no,p[i][j].peq.Q,p[i][j].peq.Gain, p[i][j].peq.Fc,p[i][j].peq.Type,p[i][j].peq.en);            memset(tmp,0,64);
            sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p[i][j].Ch,p[i][j].no,p[i][j].peq.Q,p[i][j].peq.Gain, p[i][j].peq.Fc,p[i][j].peq.Type,p[i][j].peq.en);
            strcpy(dest+len,tmp);
            len += strlen(tmp);
        }

    }
    //printf("%s,len=%d\n",dest,strlen(dest));
}

void volToStr(VOL_OP *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<3;i++,p+=1)
    {
        //printf("vol%d,%f,%d,%d,",p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
        memset(tmp,0,64);
        sprintf(tmp,"vol%d,%f,%d,%d,",p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    //printf("%s,len=%d\n",dest,strlen(dest));
}


void initDsp(STR_DSP *dspInfo)
{
    int i;
    for(i=0;i<3;i++) {
        dspInfo->vol[i].vol.Gain = 2+i;
        dspInfo->vol[i].vol.Pol =0;
        dspInfo->vol[i].vol.Mute=0;
        dspInfo->vol[i].Ch=i;
    }

    for(i=0;i<48;i++) {
        dspInfo->achEQ[i].peq.Q = 1.0+i;
        dspInfo->achEQ[i].peq.Gain = 1.1+i;
        dspInfo->achEQ[i].peq.Fc = 100+i*10;
        dspInfo->achEQ[i].peq.Type = 8;
        dspInfo->achEQ[i].peq.en = 1;
        dspInfo->achEQ[i].Ch = i%5;
        dspInfo->achEQ[i].no = i%10;
    }
    
    int j;
    for(i=0;i<2;i++) {
        for(j=0;j<7;j++) {
            dspInfo->bchEQ[i][j].peq.Q = 1;
            dspInfo->bchEQ[i][j].peq.Gain = 2;
            dspInfo->bchEQ[i][j].peq.Fc = 100+i*10;
            dspInfo->bchEQ[i][j].peq.Type = 7;
            dspInfo->bchEQ[i][j].peq.en = 1;
            dspInfo->bchEQ[i][j].Ch = i;
            dspInfo->bchEQ[i][j].no = j;
            //printf("EQ%d,%d,%f,%f,%d,%d,%d,",dspInfo->bchEQ[i][j].Ch,dspInfo->bchEQ[i][j].no,dspInfo->bchEQ[i][j].peq.Q,dspInfo->bchEQ[i][j].peq.Gain, dspInfo->bchEQ[i][j].peq.Fc,dspInfo->bchEQ[i][j].peq.Type,dspInfo->bchEQ[i][j].peq.en);
        }
    }

    for(i=0;i<6;i++) {
        dspInfo->outDly[i].delay.Dly = i;
        dspInfo->outDly[i].delay.en = 1;
        dspInfo->outDly[i].Ch = i;
    }

    for(i=0;i<6;i++) {
        dspInfo->limit[i].limiter.T2 = i;
        dspInfo->limit[i].limiter.k2 = i;
        dspInfo->limit[i].limiter.Attack = 1;
        dspInfo->limit[i].limiter.Release = 1;
        dspInfo->limit[i].limiter.en = 1;
        dspInfo->limit[i].Ch = i;
    }

    for(i=0;i<2;i++) {
        dspInfo->m3D[i].delay.Dly=12;
        dspInfo->m3D[i].delay.en =1;
        dspInfo->m3D[i].mix[0] =1;
        dspInfo->m3D[i].mix[1] =2;
        dspInfo->m3D[i].mix[2] =3;
        dspInfo->m3D[i].mix[3] =4;
        dspInfo->m3D[i].en = 1;
        dspInfo->m3D[i].Ch = i;
    }

    for(i=0;i<2;i++) {
        dspInfo->sct[i].hpf.Fc = i*1000;
        dspInfo->sct[i].hpf.Type = i;
        dspInfo->sct[i].hpf.en = 1;
        dspInfo->sct[i].AGChp.T2 = i+1;
        dspInfo->sct[i].AGChp.k2 = i+1;
        dspInfo->sct[i].AGChp.Attack = 1;
        dspInfo->sct[i].AGChp.Release = 1;
        dspInfo->sct[i].AGChp.en = 1;

        dspInfo->sct[i].bpf.Fp = 1000;
        dspInfo->sct[i].bpf.Fs = 2000;
        dspInfo->sct[i].bpf.Type = 1;
        dspInfo->sct[i].bpf.en = 1;
        dspInfo->sct[i].AGCbp.T2 = i+2;
        dspInfo->sct[i].AGCbp.k2 = i+2;
        dspInfo->sct[i].AGCbp.Attack = 2;
        dspInfo->sct[i].AGCbp.Release = 2;
        dspInfo->sct[i].AGCbp.en = 1;

        dspInfo->sct[i].lpf.Fc = i*2000;
        dspInfo->sct[i].lpf.Type = i+1;
        dspInfo->sct[i].lpf.en = 1;
        dspInfo->sct[i].AGClp.T2 = i+3;
        dspInfo->sct[i].AGClp.k2 = i+3;
        dspInfo->sct[i].AGClp.Attack = 3;
        dspInfo->sct[i].AGClp.Release = 3;
        dspInfo->sct[i].AGClp.en = 1;

        dspInfo->sct[i].hVolDepth = 23;
        dspInfo->sct[i].bVolDepth = 13;
        dspInfo->sct[i].lVolDepth = 10;
        dspInfo->sct[i].mix[0] = 1;
        dspInfo->sct[i].mix[1] = 1;
        dspInfo->sct[i].mix[2] = 1;
        dspInfo->sct[i].mix[3] = 1;
        dspInfo->sct[i].en = 1;
        dspInfo->sct[i].Ch = i;
    }

    for(i=0;i<6;i++) {
        dspInfo->hpf[i].xpf.Fc = i*100+500;
        dspInfo->hpf[i].xpf.Type = i;
        dspInfo->hpf[i].xpf.en = 1;
        dspInfo->hpf[i].Ch = i;
    }

    for(i=0;i<1;i++) {
        dspInfo->lpf.xpf.Fc = i*100+500;
        dspInfo->lpf.xpf.Type = i+1;
        dspInfo->lpf.xpf.en = 1;
        dspInfo->lpf.Ch = 5;
    }

    dspInfo->ad.en = 1;
    dspInfo->ad.mixer = 1.1;

    for(i=0;i<2;i++)
    for(j=0;j<6;j++) {
        dspInfo->crossbar1[i][j].in = i;
        dspInfo->crossbar1[i][j].out = j;
        dspInfo->crossbar1[i][j].rd = 1;
        dspInfo->crossbar1[i][j].mix = 1.5;
    }


    for(i=0;i<6;i++){
        dspInfo->outVol[i] = i*2+1;
    }
}



#if 0 //TEST_STRING
int main()
{
    char *dest = (char*)malloc(1024*4);
    memset(&dspInfo,0,sizeof(dspInfo));

    initDsp(&dspInfo);
    volToStr(dspInfo.vol,dest);
    //achEQToStr(dspInfo.achEQ, dest+strlen(dest));
    //bchEQToStr(dspInfo.bchEQ, dest+strlen(dest));
    //outDlyToStr(dspInfo.outDly, dest+strlen(dest));
    //limitToStr(dspInfo.limit, dest+strlen(dest));
    //m3DToStr(dspInfo.m3D, dest+strlen(dest));
    //sctToStr(dspInfo.sct,  dest+strlen(dest));
    //hpfToStr(dspInfo.hpf, dest+strlen(dest));
    //lpfToStr(&(dspInfo.lpf), dest+strlen(dest));
    //ADToStr(&(dspInfo.ad), dest+strlen(dest));
    //crossbar1ToStr(&(dspInfo.crossbar1), dest+strlen(dest));
    outVolToStr(dspInfo.outVol, dest+strlen(dest));

    printf("\n%s,len=%d\n",dest,strlen(dest));

    return 0;
}

#endif










































