all:
	gcc  main.c fhospital.c -Iinclude -o hospital  -std=c99

clean:
	rm main