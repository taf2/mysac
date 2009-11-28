bin_PROGRAMS = client

client_SOURCES  = client.c
client_LDADD    = $(top_srcdir)/libmysac.la
client_LDFLAGS  = $(MYSQL_LDFLAGS)
client_CPPFLAGS = -I$(top_srcdir) $(MYSQL_CFLAGS)
