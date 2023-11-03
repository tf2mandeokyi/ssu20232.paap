@echo off

SET PROJECT_ROOT=%~dp0
cd %PROJECT_ROOT%
cd build-module
node index.js %*