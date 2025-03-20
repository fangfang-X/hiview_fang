#ifndef __codec_h__
#define  __codec_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "inc/gsf.h"

//for json cfg;
#include "mod/codec/inc/sjb_codec.h"

#define GSF_IPC_OSD        "ipc:///tmp/codec_osd"
#define GSF_IPC_CODEC      "ipc:///tmp/codec_rep"
#define GSF_IPC_VOICE        "ipc:///tmp/codec_voice"

enum {
    GSF_ID_CODEC_VENC     = 1,  // ch, sid, gsf_venc_t
    GSF_ID_CODEC_AENC     = 2,  // ch, sid, gsf_aenc_t
    GSF_ID_CODEC_SDP      = 3,  // ch, sid, gsf_sdp_t;
    GSF_ID_CODEC_IDR      = 4,  // ch, sid, nil;
    GSF_ID_CODEC_OSD      = 5,  // ch, sid, gsf_osd_t
    GSF_ID_CODEC_VMASK    = 6,  // ch, sid, gsf_vmask_t
    GSF_ID_CODEC_SNAP     = 7,  // ch, sid, nil;
    GSF_ID_CODEC_VORES    = 8,  // ch, sid, gsf_resolu_t;
    GSF_ID_CODEC_VOLY     = 9,  // ch, sid, gsf_layout_t;
    GSF_ID_CODEC_VOMV     = 10, // ch, sid, gsf_rect_t;
    GSF_ID_CODEC_LENS     = 11, // ch, sid, gsf_lens_t;
    GSF_ID_CODEC_LENSCFG  = 12, // ch, sid, gsf_lenscfg_t;
    GSF_ID_CODEC_IMGALL   = 13, // ch, sid, gsf_img_all_t;
    GSF_ID_CODEC_IMGCSC   = 14, // ch, sid, gsf_img_csc_t;
    GSF_ID_CODEC_IMGAE    = 15, // ch, sid, gsf_img_ae_t;
    GSF_ID_CODEC_IMGDEHAZE= 16, // ch, sid, gsf_img_dehaze_t;
    GSF_ID_CODEC_IMGSCENE  = 17, // ch, sid, gsf_img_scene_t;
    GSF_ID_CODEC_IMGSHARPEN= 18, // ch, sid, gsf_img_sharpen_t;
    GSF_ID_CODEC_IMGHLC    = 19, // ch, sid, gsf_img_hlc_t;
    GSF_ID_CODEC_IMGGAMMA  = 20, // ch, sid, gsf_img_gamma_t;
    GSF_ID_CODEC_IMGDRC    = 21, // ch, sid, gsf_img_drc_t;
    GSF_ID_CODEC_IMGLDCI   = 22, // ch, sid, gsf_img_ldci_t;
    GSF_ID_CODEC_IMG3DNR   = 23, // ch, sid, gsf_img_3dnr_t;
    GSF_ID_CODEC_SCENEAE   = 24, // ch, sid, gsf_scene_ae_t;
    GSF_ID_CODEC_IMGLDC    = 25, // ch, sid, gsf_img_ldc_t;
    
    GSF_ID_CODEC_END
};

enum {
    GSF_CODEC_ERR = -1,
};


enum {
  GSF_OSD_TYPE_TXT  = 0,
  GSF_OSD_TYPE_BIN  = 1,
};

typedef struct {
  int resolu;
  int w, h;
}gsf_resolu_t;

typedef struct {
  int video_shmid;
  int audio_shmid;
}gsf_shmid_t;

typedef struct {
  int layout;
  gsf_shmid_t shmid[GSF_CODEC_NVR_CHN];
}gsf_layout_t;

typedef struct {
  int x, y;
  int w, h;
}gsf_rect_t;

typedef struct {
  int size;
  unsigned char data[128];
}gsf_sdp_val_t;

enum {
  GSF_SDP_VAL_SPS  = 0,
  GSF_SDP_VAL_PPS  = 1,
  GSF_SDP_VAL_VPS  = 2,
  GSF_SDP_VAL_SEI  = 3,
};

typedef struct {
  int video_shmid;
  int audio_shmid;
  gsf_aenc_t aenc;
  gsf_venc_t venc;
  gsf_sdp_val_t val[4];
}gsf_sdp_t;

typedef struct {
  int  pixel;   /*16 bit per pixel*/
  int  x, y, w, h;
  int  x1,y1,x2,y2;
  char data[0]; /*data of pixel buffer */
}gsf_osd_act_t;

#ifdef __cplusplus
}
#endif

#endif