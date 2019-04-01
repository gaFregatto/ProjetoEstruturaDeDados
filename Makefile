CC := gcc
CFLAGS := -lm -g -fstack-protector-all -std=c99
FONTES := $(wildcard *.c)
OBJS := $(FONTES:.c=.o)
EXEC := siguel
VALGRIND := valgrind #--leak-check=full #--show-leak-kinds=all
BED := -e /mnt/d/Faculdade/2ºano/ED/mainT/testes
BSD := -o /mnt/d/Faculdade/2ºano/ED/mainT/saidas
FILE := -f c1.geo -ec c1.ec -pm c1.pm -q c1/dpr-1.qry

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	@rm -rf *.o $(EXEC)

run: $(EXEC)
	$(VALGRIND) ./$(EXEC) $(BED) $(FILE) $(BSD)

