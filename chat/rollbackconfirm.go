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

	// Restore word database
	os.Rename(db_en_dir, db_en_dir + ".prev")
	os.Rename(tmpdb_en_dir, db_en_dir)

	// Restore definition database
	os.Rename(db_cn_dir, db_cn_dir + ".prev")
	os.Rename(tmpdb_cn_dir, db_cn_dir)

	c.send <- []byte("rollbackconfirm: word \"" + word + "\"'s definitions has been restored.")
}