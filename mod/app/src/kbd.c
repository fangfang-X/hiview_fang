#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "fw/comm/inc/serial.h"
#include "cfg.h"
#include "kbd.h"
#include "msg_func.h"

static pthread_t tid;
static int serial_fd;
static void* kbd_task(void *parm);

int kbd_mon(char *ttyAMA)
{
  system("himm 0x120F002C  1;");
  system("himm 0x120F0030  1;");
   
  if(!ttyAMA || strlen(ttyAMA) < 1)
    return -1;
    
  serial_fd = open(ttyAMA, O_RDWR | O_NOCTTY /*| O_NDELAY*/);
  if (serial_fd < 0)
  {
      return -2;
  }
  
	// set serial param
  if(serial_set_param(serial_fd, 9600, 0, 1, 8) < 0)
  {
    return -3;
  }
  
  return pthread_create(&tid, NULL, kbd_task, (void*)NULL);
}


static char onvif_url[128];

int kbd_set_url(char *url)
{
  if(url)
  {
    strncpy(onvif_url, url, sizeof(onvif_url)-1);
    printf("onvif_url:[%s]\n", onvif_url);
  } 
  return 0;
}



#if 0
//
//[��]        FF 01 00 53 0E 01 63 // ����3��
//[��]        FF 01 00 53 0E 00 62  // ����3��
//[��ʼ¼��]  FF 01 00 DB 00 01 DD
//[����¼��]  FF 01 00 DB 00 00 DC
//
//[��ʼ����]  FF 01 00 19 00 01 1B
//[�������]  FF 01 00 19 00 00 1A
//[F1]        FF 01 00 72 00 00 73
//[���Զ�]  FF 01 00 53 05 00 59
//[�ر��Զ�]  FF 01 00 53 05 03 5C
//
//[�ֶ�]
// �ں���ģʽ�� // FF 01 00 53 05 11 6A
// �ڳ���ģʽ�� // FF 01 00 53 05 21 7A
// �ڳ�ʼģʽ�� // FF 01 00 53 05 01 5A
// ���ֶ�ģʽ�� // FF 01 00 53 05 03 5C
//[����]      // FF 01 00 56 00 01 58, FF 01 00 53 05 03 5C
//[����]      // FF 01 00 57 00 00 58, FF 01 00 53 05 02 5B         
//[�۹�]         FF 01 00 53 0D 00 61
//[�۹�+]        FF 01 00 53 0F 00 63
//[�۹�-]        FF 01 00 53 0F 01 64
//[F2]           FF 01 00 70 00 00 71
//[����/����]    FF 01 00 53 0D 01 62
//[����+]        FF 01 00 53 0F 10 73
//[����-]        FF 01 00 53 0F 11 74

//[1][2][3] ��������Ԥ��λ FF 01 00 03 00 XX SUM  XX��ʾԤ��λ, SUM = (01+00+03+00+XX)%256
//[4][5][6] �̰�����Ԥ��λ FF 01 00 07 00 XX SUM  XX��ʾԤ��λ, SUM = (01+00+07+00+XX)%256
//
//[Ѳ��]FF 01 00 07 00 23 2B
//[��λ]FF 01 00 53 00 00 54
//
//[�۽�+]FF 01 01 00 00 00 02
//[�۽�-]FF 01 00 80 00 00 81
//[��Ȧ+]FF 01 02 00 00 00 03
//[��Ȧ-]FF 01 04 00 00 00 05
//
// /////////////////////////////
//[ץ��] FF 01 00 53 10 01 65
//
//[�䱶+]FF 01 00 40 00 00 41 
//[�䱶-]FF 01 00 20 00 00 21 
//
//[��]  FF 01 00 10 XX YY SUM // XX��ʾˮƽ������ٶ�, ��Χ00~3F
//[��]  FF 01 00 08 XX YY SUM // YY��ʾ��ֱ������ٶ�, ��Χ00~3F
//[��]  FF 01 00 04 XX YY SUM // SUM=��FF����֮��ȡģ256
//[��]  FF 01 00 02 XX YY SUM
//[����]FF 01 00 14 XX YY SUM
//[����]FF 01 00 12 XX YY SUM
//[����]FF 01 00 0C XX YY SUM
//[����]FF 01 00 0A XX YY SUM
//
#endif



static int func_zoom_add(unsigned char *buf)
{
  GSF_MSG_DEF(gsf_onvif_ptz_ctl_t, ptz, 8*1024);
  
  memset(ptz, 0, sizeof(gsf_onvif_ptz_ctl_t));
  strcpy(ptz->url, onvif_url);
  ptz->ctl.cmd = NVC_PTZ_ZOOM_ADD_START;
  ptz->ctl.speed = 5;
  
  GSF_MSG_SENDTO(GSF_ID_ONVIF_C_PTZCTL, 0, SET, 0
                , sizeof(gsf_onvif_ptz_ctl_t)
                , GSF_IPC_ONVIF, 2000);
  return 0;
}

static int func_zoom_sub(unsigned char *buf)
{
  GSF_MSG_DEF(gsf_onvif_ptz_ctl_t, ptz, 8*1024);
  
  memset(ptz, 0, sizeof(gsf_onvif_ptz_ctl_t));
  strcpy(ptz->url, onvif_url);
  ptz->ctl.cmd = NVC_PTZ_ZOOM_SUB_START;
  ptz->ctl.speed = 5;
  
  GSF_MSG_SENDTO(GSF_ID_ONVIF_C_PTZCTL, 0, SET, 0
                , sizeof(gsf_onvif_ptz_ctl_t)
                , GSF_IPC_ONVIF, 2000);
  return 0;
}

static int func_zoom_stop(unsigned char *buf)
{
  GSF_MSG_DEF(gsf_onvif_ptz_ctl_t, ptz, 8*1024);
  
  memset(ptz, 0, sizeof(gsf_onvif_ptz_ctl_t));
  strcpy(ptz->url, onvif_url);
  ptz->ctl.cmd = NVC_PTZ_ZOOM_SUB_STOP;
  ptz->ctl.speed = 5;
  
  GSF_MSG_SENDTO(GSF_ID_ONVIF_C_PTZCTL, 0, SET, 0
                , sizeof(gsf_onvif_ptz_ctl_t)
                , GSF_IPC_ONVIF, 2000);
  return 0;
}

static int func_layout(unsigned char *buf)
{
  static int num = 0;
  extern int vo_ly(int num); vo_ly(num++%5+1);
}


typedef int(func_t)(unsigned char *buf);

static func_t* func[0x08ff] = {
  [0x0000] = func_zoom_stop,
  [0x0040] = func_zoom_add,
  [0x0020] = func_zoom_sub,
  [0x0053] = func_layout,
};


static void* kbd_task(void *parm)
{
  int ret = 0;
  unsigned short cmd = 0;
  unsigned char buf[128] = {0};
  unsigned char buf2[128] = {0};
  while(1)
  {
    ret = read(serial_fd, buf, 7);
    
    cmd = (buf[2] << 8) | buf[3];
    
    if(  cmd == 0x0000 // rocker
      || cmd == 0x0040 || cmd == 0x0020
      || cmd == 0x0010 || cmd == 0x0008
      || cmd == 0x0004 || cmd == 0x0002
      || cmd == 0x0014 || cmd == 0x0012
      || cmd == 0x000C || cmd == 0x000A)
    {
      if(!memcmp(buf2, buf, 7))
      {
        memcpy(buf2, buf, 7);
        continue;
      }
    }
    memcpy(buf2, buf, 7);
    
    printf("ret:%d, buf[%02x %02x %02x %02x %02x %02x %02x]\n"
          , ret, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);

    if(buf[0] == 0xff)
    {  
      if(cmd >= 0 && cmd < 0x08ff && func[cmd])
      {
        func[cmd](buf);
      }
    }
        
  }
  return NULL;
}