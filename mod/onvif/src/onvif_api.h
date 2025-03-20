#ifndef __onvif_api_h__
#define __onvif_api_h__

#include <stdint.h>

#include "onvif.h"

#define MAX_PRESET_NUM  512
#define ONVIF_PRESET_NAME_FMT  "PtzName_%d"


/* probe */
typedef struct nvc_probe_item_s {
    uint8_t  dst_id[32];/* Ŀ���豸ID */
    uint8_t  ip[64];
    uint32_t type;	    /**Device_Type_E 0:Device 1:NetworkVideoTransmitter*/
    uint32_t ch_num;
    uint32_t port;
}nvc_probe_item_t;
typedef int (NVC_PROBER_CB)(nvc_probe_item_t *item, void *user_args);

/*------------------------------------------------------*/

int32_t nvc_init(void);
int32_t nvc_uninit(void);

/*------------------------------------------------------*/

int32_t nvc_probe(int type, int timeout, NVC_PROBER_CB *cb, void *user_args);

/*------------------------------------------------------*/

void *nvc_dev_open(char *url, int timeout /*EVENT_CB*/);
int32_t nvc_dev_close(void *dev);

typedef struct {
    uint8_t    trans;       /* 0: udp, 1: tcp, 2: rtsp 3: http*/
    uint8_t    proto;       /* 0: Unicast, 1: multicast */
    int8_t     url[256];    /* url */
}nvc_media_url_t;

int32_t nvc_media_url_get(void *dev, int ch, int st, nvc_media_url_t* media);

// NVC_PTZ_ID_E #include "onvif.h"
// nvc_ptz_ctl_t #include "onvif.h"
int32_t nvc_ptz_ctl(void *dev, int ch, int st, nvc_ptz_ctl_t *ctl);

/*
 * Ԥ�õ㶨��
 */
typedef struct {
    uint8_t enable;         //�Ƿ�����
    uint8_t no;             //Ԥ�õ��
    uint8_t res[2];         //����
    uint8_t name[32];       //Ԥ�õ�����
}nvc_preset_t;
 
/*
 * Ԥ�õ㼯��(ÿ��ͨ��һ������)
 */
typedef struct {
    uint8_t         num;                       //�����õ�Ԥ�õ����
    uint8_t         res[3];                    //����
    nvc_preset_t    preset_set[MAX_PRESET_NUM];//Ԥ�õ�
}nvc_preset_param_t;

// ��ѯԤ��λ����,�Ա�������Ѳ�� 
int32_t nvc_ptz_presets_get(void *dev, int ch, int st, nvc_preset_param_t *preset);


typedef struct {
    uint8_t brightness;         //����
    uint8_t contrast;           //�Աȶ�
    uint8_t saturation;         //���Ͷ�
    uint8_t hue;                //ɫ��
    uint8_t sharpness;          //���
    uint8_t effect_mode;        //0:ʹ���Զ���ֵ��1��ʹ��Ĭ��ֵ
    uint8_t res[2];
}nvc_image_attr_t;

int32_t nvc_img_attr_get(void *dev, int ch, int st, nvc_image_attr_t *attr);
int32_t nvc_img_attr_set(void *dev, int ch, int st, nvc_image_attr_t *attr);

int32_t nvc_snap_url_get(void *dev, int ch, int st, char *url);

typedef struct {
    uint32_t year;
    uint32_t mon;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
}nvc_time_t; // == NVC_time_t;

//Time synchronization to the device
int32_t nvc_systime_set(void *dev, int ch, int st, nvc_time_t *time);

/*------------------------------------------------------*/

/*NVT��������*/
typedef struct nvt_parm_s {
  int ch_num;     //nvt�豸ͨ����
  int auth;       //auth;
	uint16_t port;  //nvt�����˿�
}nvt_parm_t;

typedef struct user_right_s {
    uint8_t user_name[32];
    uint8_t user_pwd[32];
    int32_t local_right;    //����GUIȨ��
    uint32_t remote_right;  //Զ��Ȩ��
}user_right_t;


/* ��ʼ��NVT */
int32_t nvt_init(nvt_parm_t *parm);
int32_t nvt_uninit(void);

/* ����NVT���� */
int32_t nvt_start(void);
int32_t nvt_stop(void);

/*------------------------------------------------------*/


#endif //__onvif_api_h__


