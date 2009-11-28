#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>
#include <mysac.h>

#define BUFS (1024*1024)
char buf[BUFS];
char res[BUFS];
char _q[BUFS];

static inline int client_wait(fd, code) {
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(fd, &fds);

	if (code == MYERR_WANT_WRITE)
		select(fd+1, NULL, &fds, NULL, NULL);
	else if (code == MYERR_WANT_READ)
		select(fd+1, &fds, NULL, NULL, NULL);
	else
		return 0;
	return 1;
}

void usage(char *cmd) {
	fprintf(stderr,
		"usage: %s -h host -u login -p pass -d db {-|query}\n"
		"  host  : \"path\" or \"<ip>:<port>\"\n"
		"  login : database login\n"
		"  pass  : database password\n"
		"  db    : database\n"
		"  -     : read request on stdin\n"
		"	query : SQL request\n",
		cmd
	);
	exit(1);
}

int main(int argc, char *argv[]) {
	int ret_code;
	int len;
	int i;
	char *q;
	struct timeval start, stop, diff;
	int fd;
	MYSAC my;
	MYSAC_RES *r;
	const char *host = NULL;
	const char *login = NULL;
	const char *pass = NULL;
	const char *db = NULL;

	/* check */
  /*printf("argc: %d\n", argc);
	if (argc != 10)
		usage(argv[0]);
    */

	/* read cmd line */
	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "-h")==0) {
			i++;
			host = argv[i];
		}
		else if (strcmp(argv[i], "-u")==0) {
			i++;
			login = argv[i];
		}
		else if (strcmp(argv[i], "-p")==0) {
			i++;
			pass = argv[i];
		}
		else if (strcmp(argv[i], "-d")==0) {
			i++;
			db = argv[i];
		}
	}

	/* init memory */
	mysac_init(&my, buf, BUFS);

	/* get file descriptor */
	fd = mysac_get_fd(&my);

  if (!pass) { printf("no pass\n"); pass = ""; }

	/* init connection */
	mysac_setup(&my, host, login, pass, db, 0);
  printf("login {host: %s, login: %s, pass: %s, db: %s}\n", host, login, pass, db);
	do {
		ret_code = mysac_connect(&my);
  } while (client_wait(fd, ret_code));

	if (ret_code != 0) {
		fprintf(stderr, "mysac_connect error %d: %s\n", ret_code, mysac_advance_error(&my));
		exit(1);
	}

	/* choose database */
	mysac_set_database(&my, db);
	do {
		ret_code = mysac_send_database(&my);
  } while (client_wait(fd, ret_code));

	if (ret_code != 0) {
		fprintf(stderr, "mysac_send_database error %d: %s\n", ret_code, mysac_advance_error(&my));
		exit(1);
	}

	/* send flush */
	r = mysac_init_res(res, BUFS);
	mysac_set_query(&my, r, "RESET QUERY CACHE;");

	/* send query to database */
	do {
		ret_code = mysac_send_query(&my);
  } while (client_wait(fd, ret_code));

	/* la reponse est arrivée */
	if (ret_code != 0) {
		fprintf(stderr, "mysac_send_query(RESET QUERY CACHE) error %d: %s\n",
		        ret_code, mysac_advance_error(&my));
		exit(1);
	}

	/* read request from stdin */
	if (strcmp(argv[9], "-")==0) {
		len = fread(_q, 1, BUFS, stdin);
		q = _q;
	}
	else {
		q = argv[9];
		len = strlen(q);
	}

	/* declare request */
	r = mysac_init_res(res, BUFS);
	mysac_b_set_query(&my, r, q, len);

	/* get time */
	gettimeofday(&start, NULL);

	/* send query to database */
	do {
		ret_code = mysac_send_query(&my);
  } while (client_wait(fd, ret_code));

	/* la reponse est arrivée */
	if (ret_code != 0) {
		fprintf(stderr, "mysac_send_query error %d: %s\n", ret_code, mysac_advance_error(&my));
		exit(1);
	}

	/* get time */
	gettimeofday(&stop, NULL);

	/* display */
	diff.tv_sec  = stop.tv_sec  - start.tv_sec;
	diff.tv_usec = stop.tv_usec - start.tv_usec;
	if (diff.tv_usec < 0) {
		diff.tv_sec--;
		diff.tv_usec += 1000000;
	}
	printf("%u rows in set (%u.%06u s)\n", mysac_num_rows(r), diff.tv_sec, diff.tv_usec);
}
