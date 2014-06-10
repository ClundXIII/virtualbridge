#Makefile for VirtualBridge
#Simon Michalke, (c) 2014
#this is licensed under the BSD-3-Clause License
#see https://github.com/ClundXIII/virtualbridge.git

all: createtemp insert.exe result.exe

createtemp:
	mkdir -p temp

insert.exe: createtemp

result.exe: createtemp

clean:


#all object files: