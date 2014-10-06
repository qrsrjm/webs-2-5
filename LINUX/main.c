/*
 * main.c -- Main program for the GoAhead WebServer (LINUX version)
 *
 * Copyright (c) GoAhead Software Inc., 1995-2010. All Rights Reserved.
 *
 * See the file "license.txt" for usage and redistribution license requirements
 *
 */

/******************************** Description *********************************/

/*
 *	Main program for for the GoAhead WebServer.
 */

/********************************* Includes ***********************************/

#include	"../uemf.h"
#include	"../wsIntrn.h"
#include	<signal.h>
#include	<unistd.h>
#include	<sys/types.h>

#ifdef WEBS_SSL_SUPPORT
#include	"../websSSL.h"
#endif

#ifdef USER_MANAGEMENT_SUPPORT
#include	"../um.h"
void	formDefineUserMgmt(void);
#endif


/** add by qmd  2014.9.20  */
#include "dsp/DSP.h"
#include "dsp/dataToString.h"

STR_DSP *rDspInfo = NULL;

/*********************************** Locals ***********************************/
/*
 *	Change configuration here
 */

static char_t		*rootWeb = T("www");			/* Root web directory */
static char_t		*demoWeb = T("wwwdemo");		/* Root web directory */
static char_t		*password = T("");				/* Security password */
static int			port = WEBS_DEFAULT_PORT;		/* Server port */
static int			retries = 5;					/* Server port retries */
static int			finished = 0;					/* Finished flag */

/****************************** Forward Declarations **************************/

static int 	initWebs(int demo);
static int	aspTest(int eid, webs_t wp, int argc, char_t **argv);
static void formTest(webs_t wp, char_t *path, char_t *query);
static void formUploadFileTest(webs_t wp, char_t *path, char_t *query); // add by gyr 2011.10.15
static int  websHomePageHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,
				int arg, char_t *url, char_t *path, char_t *query);
static void	sigintHandler(int);
#ifdef B_STATS
static void printMemStats(int handle, char_t *fmt, ...);
static void memLeaks();
#endif


static int	aspTest2(int eid, webs_t wp, int argc, char_t **argv);

static int	aspVol(int eid, webs_t wp, int argc, char_t **argv);

static int aspGetVersion(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetOutVol(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetOutMix(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetAd(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetLpf(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetHpf(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetSct(int eid, webs_t wp, int argc, char_t **argv);
static int aspGet3D(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetLimit(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetOutDly(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetAchEQ(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetBchEQ(int eid, webs_t wp, int argc, char_t **argv);
static int aspGetInputVol(int eid, webs_t wp, int argc, char_t **argv);
static int aspVuDetect(int eid, webs_t wp, int argc, char_t **argv);



static void formDlownload(webs_t wp, char_t *path, char_t *query);
static void formACHEQ(webs_t wp, char_t *path, char_t *query);
static void formBCHEQ(webs_t wp, char_t *path, char_t *query);
static void formHPF(webs_t wp, char_t *path, char_t *query);
static void formLPF(webs_t wp, char_t *path, char_t *query);
static void formBPF(webs_t wp, char_t *path, char_t *query);

static void formLIMT(webs_t wp, char_t *path, char_t *query);
static void formDelay(webs_t wp, char_t *path, char_t *query);
static void formVol(webs_t wp, char_t *path, char_t *query);
static void form3DDelay(webs_t wp, char_t *path, char_t *query);
static void form3DEn(webs_t wp, char_t *path, char_t *query);
static void form3DMixer(webs_t wp, char_t *path, char_t *query);
static void formSctHpf(webs_t wp, char_t *path, char_t *query);
static void formVolDepth(webs_t wp, char_t *path, char_t *query);
static void formAGC(webs_t wp, char_t *path, char_t *query);
static void formSctBpf(webs_t wp, char_t *path, char_t *query);
static void formSctLpf(webs_t wp, char_t *path, char_t *query);
static void formSctMixer(webs_t wp, char_t *path, char_t *query);
static void formAD(webs_t wp, char_t *path, char_t *query);
static void formSigSourSelectOut(webs_t wp, char_t *path, char_t *query);
static void formSSCancel(webs_t wp, char_t *path, char_t *query);
static void formSSEnable(webs_t wp, char_t *path, char_t *query);
static void formCrossbar1(webs_t wp, char_t *path, char_t *query);
static void formOutVol(webs_t wp, char_t *path, char_t *query);
static void formVuDetect(webs_t wp, char_t *path, char_t *query);
static void formSave(webs_t wp, char_t *path, char_t *query);
static void formRead(webs_t wp, char_t *path, char_t *query);
static void formShowInfo(webs_t wp, char_t *path, char_t *query);
static void formAllByPass(webs_t wp, char_t *path, char_t *query);

void repACHEQ(EQOP_STR *p);
void repBCHEQ(EQOP_STR *p);
void repVol(VOL_OP *p); //void repVol(VOL_STR *p);
void repOutDly(Outdly *p);
void repLimit(LimiterOP_STR *p);
void rep3DDly(unsigned char Ch, DLY_STR *p);
void rep3DMix(unsigned char Ch, float mixer[4]);
void rep3DEn(unsigned char Ch, unsigned char en);
void repSctHLpf(unsigned char Ch, unsigned char hl,HLPF_STR *p);
void repSctBpf(unsigned char Ch, BPF_STR *p);
void repSctAgc(unsigned char Ch, unsigned char hbl, DRC_STR *p);
void repSctDepth(unsigned char Ch, unsigned char hbl, float depth);
void repSctMix(unsigned char Ch, float mixer[4]);
void repHPF(CHanHLPF_STR *p);void repLPF(CHanHLPF_STR *p);
void repAD(AnaOrDigSrc_STR *p);
void repCrossBar(Crossbar_STR *p);
void repOutVol(uint8_t out, fp32 vol);
void repSctEn(unsigned char Ch, uint8_t en);
void repBPF(BPF_STR *p, uint8 Ch);

static void firmwareDownload();


/*********************************** Code *************************************/
/*
 *	Main -- entry point from LINUX
 */

int main(int argc, char** argv)
{
	int i, demo = 0;

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-demo") == 0) {
			demo++;
		}
	}
    //add qmd 2014.9.30
    #if 1 //test_info
    rDspInfo = (STR_DSP*)malloc(sizeof(STR_DSP));
    #else
    rDspInfo = &dspInfo;
    #endif
/*
*    2014.10.6
*/
    firmwareDownload();
    
/*
 *	Initialize the memory allocator. Allow use of malloc and start
 *	with a 60K heap.  For each page request approx 8KB is allocated.
 *	60KB allows for several concurrent page requests.  If more space
 *	is required, malloc will be used for the overflow.
 */
	bopen(NULL, (60 * 1024), B_USE_MALLOC);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, sigintHandler);
	signal(SIGTERM, sigintHandler);

/*
 *	Initialize the web server
 */
	if (initWebs(demo) < 0) {
		printf("initWebs error.\n");	// added by gyr 2011.09.17
		return -1;
	}

#ifdef WEBS_SSL_SUPPORT
	websSSLOpen();
/*	websRequireSSL("/"); */	/* Require all files be served via https */
#endif

/*
 *	Basic event loop. SocketReady returns true when a socket is ready for
 *	service. SocketSelect will block until an event occurs. SocketProcess
 *	will actually do the servicing.
 */
	finished = 0;
	while (!finished) {
		if (socketReady(-1) || socketSelect(-1, 1000)) {
			socketProcess(-1);
		}
		websCgiCleanup();
		emfSchedProcess();
	}

#ifdef WEBS_SSL_SUPPORT
	websSSLClose();
#endif

#ifdef USER_MANAGEMENT_SUPPORT
	umClose();
#endif

/*
 *	Close the socket module, report memory leaks and close the memory allocator
 */
	websCloseServer();
	socketClose();
#ifdef B_STATS
	memLeaks();
#endif
	bclose();

	return 0;
}

/*
 *	Exit cleanly on interrupt
 */
static void sigintHandler(int unused)
{
	finished = 1;
}

/******************************************************************************/
/*
 *	Initialize the web server.
 */

static int initWebs(int demo)
{
	struct hostent	*hp;
	struct in_addr	intaddr;
	char			host[128], dir[128], webdir[128];
	char			*cp;
	char_t			wbuf[128];

/*
 *	Initialize the socket subsystem
 */
	socketOpen();

#ifdef USER_MANAGEMENT_SUPPORT
/*
 *	Initialize the User Management database
 */
	umOpen();
	umRestore(T("umconfig.txt"));
#endif

/*
 *	Define the local Ip address, host name, default home page and the
 *	root web directory.
 */

#if 1
 	// del by gyr 2011.09.17
	if (gethostname(host, sizeof(host)) < 0) {
		error(E_L, E_LOG, T("Can't get hostname"));
		printf("initWebs::Can't get hostname.\n");		// added by gyr 2011.09.17
		return -1;
	}
	if ((hp = gethostbyname(host)) == NULL) {
		error(E_L, E_LOG, T("Can't get host address"));
		printf("initWebs::Can't get hostname...\n");	// added by gyr 2011.09.17
		return -1;
	}
	memcpy((char *) &intaddr, (char *) hp->h_addr_list[0],
		(size_t) hp->h_length);
#else
	intaddr.s_addr = inet_addr(T("10.10.10.254"));		// added by gyr 2011.09.17
#endif
/*
 *	Set ../web as the root web. Modify this to suit your needs
 *	A "-demo" option to the command line will set a webdemo root
 */
	getcwd(dir, sizeof(dir));// Get the name of the current working directory, note | gyr 2011.09.17
	if ((cp = strrchr(dir, '/'))) {// 查找字符在指定字符串中从后面开始的第一次出现的位置，
		*cp = '\0';					// 如果成功，则返回指向该位置的指针，如果失败，则返回 false。
	}
	if (demo) {
		sprintf(webdir, "%s/%s", dir, demoWeb);
	} else {
		sprintf(webdir, "%s/%s", dir, rootWeb);
	}

/*
 *	Configure the web server options before opening the web server
 */
	websSetDefaultDir(webdir);
	cp = inet_ntoa(intaddr);
	ascToUni(wbuf, cp, min(strlen(cp) + 1, sizeof(wbuf)));
	websSetIpaddr(wbuf);
	ascToUni(wbuf, host, min(strlen(host) + 1, sizeof(wbuf)));
	websSetHost(wbuf);

/*
 *	Configure the web server options before opening the web server
 */
	websSetDefaultPage(T("default.asp"));
	websSetPassword(password);

/*
 *	Open the web server on the given port. If that port is taken, try
 *	the next sequential port for up to "retries" attempts.
 */
	websOpenServer(port, retries);

/*
 * 	First create the URL handlers. Note: handlers are called in sorted order
 *	with the longest path handler examined first. Here we define the security
 *	handler, forms handler and the default web page handler.
 */
	websUrlHandlerDefine(T(""), NULL, 0, websSecurityHandler,
		WEBS_HANDLER_FIRST);
	websUrlHandlerDefine(T("/goform"), NULL, 0, websFormHandler, 0);
	websUrlHandlerDefine(T("/cgi-bin"), NULL, 0, websCgiHandler, 0);
	websUrlHandlerDefine(T(""), NULL, 0, websDefaultHandler,
		WEBS_HANDLER_LAST);

/*
 *	Now define two test procedures. Replace these with your application
 *	relevant ASP script procedures and form functions.
 */
    websAspDefine(T("aspTest2"), aspTest2);

	websAspDefine(T("aspTest"), aspTest);
	websFormDefine(T("formTest"), formTest);
	websFormDefine(T("formUploadFileTest"), formUploadFileTest);// add by gyr 2011.10.15


	websAspDefine(T("aspVol"), aspVol);
    
    websAspDefine(T("aspGetInputVol"), aspGetInputVol);
    websAspDefine(T("aspGetBchEQ"), aspGetBchEQ);
    websAspDefine(T("aspGetAchEQ"), aspGetAchEQ);
    websAspDefine(T("aspGetOutDly"), aspGetOutDly);
    websAspDefine(T("aspGetLimit"), aspGetLimit);
    websAspDefine(T("aspGet3D"), aspGet3D);
    websAspDefine(T("aspGetSct"), aspGetSct);
    websAspDefine(T("aspGetHpf"), aspGetHpf);
    websAspDefine(T("aspGetLpf"), aspGetLpf);
    websAspDefine(T("aspGetAd"), aspGetAd);
    websAspDefine(T("aspGetOutMix"), aspGetOutMix);
    websAspDefine(T("aspGetOutVol"), aspGetOutVol);
    websAspDefine(T("aspGetVersion"), aspGetVersion);

	websFormDefine(T("formDlownload"), formDlownload);   
	websFormDefine(T("formACHEQ"), formACHEQ);
	websFormDefine(T("formBCHEQ"), formBCHEQ); 
	websFormDefine(T("formHPF"), formHPF);   
	websFormDefine(T("formLPF"), formLPF); 
	websFormDefine(T("formBPF"), formBPF); 
	websFormDefine(T("formLIMT"), formLIMT);
	websFormDefine(T("formDelay"), formDelay);
	websFormDefine(T("formVol"), formVol);
	websFormDefine(T("form3DDelay"), form3DDelay);
	websFormDefine(T("form3DEn"), form3DEn);
	websFormDefine(T("form3DMixer"), form3DMixer);
	websFormDefine(T("formSctHpf"), formSctHpf);
	websFormDefine(T("formVolDepth"), formVolDepth);
	websFormDefine(T("formAGC"), formAGC);
	websFormDefine(T("formSctBpf"), formSctBpf);
	websFormDefine(T("formSctLpf"), formSctLpf);
	websFormDefine(T("formSctMixer"), formSctMixer);
	websFormDefine(T("formAD"), formAD);
	websFormDefine(T("formSigSourSelectOut"), formSigSourSelectOut);
    websFormDefine(T("formSSEnable"), formSSEnable);
    websFormDefine(T("formSSCancel"), formSSCancel);
    websFormDefine(T("formOutVol"), formOutVol);
	websFormDefine(T("formCrossbar1"), formCrossbar1);
	websFormDefine(T("formVuDetect"), formVuDetect);
	websFormDefine(T("formSave"), formSave);
	websFormDefine(T("formRead"), formRead);
    websFormDefine(T("formShowInfo"), formShowInfo);
    websFormDefine(T("formAllByPass"), formAllByPass);

	
/*
 *	Create the Form handlers for the User Management pages
 */
#ifdef USER_MANAGEMENT_SUPPORT
	formDefineUserMgmt();
#endif

/*
 *	Create a handler for the default home page
 */
	websUrlHandlerDefine(T("/"), NULL, 0, websHomePageHandler, 0);

	return 0;
}

/******************************************************************************/
/*
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */

static int aspTest(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name, *address;

	if (ejArgs(argc, argv, T("%s %s"), &name, &address) < 2) {
		websError(wp, 400, T("Insufficient args\n"));
		return -1;
	}
	return websWrite(wp, T("Name: %s, Address %s"), name, address);
}


static int	aspTest2(int eid, webs_t wp, int argc, char_t **argv)
{
    char *dest = (char*)malloc(1024*4);


    return websWrite(wp, T("%s"),dest);
}


/******************************************************************************/
/*   by  qmd  2014.9.19
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspVol(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;
    
    if (ejArgs(argc, argv, T("%d"), &Gain) < 1) {
		websError(wp, 400, T("Insufficient args\n"));
		return -1;
	}
    
    printf("%s>%d\n",__FUNCTION__,Gain);
	return websWrite(wp, T("Vol=%d"),10);
}



/******************************************************************************/
/*	 by  qmd  2014.9.19
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspVuDetect(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
		websError(wp, 400, T("Insufficient args\n"));
		return -1;
	}
	return websWrite(wp, T("vol: %s, Gain %d"), name, Gain);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetInputVol(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
    char dest[64];
    memset(dest,0,64);
    volToStr(rDspInfo->vol, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("vol: %s"), dest);
}



/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetBchEQ(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[512]={0};
    memset(dest,0,512);
    for(i=0;i<2;i++)
    for(j=0;j<7;j++)
        eqToStr(&(rDspInfo->bchEQ[i][j]), dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("bcheq: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetAchEQ(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[1024*2]={0};
    memset(dest,0,512*4);
    for(i=0;i<48;i++)
        eqToStr(&(rDspInfo->achEQ[i]), dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("acheq: %s"), dest);
}


/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetOutDly(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[128]={0};
    memset(dest,0,128);
    outDlyToStr(rDspInfo->outDly, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("outdly: %s"), dest);
}


/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetLimit(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[280]={0};
    memset(dest,0,280);
    limitToStr(rDspInfo->limit, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("limit: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGet3D(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[120]={0};
    memset(dest,0,120);
    m3DToStr(rDspInfo->m3D, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("3d: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetSct(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[512]={0};
    memset(dest,0,512);
    sctToStr(rDspInfo->sct, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("sct: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetHpf(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[100]={0};
    memset(dest,0,100);
    hpfToStr(rDspInfo->hpf, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("hpf: %s"), dest);
}


/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetLpf(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[100]={0};
    memset(dest,0,100);
    lpfToStr(&(rDspInfo->lpf), dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("lpf: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetAd(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[32]={0};
    memset(dest,0,32);
    ADToStr(&(rDspInfo->ad), dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("ad: %s"), dest);
}


/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetOutMix(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[512]={0};
    memset(dest,0,512);
    crossbar1ToStr(rDspInfo->crossbar1, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("outMix: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetOutVol(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[100]={0};
    memset(dest,0,100);
    outVolToStr(rDspInfo->outVol, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("outVol: %s"), dest);
}

/******************************************************************************/
/*	 by  qmd  2014.9.30
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to
 *	"localhost/asp.asp" to test.
 */
static int aspGetVersion(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name;
	int Gain;

	//if (ejArgs(argc, argv, T("%s %d"), &name, &Gain) < 2) {
	//	websError(wp, 400, T("Insufficient args\n"));
	//	return -1;
	//}
	int i,j;
    char dest[8]={0};
    memset(dest,0,8);
    strcpy(rDspInfo->version,"1.0.21");
    versionToStr(rDspInfo->version, dest);

    printf("%s>\n",__FUNCTION__);
    
	return websWrite(wp, T("version: %s"), dest);
}


/******************************************************************************/
/*
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */

static void formTest(webs_t wp, char_t *path, char_t *query)
{
	char_t	*name, *address;
	char_t  *Q, *Gain;

	name = websGetVar(wp, T("name"), T("Joe Smith"));
	address = websGetVar(wp, T("address"), T("1212 Milky Way Ave."));

	Q = websGetVar(wp, T("Q"), T("1.0"));
	Gain = websGetVar(wp, T("Gain"), T("1.0"));	

	websHeader(wp);
	websWrite(wp, T("<body><h2>Name: %s, Address: %s</h2>\n"), name, address);
	
	websWrite(wp, T("<body><h2>Q: %s, Gain: %s</h2>\n"), Q, Gain);
	
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*   by qmd 2014.10.6
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void firmwareDownload()
{
    DapHwInit();
    DspAllByPass();
    printf("firmwareDownload finish\n");
}

/******************************************************************************/
/*   by qmd 2014.10.6
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void initArchive()
{
    char_t  *fileName = "default.txt";
    //fileName =    websGetVar(wp, T("fileName"), T("default.txt"));    

    FILE *fp = fopen(fileName,"r");
    if (fp == NULL) {
        printf("can't open default.txt\n");
        return;
    }
    
    int rt = fread(rDspInfo,1,sizeof(STR_DSP),fp);
	memcpy(&dspInfo,rDspInfo,sizeof(rDspInfo));

	//AD
	DspAorDChanMixer(&(rDspInfo->ad));
	
	//input vol
	int i,j;
	for(i=0;i<3;i++)
		DspGain(&(rDspInfo->vol[i]));

	//3D
	for(i=0;i<2;i++)
		Dsp3DMusicDelay(rDspInfo->m3D[i].delay, rDspInfo->m3D[i].Ch);
	Dsp3DMusicEn(rDspInfo->m3D[i].en, rDspInfo->m3D[i].Ch);

	//SCT
	for(i=0;i<2;i++) {
		DspSctHp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].hpf);
		DspSctLp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].lpf);
		DspSctBp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].bpf);
		
		DspSetSctAgc(0,rDspInfo->sct[i].AGChp,rDspInfo->sct[i].Ch);		
		DspSetSctAgc(1,rDspInfo->sct[i].AGCbp,rDspInfo->sct[i].Ch);
		DspSetSctAgc(2,rDspInfo->sct[i].AGClp,rDspInfo->sct[i].Ch);	
		
		DspSetSctDepth(0, rDspInfo->sct[i].hVolDepth, rDspInfo->sct[i].Ch);
		DspSetSctDepth(1, rDspInfo->sct[i].bVolDepth, rDspInfo->sct[i].Ch);
		DspSetSctDepth(2, rDspInfo->sct[i].lVolDepth, rDspInfo->sct[i].Ch);
	}

	//crossbar1
	for(i=0;i<2;i++) {
	for(i=0;i<6;i++)
    	DspMixerSet(1, rDspInfo->crossbar1[i][j].in, rDspInfo->crossbar1[i][j].out, rDspInfo->crossbar1[i][j].mix);
	}

	//output vol
	for(i=0;i<6;i++) {
		volOutput(0, i, rDspInfo->outVol[i]);
	}
	
	//BCHEQ
	for(i=0;i<2;i++) {
	for(i=0;i<7;i++)
		DspBCHPEQ(&(rDspInfo->bchEQ[i][j]));		
	}

	//ACHEQ
	for(i=0;i<48;i++) {
		DspACHPEQ(&(rDspInfo->achEQ[i]));
	}

	//hpf
	for(i=0;i<6;i++) {
		if (i == 4) continue;
		DspACHBp_HP(&(rDspInfo->hpf[i]));
	}

	//bpf
	DspACHBp_BP(&(rDspInfo->bpf), rDspInfo->bpf.Ch);

	//limit
	for(i=0;i<6;i++) {
		DspLimiter(&(rDspInfo->limit[i]));
	}

	//output dly
	for(i=0;i<6;i++)
		DspOutDelay(&(rDspInfo->outDly[i]));

    printf("firmwareDownload finish\n");
}

/******************************************************************************/
/*   by qmd 2014.9.20
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formDlownload(webs_t wp, char_t *path, char_t *query)
{
	printf("formDlownload()\n");
	DapHwInit();
    //DspFunModInit();
    DspAllByPass();
    //readAllHLpfEQ();
    //testMUX();
}


/******************************************************************************/
/*   by qmd 2014.9.20
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formAllByPass(webs_t wp, char_t *path, char_t *query)
{
    DspAllByPass();
}


/******************************************************************************/
/*   by qmd 2014.9.23
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formACHEQ(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type,	*Q, *Gain, *En, *Ch, *no;
	
	Q =    websGetVar(wp, T("Q"), T("1.0"));	
	Gain = websGetVar(wp, T("Gain"), T("1.0")); 	
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =	 websGetVar(wp, T("En"), T("0"));	
	no =	websGetVar(wp, T("no"), T("0"));
	Ch=	websGetVar(wp, T("Ch"), T("0"));
	
	EQOP_STR *p = (EQOP_STR*)malloc(sizeof(EQOP_STR));
	p->peq.Q = atof(Q);
	p->peq.Gain = atof(Gain);
	p->peq.Fc = atoi(Fc);
	p->peq.Type = atoi(Type);
	p->peq.en = atoi(En);
	p->no = atoi(no);
	p->Ch = atoi(Ch);

	repACHEQ(p);
    
    DspACHPEQ(p);
    
	free(p);

	printf("%s> Q=%f,Gain=%f,Fc=%d,Type=%d,En=%d,no=%d,Ch=%d\n",	__FUNCTION__,	  
		atof(Q),atof(Gain),atoi(Fc),atoi(Type),atoi(En),atoi(no),atoi(Ch));
}


/******************************************************************************/
/*   by qmd 2014.9.23
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formBCHEQ(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type,	*Q, *Gain, *En, *Ch, *no;
	
	Q =    websGetVar(wp, T("Q"), T("1.0"));	
	Gain = websGetVar(wp, T("Gain"), T("1.0")); 	
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =	 websGetVar(wp, T("En"), T("0"));	
	no =	websGetVar(wp, T("no"), T("0"));
	Ch=	websGetVar(wp, T("Ch"), T("0"));
	
	EQOP_STR *p = (EQOP_STR*)malloc(sizeof(EQOP_STR));
	p->peq.Q = atof(Q);
	p->peq.Gain = atof(Gain);
	p->peq.Fc = atoi(Fc);
	p->peq.Type = atoi(Type);
	p->peq.en = atoi(En);
	p->no = atoi(no);
	p->Ch = atoi(Ch);
    
    repBCHEQ(p);

    DspBCHPEQ(p);
	free(p);

	printf("%s> Q=%f,Gain=%f,Fc=%d,Type=%d,En=%d,no=%d,Ch=%d\n",	__FUNCTION__,	  
		atof(Q),atof(Gain),atoi(Fc),atoi(Type),atoi(En),atoi(no),atoi(Ch));
}


/******************************************************************************/
/*   by qmd 2014.9.23
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formHPF(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type, *En, *Ch;
		
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =	 websGetVar(wp, T("En"), T("0"));	 
	Ch=	websGetVar(wp, T("Ch"), T("0"));	

	CHanHLPF_STR *p = (CHanHLPF_STR*)malloc(sizeof(CHanHLPF_STR));   
	p->xpf.Fc = (uint16_t)atoi(Fc);
	p->xpf.Type = (uint8)atoi(Type);
	p->xpf.en = (uint8)atoi(En);
	p->Ch = (uint8)atoi(Ch);

    repHPF(p);
    DspACHBp_HP(p);
    
	free(p);

	printf("%s> Fc=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fc),atoi(Type),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*   by qmd 2014.9.23
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formLPF(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type, *En, *Ch;
		
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =	 websGetVar(wp, T("En"), T("0"));	 
	Ch=	websGetVar(wp, T("Ch"), T("0"));	

	CHanHLPF_STR *p = (CHanHLPF_STR*)malloc(sizeof(CHanHLPF_STR));   
	p->xpf.Fc = atoi(Fc);
	p->xpf.Type = atoi(Type);
	p->xpf.en = atoi(En);
	p->Ch = atoi(Ch);

    repLPF(p);
	DspACHBp_LP(p);
	free(p);

	printf("%s> Fc=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fc),atoi(Type),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.10.6
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formBPF(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fp, *Fs, *Type, *En, *Ch;

	Fp =   websGetVar(wp, T("Fp"), T("0")); 	
	Fs =   websGetVar(wp, T("Fs"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =   websGetVar(wp, T("En"), T("0"));  
	Ch= websGetVar(wp, T("Ch"), T("0"));	

	struct bpfstr *bp = (struct bpfstr*)malloc(sizeof(struct bpfstr));
	bp->Fp = atoi(Fp);
	bp->Fs = atoi(Fs);
	bp->Type = atoi(Type);
	bp->en = atoi(En);

    repBPF(bp, atoi(Ch));
    DspACHBp_BP(bp, atoi(Ch));

	printf("%s> Fp=%d,Fs=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fp),atoi(Fs),atoi(Type),atoi(En),atoi(Ch));    
    free(bp);
}



/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formLIMT(webs_t wp, char_t *path, char_t *query)
{
	char_t	*T2, *k2, *attack, *release,*En, *Ch;
		
	T2=   websGetVar(wp, T("T2"), T("0")); 
	k2=  websGetVar(wp, T("k2"), T("0"));	
	attack=   websGetVar(wp, T("Attack"), T("0")); 
	release=  websGetVar(wp, T("Release"), T("0"));	
	En =	 websGetVar(wp, T("En"), T("0"));	 
	Ch= websGetVar(wp, T("Ch"), T("0"));
	
    LimiterOP_STR *p= (LimiterOP_STR*)malloc(sizeof(LimiterOP_STR));
	p->limiter.T2 = atof(T2);
	p->limiter.k2 = atof(k2);
	p->limiter.Attack = atof(attack);
	p->limiter.Release = atof(release);
	p->limiter.en = atoi(En);
	p->Ch = atoi(Ch);
    
    repLimit(p);
	DspLimiter(p);
	free(p);

	printf("%s> T2=%f,k2=%f,attack=%f,release=%f,En=%d,Ch=%d\n",	__FUNCTION__,	  
		atof(T2),atof(k2),atof(attack),atof(release),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formDelay(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Dly,*En, *Ch;
		
	Dly=   websGetVar(wp, T("Dly"), T("0")); 
	En =	 websGetVar(wp, T("En"), T("0"));	 
	Ch= websGetVar(wp, T("Ch"), T("0"));

    Outdly *p = (Outdly *)malloc(sizeof(Outdly));
	p->delay.Dly = atof(Dly);
	p->delay.en = (uint8_t)atoi(En);
	p->Ch = (uint8_t)atoi(Ch);

    repOutDly(p);
	DspOutDelay(p);
	free(p);
	
	printf("%s> Dly=%f,En=%d,Ch=%d\n",	__FUNCTION__,	  
		atof(Dly),atoi(En),atoi(Ch));
}

/******************************************************************************/
/*	 by qmd 2014.9.23     v2.0
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
 #if 0 //v2.0
static void formVol_0(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Gain,*Pol, *Mute, *En;
		
	Gain=   websGetVar(wp, T("Gain"), T("0")); 
	Pol =	 websGetVar(wp, T("Pol"), T("0"));	
	Mute =	 websGetVar(wp, T("Mute"), T("0"));
    
    VOL_STR *p = (VOL_STR*)malloc(sizeof(VOL_STR));
	p->Gain = atof(Gain);
	p->Pol = (int8_t)atoi(Pol);
	p->Mute = (int8_t)atoi(Mute);

    repVol(p);
	DspGain(p);
	free(p);
	
	printf("%s> Gain=%f,Pol=%d,Mute=%d\n",__FUNCTION__,		  
		atof(Gain),atoi(Pol),atoi(Mute));
}
#endif //v2.0
static void formVol(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Gain,*Pol, *Mute, *Ch;
		
	Gain=   websGetVar(wp, T("Gain"), T("0")); 
	Pol =	 websGetVar(wp, T("Pol"), T("0"));	
	Mute =	 websGetVar(wp, T("Mute"), T("0"));
    Ch= 	websGetVar(wp, T("Ch"), T("0"));
    
    VOL_OP *p = (VOL_OP*)malloc(sizeof(VOL_OP));
	p->vol.Gain = atof(Gain);
	p->vol.Pol = (int8_t)atoi(Pol);
	p->vol.Mute = (int8_t)atoi(Mute);
	p->Ch = (uint8)atoi(Ch);

    repVol(p);
	DspGain(p);
	free(p);
	
	printf("%s> Gain=%f,Pol=%d,Mute=%d\n",__FUNCTION__,		  
		atof(Gain),atoi(Pol),atoi(Mute));
}

	
/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void form3DDelay(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Dly,*En, *Ch;
		
	Dly=   	websGetVar(wp, T("Dly"), T("0")); 
	En =	websGetVar(wp, T("En"), T("0"));	 
	Ch= 	websGetVar(wp, T("Ch"), T("0"));
	
	DLY_STR delay;//延时
	delay.Dly = atof(Dly);
	delay.en = atoi(En);

    rep3DDly(atoi(Ch),&delay);
	Dsp3DMusicDelay(delay, atoi(Ch));
	
	printf("%s> Dly=%f,En=%d,Ch=%d\n",__FUNCTION__,		  
		delay.Dly,delay.en,atoi(Ch));
	printf("%s> Dly=%f,En=%d,Ch=%d\n",__FUNCTION__,		  
		atof(Dly),atoi(En),atoi(Ch));
}

/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void form3DEn(webs_t wp, char_t *path, char_t *query)
{
	char_t	*En, *Ch;
	float mixer[4]={0};
    
	En =	websGetVar(wp, T("En"), T("0"));	 
	Ch= 	websGetVar(wp, T("Ch"), T("0"));

    if (0 == atoi(En)) {
	    mixer[0]=1.0; mixer[1]=mixer[2]=mixer[3] = 0.0;
    } else if (1 == atoi(En)) {
        mixer[0]=0.0; mixer[1]=mixer[2]=mixer[3] = 1.0;
    }
    rep3DMix(atoi(Ch),mixer);

    rep3DEn(atoi(Ch), atoi(En));
	Dsp3DMusicEn(atoi(En), atoi(Ch));
	
	printf("%s> En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(En),atoi(Ch));
}

/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void form3DMixer(webs_t wp, char_t *path, char_t *query)
{
	char_t	*mix0, *mix1, *mix2, *mix3,*Ch;
	float mixer[4]={0};
	
	mix0 =	websGetVar(wp, T("mix0"), T("0"));	
	mix1 =	websGetVar(wp, T("mix1"), T("0"));	
	mix2 =	websGetVar(wp, T("mix2"), T("0"));
    mix3 =	websGetVar(wp, T("mix3"), T("0"));
	Ch= 	websGetVar(wp, T("Ch"), T("0"));

	mixer[0] = atof(mix0); mixer[1] = atof(mix1); mixer[2] = atof(mix2);mixer[3] = atof(mix3);

    rep3DMix(atoi(Ch),mixer);
	Dsp3DMusicMix(mixer,atoi(Ch));
	
	printf("%s> mix0=%f,mix1=%f,mix2=%f,Ch=%d\n",__FUNCTION__, 	  
		atof(mix0),atof(mix1),atof(mix2),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */

static void formSctHpf(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type, *En, *Ch;
		
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =   websGetVar(wp, T("En"), T("0"));	 
	Ch= websGetVar(wp, T("Ch"), T("0"));

	struct hlpfstr hp;
	hp.Fc = atoi(Fc);
	hp.Type = atoi(Type);
	hp.en = atoi(En);

    repSctHLpf(atoi(Ch),0,&hp);
	DspSctHp(atoi(Ch), hp);
	
	printf("%s> Fc=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fc),atoi(Type),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */

static void formVolDepth(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Gain, *Type, *Ch;
		
	Gain =   websGetVar(wp, T("Gain"), T("0")); 
	Type=    websGetVar(wp, T("Type"), T("0"));	   
	Ch=      websGetVar(wp, T("Ch"), T("0"));	

	repSctDepth(atoi(Ch),atoi(Type),atof(Gain));
	DspSetSctDepth(atoi(Type), atof(Gain), atoi(Ch));
	
	printf("%s> Gain=%f,Type=%d,Ch=%d\n",__FUNCTION__,		  
		atof(Gain),atoi(Type),atoi(Ch));
}



/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formAGC(webs_t wp, char_t *path, char_t *query)
{
	char_t	*T2, *k2, *attack, *release,*En, *Ch, *Type;
		
	T2 =   websGetVar(wp, T("T2"), T("0")); 
	k2 =  websGetVar(wp, T("k2"), T("0"));	
	attack =   websGetVar(wp, T("Attack"), T("0")); 
	release =  websGetVar(wp, T("Release"), T("0"));	
	Type =    websGetVar(wp, T("Type"), T("0"));	   
	En =	 websGetVar(wp, T("En"), T("0"));	 
	Ch = websGetVar(wp, T("Ch"), T("0"));
    
    DRC_STR agc; agc.T2=atof(T2); agc.k2=atof(k2); agc.Attack=atof(attack); agc.Release=atof(release); agc.en=atoi(En);
    repSctAgc(atoi(Ch),atoi(Type),&agc);
    //DspSetSctAgc(atoi(Type),atoi(En), atof(T2),atof(k2),atof(attack),atof(release),atoi(Ch));
	DspSetSctAgc(atoi(Type),agc,atoi(Ch));
    
	printf("%s> T2=%f,k2=%f,attack=%f,release=%f,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atof(T2),atof(k2),atof(attack),atof(release),atoi(Type),atoi(En),atoi(Ch));
}

/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSctBpf(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fp, *Fs, *Type, *En, *Ch;

	Fp =   websGetVar(wp, T("Fp"), T("0")); 	
	Fs =   websGetVar(wp, T("Fs"), T("0")); 
	Type=  websGetVar(wp, T("Type"), T("0"));	  
	En =   websGetVar(wp, T("En"), T("0"));  
	Ch= websGetVar(wp, T("Ch"), T("0"));	

	struct bpfstr bp;
	bp.Fp = atoi(Fp);
	bp.Fs = atoi(Fs);
	bp.Type = atoi(Type);
	bp.en = atoi(En);

    repSctBpf(atoi(Ch), &bp);
	DspSctBp(atoi(Ch), bp);
	
	printf("%s> Fp=%d,Fs=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fp),atoi(Fs),atoi(Type),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */

static void formSctLpf(webs_t wp, char_t *path, char_t *query)
{
	char_t	*Fc, *Type, *En, *Ch;
		
	Fc =   websGetVar(wp, T("Fc"), T("0")); 
	Type =  websGetVar(wp, T("Type"), T("0"));	  
	En =   websGetVar(wp, T("En"), T("0"));	 
	Ch = websGetVar(wp, T("Ch"), T("0"));	

	struct hlpfstr lp;
	lp.Fc = atoi(Fc);
	lp.Type = atoi(Type);
	lp.en = atoi(En);

    repSctHLpf(atoi(Ch),2,&lp);
	DspSctLp(atoi(Ch), lp);
	
	printf("%s> Fc=%d,Type=%d,En=%d,Ch=%d\n",__FUNCTION__,		  
		atoi(Fc),atoi(Type),atoi(En),atoi(Ch));
}


/******************************************************************************/
/*	 by qmd 2014.9.19
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSctMixer(webs_t wp, char_t *path, char_t *query)
{
	char_t	*mix0, *mix1, *mix2, *mix3, *Ch, *en;
	float mixer[4]={0};
	
	mix0 =	websGetVar(wp, T("mix0"), T("0"));	
	mix1 =	websGetVar(wp, T("mix1"), T("0"));	
	mix2 =	websGetVar(wp, T("mix2"), T("0"));	
	mix3 =	websGetVar(wp, T("mix3"), T("0"));	
	en =	websGetVar(wp, T("en"), T("0"));
	Ch= 	websGetVar(wp, T("Ch"), T("0"));

	if (atoi(en)) {
		mixer[0] = atof(mix0); mixer[1] = atof(mix1); 
		mixer[2] = atof(mix2); mixer[3] = atof(mix3);
		
		repSctEn(atoi(en), atoi(Ch));
		DspSctEn(atoi(en), atoi(Ch));
	    repSctMix(atoi(Ch),mixer);
		DspSctMix(mixer,atoi(Ch));
	} else {
		repSctEn(atoi(en), atoi(Ch));
		DspSctEn(atoi(en), atoi(Ch));
	}	
	printf("%s> -->=%f,xpf=%f,bpf=%f,lpf=%f,Ch=%d,en=%d\n", __FUNCTION__,	  
		atof(mix0),atof(mix1),atof(mix2),atof(mix3),atoi(Ch),atoi(en));
}



/******************************************************************************/
/*	 by qmd 2014.9.20
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formAD(webs_t wp, char_t *path, char_t *query)
{
	char_t	*ad, *mix;

	ad =	websGetVar(wp, T("ad"), T("0"));
	mix =	websGetVar(wp, T("mix"), T("0"));
	
    AnaOrDigSrc_STR *AnaOrDig = (AnaOrDigSrc_STR*)malloc(sizeof(AnaOrDigSrc_STR));
	AnaOrDig->en = atoi(ad);
	AnaOrDig->mixer = atof(mix);

    repAD(AnaOrDig);
	DspAorDChanMixer(AnaOrDig);
	free(AnaOrDig);
	
	printf("%s> ad=%d,mix=%f\n", __FUNCTION__,	  
		        atoi(ad),atof(mix));
}

/******************************************************************************/
/*   by qmd 2014.9.28
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formOutVol(webs_t wp, char_t *path, char_t *query)
{
	char_t	*vol, *out;

	vol =	websGetVar(wp, T("vol"), T("0"));
	out =	websGetVar(wp, T("out"), T("0"));

    repOutVol(atoi(out),atof(vol));
    volOutput(0, atoi(out), atof(vol));

    printf("%s>, out=%d, vol=%f\n", __FUNCTION__, atoi(out), atof(vol));
}

/******************************************************************************/
/*   by qmd 2014.9.28
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSSEnable(webs_t wp, char_t *path, char_t *query)
{    
    uint8 outVal[8]={0};

    DspSignalSourceEnable();
	printf("%s>\n", __FUNCTION__);
}

/******************************************************************************/
/*   by qmd 2014.9.28
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSSCancel(webs_t wp, char_t *path, char_t *query)
{    
    uint8 outVal[8]={0};

    DspSignalSourceCancel();
	printf("%s>\n", __FUNCTION__);
}


/******************************************************************************/
/*	 by qmd 2014.9.21
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSigSourSelectOut(webs_t wp, char_t *path, char_t *query)
{
	char_t	*in, *out, *total, *type;

	in =	websGetVar(wp, T("in"), T("0"));
	out =	websGetVar(wp, T("out"), T("0"));
	total =	websGetVar(wp, T("total"), T("0"));
	type =	websGetVar(wp, T("type"), T("0"));
	
	DspSigSourSelectOut((uint8_t)atoi(in), (uint8_t)atoi(out), (uint8_t)atoi(total), (uint8_t)atoi(type));

	
	printf("%s> in=%d, out=%d, total=%d, type=%d\n", __FUNCTION__,	  
		(uint8_t)atoi(in), (uint8_t)atoi(out), (uint8_t)atoi(total), (uint8_t)atoi(type));
}



/******************************************************************************/
/*   by qmd 2014.9.22
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formCrossbar1(webs_t wp, char_t *path, char_t *query)
{
    char_t  *in, *out, *rd, *mix;

    in =    websGetVar(wp, T("in"), T("0"));
    out =   websGetVar(wp, T("out"), T("0"));
    rd = websGetVar(wp, T("rd"), T("0"));
    mix =  websGetVar(wp, T("mix"), T("0"));

    Crossbar_STR *p = (Crossbar_STR*)malloc(sizeof(Crossbar_STR));
    p->in=atoi(in); p->out=atoi(out); p->rd=atoi(rd); p->mix=atof(mix);
    repCrossBar(p);
    DspMixerSet((uint8_t)atoi(rd), (uint32_t)atoi(in), (uint32_t)atoi(out), (float)atof(mix));

    printf("%s> in=%d, out=%d, rd=%d, mix=%f\n", __FUNCTION__,    
        (uint8_t)atoi(in), atoi(out), atoi(rd), atof(mix));
}



/******************************************************************************/
/*   by qmd 2014.9.22
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formVuDetect(webs_t wp, char_t *path, char_t *query)
{    
    uint8 outVal[8]={0};

    VuDetect(outVal);

	printf("%s> %x,%x,%x,%x,%x,%x,%x,%x\n", __FUNCTION__,
        outVal[0],outVal[1],outVal[2],outVal[3],outVal[4],outVal[5],outVal[6],outVal[7]);
}



/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formSave(webs_t wp, char_t *path, char_t *query)
{    
    uint8 outVal[8]={0};

    char_t  *fileName;
    fileName =    websGetVar(wp, T("fileName"), T("default.txt"));
    
    FILE *fp = fopen(fileName,"w");
    if (fp == NULL) {
        printf("can't open %s\n",fileName);
        return;
    }
    int rt = fwrite(&dspInfo,1,sizeof(dspInfo),fp);
    
    fclose(fp);
	printf("%s> save %s ,rt=%d\n", __FUNCTION__,fileName,rt);
}



/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static int first = 1;
static void formRead(webs_t wp, char_t *path, char_t *query)
{    
    uint8 outVal[8]={0};
    
    char_t  *fileName;
    fileName =    websGetVar(wp, T("fileName"), T("default.txt"));    

    FILE *fp = fopen(fileName,"r");
    if (fp == NULL) {
        printf("can't open default.txt\n");
        return;
    }
    
    //if(first) {
    //    first = 0;
    //    rDspInfo = (STR_DSP*)malloc(sizeof(STR_DSP));
    //}
    int rt = fread(rDspInfo,1,sizeof(STR_DSP),fp); 
    printf("read rt=%d read %s\n",rt,fileName);
}

/******************************************************************************/
/*   by qmd 2014.9.30
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
static void formShowInfo(webs_t wp, char_t *path, char_t *query)
{    
    //showInputVol(dspInfo.vol);
	//showOutputVol(dspInfo.outVol);
	//showOutDly(dspInfo.outDly);
	//showAchEQ(dspInfo.achEQ);
	//showBchEQ(dspInfo.bchEQ);
	//showLimit(dspInfo.limit);
	//show3D(dspInfo.m3D);
	//showSct(dspInfo.sct);
	//showHLpf(dspInfo.hpf, 1);
	//showHLpf(&(dspInfo.lpf), 0);
	//showAD(&(dspInfo.ad));
	//showCrossbar1(dspInfo.crossbar1);
	
	
    showInputVol(rDspInfo->vol);
	showOutputVol(rDspInfo->outVol);
	showOutDly(rDspInfo->outDly);
	showAchEQ(rDspInfo->achEQ);
	showBchEQ(rDspInfo->bchEQ);
	showLimit(rDspInfo->limit);
	show3D(rDspInfo->m3D);
	showSct(rDspInfo->sct);
	showHLpf(rDspInfo->hpf, 1);
	//showHLpf(&(rDspInfo->lpf), 0);
	showBpf(&(rDspInfo->bpf));
	showAD(&(rDspInfo->ad));
    showCrossbar1(rDspInfo->crossbar1);

}




#if 1
/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repACHEQ(EQOP_STR *p)
{
    unsigned char Ch=0, no = p->no;
 
    switch (p->Ch) {
    case 0:Ch = 0; break;
    case 1:Ch = 10; break;
    case 2:Ch = 20; break;
    case 3:Ch = 30; break;
    case 4:Ch = 40; break;
    case 5:Ch = 45; break;
    default:break;
    }
  
    dspInfo.achEQ[Ch+no].peq.Q = p->peq.Q;
    dspInfo.achEQ[Ch+no].peq.Gain = p->peq.Gain;
    dspInfo.achEQ[Ch+no].peq.Fc = p->peq.Fc;
    dspInfo.achEQ[Ch+no].peq.Type = p->peq.Type;
    dspInfo.achEQ[Ch+no].peq.en = p->peq.en;
    dspInfo.achEQ[Ch+no].Ch = p->Ch;
    dspInfo.achEQ[Ch+no].no = p->no;
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repBCHEQ(EQOP_STR *p)
{
	if (p->Ch >= 2 || p->no >= 8) return;
    dspInfo.bchEQ[p->Ch][p->no].peq.Q = p->peq.Q;
    dspInfo.bchEQ[p->Ch][p->no].peq.Gain = p->peq.Gain;
    dspInfo.bchEQ[p->Ch][p->no].peq.Fc = p->peq.Fc;
    dspInfo.bchEQ[p->Ch][p->no].peq.Type = p->peq.Type;
    dspInfo.bchEQ[p->Ch][p->no].peq.en = p->peq.en;
    dspInfo.bchEQ[p->Ch][p->no].Ch = p->Ch;
    dspInfo.bchEQ[p->Ch][p->no].no = p->no;
}

/******************************************************************************/
/*   by qmd 2014.9.25   v2.0
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
 #if 0  //v2.0
void repVol(VOL_STR *p)
{
    dspInfo.vol.Gain = p->Gain;
    dspInfo.vol.Pol = p->Pol;
    dspInfo.vol.Mute = p->Mute;   
}
 #endif

//v2.1
void repVol(VOL_OP *p)
{
    if (p->Ch >= 3) return;
    dspInfo.vol[p->Ch].vol.Gain = p->vol.Gain;
    dspInfo.vol[p->Ch].vol.Pol = p->vol.Pol;
    dspInfo.vol[p->Ch].vol.Mute = p->vol.Mute;   
    dspInfo.vol[p->Ch].Ch = p->Ch;
}

//v2.1
void repOutVol(uint8_t out, fp32 vol)
{
    if (out >= 6) return;
    dspInfo.outVol[out] = vol;
} 


/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repOutDly(Outdly *p)
{
    dspInfo.outDly[p->Ch].delay.Dly = p->delay.Dly;
    dspInfo.outDly[p->Ch].delay.en  = p->delay.en;
    dspInfo.outDly[p->Ch].Ch = p->Ch;
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repLimit(LimiterOP_STR *p)
{
    dspInfo.limit[p->Ch].limiter.T2 = p->limiter.T2;
    dspInfo.limit[p->Ch].limiter.k2 = p->limiter.k2;
    dspInfo.limit[p->Ch].limiter.Attack = p->limiter.Attack;
    dspInfo.limit[p->Ch].limiter.Release = p->limiter.Release;
    dspInfo.limit[p->Ch].limiter.en= p->limiter.en;
    dspInfo.limit[p->Ch].Ch = p->Ch;
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void rep3DDly(unsigned char Ch, DLY_STR *p)
{
    if (Ch >= 2) return;
    dspInfo.m3D[Ch].delay.Dly = p->Dly;
    dspInfo.m3D[Ch].delay.en = p->en;
    dspInfo.m3D[Ch].Ch = Ch;
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void rep3DMix(unsigned char Ch, float mixer[4])
{
    if (Ch >=2) return;
    memcpy(dspInfo.m3D[Ch].mix, mixer, sizeof(float)*4);
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void rep3DEn(unsigned char Ch, unsigned char en)
{
    if (Ch >=2) return;
    dspInfo.m3D[Ch].en = en;
    dspInfo.m3D[Ch].Ch = Ch;
}



/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repSctHLpf(unsigned char Ch, unsigned char hl,HLPF_STR *p)
{
    if (Ch >=2) return;
    
    dspInfo.sct[Ch].Ch = Ch;
    dspInfo.sct[Ch].en = p->en;
    
    if (hl == 0) {
        dspInfo.sct[Ch].hpf.Fc = p->Fc;
        dspInfo.sct[Ch].hpf.Type = p->Type;
        dspInfo.sct[Ch].hpf.en = p->en;
    } else if (hl == 2) {
        dspInfo.sct[Ch].lpf.Fc = p->Fc;
        dspInfo.sct[Ch].lpf.Type = p->Type;
        dspInfo.sct[Ch].lpf.en = p->en;
    }
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repSctBpf(unsigned char Ch, BPF_STR *p)
{
    if (Ch >=2) return;
    
    dspInfo.sct[Ch].Ch = Ch;
    dspInfo.sct[Ch].en = p->en;
    
    dspInfo.sct[Ch].bpf.Fp = p->Fp;
    dspInfo.sct[Ch].bpf.Fs = p->Fs;
    dspInfo.sct[Ch].hpf.Type = p->Type;
    dspInfo.sct[Ch].hpf.en = p->en;
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repSctAgc(unsigned char Ch, unsigned char hbl, DRC_STR *p)
{
    if (Ch >=2) return;
    dspInfo.sct[Ch].Ch = Ch;
    dspInfo.sct[Ch].en = p->en;
    
    if (hbl == 0) {    
        dspInfo.sct[Ch].AGChp.T2 = p->T2;
        dspInfo.sct[Ch].AGChp.k2 = p->k2;
        dspInfo.sct[Ch].AGChp.Attack = p->Attack;
        dspInfo.sct[Ch].AGChp.Release = p->Release;
        dspInfo.sct[Ch].AGChp.en = p->en;
    } else if (hbl == 1) {
        dspInfo.sct[Ch].AGCbp.T2 = p->T2;
        dspInfo.sct[Ch].AGCbp.k2 = p->k2;
        dspInfo.sct[Ch].AGCbp.Attack = p->Attack;
        dspInfo.sct[Ch].AGCbp.Release = p->Release;
        dspInfo.sct[Ch].AGCbp.en = p->en;
    } else if (hbl ==2) {
        dspInfo.sct[Ch].AGClp.T2 = p->T2;
        dspInfo.sct[Ch].AGClp.k2 = p->k2;
        dspInfo.sct[Ch].AGClp.Attack = p->Attack;
        dspInfo.sct[Ch].AGClp.Release = p->Release;
        dspInfo.sct[Ch].AGClp.en = p->en;
    }
}

/******************************************************************************/
/*   by qmd 2014.9.25
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repSctDepth(unsigned char Ch, unsigned char hbl, float depth)
{
    if (Ch >=2) return;
    
    dspInfo.sct[Ch].Ch = Ch;
    dspInfo.sct[Ch].en = 1;
    
    if (hbl == 0) {
        dspInfo.sct[Ch].hVolDepth = depth;
    } else if (hbl == 1) {
        dspInfo.sct[Ch].bVolDepth = depth;
    } else if (hbl == 2) {
        dspInfo.sct[Ch].lVolDepth = depth;
    }
}

void repSctMix(unsigned char Ch, float mixer[4])
{
	if (Ch >= 2) return;
	memcpy(dspInfo.sct[Ch].mix,mixer,sizeof(mixer)*4);	
	dspInfo.sct[Ch].Ch = Ch;
    if (0 == (int32)(mixer[0] * 0x00800000)) {
        dspInfo.sct[Ch].en = 0;
    } else {
        dspInfo.sct[Ch].en = 1;
    }
}

void repSctEn(unsigned char Ch, uint8_t en)
{
	if (Ch >= 2) return;
	dspInfo.sct[Ch].en = en;
	dspInfo.sct[Ch].Ch = Ch;
}



/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repHPF(CHanHLPF_STR *p)
{
    if (p->Ch >= 6) return;
    dspInfo.hpf[p->Ch].Ch = p->Ch;
    dspInfo.hpf[p->Ch].xpf.Fc = p->xpf.Fc;
    dspInfo.hpf[p->Ch].xpf.Type = p->xpf.Type;
    dspInfo.hpf[p->Ch].xpf.en = p->xpf.en;
}

/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repLPF(CHanHLPF_STR *p)
{
    if (p->Ch == 4) {
        dspInfo.lpf.Ch = p->Ch;
        dspInfo.lpf.xpf.Fc = p->xpf.Fc;
        dspInfo.lpf.xpf.Type = p->xpf.Type;
        dspInfo.lpf.xpf.en = p->xpf.en;
    }
}

/******************************************************************************/
/*   by qmd 2014.10.6
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repBPF(BPF_STR *p, uint8 Ch)
{
    if (Ch != 4) return;
    dspInfo.bpf.Ch = Ch;
    dspInfo.bpf.Fp = p->Fp;
    dspInfo.bpf.Fs = p->Fs;
    dspInfo.bpf.Type = p->Type;
    dspInfo.bpf.en = p->en;

}


/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repAD(AnaOrDigSrc_STR *p)
{
	if (p->en >= 3) return;
    dspInfo.ad.en = p->en;
    dspInfo.ad.mixer = p->mixer;
}

/******************************************************************************/
/*   by qmd 2014.9.26
 *  Test form for posted data (in-memory CGI). This will be called when the
 *  form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */
void repCrossBar(Crossbar_STR *p)
{
	if (p->in >= 2 || p->out >= 6) return;
    dspInfo.crossbar1[p->in][p->out].in = p->in;
    dspInfo.crossbar1[p->in][p->out].out = p->out;
    dspInfo.crossbar1[p->in][p->out].rd = p->rd;
    dspInfo.crossbar1[p->in][p->out].mix = p->mix;
}



#endif


/******************************************************************************/
/*
 *	Home page handler
 */
static int websHomePageHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,
	int arg, char_t *url, char_t *path, char_t *query)
{
/*
 *	If the empty or "/" URL is invoked, redirect default URLs to the home page
 */
	if (*url == '\0' || gstrcmp(url, T("/")) == 0) {
		websRedirect(wp, WEBS_DEFAULT_HOME);
		return 1;
	}
	return 0;
}

/******************************************************************************/

#ifdef B_STATS
static void memLeaks()
{
	int		fd;

	if ((fd = gopen(T("leak.txt"), O_CREAT | O_TRUNC | O_WRONLY, 0666)) >= 0) {
		bstats(fd, printMemStats);
		close(fd);
	}
}

/******************************************************************************/
/*
 *	Print memory usage / leaks
 */

static void printMemStats(int handle, char_t *fmt, ...)
{
	va_list		args;
	char_t		buf[256];

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);
	write(handle, buf, strlen(buf));
}
#endif


/******************************************************************************/
/*
 * for test html upload file to web server
 * add by gyr 2011.10.15
 */

static void formUploadFileTest(webs_t wp, char_t *path, char_t *query)
{
    FILE *       fp;
    char_t *     fn;
    char_t *     bn = NULL;
    int          locWrite;
    int          numLeft;
    int          numWrite;

	printf("\n...................formUploadFileTest...................\n\n");

    a_assert(websValid(wp));
    websHeader(wp);

    fn = websGetVar(wp, T("filename"), T(""));
    if (fn != NULL && *fn != '\0') {
        if ((int)(bn = gstrrchr(fn, '/') + 1) == 1) {
            if ((int)(bn = gstrrchr(fn, '\\') + 1) == 1) {
                bn = fn;
            }
        }
    }

	printf("fn=%s, bn=%s  .......\n", fn, bn);

    websWrite(wp, T("Filename = %s<br>Size = %d bytes<br>"), bn, wp->lenPostData);

    if ((fp = fopen((bn == NULL ? "upldForm.bin" : bn), "w+b")) == NULL) {
        websWrite(wp, T("File open failed!<br>"));
    } else {
        locWrite = 0;
        numLeft = wp->lenPostData;
        while (numLeft > 0) {
            numWrite = fwrite(&(wp->postData[locWrite]), sizeof(*(wp->postData)), numLeft, fp);
            if (numWrite < numLeft) {
                websWrite(wp, T("File write failed.<br>  ferror=%d locWrite=%d numLeft=%d numWrite=%d Size=%d bytes<br>"), ferror(fp), locWrite, numLeft, numWrite, wp->lenPostData);
            break;
            }
            locWrite += numWrite;
            numLeft -= numWrite;
        }

        if (numLeft == 0) {
            if (fclose(fp) != 0) {
                websWrite(wp, T("File close failed.<br>  errno=%d locWrite=%d numLeft=%d numWrite=%d Size=%d bytes<br>"), errno, locWrite, numLeft, numWrite, wp->lenPostData);
            } else {
                websWrite(wp, T("File Size Written = %d bytes<br>"), wp->lenPostData);
            }
        } else {
            websWrite(wp, T("numLeft=%d locWrite=%d Size=%d bytes<br>"), numLeft, locWrite, wp->lenPostData);
        }
    }

    websFooter(wp);
    websDone(wp, 200);

}

/******************************************************************************/
