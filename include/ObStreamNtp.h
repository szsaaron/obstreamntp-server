#ifndef ORB_STREAM_NTP_H
#define ORB_STREAM_NTP_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	unsigned char checksum;
	unsigned char stream_type;
	unsigned int depth_timestamp;
	unsigned int ir_timestamp;
}ORB_FRAME_INFO;

typedef struct
{
	//unsigned char *pframe;
	unsigned char ntp_status;
	ORB_FRAME_INFO frame_info;
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
void orb_ntp_close();
void orb_ntp_worker(void* resp, unsigned char *pdata, unsigned int sizes);
void orb_ntp_frame_info_set(ORB_FRAME_INFO *pfinfo);

#ifdef __cplusplus
}
#endif

#endif
