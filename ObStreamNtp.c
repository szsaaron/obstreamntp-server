//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "md5.h"
#include "ObStreamNtp.h"

#define __DEBUG
#ifdef __DEBUG
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

ROB_STREAM_NTP rframe;
ROB_STREAM_NTP * pframe = &rframe;

void* context = NULL;
void* responder = NULL;
void* orb_ntp_init(const char *netinfo)
{
        context = zmq_ctx_new ();
        void *responder = zmq_socket (context, ZMQ_REP);
        int rc = zmq_bind (responder, netinfo);
  //      assert (rc == 0);
	DEBUG("rc = %d \n",rc);
        return responder;
}
void orb_ntp_close()
{
    	zmq_close (responder);
    	zmq_term (context);
	context = NULL;
	responder = NULL;
}
void orb_ntp_worker(void* resp, unsigned char *pdata, unsigned int sizes)
{
        char rec_buffer [10];
//        ROB_STREAM_NTP rframe;
//        ROB_STREAM_NTP * pframe = &rframe;
        unsigned char comm_status;

	memset(rec_buffer,0,sizeof(rec_buffer));
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
			if(pframe->frame_info.checksum == 1)
			{
                        	Compute_string_md5(pframe->frame_data, sizeof(pframe->frame_data), pframe->md5_str);
			}
                        zmq_send (resp, (unsigned char*)pframe, sizeof(rframe), 0);
                        DEBUG ("Send raw data \n");  
                        DEBUG ("    stream_type:%d \n",pframe->frame_info.stream_type);  
                        DEBUG ("   ir_timestamp:%d \n",pframe->frame_info.ir_timestamp);  
                        DEBUG ("depth_timestamp:%d \n",pframe->frame_info.depth_timestamp);  
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

void orb_ntp_frame_info_set(ORB_FRAME_INFO *pfinfo)
{
//	ROB_STREAM_NTP rframe;
//        ROB_STREAM_NTP * pframe = &rframe;
	pframe->frame_info.checksum = pfinfo->checksum;
	pframe->frame_info.stream_type = pfinfo->stream_type;
	pframe->frame_info.ir_timestamp = pfinfo->ir_timestamp;
	pframe->frame_info.depth_timestamp = pfinfo->depth_timestamp;
}
