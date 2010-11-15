CC = gcc

CFLAGS = -ansi -pedantic -Wall -g

LDFLAGS =

TARGET = mypwd

SRC = mypwd.c 

HEADERS =  

EXTRACLEAN = $(TARGET) 

all:  $(TARGET) 

allclean: clean
	@rm -f $(EXTRACLEAN) 
clean:
	rm -f $(TARGET)

$(TARGET): mypwd.c 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)  

			   
depend:
	@echo Regenerating local dependencies
	@makedepend $(SRC) $(HEADERS)
tags: $(SRC) $(HEADERS)
	cscope -b $(SRC) $(HEADERS)
test:
	./$(TARGET) test1.test
