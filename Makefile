CXX=g++

CXXFLAGS = -pthread -g -fPIC 
CXXFLAGS+=$(shell eval-pkg-config --cflags ual-cpp-gnu)
LDFLAGS=$(shell eval-pkg-config --libs ual-cpp-gnu)
CXXFLAGS += -I$(ITMLIBDIR)/itmconstants/include/

all: librunin.a 

librunin.a: runin.o cpo_utils.o critical_field.o growth_rate.o
	ar -rvs $@ $^
	
test/test.o: test/test.cpp
	$(CXX) -include UALClasses.h $(CXXFLAGS) -I$(ITMWORK)/gtest-1.7.0/include/ -c -o $@ $^

test: runin.o cpo_utils.o critical_field.o growth_rate.o test/test.o
	$(CXX) $(LDFLAGS) -L$(ITMWORK)/gtest-1.7.0/ -lgtest_main $^ -lgtest -o test.bin

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
	
ual:
	$(CXX) $(CXXFLAGS) $(UAL)/include/UALClasses.h -o $(ITMWORK)/runin/UALClasses.h.gch
	
clean:
	rm *.a *.o test/*.o test.bin
