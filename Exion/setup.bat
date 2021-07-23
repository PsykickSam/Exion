@echo off

if exist ./Debug (
	mkdir "./Debug/Exion"
	mkdir "./Debug/Website"

	xcopy /s "Exion" "./Debug/Exion"
	xcopy /s "Website" "./Debug/Website"
)
