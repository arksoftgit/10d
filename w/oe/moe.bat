:: Make sure we're in the right directory.
%kzd%:
call cds %kzt% oe
nmake -f %kzd%:\%kzv%\mak\kzoengaa.mak %1 %2 %3 %4 %5 %6 %7 %8 %9 -nologo
