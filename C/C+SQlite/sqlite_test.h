#pragma once

void CreateDB(char* db_name, sqlite3* db);

void InsertDB(char* db_name, sqlite3* db);

void SelectDB(char* db_name, sqlite3* db);

void UpdateDB(char* db_name, sqlite3* db);

void DeleteDB(char* db_name, sqlite3* db);
