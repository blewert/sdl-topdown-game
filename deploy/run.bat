@echo off

timeout /t 3

echo Opening caffeine
start \\silo\student\games\caffeine\caffeine64.exe

echo Cloning repository
git clone https://github.com/StaffsUniGames/sdl-topdown-game.git
cd sdl-topdown-game

echo Opening instructions
start "" https://github.com/StaffsUniGames/sdl-topdown-game/blob/main/README.md

echo Opening project
start ./sdl-game-activity.sln

timeout /t 5

echo.
echo.
echo.

echo Checking processes running (no output = not running):

echo .. Caffiene:
tasklist | find "caff"

echo .. Visual Studio:
tasklist | find "devenv"

echo .. Browser:
tasklist | find "edge"
tasklist | find "chrome"

timeout /t 5