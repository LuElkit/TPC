package main

import (
	"fmt"
	"math/rand"
	"log"
	"os"
	"strconv"
	"tutorial20180402/merge_sort"
)

func sorted_fill(l []int) {
	for i, _ := range l {
		l[i] = i
	}
}

func rev_fill(l []int) {
	j := len(l) - 1
	for i, _ := range l {
		l[i] = j - i
	}
}

func main() {
	var p =256
	if len(os.Args) < 2{
	l := make([]int, p)
	sorted_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	rev_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	l = rand.Perm(len(l))
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)}else{
  n, err := strconv.ParseInt(os.Args[1],10,32)
	if err!=nil || n<0{
		log.Fatalf("arguement %v is not a proper positive integer",os.Args[1])}
	l := make([]int, n)

	sorted_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	rev_fill(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)

	l = rand.Perm(len(l))
	fmt.Println("Array:")
	fmt.Println("  ", l)
	l = merge_sort.MergeSort(l)
	fmt.Println("Array:")
	fmt.Println("  ", l)
}}
