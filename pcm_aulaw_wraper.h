#ifndef _PCM_AULAW_WRAPER_H_
#define _PCM_AULAW_WRAPER_H_


/* 16bit little endian PCM encode to A-Law */
void pcm_2_alaw(const short *src_16lepcm, unsigned char *dst_alaw, unsigned int sample_cnt);
void alaw_2_pcm(const unsigned char *src_alaw, short *dst_16lepcm, unsigned int sample_cnt);


/* 16bit little endian PCM encode to MU-Law */
void pcm_2_ulaw(const short *src_16lepcm, unsigned char *dst_ulaw, unsigned int sample_cnt);
void ulaw_2_pcm(const unsigned char *src_ulaw, short *dst_16lepcm, unsigned int sample_cnt);


/* G711A and G711U transform */
void alaw_2_ulaw(const unsigned char *src_alaw, char *dst_ulaw, unsigned int sample_cnt);
void ulaw_2_alaw(const unsigned char *src_ulaw, char *dst_alaw, unsigned int sample_cnt);


#endif
