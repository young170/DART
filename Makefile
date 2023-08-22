main.exe: main.cpp
	g++ -std=c++17 -o main main.cpp

.PHONY: test

test:
	main.exe -i testdir -c "g++ -std=c++11 -o solution solution/driver.cpp solution/treeprintx.cpp solution/treex.cpp -I./include -L./lib -lnowic" \
	-t "g++ -std=c++11 -o student student/driver.cpp student/treeprintx.cpp student/treex.cpp -I./include -L./lib -lnowic" \