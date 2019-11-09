
BUILDDIR       = ../build
BINDIR         = $(BUILDDIR)/bin
INCDIR         = $(BUILDDIR)/include
LIBDIR         = $(BUILDDIR)/lib
OBJDIR         = $(BUILDDIR)/obj
LIBPATH        = $(LIBDIR)/libumalloc.a
UMMAP_BUILDDIR = ../ummap-io/build
UMMAP_SRCDIR   = ../ummap-io/src
UMMAP_INCDIR   = $(UMMAP_BUILDDIR)/include
UMMAP_LIBDIR   = $(UMMAP_BUILDDIR)/lib
UMMAP_OBJDIR   = $(UMMAP_BUILDDIR)/obj
UMMAP_LIBPATH  = $(UMMAP_LIBDIR)/libummapio.a
CLIBS          = -lumalloc
CFLAGS         = -DDEBUG_PRINT=$(or $(DEBUG_PRINT),0) -O2 -I. \
				 -I$(UMMAP_INCDIR) -L$(LIBDIR)

ifeq (,$(findstring Cray,$(shell cc -V 2>&1)))
    CLIBS  += -pthread -lrt
    CFLAGS += -Wall -Wno-unused-label -Wno-unused-function -std=c99
endif

all: setup $(LIBPATH) $(BINDIR)/example.out

$(BINDIR)/example.out: $(LIBPATH) example/main.c
	$(CC) $(CFLAGS) example/main.c -o $(BINDIR)/example.out $(CLIBS)

$(LIBPATH): $(UMMAP_LIBPATH) $(OBJDIR)/umalloc.o
	ar -cq $(LIBPATH) $(OBJDIR)/*.o $(UMMAP_OBJDIR)/*.o

$(OBJDIR)/umalloc.o: umalloc.* common.h
	$(CC) $(CFLAGS) -c umalloc.c -o $(OBJDIR)/umalloc.o

$(UMMAP_LIBPATH):
	@$(MAKE) -C $(UMMAP_SRCDIR)

setup:
	@mkdir -p $(BINDIR) $(INCDIR) $(LIBDIR) $(OBJDIR) 2> /dev/null
	@cp umalloc.h $(INCDIR) 2> /dev/null

clean:
	@rm -rf $(BUILDDIR)
clean_all: clean
	@$(MAKE) clean --no-print-directory -C $(UMMAP_SRCDIR)

rebuild: clean all
rebuild_all: clean_all all

