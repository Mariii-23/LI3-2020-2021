BUILDDIR := build/
SRCFILES = $(wildcard src/*/*.c) $(wildcard src/*.c)
OBJFILES = $(SRCFILES:src/%.c=$(BUILDDIR)/%.o)

LDFLAGS += $(shell pkg-config --libs glib-2.0)
CFLAGS += -Wall -std=c99 -Isrc -O2 $(shell pkg-config --cflags glib-2.0)

.PHONY: run clean

program: $(OBJFILES)
	$(CC) -o "$@" $^ $(LDFLAGS)

run: program
	./program

clean:
	rm -rf $(BUILDDIR) program

$(BUILDDIR)%/:
	mkdir -p $@

$(BUILDDIR):
	mkdir -p $@

.SECONDEXPANSION:
# $(BUILDDIR) está depois de um pipe para que não crie o objeto sempre que a
# diretoria é modificada (o que vai ser sempre que se cria algum ficheiro
# dentro dela)
# -MMD -MP -MF ... gera um Makefile com as dependências dos headers
$(BUILDDIR)%.o: src/%.c | $(BUILDDIR) $$(@D)/
	$(CC) -o "$@" -c "$<" $(CFLAGS) -MMD -MP -MF $(@:%.o=%.d)

# ...e agora incluímos estes Makefiles, mas ignoramos se não existirem
-include $(OBJFILES:%.o=%.d)
