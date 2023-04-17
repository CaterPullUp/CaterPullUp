#
# @author @trudelle200902
# @file MakeFile
# @date 12 avril 2023
#
all: test_sequence

test_sequence: test.o Caterpullup.o Corps.o DXL_Corps.o Patte.o DXL_Patte.o ElectroCPU.o timer.o Dynamixel2ArduinoSimul.o SerialSimul.o Uart.o
	g++ -o test_sequence.exe test.o Caterpullup.o Corps.o DXL_Corps.o Patte.o DXL_Patte.o ElectroCPU.o timer.o Dynamixel2ArduinoSimul.o SerialSimul.o

test.o: test.cpp Caterpullup.h Patte.h Corps.h Dynamixel.h Dynamixel2ArduinoSimul.h Arduino_function.h SerialSimul.h Uart.h
	g++ -c test.cpp

Caterpullup.o: Caterpullup.cpp Caterpullup.h Patte.h Corps.h Dynamixel.h Dynamixel2ArduinoSimul.h timer.h
	g++ -c Caterpullup.cpp

Corps.o: Corps.cpp Corps.h ElectroCPU.h DXL_Corps.h
	g++ -c Corps.cpp

DXL_Corps.o: DXL_Corps.cpp DXL_Corps.h Arduino_function.h SerialSimul.h Dynamixel.h Dynamixel2ArduinoSimul.h Moteur.h
	g++ -c DXL_Corps.cpp

Patte.o: Patte.cpp Patte.h ElectroCPU.h DXL_Patte.h
	g++ -c Patte.cpp

DXL_Patte.o: DXL_Patte.cpp DXL_Patte.h Dynamixel.h Dynamixel2ArduinoSimul.h Moteur.h
	g++ -c DXL_Patte.cpp

ElectroCPU.o: ElectroCPU.cpp ElectroCPU.h Arduino_function.h SerialSimul.h Electroaimant.h
	g++ -c ElectroCPU.cpp

timer.o: timer.cpp timer.h Arduino_function.h SerialSimul.h 
	g++ -c timer.cpp

Dynamixel2ArduinoSimul.o: Dynamixel2ArduinoSimul.cpp Dynamixel2ArduinoSimul.h
	g++ -c Dynamixel2ArduinoSimul.cpp

SerialSimul.o: SerialSimul.cpp SerialSimul.h
	g++ -c SerialSimul.cpp

Uart.o: Uart.cpp Uart.h Arduino_function.h Caterpullup.h
	g++ -c Uart.cpp

clean:
	rm  -f *.o
	rm  -f *.gch