OUTPUT := pcm_alaw_ulaw
SRC := main.c pcm_aulaw.c pcm_aulaw.h pcm_aulaw_wraper.c pcm_aulaw_wraper.h

CC := gcc
CFLAG := 

all: $(OUTPUT)

$(OUTPUT) : $(SRC)
	$(CC) $^ -o $@

clean : 
	rm -rf $(OUTPUT)
.PHONY := clean

