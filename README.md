# # ollvm4.0-and-llvm9.0

ollvm4.0+llvm9.0 合并
# 

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
> export PATH="/media/dev/A/home/dev/code/git/llvm_course/android-ndk-r20:$PATH"

> which ndk-build


## Android.mk工程
Android.mk中添加LOCAL_CFLAGS，即可开启ollvm

> LOCAL_CFLAGS := -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -sub -mllvm -sub_loop=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -sobf


## CMakeLists.txt工程
CMakeLists.txt中添加编译选项

> add_definitions(-mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -sub -mllvm -sub_loop=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -sobf)


### local.properties中添加ndk.dir

> sdk.dir=/Android/Sdk
> ndk.dir=/Android/android-ndk-r20



# 效果：
>





