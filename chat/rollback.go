package main

import (
	"io/ioutil"
	"strconv"
	"strings"
	"os"
)

func (c *Client) rollback(word string) {

	var lth = strconv.Itoa(len(word))
	var db_en_dir = rootdir + "/en/english" + lth + ".csv"
	var db_cn_dir = rootdir + "/ch/chinese" + lth + ".csv"
	var prev_db_en_dir = rootdir + "/en/english" + lth + ".csv.prev"
	var prev_db_cn_dir = rootdir + "/ch/chinese" + lth + ".csv.prev"
	var tmpdb_en_dir = rootdir + "/en/english" + lth + ".csv.rollback.tmp"
	var tmpdb_cn_dir = rootdir + "/ch/chinese" + lth + ".csv.rollback.tmp"

	var IsWordInCurrentWords bool = false
	var IsWordInBackupWords bool = false
	// Index of the Indexed Word in Current Word Database
	var Index int
	// Index of the Definitions Line of the Indexed Word in the Current Definitions Database
	var IndexOfDefsLineInCurrentDefsDb int
	// Definitions Line of the Indexed Word in the Current Definitions Database
	var IndexedDefsLineInCurrentDefsDb string
	// Definitions Line of the Indexed Word in the Backup Definitions Database
	var IndexedDefsLineInBackupDefsDb string

	var Mode string

	var defsLines []string

	// Load words from current words database
	wordsData, err := ioutil.ReadFile(db_en_dir)
	if err != nil {
		panic(err)
	}
	words := strings.Split(string(wordsData), "\n")
	// Search the word in current words
	for index, elem := range words {
		temp := elem[:len(word)]
		if strings.EqualFold(temp, word) == true {
			// If the word is found in current words
			IsWordInCurrentWords = true
			// Record the word's Index
			Index = index
			IndexOfDefsLineInCurrentDefsDb = index
			// Load definitions from current definition database
			defsData, err := ioutil.ReadFile(db_cn_dir)
			if err != nil {
				panic(err)
			}
			defsLines = strings.Split(string(defsData), "\n")
			// Fetch the current definition of the word by its Index.
			// This place has vulnerabilities when we assume the Index of Definitions Line
			// is same to the Index of the word.
			IndexedDefsLineInCurrentDefsDb = defsLines[index]
			
			// Load words from backup words database.
			backupwordsData, err := ioutil.ReadFile(prev_db_en_dir)
			if err != nil {
				c.send <- []byte("rollback: backup not found for word \"" + word + "\". unable to restore.")
				return
			}
			backupwords := strings.Split(string(backupwordsData), "\n")
			// Search the word in backup words database.
			for index, elem := range backupwords {
				temp := elem[:len(word)]
				if strings.EqualFold(temp, word) == true {
					// If the word is found in backup words database,
					// then the word is Newly Updated Not Newly Added.
					IsWordInBackupWords = true
					// Record the word's Index

					// Load definitions from backup definition database.
					backupDefsData, err := ioutil.ReadFile(prev_db_cn_dir)
					if err != nil {
						panic(err)
					}
					backupDefsLines := strings.Split(string(backupDefsData), "\n")
					// Fetch the previous definitions of the word by its Index.
					// This place has vulnerabilities when we assume the Index of Definitions Line
					// is same to the Index of the word.
					// There are chances that word database backup's word amount be less than
					// definitions database backup's definitions amount since adding definitions
					// will cause both database to backup but updating definitions will cause only
					// definitions database backup therefore if we add definitions and then update
					// definitions, the word database's backup will not have the word we added but
					// the definitions database's backup will have the originally added definitions.
					var errorcode string = ""
					IndexedDefsLineInBackupDefsDb = func (lines []string, index int, prefix string) string {
						for _, line := range lines[index:] {
							if strings.HasPrefix(line, prefix) {
								return line
							} else if len(strings.TrimSpace(line)) < len(prefix) {
								errorcode = "too short"
								return line
							}
						}
						errorcode = "not found"
						return ""
					}(backupDefsLines, index, word + " ")

					if len(errorcode) > 0 {
						if errorcode == "not found" {
							c.send <- []byte("rollback: backup definitions not found for word \"" + word + "\"")
						} else if errorcode == "too short" {
							c.send <- []byte("rollback: invalid backup definitions \"" + IndexedDefsLineInBackupDefsDb + "\" cannot be restored for word \"" + word + "\".")
						}
						return
					}
					// Compare the current definition and the backup definiton.
					if IndexedDefsLineInCurrentDefsDb == IndexedDefsLineInBackupDefsDb {
						// If the current definition equals the backup definition,
						// then the current definition has not been updated.
						// Send message to client to inform him that the
						// definition has not been updated.
						c.send <- []byte("rollback: word " + word + " has no backup. unable to rollback.")
						// return.
						return
					} else {
						// Else the current definition differs the backup definition,
						// then the current definition of the word has been updated lately.
						// Send message to client to inform him the current word
						// definition and previous word definition.
						c.send <- []byte("rollback: restore definitions from \"" + IndexedDefsLineInCurrentDefsDb + "\" to \"" + IndexedDefsLineInBackupDefsDb + "\"")
						// Set Mode to "Undo Update Mode" which means to restore
						// the word's previous definitions.
						Mode = "Undo Update Mode"
						// Record the previous definitions of the Indexed word.
					}
				}
			}
			if IsWordInBackupWords == false {
				// If the word is not found in backup words database,
				// then the word is Newly Added.
				c.send <- []byte("rollback: delete the newly added word \"" + word + "\" and its definitions \"" + IndexedDefsLineInCurrentDefsDb + "\"")
				// Set Mode to "Undo Add Mode" which means to delete word and its
				// definitions.
				Mode = "Undo Add Mode"
			}
		}
	}
	if IsWordInCurrentWords == false {
		// Else the word is not found in current words database,
		// return with message "Word not found".
		c.send <- []byte("rollback: word " + word + " not found.")
		return
	}


	// Create temp words database.
	// The temp file must be deleted if the rollback procedure aborts.
	// If the temp file was not deleted then there will be unexpected
	// consequences.
	f, err := os.Create(tmpdb_en_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	// Loop all words in current words database.
	for index, elem := range words {
		temp := elem[:len(word)]
		if strings.EqualFold(temp, word) == true {
			// If the current word is the Indexed word.
			if Mode == "Undo Update Mode" {
				// If the Mode is "Undo Update Mode",
				// Then put it into the temp words database.
				_, err := f.WriteString(temp)// Should keep original data therefore put temp not word.
				if err != nil {
					panic(err)
				}
				// If the current word is not the last word,
				// put a newline symbol into the file.
				if index + 1 < len(words) {
					_, err := f.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
			} else {
				// Else the Mode is "Undo Add Mode",
				// "Undo Add" means to delete the Indexed word and its definitions.
				// Therefore will not put it into the temp words database.
			}
		} else {
			// If the current word is not the Indexed word.
			// Put it into the temp words database.
			_, err := f.WriteString(temp)
			if err != nil {
				panic(err)
			}
			// If the current word is not the last word,
			// put a newline symbol into the file.
			if index + 1 < len(words) {
				if Index + 1 == len(words) && Mode == "Undo Add Mode" && index + 1 == Index {
					// Should consider chances that the Indexed word was the last line and Mode
					// is "Undo Add Mode". Therefore the second last word will be the last line
					// and shall not have a newline symbol after it.
				} else {
					_, err := f.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
			}
		}
	}

	// Create temp definition database.
	// The temp file must be deleted if the rollback procedure aborts.
	// If the temp file was not deleted then there will be unexpected
	// consequences.
	f2, err := os.Create(tmpdb_cn_dir)
	if err != nil {
		panic(err)
	}
	defer f2.Close()
	// Loop all definitions in current definitions database.
	for index, line := range defsLines {
		defsLine := strings.TrimSpace(line)
		if index == IndexOfDefsLineInCurrentDefsDb && defsLine == strings.TrimSpace(IndexedDefsLineInCurrentDefsDb) {
			// If the current definition line is the Indexed definition line.
			if Mode == "Undo Update Mode" {
				// If the Mode is "Undo Update Mode"
				// Check the previous definitions of the Indexed word.
				if strings.HasPrefix(strings.ToLower(IndexedDefsLineInBackupDefsDb), strings.ToLower(word + " ")) {
					// Put the previous definitions of the Indexed word into
					// the temp definitions database.
					c.send <- []byte("rollback: stashing changes from \"" + IndexedDefsLineInCurrentDefsDb + "\" to \"" + IndexedDefsLineInBackupDefsDb + "\"")
					_, err := f2.WriteString(strings.TrimSpace(IndexedDefsLineInBackupDefsDb))
					if err != nil {
						panic(err)
					}
				} else {
					c.send <- []byte("rollback: rollback invalid from \"" + IndexedDefsLineInCurrentDefsDb + "\" to \"" + IndexedDefsLineInBackupDefsDb + "\"")
					_, err := f2.WriteString(strings.TrimSpace(IndexedDefsLineInCurrentDefsDb))
					if err != nil {
						panic(err)
					}
				}
				// If the current line is not the last line,
				// put a newline symbol into the file.
				if index + 1 < len(defsLines) {
					_, err := f2.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
			} else {
				// Else the Mode is "Undo Add Mode",
				// "Undo Add" means to delete the Indexed word and its definitions.
				// Therefore will put nothing into the temp definitions database.
			}
		} else {
			// If the current definition line is not the Indexed definition line.
			// Put the current definition line into the temp definitions database.
			_, err := f2.WriteString(strings.TrimSpace(defsLine))
			if err != nil {
				panic(err)
			}
			// If the current line is not the last line,
			// put a newline symbol into the file.
			if index + 1 < len(defsLines) {
				if IndexOfDefsLineInCurrentDefsDb + 1 == len(defsLines) && Mode == "Undo Add Mode" && index + 1 == IndexOfDefsLineInCurrentDefsDb {
					// Should consider chances that the Indexed word's definitions was the last line and Mode
					// is "Undo Add Mode". Therefore the second last definitions line will be the last line
					// and shall not have a newline symbol after it.
				} else {
					_, err := f2.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
			}
		}
	}
	c.send <- []byte("rollback: rollback is ready. you need to confirm the rollback.")
}