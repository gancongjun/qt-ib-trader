# Test Debug Version

CC      = gcc
INCLUDE = -I../../Api -I../../../Shared
CFLAGS  = -mthreads -mconsole  -D_REENTRANT -D_DEBUG
LIBS    = -L../../Api -lTwsApiL0D -lstdc++

./debug/Test.exe: ../Src/Main.cpp ../../Api/libTwsApiL0D.a
	$(CC) $(INCLUDE) $(CFLAGS) ../Src/Main.cpp $(LIBS) -o ./debug/test.exe

clean:
	rm -f ./debug/test.exe
