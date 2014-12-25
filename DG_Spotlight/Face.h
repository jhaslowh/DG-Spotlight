#pragma once
#include <vector>
using namespace std;
class Face
{
public:
	vector<int> vertex_indexes;
	vector<int> normal_indexes;
	vector<int> texture_indexes;

	Face();
	~Face();
};

