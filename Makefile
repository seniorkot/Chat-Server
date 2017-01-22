COMP=gcc
TARGET=c_server
CFLAGS= -std=c89 -pedantic -Wall -Werror -lpthread
SRC=$(wildcard server/*.c)
BUILD=$(SRC:server/%.c=%.o)

$(TARGET): $(BUILD)
	$(COMP) $(CFLAGS) $(BUILD) -o $(TARGET)
	
%.o: server/%.c
	$(COMP) -c -o $@ $(CFLAGS) $^

clean:
	rm -rf *.o

install: $(TARGET)
	mkdir -p -m=0700 .profile/admin
	echo "qwerty" > .profile/admin/password

uninstall:
	rm -rf .profile
	rm $(TARGET)