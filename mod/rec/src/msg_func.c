﻿//os

//top
#include "inc/gsf.h"

//mod
#include "rec.h"
#include "server.h"
//myself
#include "msg_func.h"

static void msg_func_qdisk(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
  // ser_query_disk;
}

static void msg_func_qfile(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
  // ser_query_file;
  gsf_file_t files[1024];
  gsf_rec_q_t *q = (gsf_rec_q_t*)req->data;

  int i = 0;
  
  struct timespec ts1, ts2;
  clock_gettime(CLOCK_MONOTONIC, &ts1);
  int size = ser_query_file(q, files);
  clock_gettime(CLOCK_MONOTONIC, &ts2);
  
  printf("q[ch:%d, btime:%d, etime:%d, tags:0x%x] total:%d, cost:%d ms\n"
        , q->channel, q->btime, q->etime, q->tags
        , size/sizeof(gsf_file_t)
        , (ts2.tv_sec*1000 + ts2.tv_nsec/1000000) - (ts1.tv_sec*1000 + ts1.tv_nsec/1000000));
  
  if(size > 0 || size <= *osize - sizeof(gsf_msg_t))
  {
    memcpy(rsp->data, files, size);
    rsp->size = size;
    #if 0
    for(i = 0; i < size/sizeof(gsf_file_t); i++)
    {
      printf("files[%04d].btime:%010u.%04u -> etime:%010u, size:%010u, tags:%04u, channel:%04u\n"
            , i
            , files[i].btime
            , files[i].btime_ms
            , files[i].etime
            , files[i].size
            , files[i].tags
            , files[i].channel 
            );
    }
    printf("\n\n");
    #endif
  }
  else
  {
    printf("files empty.\n\n");
  }
}

static void msg_func_cfg(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
  // ser_cfg_update;
  if(req->set && req->ch >= 0 && req->ch < GSF_REC_CH_NUM)
  {
    rec_parm.cfg[req->ch] = *((gsf_rec_cfg_t*)req->data);
    json_parm_save(rec_parm_path, &rec_parm);
    rsp->err  = 0;
    rsp->size = 0;
  }
  else if (!req->set && req->ch >= 0 && req->ch < GSF_REC_CH_NUM)
  {
    *((gsf_rec_cfg_t*)rsp->data) = rec_parm.cfg[req->ch];
    rsp->err  = 0;
    rsp->size = sizeof(gsf_rec_cfg_t);
  }
}

static void msg_func_pattern(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
  // ser_pattern_update;
  if(req->set && req->size && strlen(req->data))
  {
    strncpy(rec_parm.pattern, req->data, sizeof(rec_parm.pattern)-1);
    json_parm_save(rec_parm_path, &rec_parm);
    rsp->err  = 0;
    rsp->size = 0;
  }
  else if (!req->set)
  {
    strcpy(rsp->data, rec_parm.pattern);
    rsp->err  = 0;
    rsp->size = strlen(rec_parm.pattern) + 1;
  }
}

static void msg_func_image(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
  // ser_image_writer;
  if(req->set && req->size && strlen(req->data))
  { 
    rsp->err = ser_image_writer(req->ch, 0, req->data);
    rsp->size = 0;
  }
  else 
  {
    rsp->err = -1;
    rsp->size = 0;
  }
}


static msg_func_t *msg_func[GSF_ID_REC_END] = {
    [GSF_ID_MOD_CLI]      = NULL,
    [GSF_ID_REC_QDISK]    = msg_func_qdisk,
    [GSF_ID_REC_QREC]     = msg_func_qfile,
    [GSF_ID_REC_CFG]      = msg_func_cfg,
    [GSF_ID_REC_PATTERN]  = msg_func_pattern,
    [GSF_ID_REC_IMAGE]    = msg_func_image,
 };


int msg_func_proc(gsf_msg_t *req, int isize, gsf_msg_t *rsp, int *osize)
{
    if(req->id < 0 || req->id >= GSF_ID_REC_END)
    {
        return FALSE;
    }
    
    if(msg_func[req->id] == NULL)
    {
        return FALSE;
    }   
    
    msg_func[req->id](req, isize, rsp, osize);
    
    return TRUE;
}
