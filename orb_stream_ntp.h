#ifndef ORB_STREAM_NTP_H
#define ORB_STREAM_NTP_H
typedef struct
{
	unsigned char *pframe;
	unsigned char ntp_status;
	unsigned char frame_data[640*480*2];
	char md5_str[MD5_STR_LEN + 1];
	
}ROB_STREAM_NTP

#endif
