#!/bin/bash

while true ; do 
 	printf 'HTTP/1.1 200 OK\r\n\r\ncool, thanks' | netcat -l  -p 8080 
done