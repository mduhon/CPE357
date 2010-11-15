CC = gcc

CFLAGS = -ansi -pedantic -Wall -g

LDFLAGS =

TARGET = htable

OBJS = $(TARGET).o

SRC = htable.c 

HEADERS = 

EXTRACLEAN = $(TARGET) 

all: clean $(TARGET)

allclean: clean
	@rm -f $(EXTRACLEAN) 
clean:
	rm -f $(TARGET)
$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c -o $(OBJS) $(SRC)	
$(TARGET): 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) 
depend:
	@echo Regenerating local dependencies
	@makedepend $(SRC) $(HEADERS)
tags: $(SRC) $(HEADERS)
	cscope -b $(SRC) $(HEADERS)
test:
	./$(TARGET) test1.test
