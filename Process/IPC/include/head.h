#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/time.h>	/* timeval{} for select() */
#include <time.h>		/* timespec{} for pselect() */
#include <errno.h>
#include <fcntl.h>		/* for nonblocking */
#include <limits.h>		/* PIPE_BUF */
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>	/* for S_xxx file mode constants */
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define MAXLEN 80



const char* mq_name = "/mqwyh.1";
