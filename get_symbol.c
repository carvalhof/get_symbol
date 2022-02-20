#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "nfp.h"
#include "nfp_cpp.h"
#include "nfp_nffw.h"
#include "nfp-common/nfp_resid.h"

#define NFP_DEVICE 0

int main(int argc, char** argv) {
	if(argc != 4) {
		fprintf(stderr, "Usage: %s <symbol name> <size in bytes> <offset>.\n", argv[0]);
		exit(-1);
	}

	struct nfp_device *h_nfp = nfp_device_open(NFP_DEVICE);
	if(!h_nfp) {
		fprintf(stderr, "Error: failed to open nfp handle (%s)\n", strerror(errno));
		exit(-1);
	}

	const struct nfp_rtsym *rtsym = nfp_rtsym_lookup(h_nfp, argv[1]);
	if(!rtsym) {
		fprintf(stderr, "Error: could not find rtsym %s (%s)\n", argv[1], strerror(errno));
		exit(-1);
	}

	ssize_t size = atoi(argv[2]);
	unsigned long long offset = atoi(argv[3]);

	uint8_t buffer[size];
	memset(buffer, 0, size);

	ssize_t n = nfp_rtsym_read(h_nfp, rtsym, buffer, sizeof(buffer), offset);
	if(n == -1) {
		fprintf(stderr, "Error: could not read %s symbol (%s)\n", argv[1], strerror(errno));
		exit(-1);
	}

	/* do something on buffer */

	nfp_device_close(h_nfp);

	return 0;
}
