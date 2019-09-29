//For this test program only use the old style wsprintf API
#ifdef _UNICODE
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif //#ifdef _UNICODE

#include <windows.h> 
#if defined(_WIN32) || defined(_WIN64)
#include <tchar.h>
#endif //#if defined(_WIN32) || defined(_WIN64)
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "dtwinver.h"

#if defined(COSVERSION_WIN16_OR_DOS)
  #define _tcscat   strcat
  #define _stprintf sprintf
#endif //#if defined(COSVERSION_WIN16_OR_DOS)

#ifndef _In_
#define _In_
#endif //#ifndef _In_

#ifndef _In_opt_
#define _In_opt_
#endif //#ifndef _In_opt_

#pragma warning(disable: 26485)
#pragma warning(disable: 26493)
#pragma warning(disable: 26477)

#if defined(_WINDOWS)
#if defined(_UNICODE)
#if _MSC_VER >= 900
#pragma warning(suppress: 28251)
#endif //#if _MSC_VER >= 900
int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
#else
#if defined _CONSOLE
void main()
#else
#if _MSC_VER >= 900
#pragma warning(suppress: 28251)
#endif //#if _MSC_VER >= 900
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPTSTR, _In_ int)
#endif //if defined _CONSOLE
#endif //if defined(_UNICODE)
#elif defined(UNDER_CE)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#else
int main()
#endif //#if defined(_WINDOWS)
{
  COSVersion::OS_VERSION_INFO osvi;
  memset(&osvi, 0, sizeof(osvi));
#ifdef _WIN32
  TCHAR sText[2048];
  sText[0] = _T('\0');
  TCHAR sBuf[100];
  sBuf[0] = _T('\0');
#else
  char sText[2048];
  char sBuf[100];
#endif //#ifdef _WIN32

  COSVersion os;
  if (os.GetVersion(&osvi))
  {
  #ifndef UNDER_CE
    _stprintf(sText, _T("Emulated OS: "));

    switch (osvi.EmulatedPlatform)
    {
      case COSVersion::Dos:
      {
        _tcscat(sText, _T("DOS"));
        break;
      }
      case COSVersion::Windows3x:
      {
        _tcscat(sText, _T("Windows"));
        break;
      }
      case COSVersion::WindowsCE:
      {
        //This code will never really be executed, but for the same of completeness include it here
        if (os.IsWindowsEmbeddedCompact(&osvi, FALSE))
          _tcscat(sText, _T("Windows Embedded Compact"));
        else if (os.IsWindowsCENET(&osvi, FALSE))
          _tcscat(sText, _T("Windows CE .NET"));
        else
          _tcscat(sText, _T("Windows CE"));
        break;
      }
      case COSVersion::Windows9x:
      {
        if (os.IsWindows95(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 95"));
        else if (os.IsWindows95SP1(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 95 SP1"));
        else if (os.IsWindows95B(&osvi, FALSE))
          _stprintf(sBuf,  _T("Windows 95 B [aka OSR2]"));
        else if (os.IsWindows95C(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 95 C [aka OSR2.5]"));
        else if (os.IsWindows98(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 98"));
        else if (os.IsWindows98SP1(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 98 SP1"));
        else if (os.IsWindows98SE(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows 98 Second Edition"));
        else if (os.IsWindowsME(&osvi, FALSE))
          _stprintf(sBuf, _T("Windows Millenium Edition"));
        else
          _stprintf(sBuf, _T("Windows \?\?"));
        _tcscat(sText, sBuf);
        break;
      }
      case COSVersion::WindowsNT:
      {
        if (os.IsNTPreWin2k(&osvi, FALSE))
        {
          _tcscat(sText,  _T("Windows NT"));

          if (os.IsNTWorkstation(&osvi, FALSE))
            _tcscat(sText, _T(" (Workstation)"));
          else if (os.IsNTStandAloneServer(&osvi, FALSE))
            _tcscat(sText, _T(" (Server)"));
          else if (os.IsNTPDC(&osvi, FALSE))
            _tcscat(sText, _T(" (Primary Domain Controller)"));
          else if (os.IsNTBDC(&osvi, FALSE))
            _tcscat(sText, _T(" (Backup Domain Controller)"));

          if (os.IsNTDatacenterServer(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter)"));
          else if (os.IsNTEnterpriseServer(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise)"));
        }
        else if (os.IsWindows2000(&osvi, FALSE))
        {
          if (os.IsProfessional(&osvi))
            _tcscat(sText, _T("Windows 2000 (Professional)"));
          else if (os.IsWindows2000Server(&osvi, FALSE))
            _tcscat(sText, _T("Windows 2000 Server"));
          else if (os.IsWindows2000DomainController(&osvi, FALSE))
            _tcscat(sText, _T("Windows 2000 (Domain Controller)"));
          else 
            _tcscat(sText, _T("Windows 2000"));

          if (os.IsWindows2000DatacenterServer(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter)"));
          else if (os.IsWindows2000AdvancedServer(&osvi, FALSE))
            _tcscat(sText, _T(", (Advanced Server)"));
        }
        else if (os.IsWindowsXPOrWindowsServer2003(&osvi, FALSE))
        {
          if (os.IsStarterEdition(&osvi))
            _tcscat(sText, _T("Windows XP (Starter Edition)"));
          else if (os.IsPersonal(&osvi))
            _tcscat(sText, _T("Windows XP (Personal)"));
          else if (os.IsProfessional(&osvi))
            _tcscat(sText, _T("Windows XP (Professional)"));
          else if (os.IsWindowsServer2003(&osvi, FALSE))
            _tcscat(sText, _T("Windows Server 2003"));
          else if (os.IsDomainControllerWindowsServer2003(&osvi, FALSE))
            _tcscat(sText, _T("Windows Server 2003 (Domain Controller)"));
          else if (os.IsWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T("Windows Server 2003 R2"));
          else if (os.IsDomainControllerWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T("Windows Server 2003 R2 (Domain Controller)"));
          else
            _tcscat(sText, _T("Windows XP"));

          if (os.IsDatacenterWindowsServer2003(&osvi, FALSE) || os.IsDatacenterWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2003(&osvi, FALSE) || os.IsEnterpriseWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2003(&osvi, FALSE) || os.IsWebWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2003(&osvi, FALSE) || os.IsStandardWindowsServer2003R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindowsVistaOrWindowsServer2008(&osvi, FALSE))
        {
          if (os.IsWindowsVista(&osvi, FALSE))
          {
            if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows Vista (Starter Edition)"));
            else if (os.IsHomeBasic(&osvi))
              _tcscat(sText, _T("Windows Vista (Home Basic)"));
            else if (os.IsHomeBasicPremium(&osvi))
              _tcscat(sText, _T("Windows Vista (Home Premium)"));
            else if (os.IsBusiness(&osvi))
              _tcscat(sText, _T("Windows Vista (Business)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows Vista (Enterprise)"));
            else if (os.IsUltimate(&osvi))
              _tcscat(sText, _T("Windows Vista (Ultimate)"));
            else
              _tcscat(sText, _T("Windows Vista"));
          }
          else
          {
            if (os.IsWindowsServer2008(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2008"));
            else if (os.IsDomainControllerWindowsServer2008(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2008 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2008"));
          }
            
          if (os.IsDatacenterWindowsServer2008(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2008(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2008(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2008(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows7OrWindowsServer2008R2(&osvi, FALSE))
        {
          if (os.IsWindows7(&osvi, FALSE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 7 Thin PC"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 7 (Starter Edition)"));
            else if (os.IsHomeBasic(&osvi))
              _tcscat(sText, _T("Windows 7 (Home Basic)"));
            else if (os.IsHomeBasicPremium(&osvi))
              _tcscat(sText, _T("Windows 7 (Home Premium)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 7 (Professional)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 7 (Enterprise)"));
            else if (os.IsUltimate(&osvi))
              _tcscat(sText, _T("Windows 7 (Ultimate)"));
            else
              _tcscat(sText, _T("Windows 7"));
          }
          else
          {
            if (os.IsWindowsServer2008R2(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2008 R2"));
            else if (os.IsDomainControllerWindowsServer2008R2(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2008 R2 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2008"));
          }
            
          if (os.IsDatacenterWindowsServer2008R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2008R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2008R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2008R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows8OrWindowsServer2012(&osvi, FALSE))
        {
          if (os.IsWindows8(&osvi, FALSE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 8 Thin PC"));
            else if (os.IsWindowsRT(&osvi, FALSE))
              _tcscat(sText, _T("Windows 8 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 8 (Starter Edition)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 8 (Pro)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 8 (Enterprise)"));
            else
              _tcscat(sText, _T("Windows 8"));
          }
          else
          {
            if (os.IsWindowsServer2012(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2012"));
            else if (os.IsDomainControllerWindowsServer2012(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2012 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2012"));
          }
            
          if (os.IsDatacenterWindowsServer2012(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2012(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2012(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2012(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows8Point1OrWindowsServer2012R2(&osvi, FALSE))
        {
          if (os.IsWindows8Point1(&osvi, FALSE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 8.1 Thin PC"));
            else if (os.IsWindowsRT(&osvi, FALSE))
              _tcscat(sText, _T("Windows 8.1 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Starter Edition)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Pro)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Enterprise)"));
            else
              _tcscat(sText, _T("Windows 8.1"));
          }
          else
          {
            if (os.IsWindowsServer2012R2(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2012 R2"));
            else if (os.IsDomainControllerWindowsServer2012R2(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2012 R2 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2012 R2"));
          }

          if (os.IsCoreConnected(&osvi))
            _tcscat(sText, _T(", (with Bing / CoreConnected)"));
          if (os.IsWindows8Point1Or2012R2Update(&osvi))
            _tcscat(sText, _T(", (Update)"));
            
          if (os.IsDatacenterWindowsServer2012R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2012R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2012R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2012R2(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows10OrWindowsServer2016(&osvi, FALSE))
        {
          if (os.IsWindows10(&osvi, FALSE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 10 Thin PC"));
            else if (os.IsWindowsRT(&osvi, FALSE))
              _tcscat(sText, _T("Windows 10 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 10 (Starter Edition)"));
            else if (os.IsCore(&osvi))
              _tcscat(sText, _T("Windows 10 (Home)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 10 (Pro)"));
            else if (os.IsProWorkstations(&osvi))
              _tcscat(sText, _T("Windows 10 (Pro for Workstations)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 10 (Enterprise)"));
            else if (os.IsSEdition(&osvi))
              _tcscat(sText, _T("Windows 10 S"));
            else
              _tcscat(sText, _T("Windows 10"));
          }
          else
          {
            if (os.IsNanoServer(&osvi))
              _tcscat(sText, _T("Windows Server 2016 Nano Server"));
            else if (os.IsARM64Server(&osvi))
              _tcscat(sText, _T("Windows Server 2016 ARM64 Server"));
            else if (os.IsDomainControllerWindowsServer2016(&osvi, FALSE))
              _tcscat(sText, _T("Windows Server 2016 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2016"));
            if (os.IsWindowsServerVersion1709(&osvi, FALSE))
              _tcscat(sText, _T(", (version 1709)"));
            else if (os.IsWindowsServerVersion1803(&osvi, FALSE))
              _tcscat(sText, _T(", (version 1803)"));
          }

          if (os.IsWindows10RTM(&osvi, FALSE))
            _tcscat(sText, _T(", (RTM)"));
          else if (os.IsWindows10Version1511(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1511)"));
          else if (os.IsWindows10Version1607(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1607)"));
          else if (os.IsWindows10Version1703(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1703)"));
          else if (os.IsWindows10Version1709(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1709)"));
          else if (os.IsWindows10Version1803(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1803)"));
          else if (os.IsWindows10Version1809(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1809)"));
          else if (os.IsWindows10Version1903(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1903)"));
          else if (os.IsWindows10Version1909(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1909)"));
          else if (os.IsWindows10Codename20H1(&osvi, FALSE))
            _tcscat(sText, _T(", (codename \"20H1\")"));

          if (os.IsCoreConnected(&osvi))
            _tcscat(sText, _T(", (with Bing / CoreConnected)"));

          if (os.IsDatacenterWindowsServer2016(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2016(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2016(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2016(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindowsServer2019(&osvi, FALSE))
        {
          if (os.IsNanoServer(&osvi))
            _tcscat(sText, _T("Windows Server 2019 Nano Server"));
          else if (os.IsARM64Server(&osvi))
            _tcscat(sText, _T("Windows Server 2019 ARM64 Server"));
          else if (os.IsDomainControllerWindowsServer2019(&osvi, FALSE))
            _tcscat(sText, _T("Windows Server 2019 (Domain Controller)"));
          else
            _tcscat(sText, _T("Windows Server 2019"));
          if (os.IsWindowsServerVersion1809(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1809)"));
          else if (os.IsWindowsServerVersion1903(&osvi, FALSE))
            _tcscat(sText, _T(", (version 1903)"));
          else if (os.IsWindowsServerCodename19H2(&osvi, FALSE))
            _tcscat(sText, _T(", (codename \"19H2\")"));
          else if (os.IsWindowsServerCodename20H1(&osvi, FALSE))
            _tcscat(sText, _T(", (codename \"20H1\")"));
          if (os.IsDatacenterWindowsServer2019(&osvi, FALSE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2019(&osvi, FALSE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2019(&osvi, FALSE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2019(&osvi, FALSE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        break;
      }
      default: 
      {
        _tcscat(sText, _T("Unknown OS"));
        break;
      }
    }

#ifndef UNDER_CE
    switch (osvi.EmulatedProcessorType)
    {
      case COSVersion::X86_PROCESSOR:
      {
        _tcscat(sText, _T(", (x86 Processor)"));
        break;
      }
      case COSVersion::MIPS_PROCESSOR:
      {
        _tcscat(sText, _T(", (MIPS Processor)"));
        break;
      }
      case COSVersion::ALPHA_PROCESSOR:
      {
        _tcscat(sText, _T(", (Alpha Processor)"));
        break;
      }
      case COSVersion::PPC_PROCESSOR:
      {
        _tcscat(sText, _T(", (PPC Processor)"));
        break;
      }
      case COSVersion::IA64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA64 Itanium[2] Processor)"));
        break;
      }
      case COSVersion::AMD64_PROCESSOR:
      {
        _tcscat(sText, _T(", (x64 Processor)"));
        break;
      }
      case COSVersion::ALPHA64_PROCESSOR:
      {
        _tcscat(sText, _T(", (Alpha64 Processor)"));
        break;
      }
      case COSVersion::MSIL_PROCESSOR:
      {
        _tcscat(sText, _T(", (MSIL Processor)"));
        break;
      }
      case COSVersion::ARM_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM Processor)"));
        break;
      }
      case COSVersion::SHX_PROCESSOR:
      {
        _tcscat(sText, _T(", (SHX Processor)"));
        break;
      }
      case COSVersion::IA32_ON_WIN64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA32 on Win64 Processor)"));
        break;
      }
      case COSVersion::NEUTRAL_PROCESSOR:
      {
        _tcscat(sText, _T(", (Neutral Processor)"));
        break;
      }
      case COSVersion::ARM64_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM64 Processor)"));
        break;
      }
      case COSVersion::ARM32_ON_WIN64_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM32 on Win64 Processor)"));
        break;
      }
      case COSVersion::IA32_ON_ARM64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA32 on ARM64 Processor)"));
        break;
      }
      case COSVersion::UNKNOWN_PROCESSOR: //deliberate fallthrough
      default:
      {
        _tcscat(sText, _T(", (Unknown Processor)"));
        break;
      }
    }
#endif //#ifndef UNDER_CE
    _stprintf(sBuf, _T(" v%d."), (int)(osvi.dwEmulatedMajorVersion));
    _tcscat(sText, sBuf);
    if (osvi.dwEmulatedMinorVersion % 10)
    {
      if (osvi.dwEmulatedMinorVersion > 9)
        _stprintf(sBuf, _T("%02d"), (int)(osvi.dwEmulatedMinorVersion));
      else
        _stprintf(sBuf, _T("%01d"), (int)(osvi.dwEmulatedMinorVersion));
    }
    else
      _stprintf(sBuf, _T("%01u"), osvi.dwEmulatedMinorVersion / 10);
    _tcscat(sText, sBuf);
    if (osvi.dwEmulatedBuildNumber)
    {
      _stprintf(sBuf, _T(" Build:%d"), (int)(osvi.dwEmulatedBuildNumber));
      _tcscat(sText, sBuf);
    }
    if (osvi.wEmulatedServicePackMajor)
    {
      if (osvi.wEmulatedServicePackMinor)
      {
        //Handle the special case of NT 4 SP 6a which Dtwinver treats as SP 6.1
        if (os.IsNTPreWin2k(&osvi, FALSE) && (osvi.wEmulatedServicePackMajor == 6) && (osvi.wEmulatedServicePackMinor == 1))
          _stprintf(sBuf, _T(" Service Pack: 6a"));
        //Handle the special case of XP SP 1a which Dtwinver treats as SP 1.1
        else if (os.IsWindowsXP(&osvi, FALSE) && (osvi.wEmulatedServicePackMajor == 1) && (osvi.wEmulatedServicePackMinor == 1))
          _stprintf(sBuf, _T(" Service Pack: 1a"));
        else       
          _stprintf(sBuf, _T(" Service Pack:%d.%d"), (int)(osvi.wEmulatedServicePackMajor), (int)(osvi.wEmulatedServicePackMinor));
      }
      else
        _stprintf(sBuf, _T(" Service Pack:%d"), (int)(osvi.wEmulatedServicePackMajor));
      _tcscat(sText, sBuf);
    }
    else
    {
      if (osvi.wEmulatedServicePackMinor)       
        _stprintf(sBuf, _T(" Service Pack:0.%d"), (int)(osvi.wEmulatedServicePackMinor));
    }

    _tcscat(sText, _T("\n"));
  #endif //#ifndef UNDER_CE
    
    //CE does not really have a concept of an emulated OS so
    //lets not bother displaying any info on this on CE
    if (osvi.UnderlyingPlatform == COSVersion::WindowsCE)
      _tcscpy(sText, _T("OS: "));
    else
      _tcscat(sText, _T("Underlying OS: "));

    switch (osvi.UnderlyingPlatform)
    {
      case COSVersion::Dos:
      {
        _tcscat(sText, _T("DOS"));
        break;
      }
      case COSVersion::Windows3x:
      {
        _tcscat(sText, _T("Windows"));
        break;
      }
      case COSVersion::WindowsCE:
      {
        if (os.IsWindowsEmbeddedCompact(&osvi, TRUE))
          _tcscat(sText, _T("Windows Embedded Compact"));
        else if (os.IsWindowsCENET(&osvi, TRUE))
          _tcscat(sText, _T("Windows CE .NET"));
        else
          _tcscat(sText, _T("Windows CE"));
        break;
      }
      case COSVersion::Windows9x:
      {
        if (os.IsWindows95(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 95"));
        else if (os.IsWindows95SP1(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 95 SP1"));
        else if (os.IsWindows95B(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 95 B [aka OSR2]"));
        else if (os.IsWindows95C(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 95 C [aka OSR2.5]"));
        else if (os.IsWindows98(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 98"));
        else if (os.IsWindows98SP1(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 98 SP1"));
        else if (os.IsWindows98SE(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows 98 Second Edition"));
        else if (os.IsWindowsME(&osvi, TRUE))
          _stprintf(sBuf, _T("Windows Millenium Edition"));
        else
          _stprintf(sBuf, _T("Windows \?\?"));
        _tcscat(sText, sBuf);
        break;
      }
      case COSVersion::WindowsNT:
      {
        if (os.IsNTPreWin2k(&osvi, TRUE))
        {
          _tcscat(sText, _T("Windows NT"));

          if (os.IsNTWorkstation(&osvi, TRUE))
            _tcscat(sText, _T(" (Workstation)"));
          else if (os.IsNTStandAloneServer(&osvi, TRUE))
            _tcscat(sText, _T(" (Server)"));
          else if (os.IsNTPDC(&osvi, TRUE))
            _tcscat(sText, _T(" (Primary Domain Controller)"));
          else if (os.IsNTBDC(&osvi, TRUE))
            _tcscat(sText, _T(" (Backup Domain Controller)"));

          if (os.IsNTDatacenterServer(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter)"));
          else if (os.IsNTEnterpriseServer(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise)"));
        }
        else if (os.IsWindows2000(&osvi, TRUE))
        {
          if (os.IsProfessional(&osvi))
            _tcscat(sText, _T("Windows 2000 (Professional)"));
          else if (os.IsWindows2000Server(&osvi, TRUE))
            _tcscat(sText, _T("Windows 2000 Server"));
          else if (os.IsWindows2000DomainController(&osvi, TRUE))
            _tcscat(sText, _T("Windows 2000 (Domain Controller)"));
          else 
            _tcscat(sText, _T("Windows 2000"));

          if (os.IsWindows2000DatacenterServer(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter)"));
          else if (os.IsWindows2000AdvancedServer(&osvi, TRUE))
            _tcscat(sText, _T(", (Advanced Server)"));
        }
        else if (os.IsWindowsXPOrWindowsServer2003(&osvi, TRUE))
        {
          if (os.IsStarterEdition(&osvi))
            _tcscat(sText, _T("Windows XP (Starter Edition)"));
          else if (os.IsPersonal(&osvi))
            _tcscat(sText, _T("Windows XP (Personal)"));
          else if (os.IsProfessional(&osvi))
            _tcscat(sText, _T("Windows XP (Professional)"));
          else if (os.IsWindowsServer2003(&osvi, TRUE))
            _tcscat(sText, _T("Windows Server 2003"));
          else if (os.IsDomainControllerWindowsServer2003(&osvi, TRUE))
            _tcscat(sText, _T("Windows Server 2003 (Domain Controller)"));
          else if (os.IsWindowsServer2003R2(&osvi, TRUE))
            _tcscat(sText, _T("Windows Server 2003 R2"));
          else if (os.IsDomainControllerWindowsServer2003R2(&osvi, TRUE))
            _tcscat(sText, _T("Windows Server 2003 R2 (Domain Controller)"));
          else
            _tcscat(sText, _T("Windows XP"));

          if (os.IsDatacenterWindowsServer2003(&osvi, TRUE) || os.IsDatacenterWindowsServer2003R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2003(&osvi, TRUE) || os.IsEnterpriseWindowsServer2003(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2003(&osvi, TRUE) || os.IsWebWindowsServer2003R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2003(&osvi, TRUE) || os.IsStandardWindowsServer2003R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindowsVistaOrWindowsServer2008(&osvi, TRUE))
        {
          if (os.IsWindowsVista(&osvi, TRUE))
          {
            if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows Vista (Starter Edition)"));
            else if (os.IsHomeBasic(&osvi))
              _tcscat(sText, _T("Windows Vista (Home Basic)"));
            else if (os.IsHomeBasicPremium(&osvi))
              _tcscat(sText, _T("Windows Vista (Home Premium)"));
            else if (os.IsBusiness(&osvi))
              _tcscat(sText, _T("Windows Vista (Business)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows Vista (Enterprise)"));
            else if (os.IsUltimate(&osvi))
              _tcscat(sText, _T("Windows Vista (Ultimate)"));
            else
              _tcscat(sText, _T("Windows Vista"));
          }
          else
          {
            if (os.IsWindowsServer2008(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2008"));
            else if (os.IsDomainControllerWindowsServer2008(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2008 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2008"));
          }
            
          if (os.IsDatacenterWindowsServer2008(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2008(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2008(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2008(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows7OrWindowsServer2008R2(&osvi, TRUE))
        {
          if (os.IsWindows7(&osvi, TRUE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 7 Thin PC"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 7 (Starter Edition)"));
            else if (os.IsHomeBasic(&osvi))
              _tcscat(sText, _T("Windows 7 (Home Basic)"));
            else if (os.IsHomeBasicPremium(&osvi))
              _tcscat(sText, _T("Windows 7 (Home Premium)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 7 (Professional)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 7 (Enterprise)"));
            else if (os.IsUltimate(&osvi))
              _tcscat(sText, _T("Windows 7 (Ultimate)"));
            else
              _tcscat(sText, _T("Windows 7"));
          }
          else
          {
            if (os.IsWindowsServer2008R2(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2008 R2"));
            else if (os.IsDomainControllerWindowsServer2008R2(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2008 R2 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2008 R2"));
          }
            
          if (os.IsDatacenterWindowsServer2008R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2008R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2008R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2008R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows8OrWindowsServer2012(&osvi, TRUE))
        {
          if (os.IsWindows8(&osvi, TRUE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 8 Thin PC"));
            else if (os.IsWindowsRT(&osvi, TRUE))
              _tcscat(sText, _T("Windows 8 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 8 (Starter Edition)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 8 (Pro)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 8 (Enterprise)"));
            else
              _tcscat(sText, _T("Windows 8"));
          }
          else
          {
            if (os.IsWindowsServer2012(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2012"));
            else if (os.IsDomainControllerWindowsServer2012(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2012 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2012"));
          }

          if (os.IsDatacenterWindowsServer2012(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2012(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2012(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2012(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows8Point1OrWindowsServer2012R2(&osvi, TRUE))
        {
          if (os.IsWindows8Point1(&osvi, TRUE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 8.1 Thin PC"));
            else if (os.IsWindowsRT(&osvi, TRUE))
              _tcscat(sText, _T("Windows 8.1 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Starter Edition)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Pro)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 8.1 (Enterprise)"));
            else
              _tcscat(sText, _T("Windows 8.1"));
          }
          else
          {
            if (os.IsWindowsServer2012R2(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2012 R2"));
            else if (os.IsDomainControllerWindowsServer2012R2(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2012 R2 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2012 R2"));
          }
            
          if (os.IsCoreConnected(&osvi))
            _tcscat(sText, _T(", (with Bing / CoreConnected)"));
          if (os.IsWindows8Point1Or2012R2Update(&osvi))
            _tcscat(sText, _T(", (Update)"));

          if (os.IsDatacenterWindowsServer2012R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2012R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2012R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2012R2(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindows10OrWindowsServer2016(&osvi, TRUE))
        {
          if (os.IsWindows10(&osvi, TRUE))
          {
            if (os.IsThinPC(&osvi))
              _tcscat(sText, _T("Windows 10 Thin PC"));
            else if (os.IsWindowsRT(&osvi, TRUE))
              _tcscat(sText, _T("Windows 10 RT"));
            else if (os.IsStarterEdition(&osvi))
              _tcscat(sText, _T("Windows 10 (Starter Edition)"));
            else if (os.IsCore(&osvi))
              _tcscat(sText, _T("Windows 10 (Home)"));
            else if (os.IsProfessional(&osvi))
              _tcscat(sText, _T("Windows 10 (Pro)"));
            else if (os.IsProWorkstations(&osvi))
              _tcscat(sText, _T("Windows 10 (Pro for Workstations)"));
            else if (os.IsEnterprise(&osvi))
              _tcscat(sText, _T("Windows 10 (Enterprise)"));
            else if (os.IsSEdition(&osvi))
              _tcscat(sText, _T("Windows 10 S"));
            else
              _tcscat(sText, _T("Windows 10"));
          }
          else
          {
            if (os.IsNanoServer(&osvi))
              _tcscat(sText, _T("Windows Server 2016 Nano Server"));
            else if (os.IsARM64Server(&osvi))
              _tcscat(sText, _T("Windows Server 2016 ARM64 Server"));
            else if (os.IsDomainControllerWindowsServer2016(&osvi, TRUE))
              _tcscat(sText, _T("Windows Server 2016 (Domain Controller)"));
            else
              _tcscat(sText, _T("Windows Server 2016"));
            if (os.IsWindowsServerVersion1709(&osvi, TRUE))
              _tcscat(sText, _T(", (version 1709)"));
            else if (os.IsWindowsServerVersion1803(&osvi, TRUE))
              _tcscat(sText, _T(", (version 1803)"));
          }

          if (os.IsWindows10RTM(&osvi, TRUE))
            _tcscat(sText, _T(", (RTM)"));
          else if (os.IsWindows10Version1511(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1511)"));
          else if (os.IsWindows10Version1607(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1607)"));
          else if (os.IsWindows10Version1703(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1703)"));
          else if (os.IsWindows10Version1709(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1709)"));
          else if (os.IsWindows10Version1803(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1803)"));
          else if (os.IsWindows10Version1809(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1809)"));
          else if (os.IsWindows10Version1903(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1903)"));
          else if (os.IsWindows10Version1909(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1909)"));
          else if (os.IsWindows10Codename20H1(&osvi, TRUE))
            _tcscat(sText, _T(", (codename \"20H1\")"));

          if (os.IsCoreConnected(&osvi))
            _tcscat(sText, _T(", (with Bing / CoreConnected)"));
            
          if (os.IsDatacenterWindowsServer2016(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2016(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2016(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2016(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        else if (os.IsWindowsServer2019(&osvi, TRUE))
        {
          if (os.IsNanoServer(&osvi))
            _tcscat(sText, _T("Windows Server 2019 Nano Server"));
          else if (os.IsARM64Server(&osvi))
            _tcscat(sText, _T("Windows Server 2019 ARM64 Server"));
          else if (os.IsDomainControllerWindowsServer2019(&osvi, TRUE))
            _tcscat(sText, _T("Windows Server 2019 (Domain Controller)"));
          else
            _tcscat(sText, _T("Windows Server 2019"));
          if (os.IsWindowsServerVersion1809(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1809)"));
          else if (os.IsWindowsServerVersion1903(&osvi, TRUE))
            _tcscat(sText, _T(", (version 1903)"));
          else if (os.IsWindowsServerCodename19H2(&osvi, TRUE))
            _tcscat(sText, _T(", (codename \"19H2\")"));
          else if (os.IsWindowsServerCodename20H1(&osvi, TRUE))
            _tcscat(sText, _T(", (codename \"20H1\")"));
          if (os.IsDatacenterWindowsServer2019(&osvi, TRUE))
            _tcscat(sText, _T(", (Datacenter Edition)"));
          else if (os.IsEnterpriseWindowsServer2019(&osvi, TRUE))
            _tcscat(sText, _T(", (Enterprise Edition)"));
          else if (os.IsWebWindowsServer2019(&osvi, TRUE))
            _tcscat(sText, _T(", (Web Edition)"));
          else if (os.IsStandardWindowsServer2019(&osvi, TRUE))
            _tcscat(sText, _T(", (Standard Edition)"));
        }
        break;
      }
      default:
      {
        _stprintf(sBuf, _T("Unknown OS"));
        _tcscat(sText, sBuf);
        break;
      }
    }

#ifndef UNDER_CE
    switch (osvi.UnderlyingProcessorType)
    {
      case COSVersion::X86_PROCESSOR:
      {
        _tcscat(sText, _T(", (x86 Processor)"));
        break;
      }
      case COSVersion::MIPS_PROCESSOR:
      {
        _tcscat(sText, _T(", (MIPS Processor)"));
        break;
      }
      case COSVersion::ALPHA_PROCESSOR:
      {
        _tcscat(sText, _T(", (Alpha Processor)"));
        break;
      }
      case COSVersion::PPC_PROCESSOR:
      {
        _tcscat(sText, _T(", (PPC Processor)"));
        break;
      }
      case COSVersion::IA64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA64 Itanium[2] Processor)"));
        break;
      }
      case COSVersion::AMD64_PROCESSOR:
      {
        _tcscat(sText, _T(", (x64 Processor)"));
        break;
      }
      case COSVersion::ALPHA64_PROCESSOR:
      {
        _tcscat(sText, _T(", (Alpha64 Processor)"));
        break;
      }
      case COSVersion::MSIL_PROCESSOR:
      {
        _tcscat(sText, _T(", (MSIL Processor)"));
        break;
      }
      case COSVersion::ARM_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM Processor)"));
        break;
      }
      case COSVersion::SHX_PROCESSOR:
      {
        _tcscat(sText, _T(", (SHX Processor)"));
        break;
      }
      case COSVersion::IA32_ON_WIN64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA32 on Win64 Processor)"));
        break;
      }
      case COSVersion::NEUTRAL_PROCESSOR:
      {
        _tcscat(sText, _T(", (Neutral Processor)"));
        break;
      }
      case COSVersion::ARM64_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM64 Processor)"));
        break;
      }
      case COSVersion::ARM32_ON_WIN64_PROCESSOR:
      {
        _tcscat(sText, _T(", (ARM32 on Win64 Processor)"));
        break;
      }
      case COSVersion::IA32_ON_ARM64_PROCESSOR:
      {
        _tcscat(sText, _T(", (IA32 on ARM64 Processor)"));
        break;
      }
      case COSVersion::UNKNOWN_PROCESSOR: //deliberate fallthrough
      default:
      {
        _tcscat(sText, _T(", (Unknown Processor)"));
        break;
      }
    }
#endif //#ifndef UNDER_CE
    _stprintf(sBuf, _T(" v%d."), (int)(osvi.dwUnderlyingMajorVersion));
    _tcscat(sText, sBuf);
    if (osvi.dwUnderlyingMinorVersion % 10)
    {
      if (osvi.dwUnderlyingMinorVersion > 9)
        _stprintf(sBuf, _T("%02d"), (int)(osvi.dwUnderlyingMinorVersion));
      else
        _stprintf(sBuf, _T("%01d"), (int)(osvi.dwUnderlyingMinorVersion));
    }
    else
      _stprintf(sBuf, _T("%01d"), (int)(osvi.dwUnderlyingMinorVersion / 10));
    _tcscat(sText, sBuf);
    if (osvi.dwUnderlyingBuildNumber)
    {
      //Report the UBR on Windows 10 / Server 2016 and later
      if (os.IsWindows10OrWindowsServer2016(&osvi, TRUE) || os.IsWindowsServer2019(&osvi, TRUE))
        _stprintf(sBuf, _T(" Build:%d.%d"), (int)(osvi.dwUnderlyingBuildNumber), (int)(osvi.dwUBR));
      else
        _stprintf(sBuf, _T(" Build:%d"), (int)(osvi.dwUnderlyingBuildNumber));
      _tcscat(sText, sBuf);
    }
    if (osvi.wUnderlyingServicePackMajor)
    {
      if (osvi.wUnderlyingServicePackMinor)
      {
        //Handle the special case of NT 4 SP 6a which Dtwinver treats as SP 6.1
        if (os.IsNTPreWin2k(&osvi, TRUE) && (osvi.wUnderlyingServicePackMajor == 6) && (osvi.wUnderlyingServicePackMinor == 1))
          _stprintf(sBuf, _T(" Service Pack: 6a"));
        //Handle the special case of XP SP 1a which Dtwinver treats as SP 1.1
        else if (os.IsWindowsXP(&osvi, TRUE) && (osvi.wUnderlyingServicePackMajor == 1) && (osvi.wUnderlyingServicePackMinor == 1))
          _stprintf(sBuf, _T(" Service Pack: 1a"));
        else
          _stprintf(sBuf, _T(" Service Pack:%d.%d"), (int)(osvi.wUnderlyingServicePackMajor), (int)(osvi.wUnderlyingServicePackMinor));
      }
      else
        _stprintf(sBuf, _T(" Service Pack:%d"), (int)(osvi.wUnderlyingServicePackMajor));
      _tcscat(sText, sBuf);
    }
    else
    {
      if (osvi.wUnderlyingServicePackMinor)
        _stprintf(sBuf, _T(" Service Pack:0.%d"), (int)(osvi.wUnderlyingServicePackMinor));
    }

    _stprintf(sBuf, _T(", ProductType:0x%08X"), osvi.dwProductType);
    _tcscat(sText, sBuf);
    if (os.IsEnterpriseStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server Enterprise)"));
    else if (os.IsExpressStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server Express)"));
    else if (os.IsStandardStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server Standard)"));
    else if (os.IsWorkgroupStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server Workgroup)"));
    else if (os.IsEssentialsStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server Essentials)"));
    else if (os.IsStorageServer(&osvi))
      _tcscat(sText, _T(", (Storage Server)"));

    if (os.IsHomeServerPremiumEdition(&osvi))
      _tcscat(sText, _T(", (Home Server Premium Edition)"));
    else if (os.IsHomeServerEdition(&osvi))
      _tcscat(sText, _T(", (Home Server Edition)"));

    if (os.IsTerminalServices(&osvi))
      _tcscat(sText, _T(", (Terminal Services)"));
    if (os.IsEmbedded(&osvi))
      _tcscat(sText, _T(", (Embedded)"));
    if (os.IsTerminalServicesInRemoteAdminMode(&osvi))
      _tcscat(sText, _T(", (Terminal Services in Remote Admin Mode)"));
    if (os.Is64Bit(&osvi, TRUE))
      _tcscat(sText, _T(", (64 Bit Edition)"));
    if (os.IsMediaCenter(&osvi))
      _tcscat(sText, _T(", (Media Center Edition)"));
    if (os.IsTabletPC(&osvi))
      _tcscat(sText, _T(", (Tablet PC Edition)"));
    if (os.IsComputeClusterServerEdition(&osvi))
      _tcscat(sText, _T(", (Compute Cluster Edition)"));
    if (os.IsServerFoundation(&osvi))
      _tcscat(sText, _T(", (Foundation Edition)"));
    if (os.IsMultipointServerPremiumEdition(&osvi))
      _tcscat(sText, _T(", (MultiPoint Premium Edition)"));
    else if (os.IsMultiPointServer(&osvi))
      _tcscat(sText, _T(", (MultiPoint Edition)"));
    if (os.IsSecurityAppliance(&osvi))
      _tcscat(sText, _T(", (Security Appliance)"));
    if (os.IsBackOffice(&osvi))
      _tcscat(sText, _T(", (BackOffice)"));
    if (os.IsNEdition(&osvi))
      _tcscat(sText, _T(", (N Edition)"));
    if (os.IsEEdition(&osvi))
      _tcscat(sText, _T(", (E Edition)"));
    if (os.IsHyperVTools(&osvi))
      _tcscat(sText, _T(", (Hyper-V Tools)"));
    if (os.IsHyperVServer(&osvi))
      _tcscat(sText, _T(", (Hyper-V Server)"));
    if (os.IsServerCore(&osvi))
      _tcscat(sText, _T(", (Server Core)"));
    if (os.IsUniprocessorFree(&osvi))
      _tcscat(sText, _T(", (Uniprocessor Free)"));
    if (os.IsUniprocessorChecked(&osvi))
      _tcscat(sText, _T(", (Uniprocessor Checked)"));
    if (os.IsMultiprocessorFree(&osvi))
      _tcscat(sText, _T(", (Multiprocessor Free)"));
    if (os.IsMultiprocessorChecked(&osvi))
      _tcscat(sText, _T(", (Multiprocessor Checked)"));
    if (os.IsEssentialBusinessServerManagement(&osvi))
      _tcscat(sText, _T(", (Windows Essential Business Server Manangement Server)"));
    if (os.IsEssentialBusinessServerMessaging(&osvi))
      _tcscat(sText, _T(", (Windows Essential Business Server Messaging Server)"));
    if (os.IsEssentialBusinessServerSecurity(&osvi))
      _tcscat(sText, _T(", (Windows Essential Business Server Security Server)"));
    if (os.IsClusterServer(&osvi))
      _tcscat(sText, _T(", (Cluster Server)"));
    if (os.IsSmallBusiness(&osvi))
      _tcscat(sText, _T(", (Small Business)"));
    if (os.IsRestricted(&osvi))
      _tcscat(sText, _T(", (Restricted)"));
    if (os.IsSmallBusinessServerPremium(&osvi))
      _tcscat(sText, _T(", (Small Business Server Premium)"));
    if (os.IsPreRelease(&osvi))
      _tcscat(sText, _T(", (Prerelease)"));
    if (os.IsEvaluation(&osvi))
      _tcscat(sText, _T(", (Evaluation)"));
    if (os.IsAutomotive(&osvi))
      _tcscat(sText, _T(", (Automotive)"));
    if (os.IsChina(&osvi))
      _tcscat(sText, _T(", (China)"));
    if (os.IsSingleLanguage(&osvi))
      _tcscat(sText, _T(", (Single Language)"));
    if (os.IsWin32sInstalled(&osvi))
      _tcscat(sText, _T(", (Win32s)"));
    if (os.IsEducation(&osvi))
      _tcscat(sText, _T(", (Education)"));
    if (os.IsIndustry(&osvi))
      _tcscat(sText, _T(", (Industry)"));
    if (os.IsStudent(&osvi))
      _tcscat(sText, _T(", (Student)"));
    if (os.IsMobile(&osvi))
      _tcscat(sText, _T(", (Mobile)"));
    if (os.IsCloudHostInfrastructureServer(&osvi))
      _tcscat(sText, _T(", (Cloud Host Infrastructure Server)"));
    if (os.IsLTSB(&osvi))
      _tcscat(sText, _T(", (LTSB)"));
    if (os.IsCloudStorageServer(&osvi))
      _tcscat(sText, _T(", (Cloud Storage Server)"));
    if (os.IsPPIPro(&osvi))
      _tcscat(sText, _T(", (PPI Pro)"));
    if (os.IsConnectedCar(&osvi))
      _tcscat(sText, _T(", (Connected Car)"));
    if (os.IsHandheld(&osvi))
      _tcscat(sText, _T(", (Handheld)"));
    if (os.IsHolographic(&osvi))
      _tcscat(sText, _T(", (Holographic)"));
    if (os.IsBusiness(&osvi))
        _tcscat(sText, _T(", (Business)"));
    if (os.IsSubscription(&osvi))
      _tcscat(sText, _T(", (Subscription)"));
    if (os.IsUtilityVM(&osvi))
      _tcscat(sText, _T(", (Utility VM)"));
    if (os.IsAzure(&osvi))
      _tcscat(sText, _T(", (Azure)"));
    if (os.IsEnterpriseG(&osvi))
      _tcscat(sText, _T(", (Enterprise G)"));
    if (os.IsServerRDSH(&osvi))
      _tcscat(sText, _T(", (ServerRRDSH)"));
    if (os.IsHubOS(&osvi))
      _tcscat(sText, _T(", (HubOS)"));
    if (os.IsCommunicationsServer(&osvi))
      _tcscat(sText, _T(", (Communications Server)"));
    if (os.IsOneCoreUpdateOS(&osvi))
      _tcscat(sText, _T(", (One Core Update OS)"));
    if (os.IsAndromeda(&osvi))
      _tcscat(sText, _T(", (Andromeda)"));
    if (os.IsIoTCommercial(&osvi))
      _tcscat(sText, _T(", (IoT Commercial)"));
    if (os.IsIoTCore(&osvi))
      _tcscat(sText, _T(", (IoT Core)"));
    if (os.IsIoTOS(&osvi))
      _tcscat(sText, _T(", (IoT OS)"));
    if (os.IsIoTEdgeOS(&osvi))
      _tcscat(sText, _T(", (IoT EdgeOS)"));
    if (os.IsIoTEnterprise(&osvi))
      _tcscat(sText, _T(", (IoT Enterprise)"));
    if (os.IsLite(&osvi))
      _tcscat(sText, _T(", (Lite)"));
    if (os.IsXBoxSystemOS(&osvi))
      _tcscat(sText, _T(", (XBox SystemOS)"));
    if (os.IsXBoxNativeOS(&osvi))
      _tcscat(sText, _T(", (XBox NativeOS)"));
    if (os.IsXBoxGamesOS(&osvi))
      _tcscat(sText, _T(", (XBox GameOS)"));
    if (os.IsXBoxEraOS(&osvi))
      _tcscat(sText, _T(", (XBox EraOS)"));
    if (os.IsXBoxDurangoHostOS(&osvi))
      _tcscat(sText, _T(", (XBox DurangoHostOS)"));
    if (os.IsXBoxScarlettHostOS(&osvi))
      _tcscat(sText, _T(", (XBox ScarlettHostOS)"));
    _tcscat(sText, _T("\n"));

    //Some extra info for CE
  #ifdef UNDER_CE
    if (osvi.UnderlyingPlatform == COSVersion::WindowsCE)
    {
      _tcscat(sText, _T("Model: "));
      _tcscat(sText, osvi.szOEMInfo);
      _tcscat(sText, _T("\nDevice Type: "));
      _tcscat(sText, osvi.szPlatformType);
    }
  #endif //#ifdef UNDER_CE
  }
  else
    _stprintf(sText, _T("Failed in call to GetOSVersion\n"));
    
  #ifdef _WINDOWS
    MessageBox(NULL, sText, _T("Operating System details"), MB_OK);
  #elif _WIN32_WCE
    MessageBox(NULL, sText, _T("Operating System details"), MB_OK);
  #else
    printf(sText);
  #endif //#ifdef _WINDOWS

  return 0;
}