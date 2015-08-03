dnl Process this file with autoconf to produce a configure script.

AC_INIT([libusual], [0.1], [https://libusual.github.com])
AC_CONFIG_SRCDIR(usual/base.h)
AC_CONFIG_HEADER(usual/config.h)
AC_PREREQ([2.59])

AC_USUAL_INIT

AC_USUAL_PROGRAM_CHECK

LT_INIT

AC_USUAL_HEADER_CHECK

AC_USUAL_TYPE_CHECK

AC_USUAL_FUNCTION_CHECK

AC_USUAL_CASSERT

AC_USUAL_WERROR

AC_USUAL_DEBUG

AC_USUAL_UREGEX

AC_USUAL_LIBEVENT(opt)

AC_USUAL_GETADDRINFO_A

AC_USUAL_TLS

dnl search for common libraries
AC_SEARCH_LIBS(clock_gettime, rt)
AC_SEARCH_LIBS(getsockname, socket)
AC_SEARCH_LIBS(gethostbyname, nsl)
AC_SEARCH_LIBS(hstrerror, resolv)

dnl Output findings
AC_OUTPUT([config.mak mk/libusual.pc build.mk])

