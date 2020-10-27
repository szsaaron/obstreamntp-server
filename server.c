//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "md5.h"

#define __DEBUG
#ifdef __DEBUG
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

int main (void)
{
    static int frame_count = 0;
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    FILE *fp=NULL;
    unsigned char buffer[640*480*2];
    //const char *filename = "ir_640_480.stream";
    const char *filename = "ir_640_480.raw";

    fp=fopen(filename,"rb+");
    if(fp==NULL){
            printf("cannot open %s file\n",filename);
            return -1;
    }
    while (1) {
#if 0
        if(feof(fp) == 1){
                printf ("fread to the end of %s \n",filename);
                fseek(fp, 0, SEEK_SET);
                fread(buffer, 1, 640*480*2, fp); 
                frame_count = 1; 
                printf ("frame_count: %d \n",frame_count);
        }else{
                fread(buffer, 1, 640*480*2, fp);
                frame_count++;
                printf ("frame_count: %d \n",frame_count);
                printf ("re fread \n");
        } 
#else
        if (fread(buffer, 1, 640*480*2, fp) != 640*480*2){
                // Loop
                DEBUG("re fread!!!\n");
                fseek(fp, 0, SEEK_SET);
                fread(buffer, 1, 640*480*2, fp);
                frame_count = 1;
        }else{
                frame_count++;
        }
        DEBUG ("frame_count: %d \n",frame_count);
#endif


        char rec_buffer [10];
        zmq_recv (responder, rec_buffer, 10, 0);
        DEBUG ("Received Hello\n");
        zmq_send (responder, buffer, 640*480*2, 0);
	DEBUG ("Send raw frame data \n");
	zmq_recv (responder, rec_buffer, 10, 0);
	DEBUG ("Received md5 requect\n");
	char md5_str[MD5_STR_LEN + 1];
	Compute_string_md5(buffer, 640*480*2, md5_str);
	zmq_send (responder,(unsigned char*)md5_str,sizeof(md5_str),0);
	DEBUG ("Send md5sun:%s\n",md5_str);
            
    }
    return 0;
}
