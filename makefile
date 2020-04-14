# make all : crée tous les fichiers objets et les deux exe dans le dossier build
# make : lance le programme de test (cible par défaut)
# make application : lance l'application LuminIN
# make clean : supprime le dossier build contenant tous les fichier objets ainsi que les deux exécutables

.DEFAULT_GOAL := check
CC = c++
CCFLAGS = -Wall -pedantic -Werror --debug

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

# Construction de la bibliotheque
# libbibliotheque.a permet de lier les fichiers.o en bibliotheque statique
build/menu.o: lib/menu.cpp | build
	$(CC) $(CCFLAGS) -c lib/menu.cpp -I ./lib -o build/menu.o

build/groupe.o: lib/groupe.c | build
	$(CC) $(CCFLAGS) -c lib/groupe.c -I ./lib -o build/groupe.o

build/liste.o: lib/liste.c | build
	$(CC) $(CCFLAGS) -c lib/liste.c -I ./lib -o build/liste.o

build/libbibliotheques.a: build/menu.o build/groupe.o build/liste.o | build
	ar crs build/libbibliotheques.a build/menu.o build/groupe.o build/liste.o

# Programmes de test :
# test : contient tous les tests
# application : contient l'application
build/test.o: test.cpp | build
	$(CC) $(CCFLAGS) -c test.cpp -o build/test.o

build/application.o: application.cpp | build
	$(CC) $(CCFLAGS) -c application.cpp -o build/application.o

build/application_exe: build/application.o build/libbibliotheques.a | build							
	$(CC) $(CCFLAGS) build/application.o build/libbibliotheques.a -o build/application_exe			

build/test_exe: build/test.o build/libbibliotheques.a | build  										
	$(CC) $(CCFLAGS) build/test.o build/libbibliotheques.a -o build/test_exe



# Lance le programme de test.
check: build/test_exe
	./build/test_exe

# Lance l'application.
application : build/application_exe
	./build/application_exe

