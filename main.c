#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#include "pcm_aulaw_wraper.h"


void print_usage(const char *process)
{
	printf("examples: \n"
		   "\t %s -h\n"
		   "\t %s --help\n"
		   "\t %s -m pcm_2_alaw -i ./audio/test_8000_16_1.pcm -o ./test_8000_8_1.g711a\n"
		   "\t %s -m pcm_2_ulaw -i ./audio/test_8000_16_1.pcm -o ./test_8000_8_1.g711u\n"
		   "\t %s -m alaw_2_pcm -i ./audio/test_8000_8_1.g711a -o ./test_8000_16_1.pcm\n"
		   "\t %s -m ulaw_2_pcm -i ./audio/test_8000_8_1.g711u -o ./test_8000_16_1.pcm\n"
		   "\t %s -m alaw_2_ulaw -i ./audio/test_8000_8_1.g711a -o ./test_8000_8_1.g711u\n"
		   "\t %s -m ulaw_2_alaw -i ./audio/test_8000_8_1.g711u -o ./test_8000_8_1.g711a\n"
		   "\t %s --mode pcm_2_ulaw --input_file=./audio/test_8000_16_2.pcm --output_file=./test_8000_8_2.ulaw\n"
		   "\t %s --mode pcm_2_ulaw --input_file=./audio/test_22050_16_1.pcm --output_file=./test_22050_8_1.ulaw\n"
		   "\t %s --mode pcm_2_alaw --input_file=./audio/test_44100_16_2.pcm --output_file=./test_44100_8_2.alaw\n"
		   "\t ...\n"
		   "\t [mode: pcm_2_alaw | pcm_2_ulaw | alaw_2_pcm | ulaw_2_pcm | alaw_2_ulaw | ulaw_2_alaw]\n\n",
		   process, process, process, process, process, process, process, process, process, process, process);
}


#define 	BUF_LEN 	(160)


int main(int argc, char **argv)
{
	/* 输入/输出文件 */
	FILE *fpInput = NULL;
	FILE *fpOutput = NULL;
	char inputFileName[128] = {0};
	char outputFileName[128] = {0};	
	char inputBuf[BUF_LEN*2] = {0};
	char outputBuf[BUF_LEN*2] = {0};
	
	/* 输入文件与输出文件的转换模式 */	
	char convert_mode[128] = {0};	

	if (argc == 1)
	{
		print_usage(argv[0]);
		return 0;
	}


	/* 解析命令行参数 */
	char option = 0;
	int option_index = 0;
	char *short_options = "hm:i:o:";
	struct option long_options[] =
	{
		{"help",        no_argument,       NULL, 'h'},
		{"mode",        required_argument, NULL, 'm'},
		{"input_file",  required_argument, NULL, 'i'},
		{"output_file", required_argument, NULL, 'o'},
		{NULL,          0,                 NULL,  0 },
	};
	while((option = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch(option)
		{
			case 'h':
				print_usage(argv[0]);
				return 0;
			case 'm':
				strncpy(convert_mode, optarg, 128);
				break;
			case 'i':
				strncpy(inputFileName, optarg, 128);
				break;
			case 'o':
				strncpy(outputFileName, optarg, 128);
				break;
			defalut:
				printf("Unknown argument!\n");
				break;
		}
	}

	fpInput = fopen(inputFileName, "rb");
	if (fpInput == NULL)
	{
		perror("Open input file error");
		return -1;
	}
	fpOutput = fopen(outputFileName, "wb");
	if (fpOutput == NULL)
	{
		perror("Open output file error");
		return -1;
	}



	while(1)
	{
		/* read data */
		int readBytes = fread(inputBuf, 1, BUF_LEN, fpInput);
		if (readBytes <= 0)
		{
			break;
		}

		/* convert and write data */
		if(0 == strcmp(convert_mode, "pcm_2_alaw"))
		{
			pcm_2_alaw((const short *)inputBuf, outputBuf, readBytes/2);
			fwrite(outputBuf, 1, readBytes/2, fpOutput);
		}
		else if(0 == strcmp(convert_mode, "pcm_2_ulaw"))
		{
			pcm_2_ulaw((const short *)inputBuf, outputBuf, readBytes/2);
			fwrite(outputBuf, 1, readBytes/2, fpOutput);
		}
		else if(0 == strcmp(convert_mode, "alaw_2_pcm"))
		{
			alaw_2_pcm(inputBuf, (short *)outputBuf, readBytes);
			fwrite(outputBuf, 1, readBytes*2, fpOutput);
		}
		else if(0 == strcmp(convert_mode, "ulaw_2_pcm"))
		{
			ulaw_2_pcm(inputBuf, (short *)outputBuf, readBytes);
			fwrite(outputBuf, 1, readBytes*2, fpOutput);
		}
		else if(0 == strcmp(convert_mode, "alaw_2_ulaw"))
		{
			alaw_2_ulaw(inputBuf, outputBuf, readBytes);
			fwrite(outputBuf, 1, readBytes, fpOutput);
		}
		else if(0 == strcmp(convert_mode, "ulaw_2_alaw"))
		{
			ulaw_2_alaw(inputBuf, outputBuf, readBytes);
			fwrite(outputBuf, 1, readBytes, fpOutput);
		}
		else
		{
			printf("The convert mode is not supported!\n");
			goto error_exit;
		}
	}

	printf("\033[32m %s ==> %s Success!\033[0m\n", inputFileName, outputFileName);

error_exit:
	fclose(fpInput);
	fclose(fpOutput);

	return 0;
}
