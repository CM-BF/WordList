CC=g++ -std=c++11 -shared -fPIC
GCC = g++ -std=c++11


main:test_main.o libwordlist.so
	$(GCC) -fprofile-arcs -ftest-coverage -o $@ $< -I./ -L./ -lwordlist -lgtest -lpthread
wordlist.o:wordlist.cpp wordlist.h
	$(GCC) -c $< -o $@ -fprofile-arcs -ftest-coverage
libwordlist.so:wordlist.o
	$(CC) -o $@ wordlist.cpp -fprofile-arcs -ftest-coverage
test_main.o:cmd.cpp
	$(GCC) -c $^ -o $@ -fprofile-arcs -ftest-coverage

clean:
	rm -f *.o
