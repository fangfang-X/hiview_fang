#ifndef __file_h__
#define __file_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/statvfs.h>

#include "mov-format.h"
#include "mpeg4-avc.h"
#include "mpeg4-hevc.h"
#include "mpeg4-aac.h"
#include "fmp4-writer.h"
#include "mov-reader.h"

#include "rec.h"


#define strcat_s strcat
#define strcpy_s strcpy
#define sprintf_s snprintf
#define localtime_s(s, i) localtime_r(i, s)

typedef struct rec_v_info_s
{
    int w;  //���
    int h;  //�߶�
    int fps;//֡��
}rec_v_info_t;

typedef struct rec_a_info_s
{
    int sp;  //������
    int bps; //bit_per_sample
    int chs; //ͨ����
}rec_a_info_t;

typedef struct rec_rw_info_s
{
    int type;   // GSF_FRM_
    int enc;    // GSF_ENC_
    int time;   // localtime sec
    int ms;     // pts ms
    union {
        rec_v_info_t v;
        rec_a_info_t a;
    };
}rec_rw_info_t;


typedef struct _rec_media_info_s
{
	int aenc;   // GSF_ENC_
	int venc;   // GSF_ENC_
	rec_v_info_t v;
  rec_a_info_t a;
}rec_media_info_t;


typedef struct fd_av_s {
    FILE *fd; // first field;
    uint32_t stime;
    uint32_t size;
    
    // track;
    int vtrack;
    int atrack;
    
    union { 
      fmp4_writer_t *w; 
      mov_reader_t  *r;
    };
    
    // mp4-frame buffer;
	  int s_length; 
	  uint8_t *s_buffer;
	    
	  // out-mp4-frame-info;
    int type;                           // GSF_FRM_
	  int64_t pts;                        // ms;
    rec_v_info_t v;                     // media info;
    rec_a_info_t a;                     // media info;
	  
	  // out-mp4-frame-buffer;
	  int *out_size;                      // out size;
	  uint8_t *out_buffer;                // out buffer;
	  
	  int vobject, aobject;               // MOV_OBJECT;
	  union {
  	  struct mpeg4_hevc_t s_hevc;       // extra
      struct mpeg4_avc_t s_avc;         // extra
	  };
	  union {
  	  struct mpeg4_aac_t s_aac;         // extra
	  };

}fd_av_t;


typedef struct {
    FILE *fd; // first field;
}file_t;

/* �ļ���д */
file_t*
    fd_open(char *name, int type);              /* ���ļ���������ʱ�����ļ� */
int fd_close(file_t *fd);                       /* �ر��ļ� */
int fd_flush(file_t *fd);                       /* ˢ���ݵ����� */
int fd_seek(file_t *fd, int offset, int origin);/* SEEK */
int fd_write(file_t *fd, char *buf, int size);  /* д�ļ� */
int fd_read(file_t *fd, char *buf, int size);   /* ���ļ� */
int fd_size(file_t *fd);                        /* �ļ���С */
int fd_rm(char *name);                          /* ɾ���ļ� */
int fd_stat(char* filename, uint32_t *size, uint32_t *mtime, uint16_t *mtime_ms); //��ȡ�ļ���Ϣ;

/* ��Ƶ�ļ�д */
fd_av_t*
    fd_av_open(char *name);               /* ����Ƶ��������ʱ�����ļ� */
int fd_av_close(fd_av_t *fd);             /* �ر���Ƶ�ļ� */
int fd_av_flush(fd_av_t *fd);             /* ˢ���ݵ����� */
int fd_av_write(fd_av_t *fd, char *buf, int size, rec_rw_info_t *info);   /* д��Ƶ�ļ� */
uint32_t fd_av_size(fd_av_t *fd);         /* ��ȡ�ļ���С */

/* ��Ƶ�ļ��� */
fd_av_t*
    fd_av_ropen(char *name, int type, rec_media_info_t *media); /* ����Ƶ��type: ������չ��Ƶ�ļ���ʽ */
int fd_av_rclose(fd_av_t *fd);            /* �ر���Ƶ�ļ� */
int fd_av_rread(fd_av_t *fd, char *buf, int *size, rec_rw_info_t *info);    /* ����Ƶ�ļ� */
int fd_av_rseek(fd_av_t *fd, int sec);    /* SEEK��ָ����sec�� */
int fd_av_rsize(fd_av_t *fd);             /* ��ȡ�ļ���С */

/* Ŀ¼���� */
int fd_access(char *name);                /* �ж�һ���ļ���Ŀ¼�Ƿ���� 0: ������, 1: ���� */
int fd_dir_mk(char *name);                /* ����һ��Ŀ¼ �����Ŀ¼�Ѵ淵�سɹ� */
int fd_dir_mv(char *src, char *dst);      /* Ŀ¼���� */
int fd_dir_rm(char *name);                /* ɾ��Ŀ¼��Ŀ¼�е������ļ� */
int fd_dir_each(char *name, int (*cb)(char *name, int is_dir, void *u), void *u); /* ����Ŀ¼�µ������ļ�����Ŀ¼ */


#endif //__file_h__
