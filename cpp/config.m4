dnl $Id$
dnl config.m4 for extension goproxy

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(goproxy, for goproxy support,
dnl Make sure that the comment is aligned:
dnl [  --with-goproxy             Include goproxy support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(goproxy, whether to enable goproxy support,
Make sure that the comment is aligned:
[  --enable-goproxy           Enable goproxy support])

if test "$PHP_GOPROXY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-goproxy -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/goproxy.h"  # you most likely want to change this
  dnl if test -r $PHP_GOPROXY/$SEARCH_FOR; then # path given as parameter
  dnl   GOPROXY_DIR=$PHP_GOPROXY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for goproxy files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GOPROXY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GOPROXY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the goproxy distribution])
  dnl fi

  dnl # --with-goproxy -> add include path
  dnl PHP_ADD_INCLUDE($GOPROXY_DIR/include)

  dnl # --with-goproxy -> check for lib and symbol presence
  dnl LIBNAME=goproxy # you may want to change this
  dnl LIBSYMBOL=goproxy # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GOPROXY_DIR/lib, GOPROXY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GOPROXYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong goproxy lib version or lib not found])
  dnl ],[
  dnl   -L$GOPROXY_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GOPROXY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(goproxy, goproxy.c, $ext_shared)
fi
