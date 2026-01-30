#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // ident = program name, LOG_PID = include PID, LOG_NDELAY = open immediately
    openlog(argv[0], LOG_PID | LOG_NDELAY, LOG_USER);

    if (argc != 3)
    {
        syslog(LOG_ERR, "usage: %s filename string", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *msg = argv[2];

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        syslog(LOG_ERR, "Failed to create the file %s: %s", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    syslog(LOG_DEBUG, "Writing %s to %s", msg, filename);
    if (fprintf(file, "%s", msg) < 0)
    {
        syslog(LOG_ERR, "Failed to write to %s: %s", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    closelog();
    exit(EXIT_SUCCESS);
}