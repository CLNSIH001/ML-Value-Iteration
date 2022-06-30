run: compile
	./bin/ValItAl

compile:
	g++ -o bin/ValItAl src/*.cpp --std=c++11

clean:
	rm Output.txt bin/ValItAl