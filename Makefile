exam: info.o list.o main.o exam.o
	g++ -o exam info.o list.o main.o exam.o

info.o: info.cc info.h
	g++ -c info.cc
list.o: list.cc list.h info.h
	g++ -c list.cc

exam.o: exam.cc exam.h list.h info.h
	g++ -c exam.cc
main.o: main.cc list.h info.h exam.h
	g++ -c main.cc

.PHONY: clean cleanall depend

clean: 
	rm -f *.o

cleanall: 
	rm -f *.out

depend: 
	g++ -MM info.cc list.cc main.cc > dependMake