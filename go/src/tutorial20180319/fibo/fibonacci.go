/*
	fibo.go : a sinmple fibo demo
*/
package	main

import (
				"fmt"
				"log"
				"os"
				"strconv"
)

// Fibo(n) : compute fibo n
func _fibo(n int) (int, int){
		if (n ==0) {
			return 0,1
		}
		if (n <=2) {
			return 1,1
		}

	  var	a,b = _fibo(n-1)
		return a+b,a
}

func fibo(n int) int {
		var r,_=_fibo(n)
		return r
}
func main() {
	if len(os.Args) < 2{
		log.Fatalln("missing arguments")
	}
	n, err := strconv.ParseInt(os.Args[1], 10, 32)
  //m, errf := strconv.ParseInt(os.Args[2],10,32)
	if err != nil || n < 0/* || errf!=nil || m<0*/ {
		log.Fatalf("argument %v is not a proper positive integer", os.Args[1])
	}
	//for ;n<m;n++ {
	fmt.Printf("fibo(%v) = %v\n", n, fibo(int(n)))
	
}
