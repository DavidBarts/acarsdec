/*
 *  Copyright (c) 2015 David Barts
 *
 *
 *   This code is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#ifdef WITH_PORTAUDIO
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "portaudio.h"
#include "acarsdec.h"

#define MAXNBFRAMES 4096

static PaStream *capture_handle;

int initAlsa(char **argv, int optind)
{
	int err, n, inDevNum;
	unsigned int Fs;
	PaStreamParameters inputParameters;

	err = Pa_Initialize();
	if (err != paNoError) {
		fprintf(stderr, "PortAudio cannot initialize: %s\n",
			Pa_GetErrorText(err));
		return 1;
	}

	inDevNum = atoi(argv[optind]);
	bzero(&inputParameters, sizeof(inputParameters));
	inputParameters.channelCount = 1;
	inputParameters.device = inDevNum;
	inputParameters.hostApiSpecificStreamInfo = NULL;
	inputParameters.sampleFormat = paFloat32;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inDevNum)->defaultLowInputLatency ;
	err = Pa_OpenStream(
					&capture_handle,
					&inputParameters,
					NULL,
					(double) INTRATE,
					(unsigned long) MAXNBFRAMES,
					paNoFlag, //flags that can be used to define dither, clip settings and more
					NULL, //your callback function
					NULL ); //data to be passed to callback. In C++, it is frequently (void *)this
	if (err != paNoError) {
		fprintf(stderr, "PortAudio cannot open #%d: %s\n",
			inDevNum, Pa_GetErrorText(err));
		return 1;
	}

	nbch = 1;
	channel[0].chn = 0;
	channel[0].dm_buffer=malloc(MAXNBFRAMES*sizeof(float));

	return 0;
}

int runAlsaSample(void)
{
	int err;

	err = Pa_StartStream(capture_handle);
	if (err != paNoError) {
		fprintf(stderr, "PortAudio cannot start: %s\n",
			Pa_GetErrorText(err));
		return 1;
	}

	do {
		err = Pa_ReadStream(capture_handle, channel[0].dm_buffer, MAXNBFRAMES);
		if (err == paInputOverflowed) {
			fprintf(stderr, "Warning: input overflow occurred.\n");
		} else if (err != paNoError) {
			fprintf(stderr, "PortAudio cannot read: %s\n",
				Pa_GetErrorText(err));
			return -1;
		}

		demodMSK(&(channel[0]), MAXNBFRAMES);

	} while (1);

	err = Pa_Terminate();
	if (err != paNoError) {
		/* we're about to exit anyhow, so this isn't a terribly big deal */
	    fprintf(stderr, "warning - Pa_Terminate failed: %s\n", Pa_GetErrorText(err));
	}
	return 0;
}

#endif
