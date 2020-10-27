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