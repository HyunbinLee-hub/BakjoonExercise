ssu_mntr : ssu_mntr.o ssu_daemon.o
	gcc -Wall -W ssu_mntr.o ssu_daemon.o -o ssu_mntr

ssu_mntr.o : ssu_mntr.c ssu_mntr.h
	gcc -Wall -W -c ssu_mntr.c

ssu_daemon.o : ssu_daemon.c ssu_mntr.h
	gcc -Wall -W -c ssu_daemon.c

clean : 
	rm -f ssu_mntr ssu_mntr.o ssu_daemon.o
