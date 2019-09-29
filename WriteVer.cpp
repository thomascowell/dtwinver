#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "Dtwinver.h"

#pragma warning(disable: 26432)
#pragma warning(disable: 26440)
#pragma warning(disable: 26439)
#pragma warning(disable: 26472)
#pragma warning(disable: 26481)
#pragma warning(disable: 26485)
#pragma warning(disable: 26486)
#pragma warning(disable: 26477)


//The CWriteVerCommandLineInfo class aids in parsing the 
//command line at application startup. The 
//structure is styled upon the MFC class CCommandLineInfo
class CWriteVerCommandLineInfo
{
public:
// Constructors / Destructors
  CWriteVerCommandLineInfo();
  virtual ~CWriteVerCommandLineInfo()
  {
  };

//Methods
  virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);

//Member variables
  TCHAR m_pszFilename[_MAX_PATH];
};


#pragma warning(suppress: 26455)
CWriteVerCommandLineInfo::CWriteVerCommandLineInfo()
{
  m_pszFilename[0] = _T('\0');
}

void CWriteVerCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL /*bLast*/)
{
  if (!bFlag)
  {
    _tcscpy_s(m_pszFilename, sizeof(m_pszFilename)/sizeof(TCHAR), pszParam);
  }
}

//Based upon the function of the same name in CWinApp
void ParseCommandLine(CWriteVerCommandLineInfo& rCmdInfo)
{
  for (int i=1; i<__argc; i++)
  {
  #ifdef _UNICODE
#pragma warning(suppress: 26429 26481)
      LPCTSTR pszParam = __wargv[i];
  #else
#pragma warning(suppress: 26429 26481)
    LPCTSTR pszParam = __argv[i];
  #endif
    BOOL bFlag = FALSE;
    const BOOL bLast = ((i + 1) == __argc);
    if (pszParam[0] == _T('-') || pszParam[0] == _T('/'))
    {
      // remove flag specifier
      bFlag = TRUE;
      ++pszParam;
    }
    rCmdInfo.ParseParam(pszParam, bFlag, bLast);
  }
}

#ifdef _UNICODE
int wmain()
#else
int main()
#endif
{  
  //Parse the command line
  CWriteVerCommandLineInfo CmdInfo;
#pragma warning(suppress: 26486)
  ParseCommandLine(CmdInfo);

  //Assume the best
  DWORD dwErrorCode = ERROR_SUCCESS;

  if (_tcslen(CmdInfo.m_pszFilename))
  {
    //The line which will be written to disk
    TCHAR szWriteBuf[1024];
    szWriteBuf[0] = '\0';

    //Get the OS details
    COSVersion::OS_VERSION_INFO osvi;
    memset(&osvi, 0, sizeof(osvi));
    COSVersion os;  
    if (os.GetVersion(&osvi))
      _stprintf_s(szWriteBuf, sizeof(szWriteBuf)/sizeof(TCHAR), _T("%u\t%u\t%u\t%d\t%d\t%d\t%u\t%u\t%u\t%d\t%d\t%s\t%u\t%u"), osvi.dwUnderlyingMajorVersion, osvi.dwUnderlyingMinorVersion, 
                  osvi.dwUnderlyingBuildNumber, osvi.UnderlyingPlatform, static_cast<int>(osvi.wUnderlyingServicePackMajor), static_cast<int>(osvi.wUnderlyingServicePackMinor), 
                  osvi.dwSuiteMask, osvi.dwSuiteMask2, osvi.dwSuiteMask3, osvi.OSType, osvi.UnderlyingProcessorType, osvi.szUnderlyingCSDVersion, osvi.dwUBR, osvi.dwProductType);

    //Open the file we want to write to
    HANDLE hFile = CreateFile(CmdInfo.m_pszFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
      //handle the error
      return GetLastError();
    }

  #ifdef _UNICODE
    char szAsciiWriteBuf[1024];
    szAsciiWriteBuf[0] = '\0';
    if (WideCharToMultiByte(CP_ACP, 0, szWriteBuf, -1, szAsciiWriteBuf, sizeof(szAsciiWriteBuf), NULL, NULL) == 0)
    {
      dwErrorCode = GetLastError();
      CloseHandle(hFile);
      return dwErrorCode;
    }
    const char* pszAsciiWriteBuf = szAsciiWriteBuf;
  #else
    const char* pszAsciiWriteBuf = szWriteBuf;
  #endif

    //And write the OS version info to the designated file
    DWORD dwBytesWritten = 0;
    if (!WriteFile(hFile, pszAsciiWriteBuf, static_cast<DWORD>(strlen(pszAsciiWriteBuf)), &dwBytesWritten, 0))
    {
      dwErrorCode = GetLastError();
    }

    //Close the file now that we are finished with it
    CloseHandle(hFile);
  }
  else
    dwErrorCode = ERROR_FILE_NOT_FOUND;

  return dwErrorCode;
}
