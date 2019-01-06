CC=g++
CFLAGS= -Wall
DEP_FLAG= -MM

EXE=Casse-brique
SOURCE= Window/window.cpp main.cpp casseBrique.cpp balle.cpp raquette.cpp brique.cpp partie.cpp popBrique.cpp option.cpp tabOptions.cpp scoresJoueurs.cpp
HEADER= Window/window.h casseBrique.h balle.h raquette.h brique.h popBrique.h option.h partie.h tabOptions.h scoresJoueurs.h
THIS= Makefile
DEP_FILE= .depend


MSG= @echo 
RM= @rm -f

ifeq ($(wildcard $(DEP_FILE)), )
all : $(DEP_FILE)
	make −−no−print−directory 
else
all : $(EXE)
endif
dep : $(DEP_FILE)


################
# La compilation

.SUFFIXES : .c .h .o

$(DEP_FILE): $(SOURCE)
	$(MSG) "Recherche des dépendances des fichiers ..."
	$(RM) $(DEP_FILE)
	$(CC) $(DEP_FLAG) $^ >> $@

.c.o :
	$(CC) -c $(CFLAGS) $<

$(EXE): $(SOURCE:.c=.o)
	$(CC) $(FLAG) $^ -o $@ -lncurses

###########
# Nettoyage
clean: 
	$(RM) \#*
	$(RM) *.o
	$(RM) *~
	$(RM) core
	$(RM) $(EXE)

