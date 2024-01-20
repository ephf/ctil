all:
	gcc -o out/libctil.so -fpic -shared -I include src/*.c