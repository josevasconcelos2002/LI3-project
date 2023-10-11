# Compiler used
CC = gcc

# Flags to use when compiling
#  - Wall: show all warnings
#  - Iinclude: directory for the local header files
#  - `pkg-config --cflags glib-2.0`: glib header files directories (optional, only if using glib)
CFLAGS= -Wall -Iincludes -O1 -g `pkg-config --cflags glib-2.0`

# Flags to use when linking
#  - `pkg-config --libs glib-2.0`: glib library (optional, only if using glib)
#  - `-lm`: math library (optional, only if using glib)

LDFLAGS = `pkg-config --libs glib-2.0` -lm
#-I/usr/include/glib-2.0
#`pkg-config --libs glib-2.0` -lm

# Executable called 'Programa'.
#
# To generate it, we link all the .o files and the glib and math libraries.
# We use $(NAME) to use the variable NAME.
# $@ is equivalent to the target. In this case, $@ evaluates to: programa-principal programa-testes
# $^ evaluates to the dependencies: In this case, it evaluates to: src/main.o src/file1.o src/file2.o
# In this example, we have the following rule:
#  gcc `pkg-config --libs glib-2.0` -lm -Wall -Iinclude `pkg-config --cflags glib-2.0` src/main.o src/file1.o src/file2.o -o program
#
# Since this is the first rule, it will be the one called when executing 'make' without any arguments.
# In other words, 'make' is equivalent to 'make programa-principal programa-testes'.
#
# To execute this rule, the make will first need to execute rules 'src/main.o', 'src/file1.o',
# and 'src/file2.o', as specified in the list of dependencies (right)

all: programa-principal #programa-testes

programa-principal: src/Data/user.o src/Data/passenger.o src/Data/flight.o src/Data/reservation.o src/Data/validation.o  src/main.o src/interface.o src/batch.o
	$(CC) $^ $(LDFLAGS) -o $@

#programa-testes: src/tests.o src/Data/users.o src/Data/rides.o src/Data/drivers.o src/Data/hashtables.o src/Data/validations.o src/Queries/getInfoById.o src/Queries/getTopDrivers.o src/Queries/getTopUsersByDistanceTraveled.o src/Queries/getAveragePriceByCity.o src/Queries/getAveragePriceByTime.o src/Queries/getAverageDistanceByCityAndTime.o src/Queries/getTopDrivresByCity.o src/Queries/getInfoByGenderOrDate.o src/Queries/getTippedVoyagesByData.o src/batch.o src/interface.o
#	$(CC) $^ $(LDFLAGS) -o $@



# Here we generate the object files for each source.
# An empty rule is equivalent to $(CC) $(CPPFLAGS) $(CFLAGS) -c <left param> <right param>.
# As such, we set the target (left) as the name of the object file to be generated
# and the name of the source file in the list of dependencies (right).

# This specific rule is equivalent to:
# gcc -Wall -Iinclude `pkg-config --cflags glib-2.0` -c -o src/main.o src/main.c
src/main.o: src/main.c

# Equivalent to the one above
#src/main.o: src/main.c
#	$(CC) $(CFLAGS) -c -o $@ $^

# Here we generate the object files for batch mode.
#src/batch.o: src/batch.c
# Here we generate the object files for interface mode.
#src/interface.o: src/interface.c
# Here we generate the object files for tests.
#src/tests.o: src/tests.c

src/batch.o: src/batch.c

src/interface.o: src/interface.c

# Here we generate the object files for user.
src/Data/user.o: src/Data/user.c
# Here we generate the object files for passenger.
src/Data/passenger.o: src/Data/passenger.c
# Here we generate the object files for flght.
src/Data/flight.o: src/Data/flight.c
# Here we generate the object files for reservation.
src/Data/reservation.o: src/Data/reservation.c
# Here we generate the object files for validations.
src/Data/validation.o: src/Data/validation.c

# The clean will remove the executable (programa-principal && programa-testes) and object files (*.o).
# To run it, we must execute 'make clean'
clean:
	rm -f programa-principal programa-testes teste src/*.o src/Data/*.o  src/Data/*.gch  *.log src/*.gch
	rm -rf ./Resultados/
	rm -rf ./testes/
#rm -f for ubuntu
#del -rf for windows

# / for ubuntu
# \ for windows