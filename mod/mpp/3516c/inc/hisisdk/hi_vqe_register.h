/*
  Copyright (c), 2001-2024, Shenshu Tech. Co., Ltd.
 */

#ifndef HI_VQE_REGISTER_H
#define HI_VQE_REGISTER_H

#include "hi_type.h"
#include "ot_vqe_register.h"

#ifdef __cplusplus
extern "C" {
#endif

/* record */
hi_void *hi_vqe_record_get_handle(hi_void);
/* HPF */
hi_void *hi_vqe_hpf_get_handle(hi_void);
/* AEC */
hi_void *hi_vqe_aec_get_handle(hi_void);
/* ANR */
hi_void *hi_vqe_anr_get_handle(hi_void);
/* RNR */
hi_void *hi_vqe_rnr_get_handle(hi_void);
/* HDR */
hi_void *hi_vqe_hdr_get_handle(hi_void);
/* DRC */
hi_void *hi_vqe_drc_get_handle(hi_void);
/* PEQ */
hi_void *hi_vqe_peq_get_handle(hi_void);
/* AGC */
hi_void *hi_vqe_agc_get_handle(hi_void);
/* EQ */
hi_void *hi_vqe_eq_get_handle(hi_void);
/* resample */
hi_void *hi_vqe_resample_get_handle(hi_void);
/* GAIN */
hi_void *hi_vqe_gain_get_handle(hi_void);
/* talkv2 */
hi_void *hi_vqe_talkv2_get_handle(hi_void);

#ifdef __cplusplus
}
#endif
#endif /* HI_VQE_REGISTER_H */
