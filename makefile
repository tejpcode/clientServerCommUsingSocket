#! /bin/bash
run:server.o init.o infra.o exitfunc.o threadfunc.o header.h declaration.h datastructure.h
	gcc -o run server.o init.o infra.o exitfunc.o threadfunc.o -lpthread 
server.o:server.c header.h declaration.h datastructure.h
	gcc -c server.c
init.o:init.c header.h declaration.h datastructure.h
	gcc -c init.c
infra.o:infra.c header.h declaration.h datastructure.h
	gcc -c infra.c 
exitfunc.o:exitfunc.c header.h declaration.h 
	gcc -c exitfunc.c

