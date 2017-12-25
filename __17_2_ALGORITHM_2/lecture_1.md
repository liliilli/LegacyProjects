# Intro

## GPU 의 발전

Nvidia 와 ATI 는 그래픽 카드가 매우 효율좋게 발전하게 된 계기는, GPU 가 병렬 프로세싱을 이용하여 화면에 60번의 화면 묘화를 하기 위해 많은 기술적인 발전을 거듭하였기 때문이다. Intel GPU 는 대개 CPU 의 코어 내에 동봉된 형태로 제공되어 두 벤더에 비해서 매우 적은 시장 지분을 가지고 있다.

## Concurrency Revolution

기존 Data Bus 의 구조는 폰 노이만 구조라고도 불리며, 폰 노이만 박사가 개발한 것임. (하버드 구조도 있으나 많이 복잡하기 때문에 딱히 쓰여지지는 않는듯..?)

### Until year 2003

2003년 까지는 CPU 가 대개 싱글 코어로, 딱히 병렬으로 작업을 하는 것이 중요하게 자리잡지는 않았다. Processor 는 Control Unit 과 Arithmetic Logic Unit 이 있으며, 폰 노이만 구조를 이용해 Memory 에 대용량의 정보를 일시적으로 저장하는 것이 가능했다.

이 폰 노이만의 구조는 Data Bus 을 다 공유하고 있기 때문에 독점이 생길 수 있다는 것..

### Since 2003

Multi-Core CPU 의 대두로, 일반 데스크탑에서도 다중 코어의 병렬 컴퓨팅이 중요하게 자리잡게 됨.

CPU vendor 에서는 듀얼코어를 시작으로 여러가지 다중 코어 CPU 을 내놓게 됨. 하지만 8코어 이상은, CPU 코어 자체가 클 뿐더러 lightweight 하지 않기 때문에 그 이상은 잘 없음. 

GPU vendor 에서는 여러 코어가 싱글 칩에 들어가게 됨. CPU 와는 달리 lightweight 하기 때문에 많은 수의 코어를 한 칩에 얹는 것이 가능함.

## Moore's Law

2년마다, 집적된 트랜지스터의 수가 2배씩 늘어나게 된다. 하지만, 요즘 세대에 대해서는 이 법칙이 통하질 않는데, 이 이유는 트랜지스터가 2배 집적됨에 따라 Power comsumption 이 급격하게 늘어나게 되기 때문. 또한 물리적인 한계도 있으며 따라서 집적도가 2배씩 늘어남에 따라서 효율이 배가 되는건 아니라는 소리..

## Physical Limitation & Serial Performance Scaling is Over.

빛은 약 3E+8 m/sec 인데, 3Ghz CPU 에서는 약 1초에 10cm 정도 움직이게 된다. 이 때 CPU 의 회선은 매우 굽어있기 때문에 CPU 내부의 gate 들이 시그널을 받을 수 없게 될지도 모른다. 예를 들어, 10Ghz CPU 에서는 약 1초에 3cm 밖에 움직일 수 없기 때문에 CPU 내부의 gate가 시그널을 못 받아 hazard 가 일어날 수 있어 오작동이 일어날 수 있다.

따라서 Intel 이나 AMD vendor 이 CPU 을 계속 출시함에도 불구하고 Clock speed 을 올리지 못한다는 것. (물리학적 한계) 또한 power consumption 을 높여서 속도를 올릴 수도 있으나 이러면 meltdown의 위험이 초래된다. 그러나 transistor density 을 늘려서 보다 속도를 빠르게 할 수 있다는 것.

1. clock ticks (Hz) 을 올릴 수 없음.
2. power consumption 을 일정 이상으로도 올릴 수 없음.
3. transistor density 을 올릴 수는 있을 것.

## How to use transistors?

1. Instructoin-level parallelism

비효율적이며 따라서 nowadays 에서는 deprecated 되었다.

2. Data-level paralleism

은 가장 많이 사용되며, SPE 은 Playstation 에 사용되는 Data-level 병렬화.

3. Thread-level parallelism

멀티 쓰레딩, 멀티 코어 등을 이용한 Parallelism 이다.

## The New Moore's Law

컴퓨터는 더 이상 빨라지는 것이 아니라, 멀티 코어를 이용하여 **더 넓어진다** 라는 것. 따라서 algorithms 들을 parallel 로 생각해야 한다. 또한 Data-parallel computing algorithm 들은 여러개의 다양한 다수 코어에 대해서 확장성이 있는 솔루션이 되어야한다. (scalable solution)

이 이유는, 1. 다중 코어와, 수 많은 데이터 (빅데이터) 들을 seamless 하게 연동시켜야 하기 때문에.

## Generic Multi-core Chip

CPU 안의 memory 들은 각 Processor 에 대한 cache memory 이다. Global memory 는 일반 D-RAM 메모리이다.

또한, Processor 마다 하나의 스레드를 가지며 하나의 프로그램만을 실행시킬 수 있다. (여러가지 멀티 태스킹은 스케줄러를 이용해 시분할 처리를 하기 때문임.)

### 구조

* 각각 독립된 Control Unit (very big size)
- ALU (Arithmetic Logic Unit)
- Register (Memory)

또한, CPU 는 **latency (Instruction 의 처리 시간) 을 줄이기 위한 방향**으로 점차적으로 디자인되고 있다.

## Generic Many-core Chip (GPU)

많은 GPU 는 한 Processor가 set of threads (thread pool?) 을 가져서, 

### 구조

* Control Unit 이 있으나, 대개 크기가 매우 크기 때문에 CPU 에 비해서 simplified 되었다.
- 그리고 Processor 은 ALU 와 Reg 만 가진다.
- 통합된 CU 에서 각 Processor 에 명령을 보내서 동작하게 한다.

또한 출력을 하기 위해 정보를 저장하는 VRAM 을 가지고 있는데, GPU 와 VRAM 사이에는 한 방향으로는 Read, 한 방향으로는 Write 를 하는 Dual-bus 을 가지고 있기 때문에 기존 Data bus 를 가지는 메인보드보다 약 2배 빠르다.

Cache memory 는 CPU 에 비해서 Minimized 되어있다. 또한 CPU 와는 달리 **throughput (처리 양) 을 늘리기 위한 방향**으로 점차적으로 디자인되고 있다. speed 는 중요치 않음.

## CPU 에 cache 메모리가 큰 이유

von-neuuman structure 에서는 Memory 가 CPU 보다 느리기 때문에, latency 가 커질 수 밖에 없다. (bottleneck) 따라서 Memory 자체에서 정보를 따내서 CPU 에서 처리하는 것 보다는 CPU 바로 옆에 bus 없이 붙어있는 cache memory 에 잠시동안 쓰일 데이터를 저장하여 바로 가져다 쓰는 것임.

## Winning Applications Use Both CPU and GPU

어플리케이션은 용도에 따라서 CPU 가 좋을 수도, GPU 가 좋을 수도 있다.

## GeForce 8800 - 1 Gen. CUDA

한 코어에 16개의 thread pool 이 있어, 8개의 코어가 있으므로 총 128 개의 Units 가 있다..

## Current Parallel Processing Models

### MPI

Network based Processing Interface

### CUDA


### OpenCL

애플이 개발했으며, CUDA 보다는 좀 복잡하다.