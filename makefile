DebugMode:
	cl /D DEBUG wordcount.c

Deploy:
	cl wordcount.c

clean:
	del *.obj
	del *.asm
	del *.exe