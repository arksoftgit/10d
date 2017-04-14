set "variable=%1"
set "variable=%variable:/=\%"
echo "%variable%"
git diff FETCH_HEAD -- %1  %variable%