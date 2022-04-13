all: ssu_cron_files ssu_crond ssu_crontab ssu_rsync_files ssu_rsync

ssu_cron_files : 
	touch ssu_crontab_file ssu_crontab_log

ssu_crond : 
	gcc -o ssu_crond ssu_crond.c ssu_cron.c

ssu_crontab :
	gcc -o ssu_crontab ssu_crontab.c ssu_cron.c

ssu_rsync_files :
	touch ssu_rsync_log

ssu_rsync :
	gcc -o ssu_rsync ssu_rsync.c

clean :
	rm ssu_crond ssu_crontab ssu_rsync ssu_crontab_file ssu_crontab_log ssu_rsync_log
