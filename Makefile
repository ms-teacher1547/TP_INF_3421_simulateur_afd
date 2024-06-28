# Compiler
CC = gcc
# Flags de compilation
CFLAGS = -Wall -Wextra -I include

# Dossier contenant les fichiers source
SRCDIR = src
# Dossier pour les fichiers objets
OBJDIR = obj
# List des fichiers source
SRCS = $(wildcard $(SRCDIR)/*.c)
# Noms des fichiers objets générés à partir des fichiers sources
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
# Nom de l'exécutable final
TARGET = programme

# Règle pour compiler tous les fichiers objets et créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o bin/$(TARGET)

# Règle générique pour créer les fichiers objets à partir des fichiers sources
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier obj s'il n'existe pas
$(shell mkdir -p $(OBJDIR))

run :
	cd bin
	./bin/$(TARGET)
	cd ..

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) bin/$(TARGET)
