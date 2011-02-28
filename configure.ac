AC_INIT(Hourglass, 0.5)
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(src/config.h)
#AM_PROG_LIBTOOL
AM_SILENT_RULES([yes])

CXXFLAGS="-O2 -fopenmp -Wall -ggdb -Wno-depreciated"

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_HEADER_STDC

AC_LANG_CPLUSPLUS

AC_ARG_ENABLE(joggler, AS_HELP_STRING(--enable-joggler, [Tailor towards the joggler platform]), [
	if test "$enableval" = yes; then
		AC_DEFINE([JOGGLER], [1], [Build in the light sensor, etc., support])
	fi])

AC_ARG_ENABLE(shellfm, AS_HELP_STRING(--enable-shellfm, [Compile in shell-fm support]), [
	if test "$enableval" = yes; then
		AC_DEFINE([SHELLFM], [1], [Something, something, shell-fm])
	fi])

AC_CHECK_LIB(stdc++, main,,AC_MSG_ERROR(Hourglass requires libstdc++))
AC_CHECK_HEADERS(vector,,AC_MSG_ERROR(Hourglass requires vector))
AC_CHECK_HEADERS(string,,AC_MSG_ERROR(Hourglass requires string))
AC_CHECK_HEADERS(map,,AC_MSG_ERROR(Hourglass requires map))

#AC_CHECK_LIB(boost_thread-mt, main,,AC_MSG_ERROR(Hourglass requires boost threading))

PKG_CHECK_MODULES(GTKMM, gtkmm-2.4)
PKG_CHECK_MODULES(GLIBMM, glibmm-2.4)

LDFLAGS="$LDFLAGS $GTKMM_LIBS $GLIBMM_LIBS"
CPPFLAGS="$CPPFLAGS $GTKMM_CFLAGS $GLIBMM_CFLAGS"

AC_OUTPUT(Makefile)

