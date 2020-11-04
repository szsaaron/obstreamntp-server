#ifndef ORB_STREAM_NTP_H
#define ORB_STREAM_NTP_H
typedef struct
{
	//unsigned char *pframe;
	unsigned char ntp_status;
	unsigned char stream_type;
	unsigned int timestamp;
	unsigned char frame_data[640*480*2];
	char md5_str[16*2+1];
	
}ROB_STREAM_NTP;

typedef enum
{
	COMM_START	= 0,
	COMM_CRC_ERROR,
	COMM_RESET,
}COMM_STATUS;


void* orb_ntp_init(const char *netinfo);
void orb_ntp_worker(void* resp, unsigned char *pdata, unsigned int sizes);

#endif
