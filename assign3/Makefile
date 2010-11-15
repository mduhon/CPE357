CC = gcc

CFLAGS = -ansi -pedantic -Wall -g

LDFLAGS =

TARGET = htable
TARGET2 = hdecode
TARGET3 = hencode


SRC = htable.c 
SRC2 = hdecode.c
SRC3 = hencode.c

HEADERS = htable.h 

EXTRACLEAN = $(TARGET) 

all:  $(TARGET2) $(TARGET3)

allclean: clean
	@rm -f $(EXTRACLEAN) 
clean:
	rm -f $(TARGET)

$(TARGET2): hdecode.c htable.c htable.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET2) $(SRC2)  $(SRC)

$(TARGET3): hencode.c htable.c htable.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET3) $(SRC3)  $(SRC)
			   
depend:
	@echo Regenerating local dependencies
	@makedepend $(SRC) $(HEADERS)
tags: $(SRC) $(HEADERS)
	cscope -b $(SRC) $(HEADERS)
test:
	./$(TARGET) test1.test
