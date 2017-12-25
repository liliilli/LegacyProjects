# 병렬 프로그래밍 (COMP427)

## parallel programming

1. Your brain is massibvely parallel.
2. many-core GPU's with programming (also multi-core CPU's)

## Understanding CUDA, OpenCL, (and OpenMP)

Professor teaches...

1. CUDA : thing of NVidia (Compute Unified Devide Architecture)
2. OpenCL : 영상처리? (Open source)
3. OpenMP : Multi-Processing (Open source)

## Lecturer

Professor :: [백 낙훈](http://mobilegraphicslab.knu.ac.kr)<br/>
E-mail :: [mobilegraphicslab@gmail.com](mobilegraphics@gmail.com)

## Course Layout

1. focus on **a single topic**, for each lecture (usually, *a half chapter from the textbook*)
2. [http://lms.knu.ac.kr](http://lms.knu.ac.kr)

## Textbooks

1. **Programming Massively Parallel Processors, 3rd ED**
2. **CUDA by example** (also there is translated version)

PPT is based on Textbook and cuda exmaple.

---

## Course Schedule

1. Introduction to CUDA
2. CUDA basic programming
3. CUDA thread model and memory model
4. CUDA performance tuning
5. Streaming and Atomic Operations
6. Sorting and Reduction (연역) (with Parallel Programming)<br/>
(*Sorting is very complex on parallel programming*)

7. Introduction to OpenCL
8. OpenCL programming concepts

## Examinations

***Essay Style Examination.*** (At least 10 problems)

1. Mid-term exam
* Oct 17, Tues PM 01:00 ~ 03:00 (2 hours)
* Eng.9 Bldg, Rm 417

2. Fianl Exam
* Dec 05, Tues PM 01:00 ~ 03:00 (2 Hrs)
* Eng.9 Bldg, Rm 417

3. Closed Book, Essay-style Problems some pseudo-coding problems.<br/>
(No compiler, so You have to write coding problems with psuedo-style)

---

## Evaluation

HomeWork :: 5 homeworks. (Flexible)

---

# Current Trends

## Flops (Floating point operations per second) [http://www.top500.org](http://www.top500.org/)

float and float multiplication is important for calculating many complex calculations like a machine learning and forecast such as AI (like a AlphaGo), and bitcoin.

## Why graphics card?

Graphics card has enormous calculating ability with good flops like a NVidia Tesla relaeased in 2012 from 5 years ago (3.82TFlops) and NVIDIA GTX 1080 has 8.2TFlops with just one graphic card has about 2.5 thousand CUDA core.

그리고 이것을 구현하는데, Electricity 와 Heat 을 잡는것이 필요하다..