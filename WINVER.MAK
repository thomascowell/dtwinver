# Microsoft Visual C++ generated build script - Do not modify

PROJ = WINVER
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = F:\DEV\MYCODE~1\DTWINVER\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DTWINVER.CPP
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W4 /Zi /AL /Od /D "_DEBUG" /GA /GEf /Fd"WINVER.PDB"
CFLAGS_R_WEXE = /nologo /W4 /AL /O1 /D "NDEBUG" /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = libw llibcew oldnames shell.lib 
LIBS_R_WEXE = libw llibcew oldnames shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = WINVER.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DTWINVER.SBR \
		TEST.SBR


DTWINVER_DEP = f:\dev\vc15\include\tchar.h \
	f:\dev\mycode~1\dtwinver\dtwinver.h


TEST_DEP = f:\dev\vc15\include\tchar.h \
	f:\dev\mycode~1\dtwinver\dtwinver.h


all:	$(PROJ).EXE

DTWINVER.OBJ:	DTWINVER.CPP $(DTWINVER_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DTWINVER.CPP

TEST.OBJ:	TEST.CPP $(TEST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEST.CPP


$(PROJ).EXE::	DTWINVER.OBJ TEST.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DTWINVER.OBJ +
TEST.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
f:\dev\vc15\lib\+
f:\dev\vc15\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@


run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
