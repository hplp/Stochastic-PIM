CC = clang++
CFLAGS = -o2 -g

convolution: 
	$(CC) $(FLAGS) StochasticPIM.cpp Cell.cpp Parser.cpp ASDM.cpp ASC_adder.cpp SchmittTrigger.cpp Activation.cpp DutyCycle.cpp StochasticConvolution.cpp

all:
	$(CC) $(FLAGS) StochasticPIM.cpp Cell.cpp Parsre.cpp ASDM.cpp ASC_adder.cpp SchmittTrigger.cpp Activation.cpp DutyCycle.cpp newPIMTB.cpp

clean:
	rm TemporalSim 