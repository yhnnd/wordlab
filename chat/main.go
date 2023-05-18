// Copyright 2013 The Gorilla WebSocket Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"log"
	"os"
	"net/http"
)

const (
	rootdir = "../WordLabGo/files/lang-utf8"
)

type TypeDef struct {
	Text string 	`json:"text"`
	Sort string 	`json:"sort"`
	Chinese string 	`json:"chinese"`
}

type TypeResult struct {
	Pathname string `json:"pathname"`
	Word string 	`json:"word"`
	Lth int 		`json:"lth"`
	Index int 		`json:"num"`
	Defs [] TypeDef `json:"defs"`
	DefN int 		`json:"defn"`
	Found bool		`json:"found"`
	Message string	`json:"message"`
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*           Legacy Word Lab Go                        */
/* The Legacy WordLabGo project was migrated here      */
/* All Legacy files has filename begins with "legacy"  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
func serveLegacyHome(w http.ResponseWriter, r *http.Request) {
	log.Printf("url = %s\n", r.URL.Path)
	if r.URL.Path != "/legacy" {
		http.Error(w, "Not found", http.StatusNotFound)
		return
	}
	if r.Method != http.MethodGet {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}
	http.ServeFile(w, r, "legacy.html")
}

/* * * * * * * * * * * * * * * * * * * * * * */
/*            Websocket Chat                 */
/*   https://github.com/gorilla/websocket    */
/* * * * * * * * * * * * * * * * * * * * * * */
func serveHome(w http.ResponseWriter, r *http.Request) {
	log.Printf("url = %s\n", r.URL.Path)
	// log.Println(r.URL)
	if r.URL.Path != "/" {
		http.Error(w, "Not found", http.StatusNotFound)
		return
	}
	if r.Method != http.MethodGet {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}
	http.ServeFile(w, r, "index.html")
}

func main() {
	/* * * * * * * * * * * * * * * * * * * * * * */
	/*         Print Working Directory           */
	/* * * * * * * * * * * * * * * * * * * * * * */
	path, err := os.Getwd()
	if err != nil {
		log.Println(err)
	}
	log.Printf("working directory: %q\n", path)
	path, err = os.Executable()
	if err != nil {
		log.Println(err)
	}
	log.Printf("path of executable: %q\n", path)



	/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/*           Legacy Word Lab Go                        */
	/* The Legacy WordLabGo project was migrated here      */
	/* All Legacy files has filename begins with "legacy"  */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
	http.HandleFunc("/legacy", serveLegacyHome)
	http.HandleFunc("/translate", handleTranslate)
	var suggests LegacySuggestions
	suggests.substrRatio = 0.5
	suggests.subseqRatio = 0.66
	http.HandleFunc("/suggestions", suggests.handleSuggests)




	/* * * * * * * * * * * * * * * * * * * * * * */
	/*            Websocket Chat                 */
	/*   https://github.com/gorilla/websocket    */
	/* * * * * * * * * * * * * * * * * * * * * * */
	hub := newHub()
	go hub.run()
	http.HandleFunc("/", serveHome)
	/* * * * * * * * * * * * * * * * * * * * * * * * * */
	/*     Only This API uses Websocket protocol.      */
	/* * * * * * * * * * * * * * * * * * * * * * * * * */
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) {
		serveWs(hub, w, r)
	})
	// Run HTTP Server
	log.Printf("server is running on localhost:8080\n")
	err2 := http.ListenAndServe("localhost:8080", nil)
	if err2 != nil {
		log.Fatal("ListenAndServe: ", err2)
	}
}
