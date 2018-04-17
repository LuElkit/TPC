// ordered_set: a simple generic set implementation
package ordered_set

/*
OrderedType interface: describes comparable value
 
Comparable value provides:
  x.Less(y) returns true if x < y
  x.Equals(y) returns true if x == y
*/
type OrderedType interface {
	Less(OrderedType) bool
	Equals(OrderedType) bool
}

// uniq_merge(s1, s2) returns a merge of sorted list s1 and s2 without doublon
func uniq_merge(s1, s2 []OrderedType) (r []OrderedType) {
	var i=0
	var i1=0

	for i< len(s1)&&i1<len(s2){
		if s1[i].Less(s2[i]) && !s1[i].Equals(s2[i]){
			r=append(r,s1[i])
			i++}else{
			r =append(r,s2[i])
			i1++}
			if i<len(s1){
				r =append(r,s1[i:]...)}
			if i1<len(s2){
				r = append(r,s2[i1:]...)}

}
		return
}

//Set: an ordered set of OrderedType elements
type Set []OrderedType

// NewSet() creates a new empty set
func NewSet() *Set {
        s := Set(make([]OrderedType, 0))
        return &s
}

// s.bfind(x) returns expected position of x
// if x is not present, returns position of first element not smaller than x
func (s *Set) bfind(x OrderedType) (pos int) {
	var plus_grand=0
  /*for i:=0;i<len(*s);i++{
		elm := (*s)[i]
		if(x.Equals(elm)){
			pos =i}
		if(!x.Less(elm)){
			pos =i
			break}
	}
	return*/
	if !s.Mem(x){
		var right=len(*s)
		var left=0
		pos=left+(right -left)/2
		if x.Equals((*s)[pos]){
			return }
		for left <right {
			if x.Less((*s)[pos]){
				right =pos}else{
				left= pos+1}
		}
		return 
}else{
	i:=0
	for i<len(*s) && x.Less((*s)[i]){
		i++
	}
	pos =i
	return
}}
// s.Mem(x) returns true if x is in the set
func (s *Set) Mem(x OrderedType) bool {
	p := s.bfind(x)
	return p < len(*s) && x.Equals((*s)[p])
}

//s.Add(x) add x to set s, returns true if x wasn't there, false otherwise
func (s *Set) Add(x OrderedType) bool {
	v:= NewSet()
	Nhere:=true
	pos :=s.bfind(x)
	if !s.Mem(x){
		for i:=0; i <pos-1;i++{
			*v =append(*v,(*s)[i])}
		*v= append(*v,x)
		for i:=pos; i <len(*s); i++{
			*v= append(*v,(*s)[i])}
		s=v
		return Nhere}else{
			return !Nhere}
 
}
// s.Remove(x) removes x from s
// returns true if x was in the set, false otherwise
func (s *Set) Remove(x OrderedType) bool {
	here:= true
	v:=NewSet
	if s.Mem(x){
		for i:=0; i<len(*s);i++{
			if !x.Equals((*s)[i]){
				*v= append(*v,(*s)[i])}
		}
		s=v
		return here}else{
		return !here}
 
}

// s.Union(s2) adds elements from s2 to s
func (s *Set) Union(s2 *Set) {
	*s = uniq_merge(*s, *s2)
}

// s.Difference(s2) removes all elements of s2 from s
func (s *Set) Difference(s2 *Set) {
	/* FIX ME */
}
