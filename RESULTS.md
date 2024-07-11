
## Results on Windows 11 x64
-  Visual Studio 2022
-  AMD Ryzen 9 4900HS (16 cores)

```cmd
(conan2) c:\work\own\carsds>ctest --preset conan-release
Test project C:/work/own/carsds/build
      Start  1: Process.InvalidPath
 1/10 Test  #1: Process.InvalidPath ....................................................   Passed    0.01 sec
      Start  2: ReduceTest.CountBig<std::execution::sequenced_policy>
 2/10 Test  #2: ReduceTest.CountBig<std::execution::sequenced_policy> ..................   Passed    3.97 sec
      Start  3: ReduceTest.CountBig<std::execution::parallel_policy>
 3/10 Test  #3: ReduceTest.CountBig<std::execution::parallel_policy> ...................   Passed    0.05 sec
      Start  4: ReduceTest.CountBig<std::execution::parallel_unsequenced_policy>
 4/10 Test  #4: ReduceTest.CountBig<std::execution::parallel_unsequenced_policy> .......   Passed    0.05 sec
      Start  5: ProcessType/ProcessTest.smallDS/Seq  # GetParam() = 00007FF79AB126E0
 5/10 Test  #5: ProcessType/ProcessTest.smallDS/Seq  # GetParam() = 00007FF79AB126E0 ...   Passed    0.01 sec
      Start  6: ProcessType/ProcessTest.smallDS/Par  # GetParam() = 00007FF79AB120A0
 6/10 Test  #6: ProcessType/ProcessTest.smallDS/Par  # GetParam() = 00007FF79AB120A0 ...   Passed    0.01 sec
      Start  7: ProcessType/ProcessTest.juneDS/Seq  # GetParam() = 00007FF79AB126E0
 7/10 Test  #7: ProcessType/ProcessTest.juneDS/Seq  # GetParam() = 00007FF79AB126E0 ....   Passed    7.69 sec
      Start  8: ProcessType/ProcessTest.juneDS/Par  # GetParam() = 00007FF79AB120A0
 8/10 Test  #8: ProcessType/ProcessTest.juneDS/Par  # GetParam() = 00007FF79AB120A0 ....   Passed    0.56 sec
      Start  9: ProcessType/ProcessTest.bigDS/Seq  # GetParam() = 00007FF79AB126E0
 9/10 Test  #9: ProcessType/ProcessTest.bigDS/Seq  # GetParam() = 00007FF79AB126E0 .....   Passed   48.01 sec
      Start 10: ProcessType/ProcessTest.bigDS/Par  # GetParam() = 00007FF79AB120A0
10/10 Test #10: ProcessType/ProcessTest.bigDS/Par  # GetParam() = 00007FF79AB120A0 .....   Passed    3.75 sec

100% tests passed, 0 tests failed out of 10
```

## Results on Ubuntu Linux x64 build machine
- gcc 11.4.0
- in docker container
- host:
    - Linux 6.5.13-1-pve
    - 2 x Intel(R) Celeron(R) N5105 @ 2.00GHz (1 Socket)
```bash
Run ctest --preset conan-release
Test project /__w/carsds/carsds/build/Release
      Start  1: Process.InvalidPath
 1/10 Test  #1: Process.InvalidPath .......................................................   Passed    0.00 sec
      Start  2: ReduceTest.CountBig<__pstl::execution::v1::sequenced_policy>
 2/10 Test  #2: ReduceTest.CountBig<__pstl::execution::v1::sequenced_policy> ..............   Passed    1.81 sec
      Start  3: ReduceTest.CountBig<__pstl::execution::v1::parallel_policy>
 3/10 Test  #3: ReduceTest.CountBig<__pstl::execution::v1::parallel_policy> ...............   Passed    1.86 sec
      Start  4: ReduceTest.CountBig<__pstl::execution::v1::parallel_unsequenced_policy>
 4/10 Test  #4: ReduceTest.CountBig<__pstl::execution::v1::parallel_unsequenced_policy> ...   Passed    7.42 sec
      Start  5: ProcessType/ProcessTest.smallDS/Seq  # GetParam() = 0x57d1233d5380
 5/10 Test  #5: ProcessType/ProcessTest.smallDS/Seq  # GetParam() = 0x57d1233d5380 ........   Passed    0.00 sec
      Start  6: ProcessType/ProcessTest.smallDS/Par  # GetParam() = 0x57d1233d37b0
 6/10 Test  #6: ProcessType/ProcessTest.smallDS/Par  # GetParam() = 0x57d1233d37b0 ........   Passed    0.00 sec
      Start  7: ProcessType/ProcessTest.juneDS/Seq  # GetParam() = 0x57d1233d5380
 7/10 Test  #7: ProcessType/ProcessTest.juneDS/Seq  # GetParam() = 0x57d1233d5380 .........   Passed   15.26 sec
      Start  8: ProcessType/ProcessTest.juneDS/Par  # GetParam() = 0x57d1233d37b0
 8/10 Test  #8: ProcessType/ProcessTest.juneDS/Par  # GetParam() = 0x57d1233d37b0 .........   Passed    4.21 sec
      Start  9: ProcessType/ProcessTest.bigDS/Seq  # GetParam() = 0x57d1233d5380
 9/10 Test  #9: ProcessType/ProcessTest.bigDS/Seq  # GetParam() = 0x57d1233d5380 ..........   Passed   94.26 sec
      Start 10: ProcessType/ProcessTest.bigDS/Par  # GetParam() = 0x57d1233d37b0
10/10 Test #10: ProcessType/ProcessTest.bigDS/Par  # GetParam() = 0x57d1233d37b0 ..........   Passed   24.76 sec

100% tests passed, 0 tests failed out of 10
```

## cli tool usage example (Windows 11 x64)
```cmd
>build\cli\Release\carsds_cli.exe seq resources\telangana_vehicle_sales.csv
Time: 49839.8 ms

>build\cli\Release\carsds_cli.exe par resources\telangana_vehicle_sales.csv
Time: 3776.55 ms
```