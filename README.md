### cgo-cpp-php

#### 一、背景

	解决php调用go的一个deamon


#### 二、环境说明

	php 版本
		PHP 5.4.46-dev (cli) (built: Oct 10 2018 16:46:08) (DEBUG)
		Copyright (c) 1997-2014 The PHP Group
		Zend Engine v2.4.0, Copyright (c) 1998-2014 Zend Technologies


	编译Go的版本
		go version go1.10 linux/amd64

	
#### 三、go动态连接库编译说明

	如果出现错误
		/home/users/yebin02/go/go/src/net/cgo_resnew.go:20:44: could not determine kind of name for C.char
		/home/users/yebin02/go/go/src/net/cgo_resnew.go:19:60: could not determine kind of name for C.socklen_t
		make: *** [xchain] Error 2

	CC中选择高版本的gcc

		CC=/opt/compiler/gcc-4.8.2/bin/gcc  go build -o my_go_capi.so -buildmode=c-shared  my_go_capi.go

#### 四、wiki
	
	https://github.com/oldwind/cgo-cpp-php/wiki/cgo-&&-cpp-&&-php