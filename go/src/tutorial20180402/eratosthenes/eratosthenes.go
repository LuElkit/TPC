package main

import "fmt"

// Faire la liste des diviseurs de n si >2 alors pas premiers
//FAIRE LE TRUC
//https://www.mathematiquesfaciles.com/nombres-premiers_2_78336.html
func Sqrt(n int) int {
	var i=4
	var k=0
	var x=0
	var y=n
	if n==0{
		return 0
	}	else{
		for k <i{
			x= (y + (n/y))/2
			y=x
			k++
		}
		return x
	}
}
func premier(j int) int{
	var y = Sqrt(j)+1
	if j%2==0 {
		return 0
	}else{
			for i:=3; i< y;i+=2 {
				if j%i ==0 {
					return 0}
			}
			return 1
	}
}
// Eratosthenes(n) returns the list of prime numbers inferior or equal to n 
func Eratosthenes(n int) (prime []int) {
		var a=0
		for j:=1; j<n; j++ {
			a =premier(j)
			if j==2 {
				prime = append(prime,j)}
			if a==1 && j!=1{
				prime =append(prime,j)
			}
	}
	return
}
/*func Clever_Eratosthenes(n int) (prime []int){
	prime = append(prime,2)
	no_primes = make(map[int]bool)
	var i=3
	for i <= n{
		elm, ok = map[i]
		for i<= n && ok {
			delete(m,i)
			i+=2}
		if i > n{
			return prime }
		var j =i
		for i*i <=n{
			

}*/
func main() {
	prime := Eratosthenes(400)
	fmt.Println("Prime Eratosthenes : ",prime)
}
