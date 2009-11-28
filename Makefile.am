pkglibdir=$(libdir)/mysac
pkglib_LTLIBRARIES = libmysac.la
ACLOCAL_AMFLAGS = -I m4

libmysac_la_CPPFLAGS = -I$(top_srcdir)/ $(MYSQL_CFLAGS)
libmysac_la_LDFLAGS= -version-info $(LIBMYSAC_LIBRARY_VERSION) -release $(LIBMYSAC_RELEASE)

libmysac_la_SOURCES = \
mysac.c \
mysac_decode_field.c \
mysac_decode_row.c \
mysac_errors.c \
mysac_net.c
