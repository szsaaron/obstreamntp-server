//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "md5.h"
#include "OrbStreamNtp.h"

#define __DEBUG
#ifdef __DEBUG
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

int main (void)
{
    //  初始化ZMQ 建立服务端
#if 1      
        void *resp_ntp = orb_ntp_init("tcp://*:5555");
#else
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
#endif
    //从文件中读取数据，产生模拟视频流
    FILE *fp=NULL;
    unsigned char buffer[640*480*2];
    const char *filename = "ir_640_480.stream";
    //const char *filename = "ir_640_480.raw";
    static int frame_count = 0;
    fp=fopen(filename,"rb+");
    if(fp==NULL){
            printf("cannot open %s file\n",filename);
            return -1;
    }
    while (1) {

        if (fread(buffer, 1, 640*480*2, fp) != 640*480*2){
                // Loop
                DEBUG("get to file end!!!\n");
                fseek(fp, 0, SEEK_SET);
                fread(buffer, 1, 640*480*2, fp);
                frame_count = 1;
        }else{
                frame_count++;
        }
        DEBUG ("frame_count: %d \n",frame_count);



#if 1
        orb_ntp_worker(resp_ntp,buffer,sizeof(buffer));
#else
        //ZMQ 接受客户端请求后，发生帧数据
        char rec_buffer [10];
        zmq_recv (responder, rec_buffer, 10, 0);
        DEBUG ("Received from client :%s \n",rec_buffer);;
        ROB_STREAM_NTP rframe;
        ROB_STREAM_NTP *pframe = &rframe;
        Compute_string_md5(buffer, sizeof(buffer), pframe->md5_str);
        memcpy(pframe->frame_data,buffer,sizeof(buffer));
        zmq_send (responder, pframe, sizeof(rframe), 0);
	DEBUG ("Send raw frame data \n");  
#endif

    }
    return 0;
}

#if 1 
void* orb_ntp_init(char*netinfo)
{
        void *context = zmq_ctx_new ();
        void *responder = zmq_socket (context, ZMQ_REP);
        int rc = zmq_bind (responder, netinfo);
  //      assert (rc == 0);
        return responder;
}

void orb_ntp_worker(void* resp, unsigned char *pdata, unsigned int sizes)
{
        char rec_buffer [10];
        //char send_buffer[5];
        ROB_STREAM_NTP rframe;
        ROB_STREAM_NTP * pframe = &rframe;
        unsigned char comm_status;

        zmq_recv (resp, rec_buffer, 10, 0);
        DEBUG ("Received %s \n",rec_buffer);
        if(strcmp(rec_buffer,"Start") == 0){
                comm_status = COMM_START;   
        }else{
                comm_status = COMM_RESET;  
        }
        pframe->ntp_status = comm_status;
        switch(comm_status)
        {
                case COMM_START:
                        memcpy(pframe->frame_data,pdata,sizes);
                        Compute_string_md5(pframe->frame_data, sizeof(pframe->frame_data), pframe->md5_str);
                        zmq_send (resp, (unsigned char*)pframe, sizeof(rframe), 0);
                        DEBUG ("Send raw data \n");  
                        break;
                case COMM_CRC_ERROR:
                        DEBUG ("Communication error code :%d \n",comm_status); 
                        break;
                case COMM_RESET:
                        DEBUG ("Communication error code :%d \n",comm_status);
                        //send_buffer="RESET"
                        //zmq_send (resp,send_buffer,5,0);
                        break;
        }  
}
#endif