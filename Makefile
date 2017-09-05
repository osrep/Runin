CXX=g++

CXXFLAGS = -pthread -g -fPIC 

ifeq ($(ITM_ENVIRONMENT_LOADED), yes)
    CXXFLAGS += $(shell eval-pkg-config --cflags ual-cpp-gnu --cflags itmconstants)
    CXXFLAGS +=-DITM_CONSTANTS
    LDFLAGS = $(shell eval-pkg-config --libs ual-cpp-gnu)    
    all:  librunin.a
    $(info *** Compiler set to ITM *** )
else
    CXXFLAGS += $(shell pkg-config --cflags imas-cpp blitz imas-constants-cpp)
    LDFLAGS = $(shell pkg-config --libs imas-cpp blitz)    
    all: librunin_imas.a
    $(info *** Compiler set to IMAS *** )
endif

librunin.a:      runin.o      cpo_utils.o critical_field.o growth_rate.o
	ar -rvs $@ $^
	
librunin_imas.a: runin_imas.o ids_utils.o critical_field.o growth_rate.o
	ar -rvs $@ $^
	
test/test_phys.o: test/test_phys.cpp
	$(CXX) -include UALClasses.h $(CXXFLAGS) -I$(GTEST)/include/ -c -o $@ $^

#test/test_ids.o: test/test_ids.cpp
    #$(CXX) -include UALClasses.h $(CXXFLAGS) -I$(GTEST)/include/ -c -o $@ $^

test/test_cpo.o: test/test_cpo.cpp
    $(CXX) -include UALClasses.h $(CXXFLAGS) -I$(GTEST)/include/ -c -o $@ $^

test: runin.o cpo_utils.o critical_field.o growth_rate.o test/test_phys.o test/test_cpo.o
	$(CXX) $(LDFLAGS) -L$(GTEST)/ -lgtest_main $^ -lgtest -o test.bin

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
	
ual:
	$(CXX) $(CXXFLAGS) $(UAL)/include/UALClasses.h -o $(ITMWORK)/runin/UALClasses.h.gch
	
clean:
	rm *.a *.o test/*.o test.bin
