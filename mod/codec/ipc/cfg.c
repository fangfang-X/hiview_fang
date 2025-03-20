#include <stdio.h>
#include <unistd.h>
#include "cfg.h"


char codec_parm_path[128] = {0};

gsf_codec_ipc_t codec_ipc = {
  .venc = {
    [0] = {
        .en     = 1,
        .type   = 0,
        #if defined(GSF_CPU_3519a)
        .width  = 3840,
        .height = 2160,
        #elif defined(GSF_CPU_3516e)
        .width  = 1280,
        .height = 720,
        #else
        .width  = 1920,
        .height = 1080,
        #endif
        .fps    = 30,
        .gop    = 30,
        .flow   = 0,
        .bitrate= 8000,
        .profile= 0,
        .qp     = 0,
    },
    [1] = {
        .en     = 1,
        .type   = 0,
        #if defined(GSF_CPU_3516e)
        .width  = 640,
        .height = 480,
        #else
        .width  = 1280,
        .height = 720,
        #endif
        .fps    = 30,
        .gop    = 30,
        .flow   = 0,
        .bitrate= 2000,
        .profile= 0,
        .qp     = 0,
    },
    #if GSF_CODEC_VENC_NUM > 2
    [2] = {
        .en     = 1,
        .type   = 3,
        #if defined(GSF_CPU_3519a)
        .width  = 3840,
        .height = 2160,
        #elif defined(GSF_CPU_3516e)
        .width  = 1280,
        .height = 720,
        #else
        .width  = 1920,
        .height = 1080,
        #endif
        .fps    = 30,
        .gop    = 30,
        .flow   = 0,
        .bitrate= 2000,
        .profile= 0,
        .qp     = 0,
    }
    #endif
  },
  .aenc = {
    .en = 0, .type = GSF_ENC_AAC, .sprate = 48, .vol = 50,
  },
  
  .lenscfg = {
    .lens = 0,         //0: ldm lens,  1: sony lens;
    .uart = "ttyAMA2", //ttyAMA2: Single channel baseboard, ttyAMA4: double channel baseboard;
  },
  
  .osd = {
    [0] = {},
  },
  .vmask = {
    [0] = {},
  },
};

int json_parm_load(char *filename, gsf_codec_ipc_t *cfg)
{
  if(access(filename, 0)) return -1;
  FILE *f=fopen(filename,"rb");fseek(f,0,SEEK_END);long len=ftell(f);fseek(f,0,SEEK_SET);
	char *data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
  cJSON* json = cJSON_Parse(data);
  free(data);
  if (json)
	{
    sjb_bind_gsf_codec_ipc_t(json, 1, cfg, 0, 0);
    cJSON_Delete(json);
	}
  return 0;
}

int json_parm_save(char *filename, gsf_codec_ipc_t *cfg)
{
  FILE *f=fopen(filename,"wb");
  cJSON* out = cJSON_CreateObject();
  sjb_bind_gsf_codec_ipc_t(out, 0, cfg, 0, 0);
  char* print = cJSON_Print(out);
  if(print)
  {
	  fprintf(f, "%s", print);
	  fflush(f);fdatasync(fileno(f));fclose(f);
	  free(print);
  }
  cJSON_Delete(out);
  return 0;
}