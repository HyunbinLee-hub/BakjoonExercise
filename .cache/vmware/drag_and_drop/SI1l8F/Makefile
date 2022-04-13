ssu_mntr : main.o commands.o
	gcc main.o commands.o ssu_syslog.o -o ssu_mntr

main.o : main.c commands.h
	gcc -c main.c

commands.o : commands.c commands.h
	gcc -c commands.c

ssu_syslog.o : ssu_syslog.c
	gcc -c ssu_syslog.c

clean :
	rm *.o
	rm ssu_mntr
