#
# MIT License
#
# Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
# Copyright (c) 2022 Harpont, Inc. All rights reserved.
#

#
# Constants
#
PWD := $(shell pwd)

#
# Programs
#
CC  := $(shell which gcc)

#
# Directories
#
SRCDIR := $(PWD)/examples/

#
# Flags
#
CFLAGS := -std=gnu99 -I$(PWD) -O0 -NDEBUG -Wall -Wextra -Werror

all:
	$(CC) $(CFLAGS) -o $(SRCDIR)/stdlib/die    $(SRCDIR)stdlib/die.c
	$(CC) $(CFLAGS) -o $(SRCDIR)/stdlib/free   $(SRCDIR)stdlib/free.c
	$(CC) $(CFLAGS) -o $(SRCDIR)/stdlib/malloc $(SRCDIR)stdlib/malloc.c
	$(CC) $(CFLAGS) -o $(SRCDIR)/stdlib/warn   $(SRCDIR)stdlib/warn.c

	$(CC) $(CFLAGS) -o $(SRCDIR)/string/chkstr $(SRCDIR)string/chkstr.c
	$(CC) $(CFLAGS) -o $(SRCDIR)/string/memcpy $(SRCDIR)string/memcpy.c
	$(CC) $(CFLAGS) -o $(SRCDIR)/string/strcpy $(SRCDIR)string/strcpy.c
