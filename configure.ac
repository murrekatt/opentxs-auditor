#  
#
AC_PREREQ([2.68])
AC_INIT([vp-auditservice], [0.0.1], [info@monetas.net])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

AM_INIT_AUTOMAKE([1.10 foreign])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([no])])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strchr strpbrk])

AC_CONFIG_FILES([Makefile
			src/Makefile])

AC_OUTPUT
