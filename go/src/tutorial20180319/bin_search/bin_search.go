// bin_search.go: simple binary search in sorted array of integer.
package main
 
import (
	"flag"
	"fmt"
	"math/rand"
)
 
// BinSearch(tab, x) search for x in tab using efficient binary searching
// algorithm
// Returns a pair made of a position and a boolean, the boolean is false if x
// is not in the array, true otherwise.
/*func BinSearch(tab []int, x int) (int, bool) {
	 var mid = len(tab)/2
	 if tab[mid] == x{
				return mid,true
  }
	for tab[mid]!=x {
				if x < tab[mid]{
						var left = tab[0:mid]
						return BinSearch(left,x)
				} else {
						var right = tab[mid:len(tab)]
						return BinSearch(right,x)
				}
	}
	return 0,false
}*/
func _BinSearch(l int, r int, tab[]int, x int) (int, bool){
			var mid= l + (r-l)/2
			for r>l {
					if tab[mid] == x{
							return mid,true
					}
					if x < tab[mid]{
							r = mid
						}else{
					l = mid+1}
					mid = l+ (r-l)/2
			}
			return mid,false
}
func BinSearch(tab[]int, x int) (int,bool){
			var l = 0
			var r = len(tab)-1
			return _BinSearch(l,r,tab,x)
}
// genSortedArray(size) build a random sorted array of len size
func genSortedArray(size int) []int {
	tab := make([]int, size)
	cur := rand.Intn(32)
	for i := 0; i < size; i++ {
		tab[i] = cur
		cur += rand.Intn(16) + 1
	}
	return tab
}
 
// bin_search: test binary searching
func main() {
	var size int
	var seed int64 // mandatory for rand.Seed()
	// Flags
  flag.IntVar(&size,"size",10,"Size of array")
	flag.Int64Var(&seed,"seed",10,"seed")
  flag.Parse()
	// ** FIX ME **
	// take 2 flags: size and seed setting the value for variable size and seed
	// use flag.IntVar() et flag.Int64Var()
	// use some reasonable default values for size and seed.
	// see https://golang.org/pkg/flag
 
	// Init random generator
	rand.Seed(seed)
 
	tab := genSortedArray(size)
	fmt.Println(tab)
	pos := rand.Intn(size)
	x := tab[pos]
	fmt.Println("\nSearch for existing element:", x)
	pos_res, found := BinSearch(tab, x)
	fmt.Printf("BinSearch(tab, x): (%v, %v)\n", pos_res, found)
 
	x = tab[0] + rand.Intn(tab[len(tab)-1]-tab[0])
	fmt.Println("\nSearch for random element:", x)
	pos_res, found = BinSearch(tab, x)
	fmt.Printf("BinSearch(tab, x): (%v, %v)\n", pos_res, found)
}
