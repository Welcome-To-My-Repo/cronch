default: cronch

cronch: cronch.h
	c++ cronch.cpp -ocronch -g3

clean:
	rm cronch
