all: n61850

CC = gcc
CFLAGS = -g -c -Wextra -Iinclude
LINKS= lib/libiec61850.a -lpthread -lm -lstdc++ -lrt
#CC = arm-linux-gcc
RM = /bin/rm


OBJECTS = n61850.o n61850_global.o n61850_goose.o n61850_mms.o


# COMPILING
.C.o:
	${CC} ${CFLAGS} -o $*.o $<

# LINKING
n61850: $(OBJECTS)
	${CC}  -o n61850 $(OBJECTS) $(LFLAGS) $(LINKS)

install:
	cp n61850 /usr/local/bin
	cp n61850.1 /usr/local/man/man1/
	
uninstall:
	$(RM) /usr/local/bin/n61850
	$(RM) /usr/local/man/man1/n61850.1
   
clean:
	$(RM) -f n61850 $(OBJECTS) *~ 

