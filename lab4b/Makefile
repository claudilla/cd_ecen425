#####################################################################
# ECEn 425 Lab 4 Makefile

lab4b.bin:	lab4bfinal.s
		nasm lab4bfinal.s -o lab4b.bin -l lab4b.lst                           # Step 8, Assemble

lab4bfinal.s:	clib.s myisr.s myinth.s lab4b_app.s yakc.s yaks.s                     
		cat clib.s yakc.s yaks.s myisr.s myinth.s lab4b_app.s > lab4bfinal.s  # Step 7, Concatenate

myinth.s:	myinth.c
		cpp myinth.c myinth.i                                                 # Step 1, Preprocess
		c86 -g myinth.i myinth.s                                              # Step 2, Compile

yakc.s:		yakc.c 
		cpp yakc.c yakc.i                                                     # Step 3, Preprocess
		c86 -g yakc.i yakc.s                                                  # Step 4, Compile

lab4b_app.s:	lab4b_app.c yakk.h clib.h myinth.s yakc.s
		cpp lab4b_app.c lab4b_app.i                                           # Step 5, Preprocess
		c86 -g lab4b_app.i lab4b_app.s                                        # Step 6, Compile

clean:		
		rm lab4b.bin lab4b.lst lab4bfinal.s myinth.s myinth.i yakc.s yakc.i lab4b_app.s lab4b_app.i
