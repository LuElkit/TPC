package ordered_set
 
import (
	"math/rand"
	"testing"
)
 
type OrderedInt int
 
func (x OrderedInt) Equals(y OrderedType) bool {
	switch y_ := y.(type) {
	case OrderedInt:
		return x == y_
	default:
		return false
	}
}
 
func (x OrderedInt) Less(y OrderedType) bool {
	switch y_ := y.(type) {
	case OrderedInt:
		return x < y_
	default:
		return false
	}
}
 
func isSet(s Set) bool {
	i := 0
	for ; i < len(s)-1 && s[i].Less(s[i+1]) && !s[i].Equals(s[i+1]); i++ {
	}
	return i >= len(s)-1
}
 
func present(s Set, x OrderedType) bool {
	for _, v := range s {
		if x.Equals(v) {
			return true
		}
	}
	return false
}
 
func TestSet_Add_fixed(t *testing.T) {
	tmp := Set(make([]OrderedType, 0))
	var s *Set
	s = &tmp
	for i := 0; i < 100; i++ {
		n := OrderedInt(i)
		if !s.Add(n) {
			t.Fatal("Adding not present element should not return false")
		}
		if len(*s) != i+1 {
			t.Fatal("Set length does not match")
		}
		if !present(*s, n) {
			t.Fatal("Added element not in the set")
		}
		if !isSet(*s) {
			t.Log("set:", *s)
			t.Fatal("Ill formed set (not sorted or contains doublons)")
		}
	}
	if !isSet(*s) {
		t.Log("set:", *s)
		t.Fatal("Ill formed set (not sorted or contains doublons)")
	}
}
 
func TestSet_Add_random(t *testing.T) {
	tmp := Set(make([]OrderedType, 0))
	var s *Set
	s = &tmp
	size := 0
	for i := 0; i < 100; i++ {
		n := OrderedInt(rand.Intn(1000))
		if s.Add(n) {
			size += 1
		}
		if len(*s) != size {
			t.Fatal("Set length does not match")
		}
		if !present(*s, n) {
			t.Fatal("Added element not in the set")
		}
	}
	if !isSet(*s) {
		t.Log("set:", *s)
		t.Fatal("Ill formed set (not sorted or contains doublons)")
	}
}
 
func TestSet_Mem(t *testing.T) {
	s := Set(make([]OrderedType, 100))
	for i := 0; i < 100; i += 1 {
		n := OrderedInt(2 * i)
		s[i] = n
	}
	for i := 0; i < 100; i += 1 {
		n := OrderedInt(2 * i)
		if !s.Mem(n) {
			t.Log(s)
			t.Errorf("set.Mem(%d): unable to find present value\n", 2*i)
		}
	}
	for i := -1; i < 2; i++ {
		n := OrderedInt(i*201 + 1)
		if s.Mem(n) {
			t.Log(s)
			t.Errorf("set.Mem(%d): found not present value\n", 201*i+1)
		}
 
	}
}
