#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <iostream>
using namespace std;
using namespace rapidjson;
int main() {
    FILE *fp = fopen("books.json", "r");
    if (!fp) {
        cerr << "Error : Could not open file" << endl;
        return 1;
    }
    char readBuffer[65536];
    FileReadStream readStream(fp, readBuffer, sizeof(readBuffer));

    Document booksDocument;
    booksDocument.ParseStream(readStream);
    if (booksDocument.HasParseError()) {
        cerr << "Error : Failed to parse JSON" << endl;
        fclose(fp);
        return 1;
    }

    if (booksDocument.IsArray()) {
        for (int i = 0; i < booksDocument.Size(); i++) {
            Value &v = booksDocument[i];
            if (v.HasMember("title") && v["title"].IsString()) {
                cout << v["title"].GetString() << endl;
            }
        }
    }
    fclose(fp);
    return 0;
}
