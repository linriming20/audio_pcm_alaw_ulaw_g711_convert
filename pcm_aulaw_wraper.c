#include "g711.h"
#include "pcm_aulaw_wraper.h"


void pcm_2_alaw(const short *src_16lepcm, unsigned char *dst_alaw, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_alaw[i] = linear2alaw(src_16lepcm[i]);
	}
}


void alaw_2_pcm(const unsigned char *src_alaw, short *dst_16lepcm, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_16lepcm[i] = alaw2linear(src_alaw[i]);
	}
}


void pcm_2_ulaw(const short *src_16lepcm, unsigned char *dst_ulaw, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_ulaw[i] = linear2ulaw(src_16lepcm[i]);
	}
}


void ulaw_2_pcm(const unsigned char *src_ulaw, short *dst_16lepcm, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_16lepcm[i] = ulaw2linear(src_ulaw[i]);
	}
}



void alaw_2_ulaw(const unsigned char *src_alaw, char *dst_ulaw, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_ulaw[i] = alaw2ulaw(src_alaw[i]);
	}
}


void ulaw_2_alaw(const unsigned char *src_ulaw, char *dst_alaw, unsigned int sample_cnt)
{
	for (int i = 0; i < sample_cnt; i++)
	{
		dst_alaw[i] = ulaw2alaw(src_ulaw[i]);
	}
}

