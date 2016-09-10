void cdfs_test() {
	//file_t fd;
	file_t d;
	dirent_t *de;
	//int amt;

	printf("Reading directory from CD-Rom:\r\n");

	/* Read and print the root directory */
	d = fs_open("/ram", O_RDONLY | O_DIR);
	if (d == 0) {
		printf("Can't open root!\r\n");
		return;
	}

	while ( (de = fs_readdir(d)) ) {
		printf("%s  /  ", de->name);
		if (de->size >= 0) {
			printf("%d\r\n", de->size);
		} else {
			printf("DIR\r\n");
		}
	}

	fs_close(d);
}

void romdisk_test() {
	//file_t fd;
	file_t d;
	dirent_t *de;
	//int amt;

	printf("Reading directory from CD-Rom:\r\n");

	/* Read and print the root directory */
	d = fs_open("/TEST", O_RDONLY | O_DIR);
	if (d == 0) {
		printf("Can't open root!\r\n");
		return;
	}

	while ( (de = fs_readdir(d)) ) {
		printf("%s  /  ", de->name);
		if (de->size >= 0) {
			printf("%d\r\n", de->size);
		} else {
			printf("DIR\r\n");
		}
	}

	fs_close(d);
}