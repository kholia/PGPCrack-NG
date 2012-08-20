#include <config.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#ifdef HAVE_STAT
#include <sys/stat.h>		/* for stat() */
#endif
#include <fcntl.h>
#ifdef HAVE_W32_SYSTEM
#include <windows.h>
#endif

#define INCLUDED_BY_MAIN_MODULE 1
#include "gpg.h"
#include <assuan.h>
#include "packet.h"
#include "iobuf.h"
#include "util.h"
#include "main.h"
#include "options.h"
#include "keydb.h"
#include "trustdb.h"
#include "cipher.h"
#include "filter.h"
#include "ttyio.h"
#include "i18n.h"
#include "sysutils.h"
#include "status.h"
#include <unistd.h>

int status;

void g10_exit(int rc)
{
	exit(rc);
}

#define N 128

char passphrase[N];

int main(int argc, char **argv)
{
	gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
	int l;
	int ret;
	armor_filter_context_t *afx = NULL;

	while (fgets(passphrase, N, stdin) != NULL && status == 0) {
		IOBUF a;
		struct stat sb;
		unlink("output");
		l = strlen(passphrase);
		passphrase[l - 1] = 0;
		status = 1;
		a = iobuf_open(argv[1]);
		if( use_armor_filter( a ) ) {
			afx = new_armor_context ();
			push_armor_filter (afx, a);
		}
		proc_packets(NULL, a);
		ret = stat("output", &sb);
		if (status == 1 && sb.st_size > 0 && ret != -1) {
			printf("Found Password : %s\n", passphrase);
			exit(0);
		} else {
			status = 0;
		}
		iobuf_close(a);
	}
	return -1;
}
