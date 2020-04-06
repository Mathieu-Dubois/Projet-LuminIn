# make : lance le programme de test (cible par défaut)
# make application : lance l'application LuminIN
# make clean : supprime le dossier build contenant tous les fichier objets ainsi que les deux exécutables

.DEFAULT_GOAL := check
CC = c++
CCFLAGS = -Wall -pedantic -Werror

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: build/test_exe build/application_exe

build/test.o: test.cpp | build
	$(CC) $(CCFLAGS) -c test.cpp -o build/test.o

build/application.o: application.cpp | build
	$(CC) $(CCFLAGS) -c application.cpp -o build/application.o

build/application_exe: build/application.o build/menu.o | build
	$(CC) $(CCFLAGS) -o build/application_exe build/application.o build/menu.o

build/test_exe: build/test.o build/menu.o | build
	$(CC) $(CCFLAGS) -o build/test_exe build/test.o build/menu.o

build/menu.o: lib/menu/menu.h lib/menu/menu.cpp | build
	$(CC) $(CCFLAGS) -c lib/menu/menu.cpp -o build/menu.o

# Lance le programme de test.
check: build/test_exe
	./build/test_exe

# Lance l'application.
application : build/application_exe
	./build/application_exe

