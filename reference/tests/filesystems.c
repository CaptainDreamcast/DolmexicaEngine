#include <kos.h>
KOS_INIT_FLAGS(INIT_DEFAULT);


//Standard Stuff
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


//For PNG2Texture
#include <png/png.h>

/* romdisk */
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);

//Main Function. Duh.
int main ( int argc, char *argv[] )
{
    int GameLoop = 1;
    pvr_init_defaults();
    //while(GameLoop == 1)
    //{
    MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)


    if ((st->buttons & CONT_START)) {
            GameLoop = 0;
			}
    MAPLE_FOREACH_END()


    file_t test;
    int FileSize;

    test = fs_open("/pc/test.txt", O_RDONLY);
    FileSize = fs_total(test);
    printf("%d\n", FileSize);
    char buffer[FileSize];
    fs_read(test, buffer, FileSize);

    int i = 0;
    while(i < FileSize) {
    printf("%c\n", buffer[i]);
    i++;
    }
    fs_close(test);

    file_t test_again;

    fs_unlink("/pc/test2.txt");
    test_again = fs_open("/ram/test2.txt", O_RDWR);
    FileSize = fs_total(test);
    printf("%d\n", FileSize);
    char buffer2[4] = "TEST";
    fs_write(test_again, buffer2, 4);
    fs_close(test_again);

    fs_copy("/ram/test2.txt", "/pc/test2.txt");

    //}
    pvr_mem_stats();
	return(0);
}
