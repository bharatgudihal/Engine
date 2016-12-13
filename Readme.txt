1) Implemented guardbands
"\Engine\Memory\Private\FixedSizeAllocator.cpp" Line 32

2) Handling 32/64 bit platforms
"\Engine\Memory\BitArray.h" Line 31,39

3) Using _BitScanForward()/_BitScanForward64()
"\Engine\Memory\BitArray.h" Line 6
"\Engine\Memory\Private\BitArray.cpp" Line 145

4) Creating FSA in one allocation
"\Engine\Memory\Private\FixedSizeAllocator.cpp" Line 17

5)FixedSizedAllocator properly validate pointers in it's free function
"\Engine\Memory\Private\FixedSizeAllocator.cpp" Line 85 IsValid function

6)HeapManager / BlockAllocator and FixedSizeAllocator recognize and warn about outstanding allocation when they're destructed
"\Engine\Memory\Private\FixedSizeAllocator.cpp" Line 27