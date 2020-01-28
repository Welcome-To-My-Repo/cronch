default: clean cronch
proof: clean p

cronch: cronch.h
	c++ cronch.cpp -ocronch -g3 |& tee -a log
p: 
	c++ proof.cpp -oproof -g3 |& tee -a log

clean:
	rm -f cronch log proof

run:
	./cronch c test.txt file.cronch
