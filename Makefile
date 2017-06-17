CC=g++
all:
	$(CC)  mysql_demo.cpp `mysql_config --libs `
