Chat Server v0.2
=

# Build
Run make in the repository
* `make` to install program
* `make clean` to clean from object files
* `make uninstall` to uninstall program

# Using
`./c_server [port]` to run server
You can get client [here](https://github.com/seniorkot/Chat-Client)

# Version 0.2 (22.01.2017)
Chatroom for 50 users with few commands and authorization system.
## Available
* Sending messages;
* Sending private messages;
* Signing up & signing in;
* Changing nickname & password;

### Commands list
<b>\login [nickname] [password]</b> - sign in<br>
<b>\register [nickname] [password]</b> - sign up<br>
<b>\name [nickname]</b> - change nickname<br>
<b>\passwd [old] [new]</b> - change password<br>
<b>\pm [user] [message]</b> - send private message<br>
<b>\online</b> - print online users list<br>
<b>\h \help</b> - print available commands list<br>
<b>\q \quit</b> - leave server<br>

# Version 0.1 (20.11.2016)
Simple chatroom for 50 users.
### Available
* Sending messages;
* Changing nickname;
