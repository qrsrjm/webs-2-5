#include "dataToString.h"


void volToStr(char *dest, VOL_OP *p)
{
    char tmp[64]={0},dest[64]={0};
    int len=0;
    for(int i=0;i<2;i++)
    {
        memset(tmp,0,64);
        sprintf(tmp,"vol%d,%f,%d,%d,",p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
        strcpy(dest+len,tmp);
        len = strlen(tmp);
    }

    printf("%s,len=%d\n",dest,strlen(dest));
}


void eqToString(char *dest, STR_DSP *dspInfo)
{
    EQOP_STR *p = &(dspInfo->achEQ);
    char *tmp = (char*)malloc(64);

    sprintf(tmp,"EQ%d,"
            "Q=%f,"
            "G=%f,"
            "F=%d,"
            "T=%d,"
            "e=%d,"
            "C=%d,"
            "n=%d"
            ,1,p->peq.Q,p->peq.Gain,p->peq.Fc,p->peq.Type,p->peq.en,p->Ch,p->no);

    printf("\n\n%s,%d\n",tmp,strlen(tmp));
}


















