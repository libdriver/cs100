### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: Echo/TrigPA8/PA0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

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
cs100 -i

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
cs100 -p

cs100: trig pin connected to GPIOA PIN0.
cs100: echo pin connected to GPIOA PIN8.
```

```shell
cs100 -t read --times=3

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
cs100: distance is 10.574000cm.
cs100: distance is 10.234000cm.
cs100: distance is 10.250999cm.
cs100: finish read test.
```

```shell
cs100 -e read --times=3

cs100: 1/3.
cs100: distance is 0.1064m.
cs100: 2/3.
cs100: distance is 0.1073m.
cs100: 3/3.
cs100: distance is 0.1068m.
```

```shell
cs100 -h

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

