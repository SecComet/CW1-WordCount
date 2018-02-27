DebugMode:
	cl /D DEBUG wordcount.c

wordcount:
	cl wordcount.c

clean:
	del *.obj
	del *.asm
	del *.exe

singleWords:
	wordcount.exe -i single_words_test.txt

singleWordsCase:
	wordcount.exe -i single_words_test.txt -c

sentences:
	wordcount.exe -i sentences_test.txt

sentencesCase:
	wordcount.exe -i sentences_test.txt -c