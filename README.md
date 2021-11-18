
##### 前言

![g711](https://i.loli.net/2021/11/18/Xpf2N9wbukLDtrR.png)

(截图来源：[https://blog.csdn.net/u014470361/article/details/88837776](https://blog.csdn.net/u014470361/article/details/88837776))

> 我的理解：
>
> 首先需要知道的是u-law/a-law是用于脉冲编码的压缩/解压缩算法。而**G.711**是指在**8KHz采样率**（单声道）中，使用的**u-law或a-law算法**对音频进行压缩的**一种语音压缩标准**。但是，使用这两种压缩算法进行压缩的音频并不一定是G.711，要在8KHz采样率（单声道）的才是，压缩其他采样率和多声道得到的u-law/a-law文件只要设置对应的采样率和声道数照样能解压播放。


### 1. 编译

demo引用了开源代码[`g711.c`](https://www.speech.kth.se/cost250/refsys/latest/src/g711.c)和[`g711.h`](https://www.speech.kth.se/cost250/refsys/latest/src/g711.h)，然后在此基础上封装成`g711_wraper.c`和`g711_wraper.h`，并编写自己的测试程序`main.c`进行验证。整个demo程序共5个源文件，可以编译到任意环境下使用（非Unix系统可能需要简单调整`main.c`中包含的头文件）：

```bash
$ make   # 或者: make CC=your-crosscompile-gcc
```


### 2. 使用

```bash
examples: 
         ./pcm_alaw_ulaw -h
         ./pcm_alaw_ulaw --help
         ./pcm_alaw_ulaw -m pcm_2_alaw -i ./audio/test_8000_16_1.pcm -o ./test_8000_8_1.g711a
         ./pcm_alaw_ulaw -m pcm_2_ulaw -i ./audio/test_8000_16_1.pcm -o ./test_8000_8_1.g711u
         ./pcm_alaw_ulaw -m alaw_2_pcm -i ./audio/test_8000_8_1.g711a -o ./test_8000_16_1.pcm
         ./pcm_alaw_ulaw -m ulaw_2_pcm -i ./audio/test_8000_8_1.g711u -o ./test_8000_16_1.pcm
         ./pcm_alaw_ulaw -m alaw_2_ulaw -i ./audio/test_8000_8_1.g711a -o ./test_8000_8_1.g711u
         ./pcm_alaw_ulaw -m ulaw_2_alaw -i ./audio/test_8000_8_1.g711u -o ./test_8000_8_1.g711a
         ./pcm_alaw_ulaw --mode pcm_2_ulaw --input_file=./audio/test_8000_16_2.pcm --output_file=./test_8000_8_2.ulaw
         ./pcm_alaw_ulaw --mode pcm_2_ulaw --input_file=./audio/test_22050_16_1.pcm --output_file=./test_22050_8_1.ulaw
         ./pcm_alaw_ulaw --mode pcm_2_alaw --input_file=./audio/test_44100_16_2.pcm --output_file=./test_44100_8_2.alaw
         ...
         [mode: pcm_2_alaw | pcm_2_ulaw | alaw_2_pcm | ulaw_2_pcm | alaw_2_ulaw | ulaw_2_alaw]
```


### 附录：demo目录架构

```bash
.
├── audio
│   ├── test_22050_16_1.pcm
│   ├── test_22050_8_1.ulaw
│   ├── test_44100_16_2.pcm
│   ├── test_44100_8_2.alaw
│   ├── test_8000_16_1.pcm
│   ├── test_8000_16_2.pcm
│   ├── test_8000_8_1.g711a
│   ├── test_8000_8_1.g711u
│   └── test_8000_8_2.ulaw
├── docs
│   ├── G711编码原理及代码_szfhy的博客-CSDN博客_g711编码.mhtml
│   └── 音频采样及编解码——LPCM 、ADPCM、G711、G726、AAC_夜风的博客-CSDN博客_adpcm.mhtml
├── g711.c
├── g711.h
├── main.c
├── Makefile
├── pcm_aulaw_wraper.c
├── pcm_aulaw_wraper.h
└── README.md
```

