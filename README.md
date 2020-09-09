# # ollvm4.0-and-llvm9.0

将ollvm4.0 移植合并到 llvm9.0


# 环境
```c
`ubuntu20.02`
sudo apt-get -y install cmake
sudo apt-get -y install ninja-build
sudo apt-get -y install git-core gnupg flex bison build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev libgl1-mesa-dev libxml2-utils xsltproc unzip fontconfig
```

# 编译
```c
mkdir ./llvm/build_release
cd ./llvm/build_release
cmake -G Ninja ../
Ninja -j4
# if Field
# then run $ Ninja -j1
```

# 使用:
> clang helloworld.c -o helloworld_ollvm -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -sub -mllvm -sub_loop=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -sobf

# android studio使用: （ndk中移植ollvm）

> 把编译obfuscator_release出来的bin和lib复制到toolchains/llvm/prebuilt/linux-x86_64目录下，直接覆盖原来的llvm里面的clang
> 设置ndk环境变量
> export PATH="/home/zp/Android/android-ndk-r21b:$PATH"
> which ndk-build


## Android.mk工程
Android.mk中添加LOCAL_CFLAGS，即可开启ollvm

> LOCAL_CFLAGS := -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -sub -mllvm -sub_loop=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -sobf


## CMakeLists.txt工程
CMakeLists.txt中添加编译选项

> add_definitions(-mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -sub -mllvm -sub_loop=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -sobf)


## local.properties中添加ndk.dir

> sdk.dir=/home/zp/Android/Sdk
> ndk.dir=/home/zp/Android/android-ndk-r21b



# 效果：
>





