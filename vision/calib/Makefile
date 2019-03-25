CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c99 -Wpedantic -g
LDFLAGS= $(CFLAGS)
LDLIBS=-lm
RM=rm -f

# ajouter ci-dessous le nom du nouvel objet
OBJECTS=limace.o salade.o erreurs.o calib.o

# ajouter ci-dessous le nom du nouvel executable
EXE=calib

.PHONY: all
all: $(EXE)

COMMONOBJ=limace.o salade.o erreurs.o

calib: $(COMMONOBJ) calib.o 
# ajouter ici une ligne pour le nouvel executable

limace.o: limace.h
salade.o: limace.h salade.h
calib.o: limace.h salade.h erreurs.h
# ajouter ici une ligne pour le nouvel objet


clean:
	$(RM) $(OBJECTS) $(EXE)
