### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: Trig/Echo GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(cs100 REQUIRED)
```

### 3. CS100

#### 3.1 Command Instruction

1. Show cs100 chip and driver information.

   ```shell
   cs100 (-i | --information)
   ```

2. Show cs100 help. 

   ```shell
   cs100 (-h | --help)
   ```

3. Show cs100 pin connections of the current board.

   ```shell
   cs100 (-p | --port)
   ```

4. Run cs100 read test, num means the test times.

   ```shell
   cs100 (-t read | --test=read) [--times=<num>]
   ```

5. Run cs100 read function, num means the read times.

   ```shell
   cs100 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
./cs100 -i

cs100: chip is angoSense CS100.
cs100: manufacturer is angoSense.
cs100: interface is GPIO.
cs100: driver version is 1.0.
cs100: min supply voltage is 3.0V.
cs100: max supply voltage is 5.5V.
cs100: max current is 5.30mA.
cs100: max temperature is 85.0C.
cs100: min temperature is -40.0C.
```

```shell
./cs100 -p

cs100: trig pin connected to GPIO27(BCM).
cs100: echo pin connected to GPIO17(BCM).
```

```shell
./cs100 -t read --times=3

cs100: chip is angoSense CS100.
cs100: manufacturer is angoSense.
cs100: interface is GPIO.
cs100: driver version is 1.0.
cs100: min supply voltage is 3.0V.
cs100: max supply voltage is 5.5V.
cs100: max current is 5.30mA.
cs100: max temperature is 85.0C.
cs100: min temperature is -40.0C.
cs100: start read test.
cs100: distance is 9.863000cm.
cs100: distance is 9.979000cm.
cs100: distance is 10.013000cm.
cs100: finish read test.
```

```shell
./cs100 -e read --times=3

cs100: 1/3.
cs100: distance is 0.0961m.
cs100: 2/3.
cs100: distance is 0.0996m.
cs100: 3/3.
cs100: distance is 0.1040m.
```

```shell
./cs100 -h

Usage:
  cs100 (-i | --information)
  cs100 (-h | --help)
  cs100 (-p | --port)
  cs100 (-t read | --test=read) [--times=<num>]
  cs100 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <read>, --test=<read>       Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

