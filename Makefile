all: libapa102.a

clean:
	rm -f libapa102.a examples/fill examples/stripes examples/multistripes examples/blinkanim examples/pulseanim examples/stripesanim lib/build/*.o

examples: libapa102.a examples/fill examples/stripes examples/multistripes examples/blinkanim examples/pulseanim examples/stripesanim examples/multistripesanim

libapa102.a: lib/build/apa102.o lib/build/apa102_anim.o
	ar rcs libapa102.a lib/build/apa102.o lib/build/apa102_anim.o

lib/build/apa102.o: lib/apa102.c lib/apa102.h
	gcc -c -o lib/build/apa102.o lib/apa102.c

lib/build/apa102_anim.o: lib/apa102_anim.c lib/apa102.h
	gcc -c  -o lib/build/apa102_anim.o lib/apa102_anim.c

examples/fill: examples/fill.c
	gcc -L. -I./lib  -o examples/fill examples/fill.c -lwiringPi -lapa102 -lpthread

examples/stripes: examples/stripes.c
	gcc -L. -I./lib  -o examples/stripes examples/stripes.c -lwiringPi -lapa102 -lpthread

examples/multistripes: examples/multistripes.c
	gcc -L. -I./lib  -o examples/multistripes examples/multistripes.c -lwiringPi -lapa102 -lpthread

examples/blinkanim: examples/blinkanim.c
	gcc -L. -I./lib  -o examples/blinkanim examples/blinkanim.c -lwiringPi -lapa102 -lpthread

examples/pulseanim: examples/pulseanim.c
	gcc -L. -I./lib  -o examples/pulseanim examples/pulseanim.c -lwiringPi -lapa102 -lpthread

examples/stripesanim: examples/stripesanim.c
	gcc -L. -I./lib  -o examples/stripesanim examples/stripesanim.c -lwiringPi -lapa102 -lpthread

examples/multistripesanim: examples/multistripesanim.c
	gcc -L. -I./lib  -o examples/multistripesanim examples/multistripesanim.c -lwiringPi -lapa102 -lpthread