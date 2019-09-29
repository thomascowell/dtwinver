# Microsoft Visual C++ generated build script - Do not modify

PROJ = DOSVER
DEBUG = 0
PROGTYPE = 6
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
CFLAGS_D_DEXE = /nologo /G2 /W4 /Zi /AL /Od /D "_DEBUG" /D "_DOS" /Fd"DOSVER.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W4 /AL /Ox /D "NDEBUG" /D "_DOS" 
LFLAGS_D_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /CO /STACK:5120
LFLAGS_R_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /STACK:5120
LIBS_D_DEXE = oldnames llibce
LIBS_R_DEXE = oldnames llibce
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
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

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
