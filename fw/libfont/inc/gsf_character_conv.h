#ifndef _GSF_CHARACTER_CONV_H
#define _GSF_CHARACTER_CONV_H

/*
* Copyright (c) 2014
* All rights reserved.
* 
* filename:gsf_character_conv.h
* 
* func:���ļ�ʵ����gb2312 utf-8 unicode�ַ����� �໥���ת��
* 
* author : gsf
* createdate: 2014-3-10
*
* modify list: 
* 
*/

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************

����:gb2312����תutf-8����

gb2312(in) : ��Ҫת��gb2312�ַ�

gb2312Len(in): gb2312�ַ�����

utf8(in/out): ת�����utf-8�ַ���

����:utf8
*********************************************************************/	
char*  gsf_gb2312_to_utf8(const char* gb2312, int gb2312Len, char *utf8);

/*********************************************************************

����:utf-8����תgb2312����

utf8(in)   : ��Ҫת��utf-8�ַ�

utf8Len(in): utf-8�ַ�����

gb2312(in/out): ת�����gb2312�ַ���

����:gb2312
*********************************************************************/	
char*  gsf_utf8_to_gb2312(const char* utf8, int utf8Len, char *gb2312);

/***********************************************************

����:ȡutf-8 �ַ�����

utf8 : utf-8���ַ�
		
����ֵ���ɹ�����
***********************************************************/	
int gsf_get_Utf8_byte_num(unsigned char utf8);

/***********************************************************

����:utf-8����תunicode����

byte : utf-8�ַ���

index: ��Ҫת���ַ����ַ�����λ��

count: �ַ����ĳ���

unicode:ת�����unicodeֵ
		
����ֵ���ɹ�����0������Ż�-1
***********************************************************/		
int  gsf_utf8_to_unicode(unsigned char  *byte, int index, int count,  unsigned int* unicode);

/*********************************************************************
����:unicode����תutf-8����

unicode:��Ҫת��unicodeֵ

byte:ת����utf-8�ַ�����ŵĿռ�(ȷ����С����6)

pCount : ת�����ַ������ַ�����

����ֵ���ɹ�����utf-8�ַ�������(1-6)������Ż�-1
*********************************************************************/	
int  gsf_unicode_to_utf8(unsigned int unicode, unsigned char *byte);

/*********************************************************************
����:gb2312����תunicode����

gb2312:��Ҫת��gb2312ֵ

����ֵ��unicode����
*********************************************************************/
unsigned int  gsf_gb2312_to_unicode(unsigned short gb2312);

/*********************************************************************
����:unicode����תgb2312����

unicode:��Ҫת��unicodeֵ

����ֵ��gb2312����
*********************************************************************/
unsigned short  gsf_unicode_to_gb2312(unsigned int unicode);

#ifdef __cplusplus
}
#endif

#endif

