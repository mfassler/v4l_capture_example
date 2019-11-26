/*
 *  V4L2 video capture example
 *
 *  This program can be used and distributed without restrictions.
 *
 *	  This program is provided with the V4L2 API
 * see https://linuxtv.org/docs.php for more information
 */


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <getopt.h>

#include "V4L2_webcam.hpp"



static void usage(FILE *fp, int argc, char **argv)
{
	fprintf(fp,
	 "Usage: %s [options]\n\n"
		"Options:\n"
		" -h | --help          Print this message\n"
		" -m | --mmap          Use memory mapped buffers [default]\n"
		" -r | --read          Use read() calls\n"
		" -u | --userp         Use application allocated buffers\n"
		"\n", argv[0]);
}

static const char short_options[] = "hmru:";

static const struct option long_options[] = {
	{ "help",   no_argument,	   NULL, 'h' },
	{ "mmap",   no_argument,	   NULL, 'm' },
	{ "read",   no_argument,	   NULL, 'r' },
	{ "userp",  no_argument,	   NULL, 'u' },
	{ 0, 0, 0, 0 }
};



int main(int argc, char *argv[]) {
	char* device_name = (char*) "/dev/video0";
	enum io_method io_meth = IO_METHOD_MMAP;

	if (argc > 1) {
		device_name = argv[1];
	}
	//printf("Using device: %s\n", device_name);


	for (;;) {
		int idx;
		int c;

		c = getopt_long(argc, argv, short_options, long_options, &idx);

		if (-1 == c)
			break;

		switch (c) {
		case 0: // getopt_long() flag
			break;

		case 'h':
			usage(stdout, argc, argv);
			exit(EXIT_SUCCESS);

		case 'm':
			io_meth = IO_METHOD_MMAP;
			break;

		case 'r':
			io_meth = IO_METHOD_READ;
			break;

		case 'u':
			io_meth = IO_METHOD_USERPTR;
			break;

		default:
			usage(stderr, argc, argv);
			exit(EXIT_FAILURE);
		}
	}

	V4L2_webcam webcam(device_name, io_meth);

	webcam.open_device();
	webcam.init_device();
	webcam.start_capturing();
	webcam.mainloop();
	webcam.stop_capturing();
	webcam.uninit_device();
	webcam.close_device();


	fprintf(stderr, "\n");
	return 0;
}


