AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing
AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = client
client_SOURCES = main.c main.h
client_LDADD = @ELEMENTARY_LIBS@
client_CFLAGS = @ELEMENTARY_CFLAGS@
