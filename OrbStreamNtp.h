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

enum COMM_STATUS
{
	COMM_START	= 0,
	COMM_CRC_ERROR,
	COMM_RESET,
} comm_status;

#endif
