AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing
AM_CPPFLAGS = -I$(top_srcdir)
bin_PROGRAMS = server
server_SOURCES = src/main.c
server_LDADD = @ELEMENTARY_LIBS@
server_CFLAGS = @ELEMENTARY_CFLAGS@
