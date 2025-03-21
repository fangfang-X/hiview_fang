/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2012-2019. All rights reserved.
 * Description: Function of hi_isp_bin_adapt.h
 * Author: ISP SW
 * Create: 2012/06/28
 */

#ifndef __HI_ISP_BIN_ADAPT_H__
#define __HI_ISP_BIN_ADAPT_H__

#include "hi_type.h"
#include "hi_comm_isp_adapt.h"
#include "hi_isp_bin.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/* GENERAL STRUCTURES */
typedef struct {
    hi_u32  addr;    /* register addr */
    hi_u8   start_bit; /* start bit of register addr */
    hi_u8   end_bit;   /* end bit of register addr */
} hi_isp_bin_reg_attr;

/*
 * The base addr of ISP logic register
 * The base addr of ISP ext register
 * The base addr of Hisi AE ext register
 * The base addr of Hisi AWB ext register
 */
hi_isp_bin_reg_attr g_isp_bin_reg_attr[ISP_MAX_PIPE_NUM][MAX_BIN_REG_NUM] = {
    [0 ...(ISP_MAX_PIPE_NUM - 1)] = {0}
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_ISP_BIN_ADAPT_H__ */
