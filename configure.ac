AC_PREREQ(2.59)
AC_INIT(mysac.c)
LIBMYSAC_RELEASE=0.5.0
LIBMYSAC_LIBRARY_VERSION=0:5:0
AM_INIT_AUTOMAKE(libmysac,0.5.0)
AC_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST(LIBMYSAC_RELEASE)
AC_SUBST(LIBMYSAC_LIBRARY_VERSION)

dnl check for mysql
m4_include([m4/mysql_client.m4])
AX_LIB_MYSQL
old_cflags="$CFLAGS"
old_ldflags="$LDFLAGS"
CPPFLAGS="$MYSQL_CFLAGS $CPPFLAGS"
LDFLAGS="$MYSQL_LDFLAGS $LDFLAGS"

AC_CHECK_HEADERS(mysql/mysql.h,AC_CHECK_LIB(mysqlclient_r, mysql_init, [have_mysql_mysql_h=1]))
if test "$have_mysql_mysql_h" != "1"; then
  AC_CHECK_HEADERS(mysql.h,AC_CHECK_LIB(mysqlclient_r, mysql_init, [have_mysql_h=1]))
  if test "$have_mysql_h" != "1"; then
    echo "Failed to detect mysql libaries.  Make sure you have the mysql development libaries installed and try again with ./configure --with-mysql=/path/to/your/mysql_config"
    exit 1 
  fi
fi
CPPFLAGS="$old_cflags"
LDFLAGS="$old_ldflags"

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_OUTPUT(Makefile)
