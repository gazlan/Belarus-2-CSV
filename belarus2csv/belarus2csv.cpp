/* ******************************************************************** **
** @@ Belarus-2-CSV
** @  Copyrt :
** @  Author :
** @  Update :
** @  Update :
** @  Notes  : Printed Belarus Registry 2013-08 output converter
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

#include "..\shared\file_find.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#endif

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#define TAG_LINE              "-----------------------"
#define TAG_TITLE             "TITLE:"
#define TAG_FORM              "FORM:"
#define TAG_YEAR              "YEAR:"
#define TAG_ZIP               "ZIP:"
#define TAG_COUNTRY           "COUNTRY:"
#define TAG_REGION            "REGION:"
#define TAG_COUNT             "COUNT:"
#define TAG_PREFIX            "PREFIX:"
#define TAG_ADDRESS           "ADDRESS:"
#define TAG_LIDER             "LIDER:"
#define TAG_FAX               "FAX:"
#define TAG_PHONES            "PHONES:"
#define TAG_RECLAMA           "RECLAMA:"
#define TAG_COMMENT           "COMMENT:"
#define TAG_EMAIL             "EMAIL:"
#define TAG_WEB               "WEB:"
#define TAG_PROFILE           "PROFILE:"

enum E_LINE_MODE
{
   eTAG_NONE,
   eTAG_LINE,
   eTAG_TITLE,
   eTAG_FORM,
   eTAG_YEAR,
   eTAG_ZIP,
   eTAG_COUNTRY,
   eTAG_REGION,
   eTAG_COUNT,
   eTAG_PREFIX,
   eTAG_ADDRESS,
   eTAG_LIDER,
   eTAG_FAX,
   eTAG_PHONES,
   eTAG_RECLAMA,
   eTAG_COMMENT,
   eTAG_EMAIL,
   eTAG_WEB,
   eTAG_PROFILE
};

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

static CString    sTITLE   = _T("");
static CString    sFORM    = _T("");
static CString    sYEAR    = _T("");
static CString    sZIP     = _T("");
static CString    sCOUNTRY = _T("");
static CString    sREGION  = _T("");
static CString    sCOUNT   = _T("");
static CString    sPREFIX  = _T("");
static CString    sADDRESS = _T("");
static CString    sLIDER   = _T("");
static CString    sFAX     = _T("");
static CString    sPHONES  = _T("");
static CString    sRECLAMA = _T("");
static CString    sCOMMENT = _T("");
static CString    sEMAIL   = _T("");
static CString    sWEB     = _T("");
static CString    sPROFILE = _T("");

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ ResetRecord()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void ResetRecord()
{
   sTITLE   = _T("");
   sFORM    = _T("");
   sYEAR    = _T("");
   sZIP     = _T("");
   sCOUNTRY = _T("");
   sREGION  = _T("");
   sCOUNT   = _T("");
   sPREFIX  = _T("");
   sADDRESS = _T("");
   sLIDER   = _T("");
   sFAX     = _T("");
   sPHONES  = _T("");
   sRECLAMA = _T("");
   sCOMMENT = _T("");
   sEMAIL   = _T("");
   sWEB     = _T("");
   sPROFILE = _T("");
}

/* ******************************************************************** **
** @@ DumpRecord()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void DumpRecord(FILE* pOut)
{
   if (!pOut)
   {
      // Error !
      ASSERT(0);
      return;
   }

   if (sTITLE.IsEmpty())
   {
      // Empty Record
      return;
   }
   
   fprintf
   (
      pOut,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
      sTITLE, sFORM, sYEAR, sZIP, sCOUNTRY, sREGION, sCOUNT, sPREFIX, sADDRESS, sLIDER, sFAX, sPHONES, sRECLAMA, sCOMMENT, sEMAIL, sWEB, sPROFILE
   );
}

/* ******************************************************************** **
** @@ Normalize()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Normalize(CString& rField)
{
   rField.TrimLeft();
   rField.TrimRight();

   rField.Replace('\"','\'');

   while (rField.Replace("\x20\x20","\x20"))
   {
      ;  // Do nothing !
   }
}

/* ******************************************************************** **
** @@ Proceed()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void Proceed(const char* const pszFileName)
{
   char     pszCSVName[_MAX_PATH];
   char     pszDrive  [_MAX_DRIVE];
   char     pszDir    [_MAX_DIR];
   char     pszFName  [_MAX_FNAME];
   char     pszExt    [_MAX_EXT];

   _splitpath(pszFileName,pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszCSVName, pszDrive,pszDir,pszFName,"csv");

   FILE*    pIn = fopen(pszFileName,"rt");

   if (!pIn)
   {
      perror("\a\nOpen Input File Error !\n");
      return;
   }

   FILE*    pOut = fopen(pszCSVName,"wt");

   if (!pOut)
   {
      perror("\a\nOpen Output File Error !\n");
      fclose(pIn);
      pIn = NULL;
      return;
   }

   fprintf(pOut,"\"TITLE\",\"FORM\",\"YEAR\",\"ZIP\",\"COUNTRY\",\"REGION\",\"COUNT\",\"PREFIX\",\"ADDRESS\",\"LIDER\",\"FAX\",\"PHONES\",\"RECLAMA\",\"COMMENT\",\"EMAIL\",\"WEB\",\"PROFILE\"\n");

   const DWORD    BUF_SIZE = (0x01 << 20);   // About 1 Mb !

   char*    pBuf = new char[BUF_SIZE];

   E_LINE_MODE    Mode = eTAG_NONE;

   while (fgets(pBuf,BUF_SIZE,pIn))
   {
      pBuf[BUF_SIZE - 1] = 0; // ASCIIZ !

      DWORD    dwEOL = strcspn(pBuf,"\r\n");

      pBuf[dwEOL] = 0;  // Remove EOL chars

      // Mapping
      if (!*pBuf)
      {
         // Nothing to do !
         continue;
      }
      else if (!strncmp(pBuf,TAG_LINE,sizeof(TAG_LINE) - 1))
      {
         Mode = eTAG_LINE;
      }
      else if (!strncmp(pBuf,TAG_TITLE,sizeof(TAG_TITLE) - 1))
      {
         Mode = eTAG_TITLE;
      }
      else if (!strncmp(pBuf,TAG_FORM,sizeof(eTAG_FORM) - 1))
      {
         Mode = eTAG_FORM;
      }
      else if (!strncmp(pBuf,TAG_YEAR,sizeof(TAG_YEAR) - 1))
      {
         Mode = eTAG_YEAR;
      }
      else if (!strncmp(pBuf,TAG_ZIP,sizeof(TAG_ZIP) - 1))
      {
         Mode = eTAG_ZIP;
      }
      else if (!strncmp(pBuf,TAG_COUNTRY,sizeof(TAG_COUNTRY) - 1))
      {
         Mode = eTAG_COUNTRY;
      }
      else if (!strncmp(pBuf,TAG_REGION,sizeof(TAG_REGION) - 1))
      {
         Mode = eTAG_REGION;
      }
      else if (!strncmp(pBuf,TAG_COUNT,sizeof(TAG_COUNT) - 1))
      {
         Mode = eTAG_COUNT;
      }
      else if (!strncmp(pBuf,TAG_PREFIX,sizeof(TAG_PREFIX) - 1))
      {
         Mode = eTAG_PREFIX;
      }
      else if (!strncmp(pBuf,TAG_ADDRESS,sizeof(TAG_ADDRESS) - 1))
      {
         Mode = eTAG_ADDRESS;
      }
      else if (!strncmp(pBuf,TAG_LIDER,sizeof(TAG_LIDER) - 1))
      {
         Mode = eTAG_LIDER;
      }
      else if (!strncmp(pBuf,TAG_FAX,sizeof(TAG_FAX) - 1))
      {
         Mode = eTAG_FAX;
      }
      else if (!strncmp(pBuf,TAG_PHONES,sizeof(TAG_PHONES) - 1))
      {
         Mode = eTAG_PHONES;
      }
      else if (!strncmp(pBuf,TAG_RECLAMA,sizeof(TAG_RECLAMA) - 1))
      {
         Mode = eTAG_RECLAMA;
      }
      else if (!strncmp(pBuf,TAG_COMMENT,sizeof(TAG_COMMENT) - 1))
      {
         Mode = eTAG_COMMENT;
      }
      else if (!strncmp(pBuf,TAG_EMAIL,sizeof(TAG_EMAIL) - 1))
      {
         Mode = eTAG_EMAIL;
      }
      else if (!strncmp(pBuf,TAG_WEB,sizeof(TAG_WEB) - 1))
      {
         Mode = eTAG_WEB;
      }
      else if (!strncmp(pBuf,TAG_PROFILE,sizeof(TAG_PROFILE) - 1))
      {
         Mode = eTAG_PROFILE;
      }

      switch (Mode)
      {
         case eTAG_LINE:
         {
            // Write OLD Record
            DumpRecord(pOut);
            // and start NEW one
            ResetRecord();
            break;
         }
         case eTAG_TITLE:
         {
            sTITLE += pBuf + sizeof(TAG_TITLE) - 1;

            Normalize(sTITLE);
            break;
         }
         case eTAG_FORM:
         {
            sFORM += pBuf + sizeof(TAG_FORM) - 1;

            Normalize(sFORM);
            break;
         }
         case eTAG_YEAR:
         {
            sYEAR += pBuf + sizeof(TAG_YEAR) - 1;

            Normalize(sYEAR);
            break;
         }
         case eTAG_ZIP:
         {
            sZIP += pBuf + sizeof(TAG_ZIP) - 1;

            Normalize(sZIP);
            break;
         }
         case eTAG_COUNTRY:
         {
            sCOUNTRY += pBuf + sizeof(TAG_COUNTRY) - 1;

            Normalize(sCOUNTRY);
            break;
         }
         case eTAG_REGION:
         {
            sREGION += pBuf + sizeof(TAG_REGION) - 1;

            Normalize(sREGION);
            break;
         }
         case eTAG_COUNT:
         {
            sCOUNT += pBuf + sizeof(TAG_COUNT) - 1;

            Normalize(sCOUNT);
            break;
         }
         case eTAG_PREFIX:
         {
            sPREFIX += pBuf + sizeof(TAG_PREFIX) - 1;

            Normalize(sPREFIX);
            break;
         }
         case eTAG_ADDRESS:
         {
            sADDRESS += pBuf + sizeof(TAG_ADDRESS) - 1;

            Normalize(sADDRESS);
            break;
         }
         case eTAG_LIDER:
         {
            sLIDER += pBuf + sizeof(TAG_LIDER) - 1;

            Normalize(sLIDER);
            break;
         }
         case eTAG_FAX:
         {
            sFAX += pBuf + sizeof(TAG_FAX) - 1;

            Normalize(sFAX);
            break;
         }
         case eTAG_PHONES:
         {
            if (sPHONES.IsEmpty())
            {
               // First Line !
               sPHONES += pBuf + sizeof(TAG_PHONES) - 1;
            }
            else
            {
               // Mext Line
               sPHONES += "\x20";
               sPHONES += pBuf;
            }

            Normalize(sPHONES);
            break;
         }
         case eTAG_RECLAMA:
         {
            sRECLAMA += pBuf + sizeof(TAG_RECLAMA) - 1;

            Normalize(sRECLAMA);
            break;
         }
         case eTAG_COMMENT:
         {
            sCOMMENT += pBuf + sizeof(TAG_COMMENT) - 1;

            Normalize(sCOMMENT);
            break;
         }
         case eTAG_EMAIL:
         {
            sEMAIL += pBuf + sizeof(TAG_EMAIL) - 1;

            Normalize(sEMAIL);
            break;
         }
         case eTAG_WEB:
         {
            sWEB += pBuf + sizeof(TAG_WEB) - 1;

            Normalize(sWEB);
            break;
         }
         case eTAG_PROFILE:
         {
            if (sPROFILE.IsEmpty())
            {
               // First Line !
               sPROFILE += pBuf + sizeof(TAG_PROFILE) - 1;
            }
            else
            {
               // Mext Line
               sPROFILE += "\x20";
               sPROFILE += pBuf;
            }

            Normalize(sPROFILE);
            break;
         }
         default:
         {
            // Error !
            ASSERT(0);
            break;
         }
      }
   }

   delete[] pBuf;
   pBuf = NULL;

   fclose(pIn);
   pIn = NULL;

   fclose(pOut);
   pOut = NULL;
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void ShowHelp()
{
   const char  pszCopyright[] = "-*-   Belarus-2-CSV  *  (c) gazlan@yandex.ru, 2016   -*-";
   const char  pszDescript [] = "Printed Belarus Registry 2013-08 output converter";
   const char  pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: belarus2csv.com wildcards\n\n");
   printf("%s\n",pszE_Mail);
}

/* ******************************************************************** **
** @@ main()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

int main(int argc,char** argv)
{
   if (argc != 2)
   {
      ShowHelp();
      return 0;
   }

   if (argc == 2 && ((!strcmp(argv[1],"?")) || (!strcmp(argv[1],"/?")) || (!strcmp(argv[1],"-?")) || (!stricmp(argv[1],"/h")) || (!stricmp(argv[1],"-h"))))
   {
      ShowHelp();
      return 0;
   }

   FindFile   FF;

   FF.SetMask(argv[1]);

   while (FF.Fetch())
   {
      if ((FF._w32fd.dwFileAttributes | FILE_ATTRIBUTE_NORMAL) && !(FF._w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
         Proceed(FF._w32fd.cFileName);
      }
   }

   return 0;
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
