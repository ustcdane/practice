all:NON_RVO_NRVO NRVO

NON_RVO_NRVO: NRVO_test.cpp
	g++ -o NON_RVO_NRVO NRVO_test.cpp -fno-elide-constructors

#RVO: NRVO_test.cpp
#	g++ -o RVO NRVO_test.cpp -O0

NRVO: NRVO_test.cpp
	g++ -o NRVO NRVO_test.cpp

clean:
	rm -rf NON_RVO_NRVO  NRVO
