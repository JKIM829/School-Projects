# README #

### Link ###
* [Chat Server](http://ec2-174-129-86-112.compute-1.amazonaws.com:3456/Home.html)
* [Full Assignment Description](https://classes.engineering.wustl.edu/cse330/index.php/Module_6)

### File Structure ###

* In my server, I set up a directory parallel to public_html called Mod6. In that directory, I have 2 folders **node_modules** and  **static** , and one js file called *static_server.js*, which I run to get the website working. Inside **static** are the files that run on the website

### Files inside **static** folder ###
* socket_main.js
* init.js
* Home.html
* login.css
* jquery dropdown files, but I decided to go with tabs instead. 


### Creative Portion ###

* Use of drop down tabs to navigate features, including a directory 
* Scrollable interface for the chat
* Persistent send box for private messages. Clicking on the user's name in the Current Room tab will automatically adjust the private message send box to send a private message to that user specifically, and displayed in a special style in the chatlog.
* If a room is declared as a public room, it automatically shows up on the Public Room Directory, and any user can join that room.


### Notes ###
* To send private messages, click on the user in the Current Room tab (I don't know how intuitive that is, but I tried to make it more noticeable on mouseover)
* On that note, only the owner of the room can kick users. Done in the same way, under the Kick Users tab.
