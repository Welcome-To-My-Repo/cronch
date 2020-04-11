default: clean cronch

cronch:
	c++ cronch.cpp -ocronch -g3 |& tee -a log

p:
	c++ proof.cpp -oproof -g3

clean:
	rm -f cronch log proof

run:
	./cronch c test.txt file.cronch
