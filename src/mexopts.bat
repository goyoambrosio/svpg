@echo off
rem MSVC50OPTS.BAT
rem
rem    Compile and link options used for building MEX-files
rem    using the Microsoft Visual C++ compiler version 5.0 
rem
rem    $Revision: 1.1 $  $Date: 2000/01/21 13:04:55 $
rem
rem ********************************************************************
rem General parameters
rem ********************************************************************
set MATLAB=%MATLAB%
set MSVC_ROOT=C:\apps2\DevStudio
set MSVCDir=%MSVC_ROOT%\VC
set MSDevDir=%MSVC_ROOT%\sharedIDE
set PATH=%MSVCDir%\BIN;%MSDevDir%\bin;%PATH%
set INCLUDE=%MSVCDir%\INCLUDE\SGI_STL;%MSVCDir%\INCLUDE;%MSVCDir%\MFC\INCLUDE;%MSVCDir%\ATL\INCLUDE;%INCLUDE%
set LIB=%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%LIB%

rem ********************************************************************
rem Compiler parameters
rem ********************************************************************
set COMPILER=cl
rem set COMPFLAGS=-c -Zp8 -G5 -W3 -DMATLAB_MEX_FILE -DLEDA_PREFIX -DNDEBUG -DWIN32
set COMPFLAGS=-c -Zp8 -G5 -W3 -DMATLAB_MEX_FILE -DLEDA_PREFIX -DNDEBUG
set OPTIMFLAGS=-O2
set DEBUGFLAGS=-Zi

rem ********************************************************************
rem Library creation command
rem ********************************************************************
set PRELINK_CMDS=lib /def:%MATLAB%\extern\include\matlab.def /machine:ix86 /OUT:%LIB_NAME%1.lib 
set PRELINK_DLLS=lib /def:%MATLAB%\extern\include\%DLL_NAME%.def /machine:ix86 /OUT:%DLL_NAME%.lib	

rem ********************************************************************
rem Linker parameters
rem ********************************************************************
set LINKER=link
rem Library set using GUI
rem set LINKFLAGS=mkl_s.lib mkl_c.lib lapack.lib eigsrc.lib tmg.lib blas.lib libf77.lib libi77.lib libl.lib libg.lib libp.lib libw.lib libd3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /dll /export:mexFunction %LIB_NAME%1.lib /implib:%LIB_NAME%l.lib
rem Library set using console mode (smaller exe)
set LINKFLAGS=mkl_s.lib mkl_c.lib lapack.lib eigsrc.lib tmg.lib blas.lib libf77.lib libi77.lib libl.lib libg.lib libp.lib  /dll /export:mexFunction %LIB_NAME%1.lib /implib:%LIB_NAME%l.lib
set LINKOPTIMFLAGS=
set LINKDEBUGFLAGS=/debug
set LINK_FILE=d:\goyo\mio\svawin32\obj\*.obj
set LINK_LIB= 
set NAME_OUTPUT=/out:%MEX_NAME%.dll

rem ********************************************************************
rem Resource compiler parameters
rem ********************************************************************
set RC_COMPILER=rc /fo mexversion.res
set RC_LINKER= 
