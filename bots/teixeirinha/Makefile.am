lib_LTLIBRARIES = libteixeirinha.la
libteixeirinha_la_SOURCES = teixeirinha.cpp teix_robot.cpp
libteixeirinha_la_CPPFLAGS = -I../../libRobot/public_headers -shared
libteixeirinha_la_LDFLAGS = -Wl,--export-dynamic -shared -ldl
all-local: teixeirinha
teixeirinha: $(lib_LTLIBRARIES)
	cp .libs/libteixeirinha.so ../../bot_binaries/teixeirinha