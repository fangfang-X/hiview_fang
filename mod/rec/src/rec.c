#include <unistd.h>
#include <stdlib.h>
#include "inc/gsf.h"

#include "rec.h"
#include "cfg.h"
#include "msg_func.h"
#include "server.h"
#include "mod/bsp/inc/bsp.h"

GSF_LOG_GLOBAL_INIT("REC", 8*1024);

static int req_recv(char *in, int isize, char *out, int *osize, int err)
{
    int ret = 0;
    gsf_msg_t *req = (gsf_msg_t*)in;
    gsf_msg_t *rsp = (gsf_msg_t*)out;

    *rsp  = *req;
    rsp->err  = 0;
    rsp->size = 0;

    ret = msg_func_proc(req, isize, rsp, osize);

    rsp->err = (ret == TRUE)?rsp->err:GSF_ERR_MSG;
    *osize = sizeof(gsf_msg_t)+rsp->size;

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
      printf("pls input: %s rec_parm.json\n", argv[0]);
      return -1;
    }
    
    strncpy(rec_parm_path, argv[1], sizeof(rec_parm_path)-1);
    
    if(json_parm_load(rec_parm_path, &rec_parm) < 0)
    {
      json_parm_save(rec_parm_path, &rec_parm);
      json_parm_load(rec_parm_path, &rec_parm);
    }
    info("rec_parm => pattern:%s, cfg[0].en:%d, segtime:%dsec\n", rec_parm.pattern, rec_parm.cfg[0].en, rec_parm.cfg[0].segtime);
    
    GSF_LOG_CONN(1, 100);
    void* rep = nm_rep_listen(GSF_IPC_REC, NM_REP_MAX_WORKERS, NM_REP_OSIZE_MAX, req_recv);

    while(1) // DEBUG;
    {
      //register To;
      GSF_MSG_DEF(gsf_mod_reg_t, reg, 8*1024);
      reg->mid = GSF_MOD_ID_REC;
      strcpy(reg->uri, GSF_IPC_REC);
      int ret = GSF_MSG_SENDTO(GSF_ID_MOD_CLI, 0, SET, GSF_CLI_REGISTER, sizeof(gsf_mod_reg_t), GSF_IPC_BSP, 2000);
      printf("GSF_CLI_REGISTER To:%s, ret:%d, size:%d\n", GSF_IPC_BSP, ret, __rsize);

      static int cnt = 3;
      if(ret == 0)
        break;
      if(cnt-- < 0)
        return -1;
      sleep(1);
    }
    
    ser_init();
    
    if(0) // pattern
    {
      GSF_MSG_DEF(char, pattern, 4*1024);
      strcpy(pattern, "/dev/mmcblk%[0]");
      int ret = GSF_MSG_SENDTO(GSF_ID_REC_PATTERN, 0, SET, 0, strlen(pattern)+1, GSF_IPC_REC, 2000);
      printf("GSF_ID_REC_PATTERN SET, ret:%d, size:%d\n", ret, __rsize);
    }
    
    if(0) // gsf_rec_cfg_t
    {
      GSF_MSG_DEF(gsf_rec_cfg_t, cfg, 4*1024);
      cfg->en = 1;
      int ret = GSF_MSG_SENDTO(GSF_ID_REC_CFG, 0, SET, 0, sizeof(gsf_rec_cfg_t), GSF_IPC_REC, 2000);
      printf("GSF_ID_REC_CFG SET, ret:%d, size:%d\n", ret, __rsize);
    }
    
    while(1)
    {
      sleep(30);
      
      if(0) // gsf_rec_q_t
      {
        GSF_MSG_DEF(gsf_rec_q_t, q, 4*1024);
        q->channel = 0;
        q->btime = 0;
        q->etime = 0xffffffff;
        q->tags  = 0xffffffff;
        
        int ret = GSF_MSG_SENDTO(GSF_ID_REC_QREC, 0, SET, 0, sizeof(gsf_rec_q_t), GSF_IPC_REC, 2000);
        printf("GSF_ID_REC_CFG SET, ret:%d, size:%d\n", ret, __rsize);
      }
    }
      
    GSF_LOG_DISCONN();
    return 0;
}