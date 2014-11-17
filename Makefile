CXX=g++

CXXFLAGS=-pthread -g -fPIC -I$(UAL)/include -I$(UAL)/lowlevel -I$(UAL)/cppinterface/ -I/afs/ipp-garching.mpg.de/itm/switm/blitz/0.10/include/ 
#-I$(ITMLIBDIR)/itmconstants/include/

LDFLAGS=-L$(UAL)/lib -lUALCPPInterface -lUALLowLevel -L/afs/ipp-garching.mpg.de/itm/switm/blitz/0.10/lib -lblitz

all: librunin.a

librunin.a: runin.o cpo_utils.o critical_field.o growth_rate.o
	ar -rvs $@ $^

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
	
clean:
	rm *.a *.o
