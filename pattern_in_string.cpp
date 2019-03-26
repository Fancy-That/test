#include <stdio.h>
#include <vector>
#include <string>

struct Pattern {
	std::string pattern;
	int count;
};

int main(int argc, char** argv) {

	FILE* file = fopen("data", "rb");
	if (!file)
		return -1;
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	length -= ftell(file);
	char* buf = new char[length];
	fread(buf, 1, length, file);
	fclose(file);

	std::string s(buf);
	delete[] buf;


	int patternLength = 4;
	int patternCount = 1000;

	std::vector<Pattern> d;


	//printf("%d\n", (patternLength = 0));

	for (int i = patternLength; i < length/patternCount; i++) {
		for (int j = 0; j < length - i; j++) {
			std::string sub = s.substr(j, i);
			int num = 0;
			int found = -1;
			while((found = s.find(sub, found+1)) != -1)
				num++;
			if (num < patternCount)
				continue;
			bool inlist = false;
			for (int i = d.size(); i--;)
				if (inlist=d[i].pattern==sub)
					break;
			if (!inlist)
				d.push_back(Pattern{sub, num});
		}
	}

	for (int i = d.size(); i--;)
		printf("{%s, %d},", d[i].pattern.c_str(), d[i].count);
	printf("\n");

	return 0;
};
