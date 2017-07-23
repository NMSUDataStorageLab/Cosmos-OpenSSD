#include <fcntl.h>
/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>*/
#include <sys/types.h>
#include <sys/stat.h>

//int fd = open("/dev/pcissda", O_WRONLY | O_APPEND | O_CREAT,0640);
	void wtest(void)
{
	//char buffer[512];

    int fOut;
    

    //Create a new file
    fOut = open ("/dev/pcissda", O_RDWR | O_CREAT | O_SYNC);



    //write to it and close it.
    write (fOut, "0123456789", 36);
    close (fOut);


}
