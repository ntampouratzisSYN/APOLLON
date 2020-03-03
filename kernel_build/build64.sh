cd linux-arm64-gem5

echo Compile ARM KENEL ...
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- gem5_defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j4

cp vmlinux ../../kernels/binaries/vmlinux.aarch64.Apollon

echo Mount the .img ...
sudo mount -o loop,offset=32256 ../../kernels/disks/aarch64-ubuntu-trusty-headless.img /mnt/

echo Compile UserSpace Driver ...
aarch64-linux-gnu-gcc -c kernel/SensorDriver.c

echo Add this file to a library...
ar rvs SensorDriver.a SensorDriver.o

echo Copy the SensorDriver.a to Application directory...
cp SensorDriver.a ../Application

echo Copy the Header file to Application directory...
cp kernel/SensorDriver.h ../Application


echo Compile APP.C using library...
cd ../Application
make all64

echo Copy the executable in /mnt...
sudo cp App /mnt/
echo Umount the .img ...
sudo umount /mnt