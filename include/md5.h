#ifndef MD5_H
#define MD5_H

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

int Compute_file_md5(const char *file_path, char *md5_str);

int Compute_string_md5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
#endif

