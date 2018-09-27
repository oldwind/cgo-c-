/***************************************************************************
 *
 * @author yebin
 **************************************************************************/
 package main

 import "C" 
 
 import (
	//  "encoding/json"
	//  "encoding/hex"
	 "unsafe"
	//  "log"
	 "fmt"
 )
 
 var ret [10240]byte
 
 
 // export和注释符号//不能存在空格
 //export myFunc
 func myFunc(param1 string) (*C.char, int32) {
 
	fmt.Println(" ====> GO call params begin <=====");
	fmt.Println("param1:", param1);
	fmt.Println(" ====> GO call params params end <====");
 
	str := []byte("test return")
	copy(ret[:], str);
	retP := (*C.char)(unsafe.Pointer(&ret))
 
	// fmt.Println(ret);
	defer println(retP)
	return retP, int32(4)
}
 

func main() {}