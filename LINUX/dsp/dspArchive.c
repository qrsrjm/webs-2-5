#include "dspArchive.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int addName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
    if (name == NULL) return -1;
    if (strlen(name)> 19) return -2;
	for(i=0;i<NAME_CNT;i++) {
		if (Aname[i][0] == '\0') {
			printf("is null. i=%d\n",i);
			strcpy(Aname[i],name);
			return i;
		} 
	}	
	return -1;
}

int delName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
    if (name == NULL) return -1;
	for(i=0;i<NAME_CNT;i++) {
		if (0 == strcmp(Aname[i],name)) {
			memset(Aname[i],0,NAME_LEN);
		}
	}
    return 0;
}


int findName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
	if (Aname[0][0] == '\0') return -2;
	if (name == NULL) return -3;
	for(i=0;i<NAME_CNT;i++) {
		if (0 == strcmp(Aname[i],name)) {
			return i;
		}
	}
	return -1;
}


void showNameToStr(char Aname[NAME_CNT][NAME_LEN], char *str)
{	
	char tmp[NAME_LEN]={0};
	int i,len=0;
	for(i=0;i<NAME_CNT;i++) {
		if (Aname[i][0] == '\0') continue;
		sprintf(tmp,"%s,",Aname[i]);
		strcpy(str+len,tmp);
		len += strlen(tmp);
	}
	char *p = strrchr(str,',');
	*p = '\0';
}

int nameToStr(char Aname[NAME_CNT][NAME_LEN], char *str)
{	
	if (str == NULL) return -1;
    memset(str,0,NAME_CNT*NAME_LEN);
    memcpy(str,Aname,NAME_CNT*NAME_LEN-1);
    str[NAME_CNT*NAME_LEN-1] = '\0';
    printf("-->%s\n",str);
    return 0;
}


void showName(char Aname[NAME_CNT][NAME_LEN])
{
	int i;
	for(i=0;i<NAME_CNT;i++) {
		printf("%s\n",Aname[i]);
	}
}


int readMacInfo(MACINFO *mac)
{
	char tmp[36]={0};
	flash_read_archive(tmp, MACINF_ADDR, sizeof(tmp));
	if (tmp[0]=='\0') {
		flash_write_archive((char*)mac, MACINF_ADDR, sizeof(MACINFO));
		//for(i=0;i<NAME_CNT;i++)
		//	flash_write_archive(Aname[i], sizeof(MACINFO)+i*NAME_LEN, sizeof(char)*NAME_LEN);	
		//flash_write_archive((char*)&dsp, DATA_ADDR, sizeof(DSP));	
		printf("not have start name.\n");
		return -1;
	} else {
		memcpy(mac,tmp,sizeof(MACINFO));
	}
	return 0;
}


int readNameList(char Aname[NAME_CNT][NAME_LEN])
{
	char tmp[NAME_CNT*NAME_LEN]={0};
	flash_read_archive(tmp, NAME_ADDRX(0), sizeof(tmp));
	if (tmp[0]=='\0') {
		printf("not have name list.\n");
		return -1;
	} else {
		memcpy(Aname,tmp,NAME_LEN*NAME_CNT);
	}
	return 0;
}


int changeStartName(MACINFO *mac, char *name)
{
	if (name == NULL || strlen(name)>19) return -1;
	strncpy(mac->name,name,19);
    mac->name[19]='\0';
	flash_write_archive((char*)mac, MACINF_ADDR, sizeof(MACINFO));
}







