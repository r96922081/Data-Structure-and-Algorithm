package util

import (
	"encoding/binary"
	"errors"
	"os"
	"strconv"
)

type FileSerializer struct {
	FilePath_   string
	FileHandle_ *os.File
}

func NewFileSerializer(filePath string) *FileSerializer {
	return &FileSerializer{filePath, nil}
}

func (file *FileSerializer) FileExist() bool {
	_, err := os.Stat(file.FilePath_)
	if err == nil {
		return true
	}

	return false
}

func (file *FileSerializer) CreateFileIfNotExist() error {
	if file.FileExist() {
		return nil
	}

	f, err := os.Create(file.FilePath_)
	f.Close()

	return err
}

func (file *FileSerializer) DeleteFileIfExist() error {
	if !file.FileExist() {
		return nil
	}

	err := os.RemoveAll(file.FilePath_)
	return err
}

func (file *FileSerializer) CreateDirIfNotExist() error {
	if file.FileExist() {
		return nil
	}

	err := os.MkdirAll(file.FilePath_, os.ModeDir)
	return err
}

func (file *FileSerializer) OpenForAppend() error {
	h, err := os.OpenFile(file.FilePath_, os.O_CREATE|os.O_WRONLY, 0644)
	h.Seek(0, os.SEEK_END)
	file.FileHandle_ = h
	return err
}

func (file *FileSerializer) OpenForWriteTruncate() error {
	h, err := os.OpenFile(file.FilePath_, os.O_TRUNC|os.O_CREATE|os.O_WRONLY, 0644)
	file.FileHandle_ = h
	return err
}

func (file *FileSerializer) OpenForRead() error {
	h, e := os.Open(file.FilePath_)
	file.FileHandle_ = h
	return e
}

func (file *FileSerializer) GetOffset() int {
	offset, _ := file.FileHandle_.Seek(0, os.SEEK_CUR)
	return int(offset)
}

func (file *FileSerializer) Seek(offset int) error {
	_, err := file.FileHandle_.Seek(int64(offset), os.SEEK_SET)
	return err
}

func (file *FileSerializer) Close() error {
	err := file.FileHandle_.Close()
	return err
}

func (file *FileSerializer) WriteInt(i int) error {
	bs := make([]byte, 4)
	binary.LittleEndian.PutUint32(bs, uint32(i))
	n, err := file.FileHandle_.Write(bs)
	if err != nil {
		return err
	}

	if n != 4 {
		return errors.New("Write only " + strconv.Itoa(n) + " bytes")
	}

	return nil
}

func (file *FileSerializer) WriteString(s string) error {
	err := file.WriteInt(len(s))
	if err != nil {
		return err
	}

	n, err := file.FileHandle_.WriteString(s)
	if err != nil {
		return err
	}

	if n != len(s) {
		return errors.New("Write only " + strconv.Itoa(n) + " bytes")
	}

	return nil
}

func (file *FileSerializer) ReadInt() (int, error) {
	bytes := make([]byte, 4)
	_, err := file.FileHandle_.Read(bytes)
	ret := int(binary.LittleEndian.Uint32(bytes))
	return ret, err
}

func (file *FileSerializer) ReadString() (string, error) {
	sLen, err := file.ReadInt()
	if err != nil {
		return "", err
	}

	nBytes := make([]byte, sLen)
	_, err = file.FileHandle_.Read(nBytes)
	return string(nBytes), err
}

func (file *FileSerializer) GetFileSize() (int, error) {
	f, _ := os.OpenFile(file.FilePath_, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	stat, err := f.Stat()
	if err != nil {
		return -1, err
	}

	return int(stat.Size()), nil
}
