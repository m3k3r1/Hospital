all:
	gcc  -Wall main.c fhospital.c -Iinclude -o hospital 

clean:
	rm hospital