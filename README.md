# Multithreaded-Quiz-in-C

## First compile all the files:

gcc -o main_server main_server.c -pthread

gcc -o sub_server_1 sub_server_1.c -pthread

gcc -o sub_server_2 sub_server_2.c -pthread

gcc -o client client.c -pthread


## Then run the main server:

./main_server 8000

## Then run both the sub servers:

./sub_server_1 127.0.0.1 8000

./sub_server_2 127.0.0.1 8000

## Then run the clients:

./client 127.0.0.1 8000

Note : You can connect as many clients as you want!
 
-----

Now, enter the name of course you want to take quiz of :
For Example, type: OS

Now, enter the name of topic you want to take quiz of :
For Example, type: Memory Management



Now attempt quiz and write your answers as A,B,C or D 

-----

Total marks will be visible at main server,sub server and also in cli_rec.txt file

