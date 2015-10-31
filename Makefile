# See README
CC=gcc-mp-5
CFLAGS= -Ofast -msse2 -funroll-loops -pthread -DWITH_PORTAUDIO -I/opt/local/include
#CFLAGS= -Ofast -mfpu=vfpv4 -funroll-loops -pthread -D WITH_RTL -I. 
#CFLAGS= -Ofast -mfpu=neon-vfpv4 -funroll-loops -pthread -D WITH_RTL -I.  `pkg-config --cflags libairspy`
LDLIBS= -lm -pthread  -lportaudio
#LDLIBS= -lm -pthread  `pkg-config --libs libairspy` -lusb-1.0
LDFLAGS=-L/opt/local/lib


acarsdec:	acarsdec.o acars.o msk.o rtl.o air.o output.o alsa.o portaudio.o explain.o
	$(CC) acarsdec.o acars.o msk.o rtl.o air.o output.o alsa.o portaudio.o explain.o -o $@ $(LDFLAGS) $(LDLIBS)

acarsserv:	acarsserv.o dbmgn.o
	$(CC) -Ofast acarsserv.o dbmgn.o -o $@ -lsqlite3
	
pa_devs: pa_devs.c
	$(CC) -o $@ pa_devs.c $(LDFLAGS) $(LDLIBS)

acarsdec.o:	acarsdec.c acarsdec.h
acars.o:	acars.c acarsdec.h syndrom.h
msk.o:	msk.c acarsdec.h
output.o:	output.c acarsdec.h
rtl.o:	rtl.c acarsdec.h
acarsserv.o:	acarsserv.h
dbmgm.o:	acarsserv.h
alsa.o: alsa.c acarsdec.h
portaudio.o: portaudio.c acarsdec.h

clean:
	@rm *.o acarsdec acarsserv
