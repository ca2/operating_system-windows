/*
 * aspilib.c - Copyright (C) 1999 Jay A. Key
 *
 * Generic routines to access wnaspi32.dll
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/map modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, map
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY map FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 **********************************************************************
 *
 */
#include "akrip32_internal.h"



#define SHAREDMEMVER 2
typedef struct {
  int32_t iSize;
  int32_t iVer;
  CDHANDLEREC cdHandles[MAXCDHAND];
  HANDLE cdMutex[MAXCDHAND];
  int32_t nextHandle;
} AKSHAREDMEM, FAR *LPAKSHAREDMEM;

uint32_t deinitREAD10( HCDROM hCD );
uint32_t initREAD10( HCDROM hCD );
uint32_t readCDParameters( HCDROM hCD, int bChangeMask );
uint32_t setCDSpeed( HCDROM hCD, uint32_t speed );
uint32_t pauseResumeCD( HCDROM hCD, int bPause );
uint32_t startStopUnit( HCDROM hCD, int bLoEj, int bStart );
int32_t loadAspi( void );
void unloadAspi( void );
int initMutexes( void );
int deinitMutexes( void );
uint32_t CDDBSum( uint32_t n );
int32_t compBuf( BYTE *b1, BYTE *b2, int32_t n );
uint32_t testReadCDAudio( HCDROM hCD, LPTRACKBUF t );
uint32_t dummyGetASPI32SupportInfo( void );
uint32_t dummySendASPI32Command( LPSRB lpsrb );
int dummyGetASPI32Buffer( PASPI32BUFF pbuf );
int dummyFreeASPI32Buffer( PASPI32BUFF pbuf );
int dummyTranslateASPI32Address( PDWORD p1, PDWORD p2 );
uint32_t dummyGetASPI32DLLVersion( void );
int32_t InitSCSIPT( void );
int32_t DeinitSCSIPT( void );
uint32_t SPTIGetASPI32SupportInfo( void );
uint32_t SPTISendASPI32Command( LPSRB lpsrb );

/*
 * static variables
 */
static char *copyrightInfo = "Released under the GNU Lesser General Public License (http://www.fsf.org/).";
static char *aSCSIDevTypes[] = {
    "Direct-access device",
    "Sequential-access device",
    "Printer device",
    "Processor device",
    "Write-once device",
    "CD-ROM device",
    "Scanner device",
    "Optical memory device",
    "Medium changer device",
    "Communication device",
    "ASC IT8 device",
    "ASC IT8 device"
};

#define MAXCDTYPE   8
static CDREADFN aReadFn[] = {
  NULL, readCDAudioLBA_ATAPI, readCDAudioLBA_ATAPI, readCDAudioLBA_READ10,
  readCDAudioLBA_READ10, readCDAudioLBA_D8, readCDAudioLBA_D4,
  readCDAudioLBA_D4, readCDAudioLBA_READ10
};
static HINSTANCE hinstWNASPI32 = NULL;
int32_t alErrCode = 0;
BYTE alAspiErr = 0;
static LPAKSHAREDMEM pcdShared;
CDHANDLEREC *cdHandles;
HANDLE *cdMutexes;
int32_t *nextHandle = NULL;
CRITICAL_SECTION getHandle;
HANDLE hCacheMutex = NULL;
CRITICAL_SECTION csCache;
static uint32_t dwAPI = APIC_NONE;

//CRITICAL_SECTION useDbbuf;
//char dbbuf[512];

uint32_t (*pfnGetASPI32SupportInfo)();
uint32_t (*pfnSendASPI32Command)(LPSRB);
int  (*pfnGetASPI32Buffer)(PASPI32BUFF);
int  (*pfnFreeASPI32Buffer)(PASPI32BUFF);
int  (*pfnTranslateASPI32Address)(PDWORD,PDWORD);
uint32_t (*pfnGetASPI32DLLVersion)();
int  aspiLoaded = FALSE;

/*
 * local prototypes
 */
static char *devType( int32_t i );




/***************************************************************************
 * DllMain
 ***************************************************************************/
int WINAPI DllMain( HANDLE hModule, uint32_t dwReason, LPVOID lpReserved )
{
  int fInit;
  static HANDLE hMapObject = NULL;
  HANDLE hInitMutex = NULL;
  int retVal = FALSE;

  hModule = hModule;
  lpReserved = lpReserved;

  hInitMutex = CreateMutex( NULL, FALSE, L"AKRipDllMainMutex" );
  if ( !hInitMutex )
    {
      dwReason = 0xFFFFFFFF;  // do not execute any attach/detach code
    }
  else if ( WaitForSingleObject( hInitMutex, 15 * 1000 ) != WAIT_OBJECT_0 )
    {
      CloseHandle( hInitMutex );
      dwReason = 0xFFFFFFFF;    // do not execute any attach/detach code
    }

  switch( dwReason )
    {
    case DLL_PROCESS_ATTACH:
      //InitializeCriticalSection( &useDbbuf );
      InitializeCriticalSection( &getHandle );
#ifdef _DBLIBMAIN
      dbprintf( "akrip32: DLL_PROCESS_ATTACH (hModule=%04X)", hModule );
#endif
      loadAspi();
      hMapObject = CreateFileMapping( (HANDLE)(INVALID_HANDLE_VALUE), NULL,
				      PAGE_READWRITE, 0, sizeof(AKSHAREDMEM),
				      L"akrip32memmap2" );
      if ( hMapObject == NULL )
	break;
      fInit = ( GetLastError() != ERROR_ALREADY_EXISTS );
      pcdShared = (LPAKSHAREDMEM) MapViewOfFile( hMapObject, FILE_MAP_WRITE, 0, 0, 0 );
      if ( !pcdShared )
	break;
      if ( fInit )
	memset( pcdShared, 0, sizeof(AKSHAREDMEM) );
      pcdShared->iSize = sizeof(AKSHAREDMEM);
      pcdShared->iVer = SHAREDMEMVER;
      cdHandles = pcdShared->cdHandles;
      cdMutexes = pcdShared->cdMutex;
      nextHandle = &(pcdShared->nextHandle);
      initMutexes( );
      retVal = TRUE;
      break;

    case DLL_THREAD_ATTACH:
#ifdef _DBLIBMAIN
      dbprintf( "akrip32: DLL_THREAD_ATTACH (hModule=%04X)", hModule );
#endif
      retVal = TRUE;
      break;

    case DLL_THREAD_DETACH:
#ifdef _DBLIBMAIN
      dbprintf( "akrip32: DLL_THREAD_DETACH (hModule=%04X)", hModule );
#endif
      retVal = TRUE;
      break;

    case DLL_PROCESS_DETACH:
#ifdef _DBLIBMAIN
      OutputDebugString( "akrip32: DLL_PROCESS_DETACH" );
#endif
      deinitMutexes();
      UnmapViewOfFile( pcdShared );
      CloseHandle( hMapObject );
      unloadAspi();
      retVal = TRUE;
      break;
    }

  if ( hInitMutex )
    {
      ReleaseMutex( hInitMutex );
      CloseHandle( hInitMutex );
    }
  return retVal;
}



int initMutexes( void )
{
  int32_t i;
  WCHAR tmp[32];

  for( i = 0; i < MAXCDHAND; i++ )
    {
      wsprintf( tmp, L"akrip32_cdMtx%02d", i );
      cdMutexes[i] = CreateMutex( NULL, FALSE, tmp );
      if ( !cdMutexes[i] )
	return FALSE;
    }
  hCacheMutex = CreateMutex( NULL, FALSE, L"AKRipCacheMutex" );
  InitializeCriticalSection( &csCache );
  return TRUE;
}


int deinitMutexes( void )
{
  int32_t i;

  if(cdMutexes != NULL)
  {

     for(i = 0; i < MAXCDHAND; i++)
     {
        if(cdMutexes[i])
           CloseHandle(cdMutexes[i]);
     }
  }
  if ( hCacheMutex )
    CloseHandle( hCacheMutex );
  DeleteCriticalSection( &csCache );
  return TRUE;
}


static char *devType( int32_t i )
{ 
  if ( i >= 0x20 )
    return "";

  if ( i == 0x1F )
    return "Unknown map no device";

  if ( i >= 0x0C )
    return "";

  return aSCSIDevTypes[i];
}


/*
 * Assumes that loadAspi has already been called
 */
int32_t  getSCSIDevType( BYTE bHostAdapter, BYTE bTarget, BYTE bLUN,
		     LPBYTE pDevType, char * lpDevTypeStr, int32_t iDevTypeLen )
{
  SRB_GDEVBlock s;
  uint32_t dwStatus;

  memset( &s, 0, sizeof(SRB_GDEVBlock) );
  s.SRB_Cmd = SC_GET_DEV_TYPE;
  s.SRB_HaID = bHostAdapter;
  s.SRB_Target = bTarget;
  s.SRB_Lun = bLUN;

  //DebugBreak();
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  switch( dwStatus )
    {
    case SS_COMP:
#ifdef DEBUG
      dbprintf( "akrip32: getSCSIDevType() -> SS_COMP: %04X",
		s.SRB_DeviceType );
      dbprintf( "akrip32: getSCSIDevType(): pDevType == 0x%08X", pDevType );
#endif
      if ( pDevType )
	*pDevType = s.SRB_DeviceType;
      if ( lpDevTypeStr )
	strncpy( lpDevTypeStr, devType( s.SRB_DeviceType ), iDevTypeLen );
      break;

    case SS_NO_DEVICE:
#ifdef DEBUG
      dbprintf( "akrip32: getSCSIDevType() -> SS_NO_DEVICE" );
#endif
      if ( pDevType )
	*pDevType = 0x1F;
      if ( lpDevTypeStr )
	strncpy( lpDevTypeStr, "SS_NO_DEVICE", iDevTypeLen );
      return FALSE;

    default:
#ifdef DEBUG
      dbprintf( "akrip32: getSCSIDevType(): unexpected return from ASPI (%04X)", dwStatus );
#endif
      if ( pDevType )
	*pDevType = 0x1F;
      if ( lpDevTypeStr )
	strncpy( lpDevTypeStr, "Unknown return", iDevTypeLen );
      return FALSE;
    }

  return TRUE;
}


uint32_t dummyGetASPI32SupportInfo( void )
{
  return SS_NO_ASPI;
}

uint32_t dummySendASPI32Command( LPSRB lpsrb )
{
  lpsrb->SRB_Status = SS_NO_ASPI;
  return SS_NO_ASPI;
}


int dummyGetASPI32Buffer( PASPI32BUFF pbuf )
{
  return FALSE;
}


int dummyFreeASPI32Buffer( PASPI32BUFF pbuf )
{
  return FALSE;
}


int dummyTranslateASPI32Address( PDWORD p1, PDWORD p2 )
{
  return FALSE;
}


uint32_t dummyGetASPI32DLLVersion( void )
{
  return 0;
}


/***************************************************************************
 * int32_t loadAspi( void )
 ***************************************************************************/
int32_t loadAspi( void )
{
  uint32_t dwErr;
  hinstWNASPI32 = LoadLibrary( L"WNASPI32.DLL" );

  if ( hinstWNASPI32 )
    {
      pfnGetASPI32SupportInfo =
	(uint32_t(*)())GetProcAddress( hinstWNASPI32, "GetASPI32SupportInfo" );
      pfnSendASPI32Command =
	(uint32_t(*)(LPSRB))GetProcAddress( hinstWNASPI32, "SendASPI32Command" );
      pfnGetASPI32Buffer =
	(int(*)(PASPI32BUFF))GetProcAddress( hinstWNASPI32, "GetASPI32Buffer" );
      pfnFreeASPI32Buffer =
	(int(*)(PASPI32BUFF))GetProcAddress( hinstWNASPI32, "FreeASPI32Buffer" );
      pfnTranslateASPI32Address =
	(int(*)(PDWORD,PDWORD))GetProcAddress( hinstWNASPI32, "TranslateASPI32Address" );
      pfnGetASPI32DLLVersion =
	(uint32_t(*)())GetProcAddress( hinstWNASPI32, "GetASPI32DLLVersion" );

      if ( !pfnGetASPI32SupportInfo || !pfnSendASPI32Command )
	{
	  if ( !pfnGetASPI32SupportInfo )
	    alErrCode = ALERR_NOGETASPI32SUPP;
	  else
	    alErrCode = ALERR_NOSENDASPICMD;

#ifdef DEBUG
	  dbprintf( "akrip32: GetASPI32SupportInfo == 0x%08X", 
		   pfnGetASPI32SupportInfo );
	  dbprintf( "akrip32: SendASPI32Command == 0x%08X", pfnSendASPI32Command );
#endif
	  return 0;
	}
      dwAPI = APIC_ASPI;
    }
  else if ( InitSCSIPT() )
    {
      pfnGetASPI32SupportInfo = SPTIGetASPI32SupportInfo;
      pfnSendASPI32Command    = SPTISendASPI32Command;
      dwAPI = APIC_SCSIPT;
    }
  else
    {
      dwErr = GetLastError();

      alErrCode = ALERR_NOWNASPI;
      pfnGetASPI32SupportInfo = dummyGetASPI32SupportInfo;
      pfnSendASPI32Command = dummySendASPI32Command;
      pfnGetASPI32Buffer = dummyGetASPI32Buffer;
      pfnFreeASPI32Buffer = dummyFreeASPI32Buffer;
      pfnTranslateASPI32Address = dummyTranslateASPI32Address;
      pfnGetASPI32DLLVersion = dummyGetASPI32DLLVersion;

#ifdef DEBUG
      dwErr = GetLastError();
      dbprintf( "Unable to load WNASPI32.DLL" );
      dbprintf( "akrip32: GetLastError() -> %d (%04X)", dwErr, dwErr );
#endif
      dwAPI = APIC_NONE;

      return 0;
    }

   aspiLoaded = TRUE;
   return 1;
}


void unloadAspi( void )
{
  DeinitSCSIPT();

  if ( hinstWNASPI32 )
    {
      aspiLoaded = FALSE;
      pfnGetASPI32SupportInfo = NULL;
      pfnSendASPI32Command = NULL;
      pfnGetASPI32Buffer = NULL;
      pfnFreeASPI32Buffer = NULL;
      pfnTranslateASPI32Address = NULL;
      pfnGetASPI32DLLVersion = NULL;
      FreeLibrary( hinstWNASPI32 );
      hinstWNASPI32 = NULL;
    }
}

/***************************************************************************
 * GetNumAdapters
 ***************************************************************************/
int32_t GetNumAdapters( void )
{
  uint32_t d;
  BYTE bHACount;
  BYTE bASPIStatus;

  d = pfnGetASPI32SupportInfo();
  bASPIStatus = HIBYTE(LOWORD(d));
  bHACount    = LOBYTE(LOWORD(d));

  if ( bASPIStatus != SS_COMP && bASPIStatus != SS_NO_ADAPTERS )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = bASPIStatus;

#ifdef DEBUG
      dbprintf( "akrip32: GetNumAdapters: bASPIStatus == 0x%02X", bASPIStatus );
#endif
      return -1;
    }
  return (int32_t)bHACount;
}

/***************************************************************************
 * GetDriveInfo
 ***************************************************************************/
uint32_t GetDriveInfo( BYTE ha, BYTE tgt, BYTE lun, LPCDREC cdrec )
{
  uint32_t dwStatus;
  HANDLE heventSRB;
  SRB_ExecSCSICmd s;
  BYTE buf[100];
  char outBuf[101];
  CDREC cdrecTmp;

  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  if ( cdrec )
    cdrecTmp = *cdrec;

  memset( &cdrecTmp.info, 0, sizeof(CDINFO) );
  memset( &s, 0, sizeof( s ) );
  memset( buf, 0, 100 );
  s.SRB_Cmd        = SC_EXEC_SCSI_CMD;
  s.SRB_HaID       = ha;
  s.SRB_Target     = tgt;
  s.SRB_Lun        = lun;
  s.SRB_Flags      = SRB_DIR_IN | SRB_EVENT_NOTIFY;
  s.SRB_BufLen     = 100;
  s.SRB_BufPointer = buf;
  s.SRB_SenseLen   = SENSE_LEN;
  s.SRB_CDBLen     = 6;
  s.SRB_PostProc   = (LPVOID)heventSRB;
  s.CDBByte[0]     = SCSI_INQUIRY;
  s.CDBByte[4]     = 100;

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
  CloseHandle( heventSRB );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;

#ifdef DEBUG
      dbprintf( "akrip32: GetDriveInfo: Error status: 0x%04X\n", s.SRB_Status );
#endif
      return SS_ERR;
    }

#ifdef DEBUG
  {
    FILE *fp = fopen( "inquiry.dat", "wb" );
    fwrite( buf, 1, 100, fp );
    fclose( fp );
  }
#endif

  memcpy( cdrecTmp.info.vendor, &buf[8], 8 );
  memcpy( cdrecTmp.info.prodId, &buf[16], 16 );
  memcpy( cdrecTmp.info.rev, &buf[32], 4 );
  memcpy( cdrecTmp.info.vendSpec, &buf[36], 20 );
  wsprintf( outBuf, L"%s, %s v%s (%d:%d:%d)", 
	    cdrecTmp.info.vendor, cdrecTmp.info.prodId, cdrecTmp.info.rev,
	    ha, tgt, lun );
#ifdef DEBUG
  dbprintf( "akrip32: GetDriveInfo: %s", outBuf );
#endif

  strncpy( cdrecTmp.id, outBuf, MAXIDLEN );
  cdrecTmp.id[MAXIDLEN] = 0;

  if ( cdrec )
    *cdrec = cdrecTmp;

  return SS_COMP;
}


/***************************************************************************
 * Function Name    ReadTOC
 *
 * 
 ***************************************************************************/
uint32_t ReadTOC( HCDROM hCD, LPTOC toc )
{
  uint32_t dwStatus;
  uint32_t retVal = SS_COMP;
  HANDLE heventSRB;
  SRB_ExecSCSICmd s;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  if ( !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  memset( &s, 0, sizeof( s ) );
  s.SRB_Cmd        = SC_EXEC_SCSI_CMD;
  s.SRB_HaID       = cdHandles[idx].ha;
  s.SRB_Target     = cdHandles[idx].tgt;
  s.SRB_Lun        = cdHandles[idx].lun;
  s.SRB_Flags      = SRB_DIR_IN | SRB_EVENT_NOTIFY;
  s.SRB_BufLen     = 0x324;
  s.SRB_BufPointer = (BYTE FAR *)toc;
  s.SRB_SenseLen   = 0x0E;
  s.SRB_CDBLen     = 0x0A;
  s.SRB_PostProc   = (LPVOID)heventSRB;
  s.CDBByte[0]     = 0x43;
  s.CDBByte[1]     = cdHandles[idx].bMSF?0x02:0x00;
  //  s.CDBByte[1] = 0x02;               /* 0x02 == MSF format, 0x00 == LBA */
  s.CDBByte[7]     = 0x03;               /* length of buffer to hold TOC    */
  s.CDBByte[8]     = 0x24;               /*      == 0x324                   */

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );

  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, 4000 );
    }
  CloseHandle( heventSRB );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;
      retVal = SS_ERR;
    }

#ifdef DEBUG
  {
    FILE *fp = fopen( "toc.dat", "wb" );
    fwrite( toc, 1, sizeof(TOC), fp );
    fclose( fp );
  }
#endif

  ReleaseMutex( cdMutexes[idx] );
  return retVal;
}


/***************************************************************************
 * resetSCSIBus
 * 
 * According to Adaptec, this command can cause problems in Win95
 *
 ***************************************************************************/
void resetSCSIBus( void )
{
  uint32_t dwStatus;
  HANDLE heventSRB;
  SRB_BusDeviceReset s;

  dbprintf( "akrip32: reset bus!" );
  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  memset( &s, 0, sizeof( s ) );
  s.SRB_Cmd = SC_RESET_DEV;
  s.SRB_PostProc = (LPVOID)heventSRB;

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
  CloseHandle( heventSRB );

#ifdef DEBUG
  if ( s.SRB_Status != SS_COMP )
    {
      dbprintf( "akrip32: RESET BUS aspi status: 0x%08X\n", s.SRB_Status );
    }
#endif
}


/******************************************************************
 * GetCDList
 *
 * Scans all host adapters for CD-ROM units, and stores information
 * for all units located
 ******************************************************************/
int32_t GetCDList( LPCDLIST cd )
{
  SRB_HAInquiry sh;
  SRB_GDEVBlock sd;
  int32_t numAdapters, i, j, k;
  int32_t maxTgt;

  /* initialize cd list */
  maxTgt = cd->max;
  memset( cd, 0, sizeof(*cd) );
  cd->max = maxTgt;

  numAdapters = GetNumAdapters();
#ifdef DEBUG
  dbprintf( "AKRip32: GetCDList(): numAdapters == %d", numAdapters );
#endif
  if ( numAdapters == 0 )
    {
      alErrCode = ALERR_NOADAPTERS;
      return 1;
    }

  for( i = 0; i < numAdapters; i++ )
    {
      memset( &sh, 0, sizeof( sh ) );
      sh.SRB_Cmd   = SC_HA_INQUIRY;
      sh.SRB_HaID  = i;
      pfnSendASPI32Command( (LPSRB)&sh );

      /* on error skip to next adapter */
      if ( sh.SRB_Status != SS_COMP )
	continue;

      maxTgt = (int32_t)sh.HA_Unique[3];

      if ( maxTgt == 0 )
	maxTgt = 8;

      for( j = 0; j < maxTgt; j++ )
	{
	  for( k = 0; k < 8; k++ )
	    {
	      memset( &sd, 0, sizeof( sd ) );
	      sd.SRB_Cmd   = SC_GET_DEV_TYPE;
	      sd.SRB_HaID  = i;
	      sd.SRB_Target = j;
	      sd.SRB_Lun   = k;
	      pfnSendASPI32Command( (LPSRB)&sd );
	      if ( sd.SRB_Status == SS_COMP )
		{
		  if ( sd.SRB_DeviceType == DTYPE_CDROM )
		    {
		      cd->cd[cd->num].ha = i;
		      cd->cd[cd->num].tgt = j;
		      cd->cd[cd->num].lun = k;
		      memset( cd->cd[cd->num].id, 0, MAXIDLEN+1 );
		      GetDriveInfo( (BYTE)i, (BYTE)j, (BYTE)k, &(cd->cd[cd->num]) );
		      cd->num++;
		    }
#ifdef DEBUG
		  else
		    {
		      dbprintf( "       : sd.SRB_DeviceType == %d", sd.SRB_DeviceType );
		      GetDriveInfo( (BYTE)i, (BYTE)j, (BYTE)k, NULL );
		    }
#endif
		}
	    }
	}
    }

  if ( cd->num == 0 )
    alErrCode = ALERR_NOCDFOUND;

  return 1;
}


uint32_t ReadCDAudioLBA( HCDROM hCD, LPTRACKBUF t )
{
   int idx = (int)hCD - 1;
  uint32_t retVal;

  if ( (idx<0) || (idx>=MAXCDHAND) )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  retVal = WaitForSingleObject( cdMutexes[idx], TIMEOUT );
  if ( retVal != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  if ( !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

  retVal = cdHandles[idx].pfnRead( hCD, t );
  ReleaseMutex( cdMutexes[idx] );

  return retVal;
}


/*
 * Test the currently set read function.  Fills the buffer with 0xAA
 * prior to reading, and then checks the read area for a series of 0xAA
 * bytes.  This is because some read commands do not return an error, but
 * also don't read correct data map a full buffer.
 */
uint32_t testReadCDAudio( HCDROM hCD, LPTRACKBUF t )
{
  uint32_t i;
  uint32_t dwStatus;
  BYTE *p;
  int idx = (int)hCD - 1;
  int32_t count;

  // fill buffer with dummy data
  memset( t->buf, 0xAA, t->len );

  dwStatus = cdHandles[idx].pfnRead( hCD, t );
  if ( dwStatus != SS_COMP )
    {
      return dwStatus;
    }

  p = &(t->buf[t->startOffset]);
  for( i = 0, count = 0; i < t->len; i += 4 )
    {
      if ( *((uint32_t *)p) == 0xAAAAAAAA )
	count += 1;
      else
	count = 0;
      if ( count == 8 )
	{
	  return SS_ERR;
	}

      p += 4;
    }

  return dwStatus;
}


/***************************************************************************
 * readCDAudioLBA_ANY
 *
 * Attempts to autodetect the proper read function for the CD.  It tries
 * ATAPI2, ATAPI1, and then finally READ10
 *
 ***************************************************************************/
uint32_t readCDAudioLBA_ANY( HCDROM hCD, LPTRACKBUF t )
{
  uint32_t dwStatus;
  int idx = (int)hCD - 1;
  int32_t i, j;
  int32_t ord[7] = { 2, 1, 8, 4, 5, 6, 7 };

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  if ( t->numFrames * 2352 > t->maxLen )
    {
      alErrCode = ALERR_BUFTOOSMALL;
      return SS_ERR;
    }

  for( i = 0; i < 7; i++ )
    {
#ifdef DEBUG
      dbprintf( "akrip32: testing read fn %d", ord[i] );
#endif

      cdHandles[idx].readType = ord[i];
      cdHandles[idx].pfnRead = aReadFn[ord[i]];
      cdHandles[idx].pfnDeinit = NULL;
      cdHandles[idx].bInit = FALSE;

      for( j = 0; j < 3; j++ )
	{
	  dwStatus = testReadCDAudio( hCD, t );
	  if ( dwStatus == SS_COMP )
	    {
	      return dwStatus;
	    }
	}
    }


  // Failed to find compatible read mode, so we reset to the default
  // and return the error
  cdHandles[idx].readType = CDR_ANY;
  cdHandles[idx].pfnRead  = readCDAudioLBA_ANY;
  return dwStatus;
}


uint32_t GetASPI32SupportInfo( void )
{
  return pfnGetASPI32SupportInfo();
}


uint32_t SendASPI32Command( LPSRB s )
{
  return pfnSendASPI32Command( s );
}


#define _GEN_CDPARMS 0
uint32_t readCDParameters( HCDROM hCD, int bChangeMask )
{
  HANDLE h;
  SRB_ExecSCSICmd s;
  uint32_t d;
  BYTE b[256];
  int32_t lenData;
  BYTE *p;
  BYTE *pMax = b + 256;
  LPSENSEMASK psm;
  int idx = (int)hCD - 1;

#if _GEN_CDPARMS
  FILE *fp;
#endif

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  cdHandles[idx].smRead = FALSE;
  psm = &cdHandles[idx].sm;
  memset( psm, 0, sizeof( SENSEMASK ) );


  h = CreateEvent( NULL, TRUE, FALSE, NULL );
  memset( &s, 0, sizeof( s ) );
  memset( b, 0xFF, 256 );
  s.SRB_Cmd      = SC_EXEC_SCSI_CMD;
  s.SRB_HaID     = cdHandles[idx].ha;
  s.SRB_Target   = cdHandles[idx].tgt;
  s.SRB_Lun      = cdHandles[idx].lun;
  s.SRB_Flags    = SRB_DIR_IN | SRB_EVENT_NOTIFY;
  s.SRB_BufLen   = 256;
  s.SRB_BufPointer = b;
  s.SRB_CDBLen   = 12;
  s.SRB_PostProc = (LPVOID)h;
  s.CDBByte[0]   = 0x5A;
  s.CDBByte[2]   = 0x3F;
  s.CDBByte[7]   = 0x01;
  s.CDBByte[8]   = 0x00;

  /* do we want just a mask of changable items? */
  if ( bChangeMask )
    s.CDBByte[2] |= 0x40;

  ResetEvent( h );
  d = pfnSendASPI32Command( (LPSRB)&s );
  if ( d == SS_PENDING )
    {
      WaitForSingleObject( h, 500 );
    }
  CloseHandle( h );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

#if _GEN_CDPARMS
  fp = fopen( "cdparms.dat", "wb" );
  if ( fp )
    {
      fwrite( b, 1, 256, fp );
      fclose( fp );
    }
#endif

  lenData = ((uint32_t)b[0] << 8) + b[1];

  /* set to first sense mask, and then walk through the masks */
  p = b + 8;
  while( (p < &(b[2+lenData])) && (p < pMax) )
    {
      BYTE which;

      which = p[0] & 0x3F;
      switch( which )
	{
	case READERRREC:
	  psm->rerAvail = TRUE;
	  memcpy( psm->rer, p, p[1]+2 );
	  break;
	case CDRPARMS:
	  psm->cpmAvail = TRUE;
	  memcpy( psm->cpm, p, p[1]+2 );
	  break;
	case CDRAUDIOCTL:
	  psm->cacmAvail = TRUE;
	  memcpy( psm->cacm, p, p[1]+2 );
	  break;
	case CDRCAPS:
	  psm->ccsmAvail = TRUE;
	  memcpy( psm->ccsm, p, p[1]+2 );
	  break;
	}
      p += (p[1] + 2);
    }

  cdHandles[idx].smRead = TRUE;
  return s.SRB_Status;
}


/****************************************************************
 * Generic function to query CD unit capabilities and parameters
 *
 * which:   specifies the parm we wish to query
 * pNum:    pointer to uint32_t to return data
 *
 * returns: If the parm is not available, returns FALSE.  Otherwise
 *          returns TRUE.
 *
 * The data requested will either be returned as a int, map copied
 * to pNum, depending on the parameter requested.
 ****************************************************************/
int QueryCDParms( HCDROM hCD, int32_t which, uint32_t *pNum )
{
  int retVal = FALSE;
  uint32_t dwTmp;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return FALSE;
    }

  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR != FALSE;
    }

  if ( pNum )
    *pNum = 0;
  else
    pNum = &dwTmp;

  if ( !cdHandles[idx].smRead )
    {
      if ( readCDParameters( hCD, FALSE ) != SS_COMP )
	{
	  ReleaseMutex( cdMutexes[idx] );
	  return FALSE;
	}
    }

  switch( which )
    {
    case CDP_READCDR:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[2] & 0x01);
      break;

    case CDP_READCDE:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[2] & 0x02);
      break;

    case CDP_METHOD2:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[2] & 0x04);
      break;

    case CDP_WRITECDR:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[3] & 0x01);
      break;

    case CDP_WRITECDE:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[3] & 0x02);
      break;

    case CDP_AUDIOPLAY:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x01);
      break;

    case CDP_COMPOSITE:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x02);
      break;

    case CDP_DIGITAL1:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x04);
      break;

    case CDP_DIGITAL2:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x08);
      break;

    case CDP_M2FORM1:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x10);
      break;

    case CDP_M2FORM2:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x20);
      break;

    case CDP_MULTISES:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[4] & 0x40);
      break;

    case CDP_CDDA:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x01);
      break;

    case CDP_RW:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x04);
      break;

    case CDP_RWCORR:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x08);
      break;

    case CDP_C2SUPP:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x10);
      break;

    case CDP_ISRC:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x20);
      break;

    case CDP_UPC:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x40);
      break;

    case CDP_CANLOCK:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[6] & 0x01);
      break;

    case CDP_LOCKED:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[6] & 0x02);
      break;

    case CDP_PREVJUMP:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[6] & 0x04);
      break;

    case CDP_CANEJECT:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[6] & 0x08);
      break;

    case CDP_SEPVOL:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[7] & 0x01);
      break;

    case CDP_SEPMUTE:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[7] & 0x02);
      break;

    case CDP_SDP:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[7] & 0x04);
      break;

    case CDP_SSS:
      retVal = cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[7] & 0x08);
      break;

    case CDP_MECHTYPE:
      if ( cdHandles[idx].sm.ccsmAvail )
	{
	  retVal = TRUE;
	  *pNum = (uint32_t)(cdHandles[idx].sm.ccsm[6] >> 5);
	}
      break;

    case CDP_STREAMACC:
      return cdHandles[idx].sm.ccsmAvail && (cdHandles[idx].sm.ccsm[5] & 0x02);
      break;

    case CDP_MAXSPEED:
      if ( cdHandles[idx].sm.ccsmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.ccsm[8] << 8) + (uint32_t)cdHandles[idx].sm.ccsm[9];
	}
      break;

    case CDP_NUMVOL:
      if ( cdHandles[idx].sm.ccsmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.ccsm[10] << 8) + (uint32_t)cdHandles[idx].sm.ccsm[11];
	}
      break;

    case CDP_BUFSIZE:
      if ( cdHandles[idx].sm.ccsmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.ccsm[12] << 8) + (uint32_t)cdHandles[idx].sm.ccsm[13];
	}
      break;

    case CDP_CURRSPEED:
      if ( cdHandles[idx].sm.ccsmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.ccsm[14] << 8) + (uint32_t)cdHandles[idx].sm.ccsm[15];
	}
      break;

    case CDP_SPM:
      if ( cdHandles[idx].sm.cpmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.cpm[4] << 8) + (uint32_t)cdHandles[idx].sm.cpm[5];
	}
      break;

    case CDP_FPS:
      if ( cdHandles[idx].sm.cpmAvail )
	{
	  retVal = TRUE;
	  *pNum = ((uint32_t)cdHandles[idx].sm.cpm[6] << 8) + (uint32_t)cdHandles[idx].sm.cpm[7];
	}
      break;

    case CDP_INACTMULT:
      if ( cdHandles[idx].sm.cpmAvail )
	{
	  retVal = TRUE;
	  *pNum = (uint32_t)(cdHandles[idx].sm.cpm[3] & 0x0F);
	}
      break;

    case CDP_MSF:
      retVal = cdHandles[idx].bMSF;
      break;

    case CDP_JITTER:
      retVal = TRUE;
      *pNum = (uint32_t)(cdHandles[idx].numCheck);
      break;

    case CDP_OVERLAP:
      retVal = TRUE;
      *pNum = (uint32_t)(cdHandles[idx].numOverlap);
      break;

    case CDP_READMODE:
      retVal = TRUE;
      *pNum = (uint32_t)(cdHandles[idx].readMode);
      break;

    default:
      break;
    }

  ReleaseMutex( cdMutexes[idx] );
  return retVal;
}


/*
 * Complement to queryCDParms -- used to set values in the various control
 * pages on the CD drive.
 */
int ModifyCDParms( HCDROM hCD, int32_t which, uint32_t val )
{
  //SENSEMASK smask;
  //int smRead = FALSE;
  int retVal = FALSE;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return FALSE;
    }

  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR != FALSE;
    }

#if 0
  if ( readCDParameters( hCD, TRUE ) != SS_COMP )
    {
      ReleaseMutex( cdMutexes[idx] );
      return FALSE;
    }
#endif

  switch( which )
    {
    case CDP_CURRSPEED:
      if ( setCDSpeed( hCD, val ) == SS_COMP )
	retVal = TRUE;
      break;

    case CDP_MSF:
      cdHandles[idx].bMSF = val != FALSE;
      retVal = TRUE;
      break;

    case CDP_JITTER:
      cdHandles[idx].numCheck = (int32_t)val;
      retVal = TRUE;
      break;

    case CDP_OVERLAP:
      cdHandles[idx].numOverlap = (int32_t)val;
      retVal = TRUE;
      break;

    case CDP_READMODE:
      cdHandles[idx].readMode = (int32_t)val;
      retVal = TRUE;
      break;
    }

  ReleaseMutex( cdMutexes[idx] );
  return retVal;
}


/*
 * Speed is specified in KB/sec: 1x == 176, 2x == 353, 4x == 706
 *
 * To set to the maximum allowed speed, specify 0xFFFF.  Attempting to set
 * a speed higher than the allowed maximum speed should not cause an error,
 * but should set the speed at the highest allowed value.
 */
uint32_t setCDSpeed( HCDROM hCD, uint32_t speed )
{
  uint32_t dwStatus;
  HANDLE heventSRB;
  SRB_ExecSCSICmd s;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  memset( &s, 0, sizeof( s ) );

  s.SRB_Cmd      = SC_EXEC_SCSI_CMD;
  s.SRB_HaID     = cdHandles[idx].ha;
  s.SRB_Target   = cdHandles[idx].tgt;
  s.SRB_Lun      = cdHandles[idx].lun;
  s.SRB_Flags    = SRB_DIR_OUT | SRB_EVENT_NOTIFY;
  s.SRB_SenseLen = SENSE_LEN;
  s.SRB_CDBLen   = 12;
  s.SRB_PostProc = (LPVOID)heventSRB;
  s.CDBByte[0]   = 0xBB;
  s.CDBByte[2]   = (BYTE)(speed >> 8);
  s.CDBByte[3]   = (BYTE)speed;

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
  CloseHandle( heventSRB );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;
      CloseHandle( cdMutexes[idx] );
      return SS_ERR;
    }

  return s.SRB_Status;
}


uint32_t pauseResumeCD( HCDROM hCD, int bPause )
{
  uint32_t dwStatus;
  HANDLE heventSRB;
  SRB_ExecSCSICmd s;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  memset( &s, 0, sizeof( s ) );

  s.SRB_Cmd      = SC_EXEC_SCSI_CMD;
  s.SRB_HaID     = cdHandles[idx].ha;
  s.SRB_Target   = cdHandles[idx].tgt;
  s.SRB_Lun      = cdHandles[idx].lun;
  s.SRB_Flags    = SRB_EVENT_NOTIFY;
  s.SRB_SenseLen = SENSE_LEN;
  s.SRB_CDBLen   = 10;
  s.SRB_PostProc = (LPVOID)heventSRB;
  s.CDBByte[0]   = 0x4B;
  s.CDBByte[8]   = bPause?0:1;

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
  CloseHandle( heventSRB );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

  ReleaseMutex( cdMutexes[idx] );
  return s.SRB_Status;
}


uint32_t startStopUnit( HCDROM hCD, int bLoEj, int bStart )
{
  uint32_t dwStatus;
  HANDLE heventSRB;
  SRB_ExecSCSICmd s;
  int idx = (int)hCD - 1;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }
 
  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

  memset( &s, 0, sizeof( s ) );

  s.SRB_Cmd      = SC_EXEC_SCSI_CMD;
  s.SRB_HaID     = cdHandles[idx].ha;
  s.SRB_Target   = cdHandles[idx].tgt;
  s.SRB_Lun      = cdHandles[idx].lun;
  s.SRB_Flags    = SRB_EVENT_NOTIFY;
  s.SRB_SenseLen = SENSE_LEN;
  s.SRB_CDBLen   = 6;
  s.SRB_PostProc = (LPVOID)heventSRB;
  s.CDBByte[0]   = 0x1B;
  s.CDBByte[4]  |= bLoEj?0x02:0x00;
  s.CDBByte[4]  |= bStart?0x01:0x00;

  ResetEvent( heventSRB );
  dwStatus = pfnSendASPI32Command( (LPSRB)&s );
  if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
  CloseHandle( heventSRB );

  if ( s.SRB_Status != SS_COMP )
    {
      alErrCode = ALERR_ASPI;
      alAspiErr = s.SRB_Status;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

  ReleaseMutex( cdMutexes[idx] );
  return s.SRB_Status;
}


/****************************************************************
 * GetAspiLibError
 *
 * Used after functions return SS_ERR to get more specific error
 * information.  If it returns AL_ERRASPI, call getAspiLibAspiError
 * to get the actual status code returned by the calls to the ASPI
 * manager.  After reading, the error code is cleared.
 *
 ****************************************************************/
int32_t GetAspiLibError( void )
{
  int32_t retVal;

  retVal = alErrCode;
  alErrCode = ALERR_NOERROR;

  return retVal;
}


/****************************************************************
 * GetAspiLibAspiError
 *
 * Returns the last error completion code from the ASPI manager.
 * After reading, the error code is cleared.
 *
 ****************************************************************/
BYTE GetAspiLibAspiError( void )
{
  BYTE retVal;

  retVal = alAspiErr;
  alAspiErr = SS_COMP;

  return retVal;
}


/****************************************************************
 * GetCDId
 *
 * Generates an identifier string for the CD drive identified by
 * hCD
 *
 ****************************************************************/
uint32_t  GetCDId( HCDROM hCD, char *buf, int32_t maxBuf )
{
   int idx = (int)hCD - 1;
  CDREC cd;

  if ( (idx<0) || (idx>=MAXCDHAND) || !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  if ( !buf )
    {
      alErrCode = ALERR_BUFPTR;
      return SS_ERR;
    }

  if ( WaitForSingleObject( cdMutexes[idx], TIMEOUT ) != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  memset( &cd, 0, sizeof(cd) );
  GetDriveInfo( cdHandles[idx].ha, cdHandles[idx].tgt, cdHandles[idx].lun,
		&cd );
  if ( strlen( cd.id ) > (size_t)(maxBuf-1) )
    {
      alErrCode = ALERR_BUFTOOSMALL;
      strncpy( buf, cd.id, maxBuf );
      buf[maxBuf-1] = '\0';
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }
  else
    strcpy( buf, cd.id );

  ReleaseMutex( cdMutexes[idx] );
  return SS_COMP;
}


int allZeros( LPTRACKBUF t )
{
  uint32_t i;
  uint8_t *p = &t->buf[t->startOffset]; 

  for( i = 0; i < t->len; i++ )
    if ( p[i] != 0 )
      return FALSE;

  return TRUE;
}


/*
 * Returns TRUE if the overlap buffer is located in the track buffer.  The
 * track buffer startOffset is adjusted to reflect where in the buffer the
 * aligned data begins.  numFrames and len are also adjusted to reflect the
 * number of complete frames are contained in the buffer.
 */
int32_t jitterAdjust( LPTRACKBUF tbuf, LPTRACKBUF tover, int32_t checkFrames )
{
  int32_t i;
  int32_t max;
  int32_t bFound = 0;
  BYTE *p;
  int32_t checkLen = checkFrames * 2352;

  max = tbuf->len - checkLen;

  if ( tover->len == 0 || allZeros( tover ) )
    {
      return 1;
    }

  p = &tover->buf[tover->startOffset];

  bFound = 0;
  for( i = 0; i < max; i++ )
    {
      if ( compBuf( p, &(tbuf->buf[i]), checkLen ) )
	{
	  tbuf->startOffset = i + checkLen;
	  tbuf->len -= (i + checkLen);
	  tbuf->startFrame = tover->startFrame + checkFrames;
	  i = max + 1;
	  bFound = -1;
	}
    }

  /* adjust frame count and crop length */
  tbuf->numFrames = tbuf->len / 2352;
  tbuf->len = 2352 * tbuf->numFrames;

  //  return (tbuf->startOffset == 0);
  return bFound;
}


/*
 * Reads CD-DA audio, implementing jitter correction.  tOver is used to align
 * the current read, if possible.  After a successful read, numOverlap frames
 * are copied to tOver.
 */
uint32_t ReadCDAudioLBAEx( HCDROM hCD, LPTRACKBUF t, LPTRACKBUF tOver )
{
  uint32_t retVal;
  int idx = (int)hCD - 1;
  int32_t j, o;
  uint8_t *pOverAddr;
  int bJitterCorr, bSaveJitter;

  if ( (idx<0) || (idx>=MAXCDHAND) )
    {
      alErrCode = ALERR_INVHANDLE;
      return SS_ERR;
    }

  retVal = WaitForSingleObject( cdMutexes[idx], TIMEOUT );
  if ( retVal != WAIT_OBJECT_0 )
    {
      alErrCode = ALERR_LOCK;
      return SS_ERR;
    }

  if ( !cdHandles[idx].used )
    {
      alErrCode = ALERR_INVHANDLE;
      ReleaseMutex( cdMutexes[idx] );
      return SS_ERR;
    }

  j = cdHandles[idx].numCheck;
  o = cdHandles[idx].numOverlap;

  bSaveJitter = ((tOver->maxLen / 2352) >= (uint32_t)j);
  bJitterCorr = bSaveJitter && !allZeros( tOver );

  // adjust the starting address of the read if necessary
  if ( bJitterCorr && tOver->startFrame && tOver->numFrames && tOver->len )
    {
      uint32_t numFrames;

      numFrames = t->numFrames;

      // is this tOver from the last sequential read?
      if ( tOver->startFrame == (t->startFrame - j) )
	{
	  t->startFrame -= o;
	  // detect situation when trying to read less than the overlap buffer
	  if ( (numFrames <= (uint32_t)o) && ((numFrames + o) <= (t->maxLen/2352)))
	    {
	      t->numFrames += o;
	    }
#ifdef DEBUG
	  dbprintf( "rolling back start frame to %d", t->startFrame );
#endif
	}
      else
	{
	  tOver->len = tOver->startFrame = tOver->numFrames = 0;
#ifdef DEBUG
	  dbprintf( "zeroing out overlap buffer" );
#endif
	}
    }

  retVal = cdHandles[idx].pfnRead( hCD, t );

  if ( retVal == SS_COMP )
    {
      if ( bJitterCorr )
	{
	  j = cdHandles[idx].numCheck;
	  if ( !jitterAdjust( t, tOver, j ) )
	    {
#ifdef DEBUG
	      dbprintf( "akrip32: ... jitterAdjust failed!" );
#endif
	      alErrCode = ALERR_JITTER;
	      ReleaseMutex( cdMutexes[idx] );
	      return SS_ERR;
	    }
	}

      if ( bSaveJitter )
	{
	  pOverAddr = &(t->buf[2352*(t->numFrames-j)+t->startOffset]);
	  memcpy( tOver->buf, pOverAddr, 2352*j );

	  tOver->startFrame = t->startFrame + t->numFrames - j;
	  tOver->numFrames = j;
	  tOver->len = 2352 * j;
	  tOver->startOffset = 0;
	}
      else
	{
	  tOver->startFrame = tOver->numFrames = tOver->len = 0;
	}
    }
#ifdef DEBUG
  else
    dbprintf( "akrip32: ReadCDAudioLBAEx: read failed" );
#endif

  ReleaseMutex( cdMutexes[idx] );

#ifdef DEBUG
  dbprintf( "akrip32: readCDAudioLBAEx: returning %04X", retVal );
#endif

  return retVal;
}


/********************************************************************
 * compBuf
 *
 * Compares two buffers up to n bytes, returning 1 if they contain the
 * same data, map zero if they are different.
 *
 ********************************************************************/
int32_t compBuf( BYTE *b1, BYTE *b2, int32_t n )
{
#if 0
  int32_t i;

  for( i = 0; i < n; i++ )
    if ( b1[i] != b2[i] )
      {
	return 0;
      }

  return 1;
#else
  return !memcmp( b1, b2, n );
#endif
}



uint32_t GetAKRipDllVersion( void )
{
  uint32_t retVal;

  retVal = (uint32_t)( (((WORD)MAJVER)<<16) | (WORD)MINVER );
  return retVal;
}


void dbprintf( char *fmt, ... )
{
  char buf[512];
  va_list arg;

  va_start( arg, fmt );

  vsprintf( buf, fmt, arg );
  OutputDebugStringA( buf );

  va_end( arg );
}


uint32_t GetInterfaceID( void )
{
  return dwAPI;
}
