BUILDDIR := build
SRCFILES = $(wildcard src/*.c)
OBJFILES = $(SRCFILES:src/%.c=$(BUILDDIR)/%.o)

# LDFLAGS +=
CFLAGS += -Wall -std=c99 -Isrc -O2

.PHONY: run clean

program: $(OBJFILES)
	$(CC) -o "$@" $^ $(LDFLAGS)

run: program
	./program

clean:
	rm -rf $(BUILDDIR) program

$(BUILDDIR):
	mkdir -p $@

build/%.o: src/%.c $(wildcard src/*.h) $(BUILDDIR)
	$(CC) -o "$@" -c "$<" $(CFLAGS)
