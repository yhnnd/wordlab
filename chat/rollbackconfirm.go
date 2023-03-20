package main

import (
	"strconv"
	"os"
)

func (c *Client) rollbackconfirm(word string) {

	var lth = strconv.Itoa(len(word))

	var db_en_dir = rootdir + "/en/english" + lth + ".csv"
	var db_cn_dir = rootdir + "/ch/chinese" + lth + ".csv"

	var tmpdb_en_dir = rootdir + "/en/english" + lth + ".csv.tmp"
	var tmpdb_cn_dir = rootdir + "/ch/chinese" + lth + ".csv.tmp"

	// Check if temp words database exists
	_, err := os.Stat(tmpdb_en_dir)
	if os.IsNotExist(err) {
		c.send <- []byte("rollbackconfirm: no backup word database for word \"" + word + "\".")
	} else {
		// Restore word database
		os.Rename(db_en_dir, db_en_dir + ".prev")
		os.Rename(tmpdb_en_dir, db_en_dir)
		c.send <- []byte("rollbackconfirm: word database has been restored for word \"" + word + "\".")
	}
	// Check if temp definitions database exists
	_, err = os.Stat(tmpdb_cn_dir)
	if os.IsNotExist(err) {
		c.send <- []byte("rollbackconfirm: no backup defs database for word \"" + word + "\".")
	} else {
		// Restore definitions database
		os.Rename(db_cn_dir, db_cn_dir + ".prev")
		os.Rename(tmpdb_cn_dir, db_cn_dir)
		c.send <- []byte("rollbackconfirm: word \"" + word + "\"'s definitions has been restored.")
	}
}