# libapa102
C library for using the APA102 LED strip on the Raspberry Pi. This library contains functions for adressing LEDs one by one, filling the entire strip or creating 'stripes'. There is also an animation API that runs in a separate thread so it won't block your main program.

## Getting started

For getting started, [see my blog post on the library][blogpost]

## API Docs
API docs can be [found here][docs]

## Using libapa102 with openFrameworks

If you want to use libapa102 with openFrameworks, you can use [ofxLibApa102][wrapper] by James Kong ([@fishkingsin][fishkingsin])

[blogpost]: http://dirkwillem.nl/introducing-libapa102/
[docs]: http://libapa102.dirkwillem.nl/
[wrapper]: https://github.com/fishkingsin/ofxLibApa102
[fishkingsin]: https://github.com/fishkingsin
