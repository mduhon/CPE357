CC = gcc

CFLAGS = -Wall -g

LDFLAGS =

TARGET = mush

SRC = mush.c 
SRC2 = parseline.c 

HEADERS =  parseline.h

EXTRACLEAN = $(TARGET) 

all: $(clean) $(TARGET) 

allclean: clean
	@rm -f $(EXTRACLEAN) 
clean:
	rm -f $(TARGET) $(TARGET2)

$(TARGET): parseline.c mush.c 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(SRC2)

			   
depend:
	@echo Regenerating local dependencies
	@makedepend $(SRC) $(HEADERS)
tags: $(SRC) $(HEADERS)
	cscope -b $(SRC) $(HEADERS)
test:
	./$(TARGET) test1.test
