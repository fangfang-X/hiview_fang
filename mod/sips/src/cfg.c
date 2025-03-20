#include <stdio.h>
#include <unistd.h>
#include "cfg.h"

char sips_parm_path[128] = {0};

gsf_sips_t sips_parm = {
  .auth = 0,
  .port = 5060,
  .chnum = 1,
  .host = "sip:34020000002000000001@192.168.0.166:5060",
  .device = "34020000001110000001",
  .password = "12345678",
  .expired = 3600,
  .keepalive = 60,
  .enable = 0,
};

int json_parm_load(char *filename, gsf_sips_t *cfg)
{
  if(access(filename, 0)) return -1;
  FILE *f=fopen(filename,"rb");fseek(f,0,SEEK_END);long len=ftell(f);fseek(f,0,SEEK_SET);
	char *data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
  cJSON* json = cJSON_Parse(data);
  free(data);
  if (json)
	{
    sjb_bind_gsf_sips_t(json, 1, cfg, 0, 0);
    cJSON_Delete(json);
	}
  return 0;
}

int json_parm_save(char *filename, gsf_sips_t *cfg)
{
  FILE *f=fopen(filename,"wb");
  cJSON* out = cJSON_CreateObject();
  sjb_bind_gsf_sips_t(out, 0, cfg, 0, 0);
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