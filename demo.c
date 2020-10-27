//  Hello World server
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "OrbStreamNtp.h"

#define __DEBUG
#ifdef __DEBUG
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

int main (void)
{
    //  初始化NTP 建立服务端     
    void *resp_ntp = orb_ntp_init("tcp://*:5555");

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

        orb_ntp_worker(resp_ntp,buffer,sizeof(buffer));

    }
    return 0;
}
