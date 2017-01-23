COMP=gcc
TARGET=c_server
CFLAGS=-std=c89 -pedantic -Wall -Werror -lpthread -I $(INCLUDE)
INCLUDE=include
SRC=$(wildcard src/*.c)
BUILD=$(SRC:src/%.c=%.o)

install: $(TARGET)
	mkdir -p -m=0700 .profile/admin
	chmod 0700 .profile
	echo -n qwerty > .profile/admin/password
	chmod 0700 .profile/admin/password
	echo -n 2 > .profile/admin/privilege
	chmod 0700 .profile/admin/privilege

$(TARGET): $(BUILD)
	$(COMP) $(CFLAGS) $(BUILD) -o $(TARGET)
	
%.o: src/%.c
	$(COMP) -c -o $@ $(CFLAGS) $^

clean:
	rm -f *.o

uninstall:
	rm -rf .profile
	rm -f $(TARGET)