plagiarismCatcher: plagiarismCatcher.o fnameFinder.o
	g++ -std=c++11 -o plagiarismCatcher plagiarismCatcher.o fnameFinder.o
plagiarismCatcher.o: plagiarismCatcher.cpp
	g++ -std=c++11 -c plagiarismCatcher.cpp fnameFinder.cpp
fnameFinder.o: fnameFinder.cpp
	g++ -std=c++11 -c fnameFinder.cpp
