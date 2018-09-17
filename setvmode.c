#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

#define	DISP_CMD_HDMI_ENABLE       0xc0
#define	DISP_CMD_HDMI_DISABLE      0xc1
#define	DISP_CMD_HDMI_SET_MODE     0xc2
#define	DISP_CMD_HDMI_GET_MODE     0xc3
#define	DISP_CMD_HDMI_SUPPORT_MODE 0xc4

int main(int argc, char *argv[])
{
	unsigned int args[4] = { 0 };

	int ret;
	int mode;
	int fd_disp;

	if (argc == 1) {
		fprintf(stderr, "Usage: setmode <mode number>\n");
		return 0;
	}

	mode = atoi(argv[1]);

	fd_disp = open("/dev/disp", O_RDWR);
	if (fd_disp == -1) {
		fprintf(stderr, "Error: Failed to open /dev/disp: %s\n",
			strerror(errno));
		fprintf(stderr, "Are you root?\n");
		return errno;
	}

	args[0] = 0; // screen number
	args[1] = mode;
	ret = ioctl(fd_disp, DISP_CMD_HDMI_SUPPORT_MODE, args);
	if (ret == 0) {
		printf("Specified HDMI mode is not supported by the display according to the display driver.\n");
		return - 1;
	}

	// Turn HDMI off.
	args[0] = 0;
	ioctl(fd_disp, DISP_CMD_HDMI_DISABLE, args);

	// Set the mode.
	args[0] = 0;
	args[1] = mode;
	ret = ioctl(fd_disp, DISP_CMD_HDMI_SET_MODE, args);
	if (ret < 0) {
		fprintf(stderr, "Error: ioctl(DISP_CMD_HDMI_SET_MODE) failed: %s\n",
     			strerror(-ret));
		return ret;
	}

	// Turn HDMI on again.
	args[0] = 0;
	ioctl(fd_disp, DISP_CMD_HDMI_ENABLE, args);

}
