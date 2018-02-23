DebugMode:
	cl /D DEBUG wordcount.c

wordcount:
	cl wordcount.c

clean:
	del *.obj
	del *.asm
	del *.exe

single words test, no ignore case:
	wordcount -i single_words_test.txt
	exit 0