#include "FileHelper.h"

// Load a texture into opengl 
int loadPNG(std::string file){
	// Generate opengl textures
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);

	// Load texture with soil 
	int width, height;
	unsigned char* image =
		SOIL_load_image(file.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	
	// Set the active texture unit to texture unit 0.
	// Other units are used for different things. 0 is default, so 
	// we use that for general actions. 
	glActiveTexture(GL_TEXTURE0);
	// Bind to the texture in OpenGL
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	// Load texture into bound texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
              GL_UNSIGNED_BYTE, image);
	             
	// Set filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Free image data
	SOIL_free_image_data(image);

	// Unload texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureHandle;
}

// Load a obj file into an Object3D
// Basic OBJ loader
// Not all features are supported 
void loadOBJ(std::string file, Object3D* obj){
	// Open file to read from 
	std::string line;
	std::ifstream infile;
	infile.open(file);

	// Imported data
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> cords;
	vector<GLushort> indicies;

	// Read OBJ file 
	while (!infile.eof())
	{
		// Get next line of file 
		std::getline(infile, line); 
		if (line.length() != 0){
			// Cut up data 
			istringstream iss(line);
			vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};

			// Parse type 
			// Check for vertex data 
			if (tokens[0] == "v" && tokens.size() >= 4){
				verts.push_back(toDouble(tokens[1]));
				verts.push_back(toDouble(tokens[2]));
				verts.push_back(toDouble(tokens[3]));

				// TODO check for w 
			}
			else if (tokens[0] == "vp")
				cout << "OBJ: vp not currently supported\n";
			else if (tokens[0] == "f"){
				// Type 1
				// Just vertex information 
				// Ex: f 1 2 3 ... (can be 3 or more) 

				// Type 2
				// Vertex and texture
				// Ex: f 1/1 2/2 3/3 .... (can be 3 or more)

				// Type 3 
				// Vertex/texture/normal
				// Ex: f 1/2/3 2/3/4 4/5/6 ... (can be 3 or more) 

				// Type 4
				// Vertex//Normal
				// Ex: f 1//2 2//3 3//4 ... (can be 3 or more)

				// Check each token for type 
				for (int i = 1; i < tokens.size(); i++){
					// Check type
					if (tokens[i].find("//") != string::npos)
					{
						// Type 4
						cout << "Type4\n";

						//  TODO 
					}
					else if (tokens[i].find('/') != string::npos){
						// Type 2 or 3
						vector<string> tokens2;
						split(tokens[i], '/', tokens2);

						// Add indice 
						indicies.push_back(toInt(tokens2[0]));

						// TODO parse tokens2[1] and tokens2[2]
					}
					else {
						// Type 1 
						indicies.push_back(toInt(tokens[i]));
					}
				}
			}
			else if (tokens[0] == "vn" && tokens.size() == 4){
				// Vertex Normals 
				// Ex: vn 1 2 3
				norms.push_back(toDouble(tokens[1]));
				norms.push_back(toDouble(tokens[2]));
				norms.push_back(toDouble(tokens[3]));
			}
			else if (tokens[0] == "vt" && tokens.size() >= 3){
				// Texture coords 
				cords.push_back(toDouble(tokens[1]));
				cords.push_back(toDouble(tokens[2]));

				// TODO possible w 
			}
			else if (tokens[0] == "mtllib" || tokens[0] == "usemtl")
				cout << "OBJ: Materials not currently supported\n";
			else if (tokens[0] == "o")
				cout << "OBJ: Object name not currently supported\n";
			else if (tokens[0] == "g")
				cout << "OBJ: groups not currently supported\n";
			else if (tokens[0] == "s")
				cout << "OBJ: Smooth shading not currently supported\n";
			else if (line.at(0) != '#')
				std::cout << "OBJ Formal Error: " << line << "\n";
		}
	}

	// Close file 
	infile.close();

	//  TODO create Object3D from obj 

	
}

// Convert string to double
double toDouble(std::string s){
	double numb;
	std::istringstream(s) >> numb;
	return numb;
}

// Convert string to int
int toInt(std::string s){
	int numb;
	std::istringstream(s) >> numb;
	return numb;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}