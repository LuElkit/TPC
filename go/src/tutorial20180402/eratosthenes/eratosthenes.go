package main

import "fmt"

// Faire la liste des diviseurs de n si >2 alors pas premiers
//FAIRE LE TRUC
//https://www.mathematiquesfaciles.com/nombres-premiers_2_78336.html


/* Eratosthenes(n) returns the list of prime numbers inferior or equal to n */
func Eratosthenes(n int) (prime []int) {
		var i,j,c=0
		if n >=2{
			prime = append(prime,2)
			for i=3; i<n;n++{
				
			}
}
func main() {
	prime := Eratosthenes(100000)
	fmt.Println(prime)
}
