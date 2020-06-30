SRC = -pthread src/jsmpeg-vnc.c src/encoder.c src/grabber.c src/server.c src/app.c src/jskeycode2x11keycode.c

INC = -Isrc/ -Isrc/libwebsockets/

ZLIB = $(shell pkg-config --cflags --libs zlib)

LIBWEBSOCKETS = $(shell pkg-config --cflags --libs libwebsockets)

FFMPEG = $(shell pkg-config --cflags --libs libavcodec libavutil libswscale)

X11 = $(shell pkg-config --cflags --libs x11) -lXtst

OUT = -o bin/jsmpeg-vnc
VER= -std=c11

jsmpeg-vnc-linux: src/jsmpeg-vnc.c
	gcc ${OUT} ${SRC} ${INC} ${LIB_DIRS} ${FFMPEG} ${X11} ${ZLIB} ${LIBWEBSOCKETS} ${VER}
