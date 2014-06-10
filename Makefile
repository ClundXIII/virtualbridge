#Makefile for VirtualBridge
#Simon Michalke, (c) 2014
#this is licensed under the BSD-3-Clause License
#see https://github.com/ClundXIII/virtualbridge.git

CC=gcc
CFLAGS=-c -g

all: createtemp insert.exe result.exe

createtemp:
	mkdir -p temp

insert.exe: createtemp

result.exe: createtemp temp/getresult.o temp/team.o temp/game.o temp/getscore.o \
		temp/bridge.o temp/tools.o
	g++ temp/getresult.o temp/team.o temp/game.o temp/getscore.o temp/bridge.o \
		temp/tools.o \
		-o result.exe

clean:
	@mkdir -p temp
	@touch temp/dummy
	rm -r temp/*

#all object files:
temp/getresult.o: Bridge/getresult.cpp Bridge/bridge.h Bridge/team.h
	$(CC) $(CFLAGS) Bridge/getresult.cpp     -o temp/getresult.o
temp/team.o: Bridge/team.cpp Bridge/team.h
	$(CC) $(CFLAGS) Bridge/team.cpp          -o temp/team.o
temp/game.o: Bridge/game.cpp headers.h Bridge/game.h
	$(CC) $(CFLAGS) Bridge/game.cpp          -o temp/game.o
temp/getscore.o: getscore.cpp includeall.h
	$(CC) $(CFLAGS) getscore.cpp             -o temp/getscore.o
temp/bridge.o: Bridge/bridge.cpp headers.h Bridge/bridge.h
	$(CC) $(CFLAGS) Bridge/bridge.cpp        -o temp/bridge.o
temp/tools.o: tools.cpp
	$(CC) $(CFLAGS) tools.cpp                -o temp/tools.o
