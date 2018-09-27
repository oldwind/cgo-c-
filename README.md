### cgo-cpp-php

#### 0x01 背景

语言和语言之间的通讯，本身是一个比较复杂的问题，要考虑到数据格式、通讯协议等种种问题，此次，我在项目中需要实现一个php和go之间的通讯，总结起来，通讯方式有三种
> 1. 采用http协议的方式，这中方式比较常见，go启动一个http服务，php通过curl方式去调用
> 2. 采用gcpc方式，gRPC是一个高性能、通用的开源RPC框架，其由Google主要面向移动应用开发并基于HTTP/2协议标准而设计，基于ProtoBuf(Protocol Buffers)序列化协议开发，且支持众多开发语言。但是hhvm和php都需要插件支持，php 5.X暂时应该没有官方插件
> 3. php的扩展调用cgo写的动态连接库，这种方式用的比较少，但是，此次项目中却必须采用这种方式。有多个原因
	
	- php端上要采用复杂的加密方式，go的加密库中有php插件中暂时不存在的。
	- grpc的原因，Go的服务端目前提供的Grpc服务，php由于版本问题，暂时无法使用

综上，选择第三种方法是迫不得已，况且开发周期非常短，也就三天左右	

#### 0x02 关于Cgo

我们第一个情况是要将go打成可以被C++调用的动态链接库, 那么必然选择cgo，在go中import C，需要关注几点

![go代码](https://github.com/oldwind/cgo-cpp-php/blob/master/img/123.png)

1. 第1行， 如果编译成so，package 必须填main
2. 第3行， import "C" 前面如果有注释，相当于注解，一般可以把C代码放在 import "C" 上做为注解用
3. 第10行，如果要返回可变字符串，需要申请公共内存，否则，so调用结束，会释放内存，调用方，拿不到返回的字符串
4. 第13行，Go的函数上面的注释相当于注解，是必须要的，否则编译的时候，生成的C头文件，不会生成对应方法
5. 第23行，必须要有

另外，关于编译情况。 有可能出现的一种情况是

	/home/users/yebin02/go/go/src/net/cgo_resnew.go:20:44: could not determine kind of name for C.char
	/home/users/yebin02/go/go/src/net/cgo_resnew.go:19:60: could not determine kind of name for C.socklen_t
	make: *** [xchain] Error 2

这种情况多是gcc的版本问题，在make的时候或者go build的时候，指定一下gcc版本就可以

	CC=/opt/compiler/{Gcc-version}/bin/gcc make

Makefile中打动态链接库的方法
	
	go build -o my_go_capi.so -buildmode=c-shared capi/my_go_capi.go



####0x02 php的扩展写法