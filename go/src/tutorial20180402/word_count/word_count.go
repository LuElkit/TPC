package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"

)
func Occurrence(s string, words []string) int {
		var count =0
		for i:=0; i< len(words);i++ {
				if s == words[i] {
						count++
				}
		}
		return count
}
func WordCount(words []string) (wc map[string]int) {
	wc = make(map[string]int)
	for i:=0; i< len(words);i++ {
			//fmt.Printf("words[i] = %s",words[i])
			count := Occurrence(words[i],words)
			wc[words[i]]= count
			//count ++
	}
	return 
}

func LoadFile(fname string) (words []string) {
	FILE,err := os.Open(fname)

	content,err := ioutil.ReadAll(FILE)
	if err!=nil{
		fmt.Printf("err")}
fmt.Printf("Fields %q",content)
  String := strings.Fields(string(content))
var s =""
 var size=0
	var count =0
	for i:=0; i< len(content); i++{
		if content[i]>=65 && content[i] <= 90 ||content[i] >= 97 &&
			 content[i] <=122{continue;}else{size++}
}
//fmt.Printf("size %d",size)
var	S = make([]string,size)
	for i:=0; i< len(content); i++{
				if content[i] >=65 && content[i] <= 90 || content[i] >=97 && 
					content[i] <=122 {
					 s +=string(content[i])
				}else{ if content[i] != 0{
				    	S[count]= s
							s=""
							count++}
					}}
		words= S

fmt.Printf("Field %s\n",String)
	return
}

func main() {
	if len(os.Args) < 2 {
		panic("Missing argument")
	}
	wc := WordCount(LoadFile(os.Args[1]))
	fmt.Println(wc)
}
