This is my port of acarsdec to the Macintosh.

It makes use of the portaudio library. I've also made some enhancements
to how much it can break out and interpret some of the standard fields
in the message (e.g. instead of just telling you it copied an H1 label
message that starts "#M1B...", it will tell you that an H1 message
signifies "Message to/from terminal" and that moreover the H1 message
had a source of M1 or "Flight management computer #1").

MacPorts is required to build it. Yeah, I know: MacPorts sort of sucks
because when you build anything in it, it basically compiles and
installs the entire universe of common open-source software on your Mac.
In other words, it's not exactly lightweight :-) . But it was the path
of least resistance, and I already had Mac Ports installed on the system
in question.

Anyhow, from MacPorts you'll need gcc, the math library, and portaudio.

The command:
	make acarsdec
should be all that's needed to build it.

You should also build the Portaudio pa_devs utility, which is replicated
here:
	make pa_devs

Then run ./pa_devs to get a listing of the audio devices available to
Portaudio. From that you can get the number of the audio input device
you wish to listen on. In my case, that's device 1, so to run acarsdec,
I type:
	 ./acarsdec -a 1

This is with the line-level output of my receiver going to the audio
input port of my Mac. I have not yet had a chance to test it with an
SDR.