#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Raspi-ServClient], [1.0], [sat7070@gmail.com])
AC_CONFIG_SRCDIR([src/server/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE(1.6 dist-bzip2)
PKG_CHECK_MODULES([ELEMENTARY], elementary)
PKG_CHECK_MODULES([PTHREAD], pthread-stubs)

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT(Makefile src/Makefile src/client/Makefile src/server/Makefile)




#AC_CONFIG_SRCDIR(configure.ac)




