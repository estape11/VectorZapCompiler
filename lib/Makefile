#************************************************************
#
#	Instituto Tecnológico de Costa Rica
#	Computer Engineering
#
#	Programmer: Esteban Agüero Pérez (estape11)
#	Version: 1.0
#	Last Update: 08/05/2019
#
#	Computer Architecture II
#	Professor. Jeferson González Gómez
#
#************************************************************

# Classes names
INST=InstructionHelper
BASE=BaseHelper

CC=g++
INCLUDE=../include
AR=ar
OPTNS=-Wall -std=c++11

all:$(INST).o $(BASE).o

$(INST).o:$(INST).cpp
		$(CC) $(OPTNS) -c $(INST).cpp -o $(INST).o -I$(INCLUDE)

$(BASE).o:$(BASE).cpp
		$(CC) $(OPTNS) -c $(BASE).cpp -o $(BASE).o -I$(INCLUDE)

clean:
		rm -f *.o 
		rm -f *.a
		
.PHONY:clean
