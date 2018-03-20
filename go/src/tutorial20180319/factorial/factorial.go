/*
	fatorial: a simple factorial demo
*/
package main

import (
				"fmt"
				"log"
				"os"
				"strconv"
)

// Fact(n): compute n!
func Fact(n int) int{
				var r int
				for r =1; n>0;n--{
					r= r*n
			}
			return r
}

func main() {
			if len(os.Args) < 2{
						log.Fatalln("missing arguments")
			}
			n, err := strconv.ParseInt(os.Args[1],10,32)
			//m,errf := strconv.ParseInt(os.Args[2],10,32)
			if err != nil || n<0 /*|| errf != nil || m <0*/{
							log.Fatalf("argument %v is not a proper positive integer",
							os.Args[1])
			}
			//for ;n<=m; n++{
			fmt.Printf("Fact(%v) = %v\n",n,Fact(int(n)))
			//}
}
