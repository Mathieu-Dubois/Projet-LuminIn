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
all: application test

test.o: test.cpp | build
	$(CC) $(CCFLAGS) -c test.cpp -o build/test.o

application.o: application.cpp | build
	$(CC) $(CCFLAGS) -c application.cpp -o build/application.o

application_exe: application.o menu.o | build
	$(CC) $(CCFLAGS) -o build/application build/application.o build/menu.o

test_exe: test.o menu.o | build
	$(CC) $(CCFLAGS) -o build/test build/test.o build/menu.o

menu.o: lib/menu/menu.h lib/menu/menu.cpp | build
	$(CC) $(CCFLAGS) -c lib/menu/menu.cpp -o build/menu.o

# Lance le programme de test.
check: test_exe
	./build/test

# Lance l'application.
application : application_exe
	./build/application

