########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++


#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=libAtmega


# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers a compiler, separes par
# un espace. exemple: 'tp1.c tp2.cpp':

#--------MODIFIED--------
PRJSRC= $(wildcard $(addsuffix *.cpp, $(FILES_DIRS)))

# Inclusions additionnels (ex: -I/path/to/mydir)

#--------MODIFIED--------
INC=$(addprefix -I ./,$(FILES_DIRS))

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp



####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de #####
#####   ce Makefile en vue de sa modification  #####
####################################################



####### variables #######

#--------ADDED--------
#F_CPU flag
FCPU_FLAG=-DF_CPU=8000000UL
#DEBUG flag
DEBUG_FLAG=-DDEBUG
#variable containing all the defines needed (F_CPU and potentially DEBUG)
DEFINE_FLAGS=$(FCPU_FLAG)

# directories of the .cpp files (PRJSRC), and the .h files(INC)
FILES_DIRS=$(wildcard */)
#Archiver used
ARC=avr-ar

#compilateur utilise
CC=avr-gcc
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f



####### Options de compilation #######

#--------MODIFIED--------
# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall \
	$(DEFINE_FLAGS)

# Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside 
# array bounds" sur avr-gcc v12
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
    CFLAGS += --param=min-pagesize=0
endif

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions




####### Cible (Target) #######

#Nom des cibles par defaut

#--------MODIFIED--------
TRG=$(PROJECTNAME).a

####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
	
# Pour plus d'information sur cette section, consulter :
# http://bit.ly/257R53E	
# Les fonctions $(filter pattern…,text) &
# $(patsubst pattern,replacement,text) sont pertinentes
	


####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean

#--------MODIFIED--------
.PHONY: all clean debug

# Make all permet simplement de compiler le projet

#--------MODIFIED--------
all: $(TRG) 

# Implementation de la cible

#--------MODIFIED--------
$(TRG): $(OBJDEPS) 
	$(ARC) -crs $(TRG) $(OBJDEPS) 

# Production des fichiers object
# De C a objet

#--------MODIFIED--------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# De C++ a objet

#--------MODIFIED--------
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Verification des dependances (header dependencies)

#--------MODIFIED--------
-include $(OBJDEPS:.o=.d)

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8


# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation

#--------MODIFIED--------
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) $(OBJDEPS:.o=.d)

debug: DEFINE_FLAGS += $(DEBUG_FLAG)
debug: all
# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####
