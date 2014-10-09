#ifndef DSPARCHIVE____H___
#define DSPARCHIVE____H___

#include "lrx.h"


int addName(char Aname[NAME_CNT][NAME_LEN], char *name);

int delName(char Aname[NAME_CNT][NAME_LEN], char *name);

int findName(char Aname[NAME_CNT][NAME_LEN], char *name);

void showNameToStr(char Aname[NAME_CNT][NAME_LEN], char *str);

void showName(char Aname[NAME_CNT][NAME_LEN]);

int readMacInfo(MACINFO *mac);

int readNameList(char Aname[NAME_CNT][NAME_LEN]);

int changeStartName(MACINFO *mac, char *name);


#endif //DSPARCHIVE____H___
