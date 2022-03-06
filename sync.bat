@echo off
:sync 
git pull origin main:main

if errorlevel 1 (
    goto :sync
) else (
    echo Sync Succeeded
)