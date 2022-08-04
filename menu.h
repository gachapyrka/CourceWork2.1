#pragma once
#include "master.h"
#include "client.h"
#include "record.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
namespace filemanager
{

#define ADMIN_FILE  "admin.txt"
#define CLIENT_FILE "client.txt"
#define MASTER_FILE "master.txt"
#define RECORD_FILE "record.txt"

	template <class T>
	class FileManager
	{
	public:

		FileManager();
		FileManager(const std::string filename);
		FileManager(const FileManager<T>&);
		FileManager(T*);

	public:

		string GetFilename()const;
		void SetFilename(const string&);

		int Load(T*&)const;
		void Save( T* &, const int)const;

	private:

		std::string filename;
	};

	template <class T>
	FileManager<T>::FileManager() {}
	template <class T>
	FileManager<T>::FileManager(T* a) {}

	template <class T>
	FileManager<T>::FileManager(const std::string filename)
	{
		this->filename = filename;
	}

	template <class T>
	FileManager<T>::FileManager(const FileManager<T>& o)
	{
		filename = o.filename;
	}

	template <class T>
	std::string FileManager<T>::GetFilename()const
	{
		return filename;
	}

	template <class T>
	void FileManager<T>::SetFilename(const string& f)
	{
		filename = f;
	}

	template <class T>
	int FileManager<T>::Load(T*& arr)const
	{
		if (arr) delete[] arr;

		ifstream in(filename, ios_base::in);

		int n = 0;
		in >> n;

		arr = new T[n + 2];
		for (int i = 0; i < n; i++)
		{
			in >> arr[i];
		}

		in.close();
		Save(arr, n);
		return n;
	}

	template <class T>
	void FileManager<T>::Save( T* & arr, int n)const
	{
		ofstream out(filename, ios_base::trunc);
		out << n << endl;
		for (int i = 0; i < n; i++)
		{
			out << arr[i] << endl;
		}
		out.close();
	}

}
	


	
