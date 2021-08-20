#5
./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax		# ax = = 0
    0   1001 add $1, %ax		# ax  =1
    1   1002 mov %ax, 2000		# 2000 = ax = 1
    1   1003 sub  $1, %bx		# bx =2
    1   1004 test $0, %bx		# 0 <= bx	
    1   1005 jgt .top
    1   1000 mov 2000, %ax		
    1   1001 add $1, %ax
    2   1002 mov %ax, 2000
    2   1003 sub  $1, %bx		# bx= 1
    2   1004 test $0, %bx		# 0 <= bx
    2   1005 jgt .top
    2   1000 mov 2000, %ax
    2   1001 add $1, %ax
    3   1002 mov %ax, 2000
    3   1003 sub  $1, %bx		# bx = 0
    3   1004 test $0, %bx		# 0 == bx
    3   1005 jgt .top
    3   1006 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----
    3                            1000 mov 2000, %ax
    3                            1001 add $1, %ax		# ax = 4
    4	                         1002 mov %ax, 2000		
    4                            1003 sub  $1, %bx		# bx = 3
    4                            1004 test $0, %bx
    4                            1005 jgt .top
    4                            1000 mov 2000, %ax
    4                            1001 add $1, %ax
    5                            1002 mov %ax, 2000
    5                            1003 sub  $1, %bx
    5                            1004 test $0, %bx
    5                            1005 jgt .top
    5                            1000 mov 2000, %ax
    6                            1001 add $1, %ax
    6                            1002 mov %ax, 2000
    6                            1003 sub  $1, %bx
    6                            1004 test $0, %bx
    6                            1005 jgt .top
    6                            1006 halt
#6	
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 mov 2000, %ax
    1                            1001 add $1, %ax
    2                            1002 mov %ax, 2000
    2                            1003 sub  $1, %bx
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2                            1004 test $0, %bx
    2                            1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1000 mov 2000, %ax
    2   1001 add $1, %ax
    3   1002 mov %ax, 2000		
    3   ------ Interrupt ------  ------ Interrupt ------
    3                            1000 mov 2000, %ax		# ax = 3
    3                            1001 add $1, %ax		# ax = 4
    3   ------ Interrupt ------  ------ Interrupt ------
    3   1003 sub  $1, %bx
    3   1004 test $0, %bx
    3   1005 jgt .top
    3   1000 mov 2000, %ax		#ax = 3
    3   ------ Interrupt ------  ------ Interrupt ------
    4                            1002 mov %ax, 2000		#ax = 4
    4                            1003 sub  $1, %bx
    4   ------ Interrupt ------  ------ Interrupt ------
    4   1001 add $1, %ax		# ax =4
    4   1002 mov %ax, 2000
    4   ------ Interrupt ------  ------ Interrupt ------
    4                            1004 test $0, %bx
    4                            1005 jgt .top
    4                            1000 mov 2000, %ax
    4   ------ Interrupt ------  ------ Interrupt ------
    4   1003 sub  $1, %bx
    4   1004 test $0, %bx
    4   1005 jgt .top
    4   1006 halt
    4   ----- Halt;Switch -----  ----- Halt;Switch -----
    4   ------ Interrupt ------  ------ Interrupt ------
    4                            1001 add $1, %ax
    5                            1002 mov %ax, 2000
    5                            1003 sub  $1, %bx
    5   ------ Interrupt ------  ------ Interrupt ------
    5                            1004 test $0, %bx
    5                            1005 jgt .top
    5   ------ Interrupt ------  ------ Interrupt ------
    5                            1006 halt	
	
#7 
 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 -c
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   ------ Interrupt ------  ------ Interrupt ------
    0                            1000 mov 2000, %ax
    0   ------ Interrupt ------  ------ Interrupt ------
    0   1001 add $1, %ax	#ax = 1
    0   ------ Interrupt ------  ------ Interrupt ------
    0                            1001 add $1, %ax		# ax = 1
    0   ------ Interrupt ------  ------ Interrupt ------
    1   1002 mov %ax, 2000
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1002 mov %ax, 2000
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1004 test $0, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1004 test $0, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1005 jgt .top
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1005 jgt .top
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1006 halt
    1   ----- Halt;Switch -----  ----- Halt;Switch -----
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1006 halt	

#9	
 ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000
ARG seed 0
ARG numthreads 2
ARG program wait-for-me.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv ax=1,ax=0
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace ax
ARG cctrace False
ARG printstats False
ARG verbose False

 2000      ax          Thread 0                Thread 1
    0       1
    0       1   1000 test $1, %ax
    0       1   1001 je .signaller
    1       1   1006 mov  $1, 2000
    1       1   1007 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----
    1       0                            1000 test $1, %ax
    1       0                            1001 je .signaller
    1       0                            1002 mov  2000, %cx
    1       0                            1003 test $1, %cx
    1       0                            1004 jne .waiter
    1       0                            1005 halt	
	
waiter repeatedly copies %2000 and test if the value is 1
signaller set the %2000 to 1
	