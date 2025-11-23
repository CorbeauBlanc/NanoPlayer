# Environment
NAME=nanoplayer
VNUMBER=0.2

CC=gcc
CFLAGS=-Wall -Wextra -Werror -Ofast
MAKE=/usr/bin/make
ARCH=x86_64
LIBS=-Llib/fmod/$(ARCH) -Wl,-rpath,'lib' -lfmod -lpthread

SRCDIR=src
INCDIR=include
DIST=GNU-Linux
TARGET=Release
TARGETDIR=dist/$(TARGET)/$(DIST)
OBJDIR=build/$(TARGET)/$(DIST)

SRCS=errors.c list_manager.c music_manager.c thread_manager.c file_manager.c main.c proc_manager.c
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INSTALLDIR=/usr/bin

.PHONY: all install test_arch clean

all: $(OBJDIR) $(TARGETDIR) $(TARGETDIR)/$(NAME)

$(OBJDIR):
	mkdir -p $@

$(TARGETDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $^ -c -o $@ -I$(INCDIR) -I$(INCDIR)/fmod $(CFLAGS)
	@echo "$@ Done."

$(TARGETDIR)/$(NAME): $(OBJS)
	@echo "Building $(NAME) v$(VNUMBER)..."
	@$(CC) $^ -o $@ -I$(INCDIR) -I$(INCDIR)/fmod $(CFLAGS) $(LIBS)
	@echo "Done."

test_arch:
	@if ! [ -e lib/fmod/$(ARCH) ];then\
		echo "error: usable architectures: arm, arm64, x86, x86_64";\
	fi

install:
	@sudo cp $(TARGETDIR)/$(NAME) $(INSTALLDIR)
	@sudo chmod 731 /usr/bin/$(NAME)
	@sudo cp -H lib/fmod/$(ARCH)/libfmod.so /usr/lib
	@sudo ldconfig

uninstall:
	@if [ -e $(INSTALLDIR)/$(NAME) ];then\
		sudo rm $(INSTALLDIR)/$(NAME);\
		echo "$(INSTALLDIR)/$(NAME) removed";\
	fi
	@if [ -e /usr/lib/libfmod.so ];then\
		sudo rm /usr/lib/libfmod.so;\
		echo "/usr/lib/libfmod.so removed";\
	fi
	@sudo ldconfig

clean:
	@rm $(OBJS) && echo "Objects cleaned."
	@rm "$(TARGETDIR)/$(NAME)" && echo "Build cleaned."
