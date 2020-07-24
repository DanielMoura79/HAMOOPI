
rm.exe -f HAMOOPI.o HAMOOPI.exe

C:/MinGW/bin/g++.exe -c HAMOOPI.cpp -o HAMOOPI.o -I"C:/MinGW/include" -I"C:/MinGW/x86_64-w64-mingw32/include" -I"C:/MinGW/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"C:/MinGW/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++" -m32 -DALLEGRO_STATICLINK

C:/MinGW/bin/g++.exe HAMOOPI.o -o HAMOOPI.exe -L"C:/MinGW/lib32" -L"C:/MinGW/x86_64-w64-mingw32/lib32" -static-libgcc -mwindows -lalleg_s -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound -m32

DEL /F /A HAMOOPI.o