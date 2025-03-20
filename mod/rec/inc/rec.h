#ifndef __rec_h__
#define  __rec_h__

// SD��¼��ģ��:
// ʹ����־�ļ���¼�ļ���(���ڴ�/�ر��ļ�ʱ,APPENDд����һ��);
// ������Ϣ���ڴ�,��߼����ٶ�,���ٴ��̲���;
// ʹ�� fragment MP4��ʽ,�쳣����ʱδ�رյ��ļ�����������;
// ��������(��־,��Ƶ)ѭ������,֧����Ƶ�ļ�д����,��ֹ������;
// ֧��FAT32,EXT4�ļ�ϵͳ;

#ifdef __cplusplus
extern "C" {
#endif


#include "inc/gsf.h"

//for json cfg;
#include "mod/rec/inc/sjb_rec.h"


#define GSF_IPC_REC "ipc:///tmp/rec_rep"

enum {
  GSF_ID_REC_QDISK    = 1,  // [gsf_disk_t .... N];
  GSF_ID_REC_QREC     = 2,  // [gsf_rec_q_t, gsf_file_t .... N];
  GSF_ID_REC_CFG      = 3,  // [gsf_rec_cfg_t];
  GSF_ID_REC_PATTERN  = 4,  // ["pattern"]; // eg. "/dev/mmcblk0p%[2-9]", "/dev/sd%[a-z]%[1-9]"
  GSF_ID_REC_IMAGE    = 5,  // ["filename"]
  GSF_ID_REC_END
};

enum {
  GSF_REC_ERR = -1,
};

enum {
  GSF_FILE_TAGS_TIMER   = (1<<0),  // bit-mask timer;
  GSF_FILE_TAGS_PIC     = (1<<1),  // bit-mask picture;
  GSF_FILE_TAGS_THUMB   = (1<<2),  // bit-mask thumbnail;
	GSF_FILE_TAGS_MANU    = (1<<3),  // bit-mask manual; 
  GSF_FILE_TAGS_MD      = (1<<4),  // bit-mask motion;
	GSF_FILE_TAGS_IO      = (1<<5),  // bit-mask gpio
	GSF_FILE_TAGS_PIR     = (1<<6),  // bit-mask pir;
};

#ifdef __cplusplus
}
#endif

#endif