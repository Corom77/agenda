# Définition du compilateur et des drapeaux de compilation
COMPILATEUR = gcc
OPTIONS_COMPILATION = -Wall 
OPTIONS_LIENS = 

# Définition des fichiers objets et de l'exécutable
FICHIERS_OBJETS = main.o Fonctionp3.o
NOM_EXECUTABLE = pc

# Règle par défaut
tout: $(NOM_EXECUTABLE)
	./$(NOM_EXECUTABLE)

# Règle de construction de l'exécutable
$(NOM_EXECUTABLE): $(FICHIERS_OBJETS)
	$(COMPILATEUR) -o $@ $^ $(OPTIONS_LIENS)

# Règle de construction des fichiers objets
%.o: %.c
	$(COMPILATEUR) -o $@ -c $< $(OPTIONS_COMPILATION)

# Règle de nettoyage
nettoyage:
	rm -rf *.o
