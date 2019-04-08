#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

/**
* Èë¿â
*/
int insertDB(vector<string> elements) {
	int i;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string preSQL = "insert into tb_info values(";
	//µü´úÆ÷±éÀú
	for (i = 0; i < (elements.size() - 1); i++) {
		preSQL = preSQL.append("\"");
		preSQL = preSQL.append(elements[i]);
		preSQL = preSQL.append("\",");
	}
	preSQL = preSQL.append("\"");
	preSQL = preSQL.append(elements[i]);
	preSQL = preSQL.append("\");");

	rc = sqlite3_open("sniper.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return -1;
	}else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, preSQL.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}