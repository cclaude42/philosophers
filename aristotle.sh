#!/bin/bash

print()
{
	echo -en "\n\n\n"
	while tail -3 log 2> /dev/null
	do
		sleep 0.2
		tput cuu 3
	done
}

test()
{
	clear
	echo -e "\n\e[33m./philo_${1}/philo_${1} $2 $3 $4 $5 $6\e[39m"
	echo -e "\e[33mThis should run indefinitely. Ctrl-\ to interrupt\e[39m"
	print &
	./philo_${1}/philo_${1} $2 $3 $4 $5 $6 > log
	rm log
	echo -e "\e[33mDone !\n\e[39m"
	sleep 0.5
}

testo()
{
	echo "./philo_${1}/philo_${1} $2 $3 $4 $5 $6"
}

main()
{
	for exec in one two three
	do

		for nphi in 2 4 8 20 50
		do
			test $exec $nphi 500 200 200
			test $exec $nphi 410 200 200
			test $exec $nphi 400 10 10
			test $exec $nphi 400 1 300
			test $exec $nphi 400 0 300
			test $exec $nphi 400 0 0
			test $exec $nphi 100 45 45
			test $exec $nphi 10 1 1
			test $exec $nphi 5000 2450 2450
		done

		for nphi in 3 5 7 11
		do
			test $exec $nphi 600 150 150
			test $exec $nphi 600 190 200
			test $exec $nphi 600 10 10
			test $exec $nphi 100 30 50
			test $exec $nphi 4000 1000 1000
		done

	done
}

main
