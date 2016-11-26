@echo off
call "%ConEmuBaseDir%\CmdInit.cmd"

set path=%PATH%;C:\MinGW-4.8.1\bin
set path=%PATH%;C:\Program Files (x86)\Notepad++
set path=%PATH%;C:\Program Files\Sublime Text 2
set path=%PATH%;C:\Program Files (x86)\GnuWin32\bin

doskey ed=sublime_text $*

echo Environment has been set up!