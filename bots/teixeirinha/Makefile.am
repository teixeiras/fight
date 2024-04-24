lib_LTLIBRARIES = libteixeirinha.la
libteixeirinha_la_SOURCES = teixeirinha.cpp
libteixeirinha_la_CPPFLAGS = -I../../libRobot/public_headers

all-local: teixeirinha
teixeirinha: $(lib_LTLIBRARIES)
	cp .libs/libteixeirinha.so ../../bot_binaries/teixeirinha