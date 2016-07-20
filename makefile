Target=Str_reverce
CC=gcc
Flag=-Wall
Lib=
all:
	$(CC) $(Target).c -o $(Target)	$(Flag) $(Lib)
clean:
	rm $(Target)