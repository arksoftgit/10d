rem set "variable=%1"
rem set "variable=%variable:/=\%"
rem echo "%variable%"
rem git diff FETCH_HEAD -- %1 %variable%

rem git log -p -1 %1
gitk %1