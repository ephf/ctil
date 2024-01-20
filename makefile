all:
	@for file in $(shell ls src); do gcc -c -o out/$${file%%.*}.o -I include src/$${file}; done
	gcc -c -o out/lib.o -I include src/*.c