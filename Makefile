default: clean cronch

cronch: cronch.h
	c++ cronch.cpp -ocronch -g3

clean:
	rm -f cronch

run:
	./cronch c test.txt file.cronch
