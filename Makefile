CC = gcc
CFLAGS = -I./Core/Inc -I./Testing/Unity -DUNIT_TEST

SRC = Core/Src/hal_motor.c Core/Src/kinematics.c Core/Src/hal_imu_mpu6050.c Core/Src/stl_service.c Core/Src/eeprom_service.c Testing/Unity/unity.c Testing/test_main.c
OBJ = $(SRC:.c=.o)
TARGET = test_runner

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
